/* -----------------------------------------------------------------------------
 * Beacon [TUD]
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
 * $Rev:: 836                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-01-13 17:43:44 +0100 (dim., 13 janv. 2013)          $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#ifndef _BOARD_CFG_H
#define _BOARD_CFG_H

#ifdef USE_HITECH_CC

// Using HI-TECH PIC Compiler main header
#include <htc.h>

// Fore reference only, not meant to be included directly
#ifndef	_HTC_H_
    #include <pic16f1825.h>
#endif

#endif // !USE_HITECH_CC

// Compiler related types
typedef unsigned char uint8_t;
typedef signed   char sint8_t;
typedef unsigned int uint16_t;
typedef signed   int sint16_t;

// -----------------------------------------------------------------------------
// FREQUENCIES
// -----------------------------------------------------------------------------

// Oscilator frequency
#define F_OSC 32000000 // Do not use the word fOSC which is a configuration bit!

// -----------------------------------------------------------------------------
// HARDWARE
// -----------------------------------------------------------------------------

// UART for commands RX input
// --------------------------

#define UART_RX_TRIS (TRISCbits.TRISC5)
#define UART_RX      (LATCbits.LATC5)

// Laser power
// -----------

#define LASER_ON_TRIS (TRISAbits.TRISA5)
#define LASER_ON      (LATAbits.LATA5)

// LEDs for POV
// ------------

#define LED_7_TRIS (TRISAbits.TRISA4)
#define LED_7      (LATAbits.LATA4)

#define LED_6_TRIS (TRISCbits.TRISC4)
#define LED_6      (LATCbits.LATC4)

#define LED_5_TRIS (TRISCbits.TRISC3)
#define LED_5      (LATCbits.LATC3)

#define LED_4_TRIS (TRISCbits.TRISC2)
#define LED_4      (LATCbits.LATC2)

#define LED_3_TRIS (TRISCbits.TRISC1)
#define LED_3      (LATCbits.LATC1)

#define LED_2_TRIS (TRISCbits.TRISC0)
#define LED_2      (LATCbits.LATC0)

#define LED_1_TRIS (TRISAbits.TRISA2)
#define LED_1      (LATAbits.LATA2)

#endif // ! _BOARD_CFG_H