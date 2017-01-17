/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : oscillator.c
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
 * $Rev:: 862                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-02-23 18:51:48 +0100 (sam., 23 févr. 2013)         $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

// -----------------------------------------------------------------------------
// OSCILLATOR
// -----------------------------------------------------------------------------

void osc_init(void) {

    // Setup PLL to obtain FCY = 32MHz (FOSC = 64MHz)
    // POSCCLK = 8MHz,
    // FOSC = (FIN/N1) * M / N2
    // However frequency ranges must be respected as the different nodes,
    // so that :
    // 0.8  <= FIN/N1       <= 8 MHz
    // 100  <= (FIN/N1) * M <= 200 MHz
    // 12.5 <= FOSC         <= 80 MHz
    //
    // So we can pick:
    // N1 = 2,  (FIN/N1)   = 4 MHz
    // M  = 32, (FIN/N1)*M = 128 MHz
    // N2 = 2,        FOSC = 64 MHz, FIN = 32MHz

    CLKDIVbits.PLLPRE  =  0; // N1 = 2
    PLLFBDbits.PLLDIV  = 30; // M  = 32
    CLKDIVbits.PLLPOST =  0; // N2 = 2
    CLKDIVbits.DOZE    =  0; // FP = FCY

    RCONbits.SWDTEN = 0; // Software watchdog disabled

    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    while (OSCCONbits.COSC != 3) ; // Wait until HSPLL mode is set
    while (OSCCONbits.LOCK != 1) ; // Wait until PLL is lock
#warning "check clock config (HS for 8MHZ ?) + 1Mohm parallel ?"
}

