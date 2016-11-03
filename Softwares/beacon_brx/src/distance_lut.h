/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : distance_lut.h
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-23
 * -----------------------------------------------------------------------------
 * Description
 *   This file was automatically generated the 31-Mar-2013 15:58:02.
 *   See main module header file for a full description
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 880                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-31 19:56:05 +0200 (dim., 31 mars 2013)           $
 * -----------------------------------------------------------------------------
 */

#ifndef _DISTANCE_LUT_H_
#define _DISTANCE_LUT_H_

// -----------------------------------------------------------------------------
// DISTANCES LOOK-UP-TABLE PARAMETERS
// -----------------------------------------------------------------------------

// The LUT and parameters were generated assuming the following conditions:
// * Distance between lasers      = 40 mm
// * Distance between photodiodes = 10 mm
// * Turret angular speed         = 30 rp/s
// * FCY                          = 32 MHz

#if FCY != 32000000
  #error "Expected FCY frequency do not match with value used for LUT generation!"
#endif // FCY

#if DRUM_MOTOR_SPEED_TARGET_RPS != 30
  #error "Expected Turret frequency do not match with value used for LUT generation!"
#endif // DRUM_MOTOR_SPEED_TARGET_RPS

#define DISTANCE_LUT_DEPTH 256
#define DISTANCE_LUT_STEP_MM 16

#define DISTANCE_LUT_MAX_NCY 45825 // min distance in mm
#define DISTANCE_LUT_MIN_NCY 1605 // max distance in mm

#define DISTANCE_LUT_MIN_MM 150
#define DISTANCE_LUT_MAX_MM 4246

#endif // !_DISTANCE_LUT_H_
