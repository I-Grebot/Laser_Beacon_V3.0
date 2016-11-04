/* ----------------------------------------------------------------------------- 
 * I-Grebot Watchdog Timer Library
 * -----------------------------------------------------------------------------
 * File        : watchdog.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-04-13
 * -----------------------------------------------------------------------------
 * Description
 *   This is a set of few inline functions for software watchdog-timer
 *   handling.
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

#include "board_cfg.h"

// -----------------------------------------------------------------------------
// WATCHDOG TIMER
// -----------------------------------------------------------------------------

inline void wdt_run(void) {
  RCONbits.SWDTEN = 1 ;
}

inline void wdt_stop(void) {
  RCONbits.SWDTEN = 0 ;
}

inline void wdt_clear(void) {
  ClrWdt();
}

inline uint8_t wdt_occured(void) {
  return RCONbits.WDTO ;
}

