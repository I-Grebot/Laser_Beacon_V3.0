/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : board_cfg.h
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-01-13
 * -----------------------------------------------------------------------------
 * Description
 *   See main module header file for a full description
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 899                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-04-14 18:48:22 +0200 (dim., 14 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#ifndef _BOARD_H_
#define _BOARD_H_

// Hardware main include
#include <p33Fxxxx.h>

// Compiler related types
typedef unsigned char uint8_t ;
typedef signed   char sint8_t ;
typedef unsigned int  uint16_t;
typedef signed   int  sint16_t;
typedef unsigned long uint32_t;
typedef signed   long sint32_t;

// -----------------------------------------------------------------------------
// FREQUENCIES
// -----------------------------------------------------------------------------

// Primary Oscillator frequency
#define FIN 8000000

// FOSC = (FIN/N1) * M / N2
// N1 = 4, M = 32, N2 = 2
#define PLL_RATIO (32/(4*2))

// Add-up all frequency tunnings
#define FOSC 64000000 // (FIN*PLL_RATIO)
#define FCY  32000000 // (FOSC/2)

#define NCY_FOR_ONE_MS 50000 // rough estimate for 1ms active delay

// -----------------------------------------------------------------------------
// PPS IO MACROS
// -----------------------------------------------------------------------------

#define UNLOCK_PPS {__builtin_write_OSCCONL(OSCCON & 0xBF); \
                    while(OSCCONbits.IOLOCK);  }
#define LOCK_PPS   {__builtin_write_OSCCONL(OSCCON | 0x40); \
                    while(!OSCCONbits.IOLOCK); }

// -----------------------------------------------------------------------------
// HARDWARE
// -----------------------------------------------------------------------------

// Drum Motor speed regulation
// ---------------------------

// PWM Control output mapped on RB3/RP3
#define DRUM_MOTOR_TRIS     (TRISBbits.TRISB3)
#define DRUM_MOTOR_RPN      (RPOR1bits.RP3R)

// TOP Feedback input mapped on RB2/RP2/C1IN-
#define DRUM_TOP_TRIS       (TRISBbits.TRISB2)
#define DRUM_TOP            (CMCONbits.C1OUT)

// TUD Power modulation
// --------------------

// PWM_N output mapped on RC0/RP16
#define MOD_OUT_PWM_N_TRIS  (TRISCbits.TRISC0)
#define MOD_OUT_PWM_N_RPN   (RPOR8bits.RP16R)

// PWM_P output mapped on RC1/RP17
#define MOD_OUT_PWM_P_TRIS  (TRISCbits.TRISC1)
#define MOD_OUT_PWM_P_RPN   (RPOR8bits.RP17R)

// TX output mapped on RC2/RP18
#define MOD_OUT_TX_TRIS     (TRISCbits.TRISC2)
#define MOD_OUT_TX_RPN      (RPOR9bits.RP18R)
#define MOD_OUT_TX          (LATCbits.LATC2)

// RF Interface
// ------------

// RF_CSN output mapped on RB13/RP13
#define RF_CSN_TRIS   (TRISBbits.TRISB13)
#define RF_CSN (PORTBbits.RB13)

// RF_SCLK output mapped on RB11/RP11
#define RF_SCK_TRIS   (TRISBbits.TRISB11)
#define RF_SCK_RPN    (RPOR5bits.RP11R)

// RF_MOSI output mapped on RB10/RP10
#define RF_MOSI_TRIS  (TRISBbits.TRISB10)
#define RF_MOSI_RPN   (RPOR5bits.RP10R)

// RF_MISO input mapped on RB12/RP12
#define RF_MISO_TRIS  (TRISBbits.TRISB12)
#define RF_MISO_PIN   12

// CAN Interface
// -------------

// CAN_RX input mapped on RB6/RP6
#define CAN_RX_TRIS  (TRISBbits.TRISB6)
#define CAN_RX_PIN   6

// CAN_TX mapped on RB5/RP5
#define CAN_TX_TRIS  (TRISBbits.TRISB5)
#define CAN_TX_RPN   (RPOR2bits.RP5R)

// UART Interface
// --------------

