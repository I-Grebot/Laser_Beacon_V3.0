/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : drum_control.c
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

uint8_t drum_running;
uint16_t drum_speed;
float drum_control_rps ;
float current_speed_rps;

// -----------------------------------------------------------------------------
// DRUM MOTOR CONTROL
// -----------------------------------------------------------------------------

/*
 * Main Initializer for drum speed control
 * Use TIM3 and OC3 for motor PWM command
 * Use TIM4, Internal REF and Comparator 1 for TOP feedback
 */

void drum_control_init(void) {

    // I/Os mapping
    // ------------

    DRUM_MOTOR_TRIS = 0;
    DRUM_MOTOR_RPN = DRUM_MOTOR_PIN ;
    DRUM_TOP_TRIS = 1 ;

    // Motor PWM Hardware
    // ------------------

    // Init Timer 3 for motor PWM
    T3CONbits.TON   = 0     ; // Disable Timer
    T3CONbits.TCS   = 0     ; // Internal cycle clock selected
    T3CONbits.TCKPS = 0b10  ; // Set prescaler = 1:64 ; TIM3 Freq = FCY / 64
    TMR3            = 0     ; // Clear Timer
    PR3             = DRUM_MOTOR_PERIOD ; // Select TIM3 Periods

    // Init Output Compare module 3 for drum motor PWM generation
    OC3CONbits.OCM      = 0b000 ; // Disable OC3
    OC3CONbits.OCTSEL   = 1     ; // Select TIM3 as time base
    OC3R                = 0     ; // Rising-edge reference for the pulse
    DRUM_MOTOR_OCRS     = DRUM_MOTOR_DUTY ; // PWM's width
    OC3CONbits.OCM      = 0b110 ; // Set OC3 mode to PWM

    // TOP Feedback Hardware
    // ---------------------

    // Configure Voltage Reference for comparators
    CVRCONbits.CVRSS = 0  ; // Voltage reference is AVDD/AVSS
    CVRCONbits.CVRR  = 0  ; //   for a 3.3V input
    CVRCONbits.CVR   = DRUM_TOP_CVR ; // Voltage reference value
    CVRCONbits.CVROE = 0  ; // Do not output VREF on pad

    // Configure Comparator input for drum-top
    CMCONbits.C1NEG = 0 ; // VIN- mapped on CIN-
    CMCONbits.C1POS = 0 ; // VIN+ mapped on VREFIN
    CMCONbits.C1INV = 1 ; // Invert Comparator output

    // Init Timer 4
    T4CONbits.T32   = 0 ; // 16bit Timer (do not associate with TIM5)
    T4CONbits.TON   = 0 ; // Disable Timer
    T4CONbits.TCS   = 0 ; // Internal cycle clock selected
    T4CONbits.TCKPS = DRUM_TOP_TCKPS  ; // Set prescaler
    TMR4            = 0 ; // Clear Timer

    // Enable voltage ref
    CVRCONbits.CVREN = 1 ;

    // Drum is not running
    drum_running = 0 ;

}

void drum_motor_start(void) {

    // Configure ISR for C1OUT
    CMCONbits.C1EVT = 0 ; // Clear Event bit flag
    IFS1bits.CMIF = 0 ;   // Clear interrupt

    // Enable interrupts
    IEC1bits.CMIE = 1 ;   
    CMCONbits.C1EN  = 1 ;

    // Clear speed feedback variable
    drum_speed = 0;

    // Drum is running
    drum_running = 1;
    
    // Enable Timers
    T3CONbits.TON = 1 ;
    T4CONbits.TON = 1 ;
}

void drum_motor_stop(void) {

  // Disable Timers
  T3CONbits.TON = 0 ;
  T4CONbits.TON = 0 ;

  // Disable interrupts
  IEC1bits.CMIE = 0 ;
  CMCONbits.C1EN  = 0 ;
  
  // Drum is not running
  drum_running = 0 ;

}

