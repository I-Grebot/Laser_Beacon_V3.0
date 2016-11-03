/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : rf_master.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-02-23
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
 * 1.0         Initial release                           Paul M.      2013-02-23
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

// Scheduler tick count
extern uint16_t tick_cnt;

// -----------------------------------------------------------------------------
// RF MASTER HANDLER
// -----------------------------------------------------------------------------

// RX Subroutine
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void) {

  // Disable interrupt, will be enable back once all fifo RX is read
  IEC1bits.INT1IE = 0 ;
  IFS1bits.INT1IF = 0 ;

  // Timestamp the drum motor position and give it
  //  to the RF decoding and update method
  beacon_com_receive_packet(drum_motor_get_angle(), tick_cnt);

  // Clear interrupt flag and enable back interrupt
  IFS1bits.INT1IF = 0 ;
  IEC1bits.INT1IE = 1 ;
}
