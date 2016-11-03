/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : photo_detect.c
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
 * $Rev:: 880                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-31 19:56:05 +0200 (dim., 31 mars 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-03-10
 * -----------------------------------------------------------------------------
 */

#include "beacon_brx.h"

// -----------------------------------------------------------------------------
// CONFIGURATION FUNCTIONS
// -----------------------------------------------------------------------------

void photo_detect_init(void) {

  // Initialize PDD feedback pins as inputs
  PDD_N_BA_TRIS = 1 ;
  PDD_N_AB_TRIS = 1 ;
  PDD_E_BA_TRIS = 1 ;
  PDD_E_AB_TRIS = 1 ;
  PDD_S_BA_TRIS = 1 ;
  PDD_S_AB_TRIS = 1 ;
  PDD_W_BA_TRIS = 1 ;
  PDD_W_AB_TRIS = 1 ;

  // Init remappable inputs
  PDD_N_BA_RPN = PDD_N_BA_PIN ;
  PDD_E_BA_RPN = PDD_E_BA_PIN ;
  PDD_S_BA_RPN = PDD_S_BA_PIN ;
  PDD_W_BA_RPN = PDD_W_BA_PIN ;
  

  /*
   * Configure IC1 to IC4 for timing detection on *_B-A interfaces.
   * These input capture make use of TIM2.
   * Timings between *_B-A and associated *_A-B do not give useful
   * information for distance measurement.
   * The smaller the time is between the two consecutive detections of
   * *_B-A, the farer is the turret (non-linear relationship).
   *
   * As we want to have the best time resolution on timestamp, the sampling
   * frequency needs to be as large as possible. With a 16b timer this allows
   * to measure time-delta up to 2ms with FCY = 32M.
   * However this is not enough to filter time-delta between 2 consecutives
   * turret rotation (period 25ms at 40rp/s).
   * The easiest way to manage this is to use type B+C timers combinated to form
   * a 32 bit timer.
   */

  // Init Timers 2 and 3
  T2CONbits.TON   = 0          ; // Disable Timers
  T3CONbits.TON   = 0          ;
  T2CONbits.T32   = 1          ; // Form a 32bit timer with TIM3
  T2CONbits.TCS   = 0          ; // Internal cycle clock selected
  T2CONbits.TCKPS = 0b00       ; // Set prescaler = 1:1 ; TIM2 Freq = FCY
  TMR2            = 0          ; // Clear Timers
  TMR3            = 0          ;
  PR3             = PDD_PERIOD_MSW ; // Timer period MSW
  PR2             = PDD_PERIOD_LSW ; // Timer period LSW

  // Init Input captures
  IC1CONbits.ICM      = 0b000 ; // Disable Input Capture
  IC1CONbits.ICTMR    = 1     ; // Select TIM2 as time base
  IC1CONbits.ICI      = 0b00  ; // Interrupt on every captured event
  IC1CONbits.ICM      = 0b010 ; // Falling-Edge capture mode
  
  IC2CONbits.ICM      = 0b000 ; // Disable Input Capture
  IC2CONbits.ICTMR    = 1     ; // Select TIM2 as time base
  IC2CONbits.ICI      = 0b00  ; // Interrupt on every captured event
  IC2CONbits.ICM      = 0b010 ; // Falling-Edge capture mode

  IC7CONbits.ICM      = 0b000 ; // Disable Input Capture
  IC7CONbits.ICTMR    = 1     ; // Select TIM2 as time base
  IC7CONbits.ICI      = 0b00  ; // Interrupt on every captured event
  IC7CONbits.ICM      = 0b010 ; // Falling-Edge capture mode

  IC8CONbits.ICM      = 0b000 ; // Disable Input Capture
  IC8CONbits.ICTMR    = 1     ; // Select TIM2 as time base
  IC8CONbits.ICI      = 0b00  ; // Interrupt on every captured event
  IC8CONbits.ICM      = 0b010 ; // Falling-Edge capture mode

  // Configure ISR priorities
  IPC0bits.IC1IP = PDD_ISR_PRIORITY ;
  IPC1bits.IC2IP = PDD_ISR_PRIORITY ;
  IPC5bits.IC7IP = PDD_ISR_PRIORITY ;
  IPC5bits.IC8IP = PDD_ISR_PRIORITY ;

  // Clear interrupt flags
  IFS0bits.IC1IF = 0;
  IFS0bits.IC2IF = 0;
  IFS1bits.IC7IF = 0;
  IFS1bits.IC8IF = 0;

  // Enable interruption
  IEC0bits.IC1IE = 1;
  IEC0bits.IC2IE = 1;
  IEC1bits.IC7IE = 1;
  IEC1bits.IC8IE = 1;
  
}

// -----------------------------------------------------------------------------
// MANAGMENT FUNCTIONS
// -----------------------------------------------------------------------------

// Enable the photo detection
inline void photo_detect_run(void) {

  // Clear timer values before start
  TMR2 = 0 ;
  TMR3 = 0 ;
  
  // Enable associated timers
  T2CONbits.TON   = 1 ;
  T3CONbits.TON   = 1 ;
  
}

inline void photo_detect_stop(void) {

  // Disable associated timers
  T2CONbits.TON   = 0 ;
  T3CONbits.TON   = 0 ;

}

// -----------------------------------------------------------------------------
// PROCESSING FUNCTIONS
// -----------------------------------------------------------------------------

// Main processing function for Interrupt-Capture ISR
// Declared as inline because we want to duplicate the code in the different ISR
inline void photo_detect_process(uint16_t _ic_value) {

  uint16_t lut_idx ;
  uint16_t dist_mm ;
  
  // If MSW timer value is greater than 0 it means the
  // LSW timer overflowed. Hence we are not measuring
  // a time-delta between the 2 consecutive lasers but
  // a time-delta between 2 consecutive turret rotation.
  if(!TMR3) {

    // Retrieve lut index
    lut_idx = distance_lut_get_idx(_ic_value);

    // Check for lower/higher bounds
    if(lut_idx == 0) {
      dist_mm = DISTANCE_LUT_MIN_MM ;
    } else if(lut_idx == DISTANCE_LUT_DEPTH-1) {
      dist_mm = DISTANCE_LUT_MAX_MM ;

    // Treat only correctly bounded values
    } else {

      // Get distance in mm after interpollation
      dist_mm = distance_get_interp_mm(_ic_value, lut_idx);
      
      // Send it
      beacon_com_send_dist(dist_mm);

      LED_2 = ~ LED_2;
    }
    
  } // !TMR3

  // Clear timers
  TMR3 = 0;
  TMR2 = 0;
  
}

// -----------------------------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
// -----------------------------------------------------------------------------

// IC1 for PDD North
void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt(void) {

  // Read IC buffer and call main process function
  photo_detect_process(IC1BUF);

  // Clear interrupt flag
  IFS0bits.IC1IF = 0;

 }

// IC2 for PDD East
void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt(void) {

  // Clear interrupt flag
  IFS0bits.IC2IF = 0;

 }

// IC7 for PDD South
void __attribute__((__interrupt__, no_auto_psv)) _IC7Interrupt(void) {

  // Clear interrupt flag
  IFS1bits.IC7IF = 0;

 }

// IC8 for PDD West
void __attribute__((__interrupt__, no_auto_psv)) _IC8Interrupt(void) {

  // Clear interrupt flag
  IFS1bits.IC8IF = 0;

 }

