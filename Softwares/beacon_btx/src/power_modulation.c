/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : power_modulation.c
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
 * $Rev:: 870                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-23 20:33:55 +0100 (sam., 23 mars 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

/*
 * Power Modulation initializer
 * Use TIMER 2 and OC1/OC2 for PWM generation
 */

void power_modulation_init(void) {

    // I/Os mapping
    MOD_OUT_PWM_P_TRIS = 0;
    MOD_OUT_PWM_N_TRIS = 0;
    MOD_OUT_TX_TRIS    = 0;
    MOD_OUT_PWM_P_RPN = MOD_OUT_PWM_P_PIN ;
    MOD_OUT_PWM_N_RPN = MOD_OUT_PWM_N_PIN ;
    
    
    MOD_OUT_TX = 0; // Off during initialisations
    //LATCbits.LATC0 = 1 ; // N CHAN
    //LATCbits.LATC1 = 0 ; // P CHAN
    //return ;
    
    // Init Timer 2
    T2CONbits.TON   = 0     ; // Disable Timer
    T2CONbits.TCS   = 0     ; // Internal cycle clock selected
    T2CONbits.TCKPS = 0b00  ; // Set prescaler = 1:1 ; TIM2 Freq = FCY
    TMR2            = 0     ; // Clear Timer
    PR2             = MOD_OUT_PWM_PERIOD ; // Select TIM2 Periods

    // Init Output Compare module 1 for positive pulse generation
    OC1CONbits.OCM      = 0b000 ; // Disable OC1
    OC1CONbits.OCTSEL   = 0     ; // Select TIM2 as time base
    OC1R                = 0     ; // Rising-edge reference for the pulse
    OC1RS               = MOD_OUT_PWM_DUTY     ; // Falling-edge reference for the pulse
    OC1CONbits.OCM      = 0b101 ; // Set OC1 mode to Continuous Pulse Mode

    // Init Output Compare module 2 for negative pulse generation
    OC2CONbits.OCM      = 0b000 ; // Disable OC2
    OC2CONbits.OCTSEL   = 0     ; // Select TIM2 as time base
    OC2R                = MOD_OUT_PWM_PERIOD-MOD_OUT_PWM_MARGIN;//// // Rising-edge reference for the pulse
    OC2RS               = MOD_OUT_PWM_DUTY+MOD_OUT_PWM_MARGIN;//((MOD_OUT_PWM_PERIOD+2)>>1)+MOD_OUT_PWM_DUTY;//// Falling-edge reference for the pulse
    OC2CONbits.OCM      = 0b101 ; // Set OC2 mode to Continuous Pulse Mode

    // Enable Timer and Power output
    T2CONbits.TON = 1 ;
    MOD_OUT_TX = 1;
   
}

inline void power_modulation_set_state(uint8_t value) {
  MOD_OUT_TX = (value & 1);
}
