/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : led.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-16
 * -----------------------------------------------------------------------------
 * Description
 *   See main module header file for a full description
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 873                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-28 00:12:33 +0100 (jeu., 28 mars 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-03-10
 * -----------------------------------------------------------------------------
 */

#include "beacon_brx.h"

// -----------------------------------------------------------------------------
// LEDS MANAGER
// -----------------------------------------------------------------------------

void led_init(void) {

  // LEDs are output
  LED_1_TRIS = 0 ;
  LED_2_TRIS = 0 ;

  // LEDs are off by default
  LED_1 = 0 ;
  LED_2 = 1 ;

}

// Dummny DIL to LED test
inline void led_demo(void) {
    if(!DIL_1) {
      LED_1 = DIL_2;
      LED_2 = DIL_3;
    } else {
      LED_1 = ~LED_1;
      LED_2 = ~LED_2;
    }
}
