/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : board_cfg.h
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-10
 * -----------------------------------------------------------------------------
 * Description
 *   See main module header file for a full description
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 877                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-30 23:59:51 +0100 (sam., 30 mars 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-03-10
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

/*
 * Remainder for Peripheral Pin Selection
 *
 * RB0 to RB15 => RP0 to RP15
 * RC0 to RC9  => RP16 to RP25
 */

// SPI RF Interfaces //TODO rename because we use multiple SPI
// --------------

// CSN_A output mapped on RB2/RP2
#define CSN_A_TRIS    (TRISBbits.TRISB2)
#define CSN_A         (PORTBbits.RB2)

// CSN_G output mapped on RB3/RP3
#define CSN_G_TRIS    (TRISBbits.TRISB3)
#define CSN_G         (PORTBbits.RB3)

// CSN_RF output mapped on RB4/RP4
#define CSN_RF_TRIS   (TRISBbits.TRISB4)
#define CSN_RF        (PORTBbits.RB4)

// SCK output mapped on RC1/RP17
#define SCK_TRIS      (TRISCbits.TRISC1)
#define SCK_RPN       (RPOR8bits.RP17R)

// MOSI output mapped on RC0/RP16
#define MOSI_TRIS     (TRISCbits.TRISC0)
#define MOSI_RPN      (RPOR8bits.RP16R)

// MISO input mapped on RC2/RP18
#define MISO_TRIS     (TRISCbits.TRISC2)
#define MISO_PIN       18

// PDD Boards interface
// --------------------

// N_B-A input mapped on RB5/RP5
#define PDD_N_BA_TRIS      (TRISBbits.TRISB5)
#define PDD_N_BA_PIN        5

// N_A-B input mapped on RC5/RP21
#define PDD_N_AB_TRIS      (TRISCbits.TRISC5)
#define PDD_N_AB_PIN        21

// E_B-A input mapped on RC3/RP19
#define PDD_E_BA_TRIS      (TRISCbits.TRISC3)
#define PDD_E_BA_PIN        19

// E_A-B input mapped on RC4/RP20
#define PDD_E_AB_TRIS      (TRISCbits.TRISC4)
#define PDD_E_AB_PIN        20

// S_B-A input mapped on RB10/RP10
#define PDD_S_BA_TRIS      (TRISBbits.TRISB10)
#define PDD_S_BA_PIN        10

// S_A-B input mapped on RB11/RP11
#define PDD_S_AB_TRIS      (TRISBbits.TRISB11)
#define PDD_S_AB_PIN        11

// W_B-A input mapped on RC6/RP22
#define PDD_W_BA_TRIS      (TRISCbits.TRISC6)
#define PDD_W_BA_PIN        22

// W_A-B input mapped on RC7/RP23
#define PDD_W_AB_TRIS      (TRISCbits.TRISC7)
#define PDD_W_AB_PIN        23

// DIL Switchs
// -----------

// DIL_1 input mapped on RA1
#define DIL_1_TRIS    (TRISAbits.TRISA1)
#define DIL_1         (PORTAbits.RA1)

// DIL_2 input mapped on RB15
#define DIL_2_TRIS    (TRISBbits.TRISB15)
#define DIL_2         (PORTBbits.RB15)

// DIL_3 input mapped on RB14
#define DIL_3_TRIS    (TRISBbits.TRISB14)
#define DIL_3         (PORTBbits.RB14)

// LEDs
// ----

// LED_1 output mapped on RA7
#define LED_1_TRIS (TRISAbits.TRISA7)
#define LED_1      (PORTAbits.RA7)

// LED_2 output mapped on RA10
#define LED_2_TRIS (TRISAbits.TRISA10)
#define LED_2      (PORTAbits.RA10)

// UART Interface
// --------------

// UART_TX output mapped on RC9/RP25
#define UART_TX_TRIS  (TRISCbits.TRISC9)
#define UART_TX_RPN   (RPOR12bits.RP25R)

// UART_RX input mapped on RC8/RP24
#define UART_RX_TRIS  (TRISCbits.TRISC8)
#define UART_RX_PIN   24

// -----------------------------------------------------------------------------
// CC2500 LIBRARY SETUP
// -----------------------------------------------------------------------------

// CC2500 uses SPI1
#undef CC2500_USE_SPI2

// Define I/Os tristate registers
#define CC2500_SS_TRIS  CSN_RF_TRIS
#define CC2500_SCK_TRIS SCK_TRIS
#define CC2500_SDO_TRIS MOSI_TRIS
#define CC2500_SDI_TRIS MISO_TRIS

// Define I/Os remappable registers & values
#define CC2500_SCK_RPN SCK_RPN
#define CC2500_SDO_RPN MOSI_RPN
#define CC2500_SDI_PIN MISO_PIN

// Define I/Os ports
#define CC2500_SS  CSN_RF

// -----------------------------------------------------------------------------
// BEACON SYSTEM LIBRARY SETUP
// -----------------------------------------------------------------------------

// Indicate that the board is slave
#undef BEACON_COM_IS_MASTER
//#define BEACON_COM_IS_MASTER

// Define the DIL switchs
#define BEACON_COM_DIL_B2_TRIS DIL_1_TRIS // DIL_1 is MSB
#define BEACON_COM_DIL_B1_TRIS DIL_2_TRIS
#define BEACON_COM_DIL_B0_TRIS DIL_3_TRIS // DIL_3 is LSB

#define BEACON_COM_DIL_B2 DIL_1
#define BEACON_COM_DIL_B1 DIL_2
#define BEACON_COM_DIL_B0 DIL_3

// -----------------------------------------------------------------------------
// PDD BOARDS SETUP
// -----------------------------------------------------------------------------

// N_B-A detection mapped on IC1
#define PDD_N_BA_RPN (RPINR7bits.IC1R)

// E_B-A detection mapped on IC2
#define PDD_E_BA_RPN (RPINR7bits.IC2R)

// S_B-A detection mapped on IC7
#define PDD_S_BA_RPN (RPINR10bits.IC7R)

// W_B-A detection mapped on IC8
#define PDD_W_BA_RPN (RPINR10bits.IC8R)

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

#endif
