/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_brx.h
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

#ifndef _BEACON_BRX_H_
#define _BEACON_BRX_H_

// Set the DEBUG flag
#define DEBUG

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------

// Board configuration: hardware definition
// Warning: this file is also used by other modules.
#include "board_cfg.h"

// Beacon general configuration header
#include "beacon_system.h"

// LUT distances
#include "distance_lut.h"

// Libraries headers
#include "cc2500.h"

// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#ifdef DEBUG

#include <stdio.h>

#define DEBUG_UART_BAUDRATE 115200
#define DEBUG_UART_BRG ((FCY/16/DEBUG_UART_BAUDRATE)-1)

#endif

// -----------------------------------------------------------------------------
// TRANSFORMER POWER MODULATION
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// SCHEDULER
// -----------------------------------------------------------------------------

// Scheduler period in ms
#define SCHEDULER_PERIOD_MS 50

// -----------------------------------------------------------------------------
// PHOTO-DETECT
// -----------------------------------------------------------------------------

// Timer period used for PDD timestamps.
// Not really used as the timers are cleared once a correct measurement was
// done.
#define PDD_PERIOD_MSW 0xFFFF
#define PDD_PERIOD_LSW 0xFFFF

// -----------------------------------------------------------------------------
// IRQ Management
// -----------------------------------------------------------------------------

#define PDD_ISR_PRIORITY 0x04 // Middle

#define IRQ_UART_DEBUG_RX   (1<<0)

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

// Oscillator
void osc_init(void);

// LED manager
void led_init(void);

// Photo Detection Interface
void photo_detect_init(void);

// Distance matching and filtering
uint16_t distance_lut_get_idx(uint16_t _ncy_value);
uint16_t distance_get_interp_mm(uint16_t _ncy_value, uint16_t _lut_idx);

// ISRs
void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _IC7Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _IC8Interrupt(void);

#endif // !_BEACON_BRX_H_
