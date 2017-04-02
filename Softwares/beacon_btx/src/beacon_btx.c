/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_btx.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-01-13
 * -----------------------------------------------------------------------------
 * Description
 *   This is the Laser Beacon V3 [BTX] board main module. This board handles:
 *     - VCR Drum motor speed regulation
 *     - Rotary Transformer power managment for [TUD] board
 *     - CC2500 RF Interface with [BRX] boards
 *     - Opponent position computation
 *     - Main robot absolute position computation
 *     - CAN Interface with the rest of the robot (positions broadcast)
 *     - USB Interface for debug purposes
 * -----------------------------------------------------------------------------
 * Hardware ressources usage
 *   - TIM2,OC1,OC2              for Transformer Power-Modulation
 *   - TIM3,OC3,TIM4,VREF,CMCON1 for Drum Motor Speed-Control
 *   - TIM5                      for Scheduler and LED
 *   - SPI1                      for RF Interface
 *   - ECAN1                     for CAN Interface
 *   - UART1                     for [TUD] Interface
 *   - UART2                     for Debug Interface
 *   Note: TIM4/TIM5 are 16bit standalone timers (not associated)
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 902                                                                  $
 * $LastChangedBy:: sebastien.brulais                                          $
 * $LastChangedDate:: 2013-04-20 19:10:46 +0200 (sam., 20 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

// -----------------------------------------------------------------------------
// CONFIGURATION
// -----------------------------------------------------------------------------
/*
// Oscillator startup configuration, on internal fast RC
_FOSCSEL(FNOSC_FRC);

// Configure POSC in HS mode and enable clock switching.
// Also enable multiple remapping.
_FOSC(POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSECME);

// Watchdog is enabled/disabled by software control
// When used, the WDT period is 256ms (8192 / 32kHz)
_FWDT(FWDTEN_OFF & WDTPOST_PS8192);
 */ //old configuration method to be removed here for historical reason JST

// DSPIC33FJ128MC804 Configuration Bit Settings

// 'C' source line config statements

// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are enabled)

// FWDT
#pragma config WDTPOST = PS8192         // Watchdog Timer Postscaler (1:8,192)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>


// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// Scheduler tick count
extern uint16_t tick_cnt;

// Current drum and control speeds in rp/s
extern uint8_t drum_running;
extern float current_speed_rps;
extern float drum_control_rps;

// CAN control defined in another module
extern uint8_t can_match_state;
#warning "can_match_state updated no where"
extern uint8_t can_turret_cmd;

// CAN state defined in another module
extern uint8_t can_state;

// Software IRQ
uint8_t sw_irq;

// Beacons infos
extern beacon_info_t beacon_infos[BEACON_COM_NB_SLAVE];

// CAN Message for debug
#define DEBUG_CAN_MSG_MAX 128
char can_msg[DEBUG_CAN_MSG_MAX];

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

// Setup an UART, with the decicated baudrate

inline void uart_debug_setup(void) {
    setbuf(stdout, NULL); //no buffered output
            
    DEBUG_UART_RX_TRIS = 1; // DEBUG UART RX as input
    DEBUG_UART_TX_TRIS = 0; // DEBUG UART TX as output
    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // No parity, 8 data bit
    U1MODEbits.ABAUD = 0; // Auto-baud disabled
    U1MODEbits.BRGH = 0; // Low-speed mode
    U1BRG = DEBUG_UART_BRG; // Baud-rate config

    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable TX on UART

    // Configure UART1 RX ISR
    //IFS0bits.U1RXIF = 0; // Clear interrupt
    //IPC2bits.U1RXIP = 1; // Set priority to 1 (low)
    //IEC0bits.U1RXIE = 1; // Enable interrupt
#warning "TODO debug why Rx ISR fires always, code shall work with and without TTL232R"

}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(void) {

    uint8_t err_code;

    // Oscillator needs to be started first
    osc_init();
    wdt_stop(); //to simplify debug (this is normal case after POR)

    // All I/Os are digital by default
    //ADPCFG = 0xFFFF; => links same register as AD1PCFGL => to be removed
    AD1PCFGL = 0xFFFF;

    // Modules initializations
    led_init();
    uart_debug_setup();

    err_code = beacon_com_init();
    #warning "there is infinithe while inside (not covered by WDT)"

    drum_control_init();
    
    power_modulation_init();

    // Initiate the beacon startup procedure, which will sync
    // all slaves and setup the communication.
    beacon_com_startup();

    scheduler_init();

    // This calls the PPS_LOCK macro so it's better to be done at last!
    beacon_can_init();

    // Initialize default CAN state
    can_state = CAN_NODE_STATE_BEACON_BTX_IDLE ;

    if (wdt_occured()) {
        printf("Error: reset because of watch-dog!\r\n"/*, err_code*/);
        led_set_red(LED_BLINK_S2);
        can_state = CAN_NODE_STATE_ERROR;
    }

    if (err_code) {
        printf("Error with initialization: code %d\r\n", err_code);
        led_set_red(LED_BLINK_S2);
        can_state = CAN_NODE_STATE_ERROR;
    }

    //can_printf("Hello from BTX!\n");

    
    // Enable watchdog timer during main loop
    wdt_clear();
    wdt_run();

    // Start the scheduler, ready to start
    scheduler_start();
    printf("Ready to receive...\r\n");
    led_set_green(LED_BLINK_S1); //LED_PULSE_S1

    //added JST for debug
    can_match_state = CAN_SYSTEM_MATCH_STATE_SETUP;

    // Main loop
    while (1) {
        uint8_t cnt;
        // Wait for a scheduler event
        if (scheduler_ready()) {
            //printf("schedule %i\r\n", cnt++);
            // Clear watchdog timer on every scheduler tick
            wdt_clear();

            // New commands
            // ------------

            // New commands mostly depends on CAN commands inputs
            switch (can_match_state) {

                case CAN_SYSTEM_MATCH_STATE_SETUP:

                    // Start the drum motor procedure during setup
                    // Only if not already running and only if allowed to
                    //printf("CAN_SYSTEM_MATCH_STATE_SETUP\r\n");
                    if (!drum_running && can_turret_cmd) {
                        drum_motor_start();
                        can_state = CAN_NODE_STATE_READY;
                        printf("motor started \r\n");
                        can_match_state = CAN_SYSTEM_MATCH_STATE_READY; //add JST
                    }

                    break;

                case CAN_SYSTEM_MATCH_STATE_READY:
                case CAN_SYSTEM_MATCH_STATE_RUN:
                    //printf("CAN_SYSTEM_MATCH_STATE_RUN\r\n");
                    // Send CAN data only in ready and run at the specified rate
                    if (scheduler_task_ready(SCHEDULER_RATE_SEND_CAN_DATA)) {
                        //beacon_can_send_opponent_1();
#warning "commented for debug no can"
                        led_set_green(LED_BLINK_S2);
                        can_state = CAN_NODE_STATE_BEACON_BTX_RUN;

                        uint8_t cnt;
                        for(cnt=0; cnt<BEACON_COM_NB_SLAVE; cnt++)
                        {
                                printf("[%d] Dist = %4u Angle = %4d Tim. = %4u\n",
                                    beacon_infos[cnt].id ,
                                    beacon_infos[cnt].distance,
                                    beacon_infos[cnt].angle,
                                    beacon_infos[cnt].timestamp);
                        }       
                                printf("Speed %2.2f Control = %2.2f\n",
                                    current_speed_rps,
                                    drum_control_rps);
                    }

                    break;

                    // Other cases (IDLE, EMERGENCY, etc.)
                default:
                    printf("CAN_DEFAULT\r\n");
                    break;

            } // switch can_match_state

            // Control the turret if running
            if (drum_running) {
                if (!can_turret_cmd) {
                    drum_motor_stop();
                    can_state = CAN_NODE_STATE_BEACON_BTX_IDLE;
                    printf("motor stop\r\n");
                } else if (scheduler_task_ready(SCHEDULER_RATE_DRUM_CONTROL)) {
                    drum_control_thread();
                    //printf("drum ctrl\r\n");
                }
            }

            // Always send the general status
            if (scheduler_task_ready(SCHEDULER_RATE_SEND_CAN_STATUS)) {
                //beacon_can_send_status();
                //can_printf("Yo! Message from BTX!\r\nMatch State = %u\r\nThe local time is %u\r\n", can_match_state, tick_cnt);
#warning "commented out for debug without CAN"
            }

            // Call LED thread all the time
            led_thread();

        } // scheduler
    } // while(1)
} // main