// Function used to control the drum motor
float drum_motor_control(float target_drum_speed_rps, float current_drum_speed_rps) {

    // Integral error accumulation
    static float error_int = 0 ;

    // Returned controlled value
    float control_speed_rps ;

    // Error in rps
    float error;

    // Raw input error
    // Positive => Too fast
    // Negative => Too slow
    error = current_drum_speed_rps - target_drum_speed_rps ;

    // Integral error: clamp it if it reaches large values
    error_int += error*DRUM_CONTROL_KI ;
    if     (error_int >  DRUM_CONTROL_ERRI_MAX) error_int =  DRUM_CONTROL_ERRI_MAX ;
    else if(error_int < -DRUM_CONTROL_ERRI_MAX) error_int = -DRUM_CONTROL_ERRI_MAX ;

    // New control value
    control_speed_rps = target_drum_speed_rps - error*DRUM_CONTROL_KP - error_int ;

    // Clamp it
    if      (control_speed_rps > DRUM_CONTROL_RPS_MAX) control_speed_rps = DRUM_CONTROL_RPS_MAX ;
    else if (control_speed_rps < DRUM_CONTROL_RPS_MIN) control_speed_rps = DRUM_CONTROL_RPS_MIN ;

    return control_speed_rps ;
}

inline uint16_t drum_motor_get_angle(void) {
  sint32_t angle_deg ;

  // Get the current timer value
  angle_deg = (sint32_t) DRUM_TOP_TIMER ;

  // Converts the timer-unit value into a 10th of degree signed value :
  //     0 <= DRUM_TOP_TIMER < drum_speed
  // -1800 <= angle_deg      < +1800
  // (This is quite overkill to use 32bit here but we want to make sure
  //  that we dont loose precision from processing)
  angle_deg *= 3600 ;
  angle_deg /= drum_speed ;

  // Remove offset to adjuste robot's 0° with turret 0°
  // Also compensate fixed latency delay between [BRX] detection and
  // [BTX] timer sampling
  angle_deg -= DRUM_TOP_ANGLE_OFFSET;

  if(angle_deg < 0) //ensure returned value is positive
  {
      angle_deg += 3600; 
  }
  
  // Can be cast back in 16bit value
  return (sint16_t) angle_deg;
}

void drum_motor_set_speed(float drum_speed_rps) {

    // Drum speed value in pwm unit
    float drum_speed_pwm ;

    // Convert from hundreth of rps into PWM value
    drum_speed_pwm = DRUM_MOTOR_RPS_TO_DUTY(drum_speed_rps);

    // Negative and Positive clamps
    if     (drum_speed_pwm < DRUM_MOTOR_PWM_MIN) drum_speed_pwm = DRUM_MOTOR_PWM_MIN;
    else if(drum_speed_pwm > DRUM_MOTOR_PWM_MAX) drum_speed_pwm = DRUM_MOTOR_PWM_MAX;

    // AFfect final value to module duty-cycle
    DRUM_MOTOR_OCRS = (uint16_t) drum_speed_pwm ;
}

// ISR Called when a "TOP" has been detected
void __attribute__((__interrupt__, no_auto_psv)) _CMPInterrupt(void) {

    // Clear interrupt and Event bit flag
    CMCONbits.C1EVT = 0 ;
    IFS1bits.CMIF = 0 ;

    // Only rising edge and arbitrary threshold to filter glitchs
    // Update global variable
    if(DRUM_TOP && DRUM_TOP_TIMER > DRUM_TOP_GLITCH_THRS) {
        drum_speed = (uint16_t) DRUM_TOP_TIMER ;
        DRUM_TOP_TIMER = 0 ; // Reset timer
    }
}

// Retrieve the current speed in RPS
inline float drum_motor_get_speed_rps(void) {
    if(drum_speed != 0) return (((float) NCY_TO_RPS_FACTOR)/((float) drum_speed)) ;
    else                return 0;
}

// Main control handler, called on each scheduler tick
inline void drum_control_thread(void) {

    // Get the current speed in RPS
    current_speed_rps = drum_motor_get_speed_rps();    
    
    // Controller iteration: get the new control value
    drum_control_rps = drum_motor_control(DRUM_MOTOR_SPEED_TARGET_RPS, current_speed_rps);

    // Set new speed value
    drum_motor_set_speed(drum_control_rps);

}
