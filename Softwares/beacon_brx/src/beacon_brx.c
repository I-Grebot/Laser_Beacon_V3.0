/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_brx.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-10
 * -----------------------------------------------------------------------------
 * Description
 *   This is the Laser Beacon V3 [BRX] board main module. This board handles:
 *     - Time-stamping of incoming laser pulses (measure time-delta)
 *     - Converts this value into mm unit
 *     - Arbitrate different detections between the 4 possible PDD board
 *     - Determines a very-rough orientation (N, NE, E, SE, S, SW, W, NW)
 *       (useful only with opponent beacons)
 *     - Send all this stuff quickly using the beacon_com (RF)
 * -----------------------------------------------------------------------------
 * Hardware ressources usage
 *   - TIM2/TIM3 for      PDD Timings
 *   - IC1  associated to N_B-A
 *   - IC2  associated to E_B-A
 *   - IC7  associated to S_B-A
 *   - IC8  associated to W_B-A
 *   - SPI1 for           RF Interface
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 899                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-04-14 18:48:22 +0200 (dim., 14 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-03-10
 * -----------------------------------------------------------------------------
 */

#include "beacon_brx.h"

// -----------------------------------------------------------------------------
// CONFIGURATION
// -----------------------------------------------------------------------------

// Oscillator startup configuration, on internal fast RC
//_FOSCSEL(FNOSC_FRC);

// Configure POSC in HS mode and enable clock switching.
// Also enable multiple remapping.
//_FOSC(POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSECME);

// Watchdog is disabled
//_FWDT(FWDTEN_OFF);

#warning "old config to remlove JST" 

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
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
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

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// Software IRQ
uint8_t sw_irq;

// Board ID defined by the beacon_system
extern uint8_t board_id;

// Setup an UART, with the decicated baudrate
inline void uart_debug_setup(void)
{
    DEBUG_UART_RX_TRIS = 1 ; // DEBUG UART RX as input
    DEBUG_UART_TX_TRIS = 0 ; // DEBUG UART TX as output
    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // No parity, 8 data bit
    U1MODEbits.ABAUD = 0; // Auto-baud disabled
    U1MODEbits.BRGH  = 0; // Low-speed mode
    U1BRG = DEBUG_UART_BRG;    // Baud-rate config

    U1MODEbits.UARTEN = 1;// Enable UART
    U1STAbits.UTXEN = 1;  // Enable TX on UART

    // Configure UART1 RX ISR
    IFS0bits.U1RXIF = 0 ; // Clear interrupt
    IPC2bits.U1RXIP = 1 ; // Set priority to 1 (low)
    IEC0bits.U1RXIE = 0 ; // Enable interrupt

    // Clear Screen
    printf("\f");

}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(void) {

  uint8_t err_code;
  uint32_t cnt;
  uint16_t fake_dist_mm;

  // Oscillator needs to be started first
  osc_init();

  // All I/Os are digital by default
  ADPCFG   = 0xFFFF;
  AD1PCFGL = 0xFFFF;

  // TEMP uart for debug
  uart_debug_setup();

  // Modules initializations
  led_init();  
  photo_detect_init();
  err_code = beacon_com_init();

  if(err_code)
    printf("An error occured during initializations!, err_code = %d\n", err_code);
  
  printf("Hello from BRX! Your board id is %d\n", board_id);

  beacon_com_startup();
  photo_detect_run();

  // Main loop... !
  fake_dist_mm = 0;
  while(1) {
    for(cnt=1000000;cnt;cnt--);
    if(DIL_1) {
      LED_2 = ~LED_2;

      beacon_com_send_dist(fake_dist_mm++);
      printf("%i\n", fake_dist_mm);
      
    }

  }

} // main