// UART_TX output mapped on RC4/RP20
#define UART_TX_TRIS  (TRISCbits.TRISC4)
#define UART_TX_RPN   (RPOR10bits.RP20R)

// UART_RX input mapped on RC3/RP19
#define UART_RX_TRIS  (TRISCbits.TRISC3)
#define UART_RX_PIN   19

// LEDs
// ----

// LED_1 output mapped on RA7
#define LED_1_TRIS (TRISAbits.TRISA7)
#define LED_1      (PORTAbits.RA7)

// LED_2 output mapped on RA10
#define LED_2_TRIS (TRISAbits.TRISA10)
#define LED_2      (PORTAbits.RA10)

// Spare I/Os
// ----------

// SPARE_1 mapped on RB8/RP8
#define SPARE_1_TRIS (TRISBbits.TRISB8)
#define SPARE_1_RPN  (RPOR4bits.RP8R)
#define SPARE_1_PIN  8
#define SPARE_1      (LATBbits.LATB8)

// SPARE_2 mapped on RB9/RP9
#define SPARE_2_TRIS (TRISBbits.TRISB9)
#define SPARE_2_RPN  (RPOR4bits.RP9R)
#define SPARE_2_PIN  9
#define SPARE_2      (LATBbits.LATB9)

// SPARE_3 mapped on RC6/RP22
#define SPARE_3_TRIS (TRISCbits.TRISC6)
#define SPARE_3_RPN  (RPOR11bits.RP22R)
#define SPARE_3_PIN  22
#define SPARE_3      (LATCbits.LATC6)

// SPARE_4 mapped on RC7/RP23
#define SPARE_4_TRIS (TRISCbits.TRISC7)
#define SPARE_4_RPN  (RPOR11bits.RP23R)
#define SPARE_4_PIN  23
#define SPARE_4      (LATCbits.LATC7)

// SPARE_5 mapped on RC8/RP24
#define SPARE_5_TRIS (TRISCbits.TRISC8)
#define SPARE_5_RPN  (RPOR12bits.RP24R)
#define SPARE_5_PIN  24
#define SPARE_5      (LATCbits.LATC8)

// SPARE_6 mapped on RC9/RP25
#define SPARE_6_TRIS (TRISCbits.TRISC9)
#define SPARE_6_RPN  (RPOR12bits.RP25R)
#define SPARE_6_PIN  25
#define SPARE_6      (LATCbits.LATC9)

// -----------------------------------------------------------------------------
// DRUM MOTOR CONFIGURATION
// -----------------------------------------------------------------------------

// Define period slow-frequency period for output (in FCY/64 n.o. cycles)
#define DRUM_MOTOR_PERIOD  5120
#define DRUM_MOTOR_DUTY    4000 // Init value

// Define drum-motor PWM limits
// This is used to ensure correct motor behaviour
// (some values might damage it)
#define DRUM_MOTOR_PWM_MIN  250
#define DRUM_MOTOR_PWM_MAX 4900

// Minimum and maximum allowed speeds for controller
#define DRUM_CONTROL_RPS_MAX 80.0
#define DRUM_CONTROL_RPS_MIN  0.0

// RPS to PWM Conversion
#define DRUM_MOTOR_RPS_TO_PWM_OFFSET 22
#define DRUM_MOTOR_RPS_TO_PWM_FACTOR 49
#define DRUM_MOTOR_RPS_TO_DUTY(_rps) \
        (DRUM_MOTOR_PERIOD*((_rps)-DRUM_MOTOR_RPS_TO_PWM_OFFSET)\
         /DRUM_MOTOR_RPS_TO_PWM_FACTOR)

// PWM Output generated by OC3
#define DRUM_MOTOR_OCRS OC3RS
#define DRUM_MOTOR_PIN 0b10100

// -----------------------------------------------------------------------------
// TOP ROTATION CONFIGURATION
// -----------------------------------------------------------------------------

// FCY Prescaler:
// 0b00 -> 1:1
// 0b01 -> 1:8
// 0b10 -> 1:64
// 0b11 -> 1:256
#define DRUM_TOP_TCKPS   0b11
#define DRUM_TOP_DIVIDER 256

