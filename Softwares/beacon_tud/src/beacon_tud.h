/* -----------------------------------------------------------------------------
 * Beacon [TUD]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_tud.h
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
 * $Rev:: 836                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-01-13 17:43:44 +0100 (dim., 13 janv. 2013)          $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-01-13
 * -----------------------------------------------------------------------------
 */

#ifndef _BEACON_TUD_H_
#define	_BEACON_TUD_H_

// Hitech Compiler used
#define USE_HITECH_CC

// Board configuration file
#include "board_cfg.h"

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

// LED POV
void led_pov_init(void);

// Main
static void osc_init(void);

#endif	/* !_BEACON_TUD_H_ */

