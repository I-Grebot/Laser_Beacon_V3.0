/* -----------------------------------------------------------------------------
 * I-Grebot 2013
 * Robot System Library
 * -----------------------------------------------------------------------------
 * File        : robot_system.h
 * Language    : C
 * Author      : Paul M.
 * Date        : 2012-04-14
 * -----------------------------------------------------------------------------
 * Description
 *  This file defines constants and macro which are used across all the
 *  Igrebot boards. One typical example are flags present in CAN payload, but
 *  other main characteristics are present like number of sensors, etc.
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 933                                                                  $
 * $LastChangedBy:: sebastien.brulais                                          $
 * $LastChangedDate:: 2013-05-18 09:38:07 +0200 (sam., 18 mai 2013)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-04-14
 * -----------------------------------------------------------------------------
 */

#ifndef _ROBOT_SYSTEM_H_
#define _ROBOT_SYSTEM_H_

/*
 * Robot Mechanics and Structural definitions
 * ==========================================
 */

// Number of ultrasonic sensors
#define ROBOT_SENSOR_NB_ULTRASONIC 1

// Number of Osiris sensors
#define ROBOT_SENSOR_NB_OSIRIS 4


/*
 * General CAN Related Constants
 * =============================
 */

// Nodes ID
// --------

#define CAN_NB_SLAVE_NODE 5

// Slave nodes ID must be consecutive from 0x00
#define CAN_NODE_ID_IGRESUPPLY  0x00
#define CAN_NODE_ID_IGRESIVE    0x01
#define CAN_NODE_ID_IGREVATOR_A 0x02
#define CAN_NODE_ID_IGREVATOR_B 0x03
#define CAN_NODE_ID_BEACON_BTX  0x04

// Special or Master nodes (not handled by Raspi)
#define CAN_NODE_ID_IGRASPI     0x80
#define CAN_NODE_ID_IGREPLANE   0x81

// Reserved for nodes which don't want ID or
// when we don't know the ID
#define CAN_NODE_ID_UNDEFINED	0xFF 

// Nodes general state definition
// ------------------------------

// There are 2 common states for all nodes for quick check
#define CAN_NODE_STATE_READY 0x00 // Setup is finished, ready to operate
#define CAN_NODE_STATE_ERROR 0xFF // At least 1 error occured

// Other values can be used if one want to get a more detailled status

// BEACON_BTX
#define CAN_NODE_STATE_BEACON_BTX_IDLE  0x01 // After reset state, inits are in progress
#define CAN_NODE_STATE_BEACON_BTX_RUN   0x02 // System is operating normally

/*
 * CAN Payload fields definition
 * =============================
 */

// blower_* contets
// ----------------

#define CAN_ACTUATORS_BLOWER_CANDLE_UP   2
#define CAN_ACTUATORS_BLOWER_CANDLE_DN   1
#define CAN_ACTUATORS_BLOWER_CANDLE_IDLE 0


// loader grab 
// -----------

#define CAN_ACTUATORS_LOADER_GRAB_UP   2
#define CAN_ACTUATORS_LOADER_GRAB_GIFT 1
#define CAN_ACTUATORS_LOADER_GRAB_DN   0

// avoidance_osiris contents
// -------------------------

// detection
#define CAN_AVOIDANCE_OSIRIS_DETECTION_MASK_FL  0x01    // Mask for Front-Left  sensor
#define CAN_AVOIDANCE_OSIRIS_DETECTION_MASK_FR  0x02    // Mask for Front-Right sensor
#define CAN_AVOIDANCE_OSIRIS_DETECTION_MASK_RL  0x04    // Mask for Rear-Left   sensor
#define CAN_AVOIDANCE_OSIRIS_DETECTION_MASK_RR  0x08    // Mask for Rear-Right  sensor

#define CAN_AVOIDANCE_OSIRIS_DETECTION_SHIFT_FL    0
#define CAN_AVOIDANCE_OSIRIS_DETECTION_SHIFT_FR    1
#define CAN_AVOIDANCE_OSIRIS_DETECTION_SHIFT_RL    2
#define CAN_AVOIDANCE_OSIRIS_DETECTION_SHIFT_RR    3

// left/right/cherry_color contents
// --------------------------------

#define CAN_SENSOR_COLOR_BLACK          0x00 // Nothing or black color is sensed
#define CAN_SENSOR_COLOR_RED            0x01 // Red   is present in the sensed color
#define CAN_SENSOR_COLOR_GREEN          0x02 // Green is present in the sensed color
#define CAN_SENSOR_COLOR_BLUE           0x04 // Blue  is present in the sensed color

#define CAN_SENSOR_COLOR_CYAN    (CAN_SENSOR_COLOR_GREEN | CAN_SENSOR_COLOR_BLUE)
#define CAN_SENSOR_COLOR_MAGENTA (CAN_SENSOR_COLOR_RED   | CAN_SENSOR_COLOR_BLUE)
#define CAN_SENSOR_COLOR_YELLOW  (CAN_SENSOR_COLOR_RED   | CAN_SENSOR_COLOR_GREEN)

#define CAN_SENSOR_COLOR_WHITE   (CAN_SENSOR_COLOR_RED | CAN_SENSOR_COLOR_GREEN | CAN_SENSOR_COLOR_BLUE)

// system_match contents
// ---------------------

// state
#define CAN_SYSTEM_MATCH_STATE_IDLE      0x00 // Idle (after reset): all systems are OFF but logic
#define CAN_SYSTEM_MATCH_STATE_SETUP     0x01 // Setup, systems are getting prepared, bist are launched
#define CAN_SYSTEM_MATCH_STATE_READY     0x02 // Ready, once all systems are setup and waiting for start
#define CAN_SYSTEM_MATCH_STATE_RUN       0x03 // Match is running... go,go !
#define CAN_SYSTEM_MATCH_STATE_RUN_FUN   0x04 // Match is almost finished, funny action started!
#define CAN_SYSTEM_MATCH_STATE_FINISH    0x05 // Match is finished: systems go OFF
#define CAN_SYSTEM_MATCH_STATE_EMERGENCY 0x06 // Finished because of emergency button was pushed! Abort everything

// color
#define CAN_SYSTEM_MATCH_COLOR_BLUE      0x00
#define CAN_SYSTEM_MATCH_COLOR_RED       0x01
#define CAN_SYSTEM_MATCH_COLOR_UNDEFINED 0xFF // Undefined color (we are not sure yet)

// timestamp
#define CAN_SYSTEM_MATCH_RUN_LENGTH       890
#define CAN_SYSTEM_MATCH_RUN_FUN_LENGTH  1000

#endif /* _ROBOT_SYSTEM_H_ */

