/* -----------------------------------------------------------------------------
 * Beacon [TUD]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_tud.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-01-13
 * -----------------------------------------------------------------------------
 * Description
 *   The [TUD] Board is responsible for managing the Laser output and
 *   eventually some LED POV display. It receives orders via a 1 wire interface
 *   (UART). The minimum functionnality is however to simply turn on lasers.
 *   The rest of the features is more for fun and later experimentations.
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

#include "beacon_tud.h"

//------------------------------------------------------------------------------
// CONFIGURATION
//------------------------------------------------------------------------------

#ifdef USE_HITECH_CC
__CONFIG(FOSC_INTOSC    // Using internal oscillator
       & WDTE_OFF       // Watchdog Timer disabled
       & PWRTE_OFF      // Power-up Timer disabled
       & MCLRE_ON       // MCLR pin function is MCLR
       & CP_OFF         // Flash Program Memory Code Protection disabled
       & CPD_OFF        // Data memory code protection is disabled
       & BOREN_OFF      // Brown-out Reset disabled
       & CLKOUTEN_OFF   // CLKOUT function is disabled
       & IESO_OFF       // Internal/External Switchover mode is disabled
       & FCMEN_OFF      // Fail-Safe Clock Monitor is disabled
       & WRT_ALL        // Flash Memory Self-Write is disabled
       & PLLEN_ON       // PLL is ON
       & STVREN_OFF     // Stack ovf/udf will not cause a reset    
       );

// Put this one in a separate config because it's not recognized otherwise
// (this is a bug from microchip).
__CONFIG(LVP_OFF);      // High-voltage on MCLR/VPP must be used for programming
#endif

//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------------

// Configure Oscillator
static void osc_init(void) {
    OSCCONbits.SCS    = 0b00;      // System clock is determined by FOSC value
    OSCCONbits.IRCF   = 0b1110;    // Internal oscillator frequency set to 8 MHz
    OSCCONbits.SPLLEN = 0b1;       // Enable x4 PLL. Resulting frequency = 32MHz
    while(!OSCSTATbits.HFIOFR);    // Wait until Internal oscillator is ready
    while(!OSCSTATbits.PLLR);      // Wait until PLL is ready
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main(void) {

    // Initialize
    osc_init();

    // All I/Os are digital, init
    ANSELA = 0x00;

    // Init laser
    LASER_ON_TRIS = 0;
    LASER_ON = 1;

    // Init LEDs for POV
    // (Unimplemented)
    led_pov_init();
           
    // Nothing to do yet
    while(1);
    
}
