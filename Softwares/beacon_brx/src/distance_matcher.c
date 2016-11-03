/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : distance_matcher.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-23
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

// LUT is defined in an external module
extern const uint16_t lut_dist_ncy[DISTANCE_LUT_DEPTH] __attribute__((space(psv)));

// -----------------------------------------------------------------------------
// DISTANCE MATCHING AND FILTERING FUNCTIONS
// -----------------------------------------------------------------------------

// Find and return lower index bound of corresponding ncy value from the LUT
uint16_t distance_lut_get_idx(uint16_t _ncy_value) {

  uint16_t* p_idx  ;
  uint16_t  width ;

  // ncy value is greater than biggest value in LUT
  // => distance is smaller than smallest LUT value
  if(_ncy_value >= DISTANCE_LUT_MAX_NCY)
    return 0 ;

  // ncy value is lower than smallest value in LUT
  // => distance is greater than the biggest LUT value
  if(_ncy_value <= DISTANCE_LUT_MIN_NCY)
    return DISTANCE_LUT_DEPTH-1 ;

  // Fast index lookup in log2(DISTANCE_LUT_DEPTH)
  // lut_dist_ncy is sorted in decreasing order
  // (idx 0 <=> MAX, idx DISTANCE_LUT_DEPTH-1 <=> MIN)
  // DISTANCE_LUT_DEPTH is also known to be a power of 2,
  // so it'd always be an even value.
  // On each loop, split array in 2 equal width and check
  // wheather the actual ncy value is higher or lower than the
  // corresponding index.
  // Continue until the split width is 1

  // Init width to half lut size
  width  = (DISTANCE_LUT_DEPTH >> 1) ;
  p_idx  = ((uint16_t*) lut_dist_ncy) + width;

  while(width >>= 1) {
    if (_ncy_value == *p_idx)
      break;
    else if(_ncy_value > *p_idx)
      p_idx -= width; // '-' because bigger values are on smaller indexes
    else
      p_idx += width; // '+' because smaller values are on higher indexes
  }

  // Pointer addresses difference corresponds to the
  // found array index upper bound
  return (uint16_t) (p_idx - lut_dist_ncy -1) ;

}

// Retrieve values from lut and use the precise ncy value to interpollate
uint16_t distance_get_interp_mm(uint16_t _ncy_value, uint16_t _lut_idx) {

  uint16_t high_val_ncy ;
  uint16_t low_val_ncy ;
  uint16_t ref_val_ncy ;
  uint16_t delta_ncy ;

  uint16_t high_val_mm ;
  uint16_t low_val_mm ;
  uint16_t ref_val_mm ;

  sint16_t interp_mm ;

  high_val_ncy = distance_lut_get_ncy(_lut_idx);
  low_val_ncy = distance_lut_get_ncy(_lut_idx+1);

  high_val_mm = distance_lut_get_mm(_lut_idx);
  low_val_mm = distance_lut_get_mm(_lut_idx+1);
  
  delta_ncy = high_val_ncy - low_val_ncy ;

  // First check if by luck the ncy value matchs exactly an index
  if(_ncy_value == high_val_ncy)
    return high_val_mm;

  // Pickup the closest LUT index as the reference for a
  // better interpollation.
  // Higher bound is closer
  if(high_val_ncy - _ncy_value < _ncy_value - low_val_ncy) {
    ref_val_ncy = high_val_ncy;    
    ref_val_mm = high_val_mm;
  } else {
    ref_val_ncy = low_val_ncy;    
    ref_val_mm = low_val_mm;
  }

  // Distance in ncy unit between ref and measurement
  interp_mm = ((sint16_t) ref_val_ncy) - ((sint16_t) _ncy_value );

  // Convert this difference in mm with a linear interpollation
  interp_mm *= DISTANCE_LUT_STEP_MM ;
  interp_mm /= delta_ncy;

  // The signed interpollated value adds up to ref
  // to form the final computed distance in mm
  return (uint16_t) (ref_val_mm  + interp_mm);
  
}

