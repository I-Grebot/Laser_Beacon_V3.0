/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_btx.h
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

#ifndef _BEACON_BTX_H_
#define _BEACON_BTX_H_

#define DEBUG

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------

// Board configuration: hardware definition
// Warning: this file is also used by other modules.
#include "board_cfg.h"

// Beacon general configuration header
#include "beacon_system.h"

// Libraries headers
#include "igrecan.h"
#include "cc2500.h"
#include "scheduler.h"

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#ifdef DEBUG

#include <stdio.h>
#include <string.h>

#define DEBUG_UART_BAUDRATE 115200
#define DEBUG_UART_BRG ((FCY/16/DEBUG_UART_BAUDRATE)-1)

#endif

// -----------------------------------------------------------------------------
// TRANSFORMER POWER MODULATION
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// DRUM MOTOR CONTROL
// -----------------------------------------------------------------------------

// PI Controller (no derivative term)
// Units coefficients will apply on 100th of RPM values
#define DRUM_CONTROL_KP  20
#define DRUM_CONTROL_KI  5
#define DRUM_CONTROL_ERRI_MAX 2.0

// -----------------------------------------------------------------------------
// SCHEDULER
// -----------------------------------------------------------------------------

// Rates in scheduler ticks
#define SCHEDULER_RATE_SEND_CAN_STATUS 20  // every second
#define SCHEDULER_RATE_SEND_CAN_DATA    2  // every 100 ms
#define SCHEDULER_RATE_BLINK_LED        5  // every 250 ms
#define SCHEDULER_RATE_DRUM_CONTROL     2  // every 100 ms

// -----------------------------------------------------------------------------
// LED
// -----------------------------------------------------------------------------

// LED speed constants in scheduler period unit
#define LED_SPEED_1_PERIOD 40 // Slow
#define LED_SPEED_2_PERIOD 10 // Fast
#define LED_PULSE_DURATION  2 // Duration of "ON" pulse in pulsed states


// Define an LED state
typedef enum {LED_OFF,      // Switched-off
              LED_ON,       // Constantly on
              LED_BLINK_S1, // Regular blinking (50% duty-cycle) speed 1
              LED_BLINK_S2, // Speed 2
              LED_PULSE_S1, // Pulsed blinking speed 1
              LED_PULSE_S2  // Pulsed blinking speed 2
} led_state_t;

// -----------------------------------------------------------------------------
// IRQ Management
// -----------------------------------------------------------------------------

// Scheduler IRQ defined in board_cfg
#define IRQ_UART_DEBUG_RX   0x80

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

// Oscillator
void osc_init(void);

// Transformer Power-Modulation
void power_modulation_init(void);

// Drum Speed Control
void drum_control_init(void);
void drum_motor_start(void);
void drum_motor_stop(void);
float drum_motor_control(float target_drum_speed_rps, float current_drum_speed_rps);
void drum_motor_set_speed(float drum_speed_rps);

// CAN
void beacon_can_init(void);
void beacon_can_send_opponent_1(void) ;
void beacon_can_send_status(void);
void beacon_can_rx (void);

// LED
void led_init(void);
uint8_t led_manage(led_state_t _state);
void led_thread(void);

#endif // !_BEACON_BTX_H_
