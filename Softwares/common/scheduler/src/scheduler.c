/* -----------------------------------------------------------------------------
 * I-Grebot Scheduler Library
 * -----------------------------------------------------------------------------
 * File        : scheduler.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-01-13
 * -----------------------------------------------------------------------------
 * Description
 *   This is a basic scheduling implementation.
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

// Number of scheduler ticks since started
uint16_t tick_cnt;

// Software IRQ vector
extern uint8_t sw_irq;

// -----------------------------------------------------------------------------
// SCHEDULER
// -----------------------------------------------------------------------------

#define SCHEDULER_TIMER_PERIOD ((FCY/64000)*SCHEDULER_PERIOD_MS)
void scheduler_init(void) {

    // Init Timer 5 for schedulling,
    // Use timer as a regular 16 bits timer
    // It is assumed that Timer 4 is used as a standalone 16 bits timer
    T5CONbits.TON   = 0     ; // Disable Timer
    T5CONbits.TCS   = 0     ; // Internal cycle clock selected
    T5CONbits.TCKPS = 0b10  ; // Set prescaler = 1:64 ; TIM5 Freq = FCY/64
    TMR5            = 0     ; // Clear Timer
    PR5             = SCHEDULER_TIMER_PERIOD ; // Select TIM5 Period

    // Enable Timer5 Interrupt
    IFS1bits.T5IF = 0;
    IEC1bits.T5IE = 1;
}

inline void scheduler_start(void) {
    tick_cnt      = 0 ; // Clean tick counter
    T5CONbits.TON = 1 ; // Enable Timer
}

inline void scheduler_stop(void) {
    T5CONbits.TON   = 0     ; // Disable Timer
}

inline uint8_t scheduler_ready(void) {
    if(sw_irq & IRQ_SCHEDULER_READY) {
      sw_irq &= (~IRQ_SCHEDULER_READY);
      return 1;
    } else {
      return 0;
    }
}

inline uint8_t scheduler_task_ready(uint8_t _rate) {
  return !(tick_cnt % _rate);
}

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void) {
  tick_cnt++;
  sw_irq |= IRQ_SCHEDULER_READY ;
  IFS1bits.T5IF = 0; // Clear interrupt
}