// Ratio which gives the n.o. clock
// Cycles for 1 RPS (1Hz)
// (FCY/DRUM_TOP_DIVIDER)
#define NCY_TO_RPS_FACTOR 125000

// DRUM TOP uses TIMER4
#define DRUM_TOP_TIMER TMR4

// DRUM TOP angle offset compensation, in 10th of degree unit
// Includes [BRX] + processing + RF latency and physical TOP sensor offset
#define DRUM_TOP_ANGLE_OFFSET 0

// Select reference voltage = (3.3V/4) + (CVR/32)*3.3V
// 1 CVR step = 103mV
#define DRUM_TOP_CVR 12 // ~ 2.06V

// Threshold used to filter undesired spkies on comparator IRQ
#define DRUM_TOP_GLITCH_THRS 1000

// -----------------------------------------------------------------------------
// POWER MODULATION CONFIGURATION
// -----------------------------------------------------------------------------

// Define period for modulation output
// and pulse length (duty-cycle value)
#define MOD_OUT_PWM_PERIOD    512
#define MOD_OUT_PWM_DUTY        8   // max 50% duty-cycle !
#define MOD_OUT_PWM_MARGIN     0

// Modulation outputs use OC1/OC2
#define MOD_OUT_PWM_N_PIN 0b10010
#define MOD_OUT_PWM_P_PIN 0b10011

// -----------------------------------------------------------------------------
// CAN LIBRARY SETUP
// -----------------------------------------------------------------------------

// CAN uses ECAN1
#define ECAN1_RX_TRIS  CAN_RX_TRIS
#define ECAN1_RX_PIN   CAN_RX_PIN
#define ECAN1_TX_TRIS  CAN_TX_TRIS
#define ECAN1_TX_RPN   CAN_TX_RPN

// Node ID is BTX
#define CAN_NODE_ID CAN_NODE_ID_BEACON_BTX

// -----------------------------------------------------------------------------
// CC2500 LIBRARY SETUP
// -----------------------------------------------------------------------------

// CC2500 uses SPI1
#undef CC2500_USE_SPI2

// Define I/Os tristate registers
#define CC2500_SS_TRIS  RF_CSN_TRIS
#define CC2500_SCK_TRIS RF_SCK_TRIS
#define CC2500_SDO_TRIS RF_MOSI_TRIS
#define CC2500_SDI_TRIS RF_MISO_TRIS

// Define I/Os remappable registers & values
#define CC2500_SCK_RPN RF_SCK_RPN
#define CC2500_SDO_RPN RF_MOSI_RPN
#define CC2500_SDI_PIN RF_MISO_PIN

// Define I/Os ports
#define CC2500_SS  RF_CSN

// -----------------------------------------------------------------------------
// BEACON SYSTEM LIBRARY SETUP
// -----------------------------------------------------------------------------

// Indicate that the board is master
//#undef BEACON_COM_IS_MASTER
#define BEACON_COM_IS_MASTER

// -----------------------------------------------------------------------------
// LED SETUP
// -----------------------------------------------------------------------------

#define LED_GREEN_TRIS LED_1_TRIS
#define LED_RED_TRIS   LED_2_TRIS

#define LED_GREEN LED_1
#define LED_RED   LED_2

// -----------------------------------------------------------------------------
// DEBUG SETUP
// -----------------------------------------------------------------------------

#define DEBUG_UART_RX_TRIS UART_RX_TRIS
#define DEBUG_UART_RX_PIN  UART_RX_PIN
#define DEBUG_UART_TX_TRIS UART_TX_TRIS
#define DEBUG_UART_TX_RPN  UART_TX_RPN

// Using UART1
#define DEBUG_UART_TX_PIN 0b00011
#define DEBUG_UART_RX_RPN (RPINR18bits.U1RXR)

// -----------------------------------------------------------------------------
// SCHEDULER LIB SETUP
// -----------------------------------------------------------------------------

// Scheduler period in ms
#define SCHEDULER_PERIOD_MS 50

// Software IRQ
#define IRQ_SCHEDULER_READY 0x01

#endif
