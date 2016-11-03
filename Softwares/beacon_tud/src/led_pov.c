/* -----------------------------------------------------------------------------
 * Beacon [TUD]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : led_pov.c
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

#include "beacon_tud.h"

void led_pov_init(void) {

  // Init LED I/Os to output
  LED_1_TRIS = 0;
  LED_2_TRIS = 0;
  LED_3_TRIS = 0;
  LED_4_TRIS = 0;
  LED_5_TRIS = 0;
  LED_6_TRIS = 0;
  LED_7_TRIS = 0;

  // Disable all LEDs but 1st one
  LED_1 = 1;
  LED_2 = 0;
  LED_3 = 0;
  LED_4 = 0;
  LED_5 = 0;
  LED_6 = 0;
  LED_7 = 0;

}