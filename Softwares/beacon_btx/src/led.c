/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : led.c
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
 * $Rev:: 896                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-04-14 15:32:13 +0200 (dim., 14 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

// Number of scheduler ticks since started
extern uint16_t tick_cnt;

led_state_t led_green_state;
led_state_t led_red_state;

// -----------------------------------------------------------------------------
// LED MANAGER
// -----------------------------------------------------------------------------

void led_init(void) {

  LED_RED_TRIS   = 0 ;
  LED_GREEN_TRIS = 0 ;

  // Default state
  led_green_state = LED_ON  ;
  led_red_state   = LED_OFF ;

}

inline void led_set_green(led_state_t _state) {
  led_green_state = _state;
}

inline void led_set_red(led_state_t _state) {
  led_red_state = _state;
}

// Return new LED value depending on state
uint8_t led_manage(led_state_t _state) {

  switch(_state) {
    case LED_OFF:
      return 0;

    case LED_ON:
      return 1;

    case LED_BLINK_S1:
      if((tick_cnt % LED_SPEED_1_PERIOD) > (LED_SPEED_1_PERIOD>>1)) return 1;
      else return 0;
      
    case LED_BLINK_S2:
      if((tick_cnt % LED_SPEED_2_PERIOD) > (LED_SPEED_2_PERIOD>>1)) return 1;
      else return 0;

    case LED_PULSE_S1:
      if((tick_cnt % LED_SPEED_1_PERIOD) <= LED_PULSE_DURATION) return 1;
      else return 0;
  
    case LED_PULSE_S2:
      if((tick_cnt % LED_SPEED_1_PERIOD) <= LED_PULSE_DURATION) return 1;
      else return 0;

    default:
      return 0;
  }

}

// This thread must be called at scheduler rate
void led_thread(void) {

  // Needs a '0' to light LED
  LED_GREEN = ~led_manage(led_green_state);
  LED_RED   = ~led_manage(led_red_state);

}
