#ifndef _IGREBOT_CAN_H_
#define _IGREBOT_CAN_H_

#ifndef __arm__
#include "board_cfg.h"
#else
#include "arm_cfg.h"
#endif // __arm__

/* CAN Category ID Definition */
#define CAN_CID_SUPPLY 0x000
#define CAN_CID_AVOIDANCE 0x020
#define CAN_CID_BEACON 0x040
#define CAN_CID_MOTION 0x060
#define CAN_CID_ACTUATORS 0x080
#define CAN_CID_SENSORS 0x0A0
#define CAN_CID_SYSTEM 0x100
#define CAN_CID_BOOT 0x1C0
#define CAN_CID_DEBUG 0x1E0

/* CAN Frame ID Definition */
#define CAN_FID_SUPPLY_STATUS 0x000
#define CAN_FID_SUPPLY_COMMAND 0x001
#define CAN_FID_AVOIDANCE_OSIRIS 0x020
#define CAN_FID_AVOIDANCE_ULTRASONIC 0x021
#define CAN_FID_BEACON_STATUS 0x040
#define CAN_FID_BEACON_COMMAND 0x041
#define CAN_FID_BEACON_OPPONENT_1_ABS 0x042
#define CAN_FID_BEACON_OPPONENT_1_REL 0x043
#define CAN_FID_BEACON_OPPONENT_2_ABS 0x044
#define CAN_FID_BEACON_OPPONENT_2_REL 0x045
#define CAN_FID_BEACON_ROBOT_ABS 0x046
#define CAN_FID_MOTION_FB_STATUS 0x060
#define CAN_FID_MOTION_FB_POSITION 0x061
#define CAN_FID_MOTION_FB_SPEED 0x062
#define CAN_FID_MOTION_FB_ACCELERATION 0x063
#define CAN_FID_MOTION_PARAM_SPEED 0x064
#define CAN_FID_MOTION_PARAM_ACCEL 0x065
#define CAN_FID_MOTION_COMMAND 0x066
#define CAN_FID_MOTION_GOTO 0x067
#define CAN_FID_MOTION_SET_SPEED 0x068
#define CAN_FID_MOTION_MOVE_RELATIVE 0x069
#define CAN_FID_MOTION_MOVE_FORWARD 0x06A
#define CAN_FID_MOTION_MOVE_BACKWARD 0x06B
#define CAN_FID_MOTION_TURN_RIGHT 0x06C
#define CAN_FID_MOTION_TURN_LEFT 0x06D
#define CAN_FID_ACTUATORS_BLOWER_LEFT 0x080
#define CAN_FID_ACTUATORS_BLOWER_RIGHT 0x081
#define CAN_FID_ACTUATORS_LOADER 0x082
#define CAN_FID_ACTUATORS_LAUNCHER 0x083
#define CAN_FID_ACTUATORS_DEFLECTOR 0x084
#define CAN_FID_ACTUATORS_PUMP 0x085
#define CAN_FID_SENSORS_LEFT_COLOR 0x0A0
#define CAN_FID_SENSORS_RIGHT_COLOR 0x0A1
#define CAN_FID_SENSORS_CHERRY_COLOR 0x0A2
#define CAN_FID_SENSORS_PLATE 0x0A3
#define CAN_FID_SYSTEM_STATUS 0x100
#define CAN_FID_SYSTEM_MATCH 0x101
#define CAN_FID_SYSTEM_BIST_LAUNCH 0x102
#define CAN_FID_SYSTEM_BIST_STATUS 0x103
#define CAN_FID_BOOT_NODE_0 0x1C0
#define CAN_FID_BOOT_NODE_1 0x1C1
#define CAN_FID_BOOT_NODE_2 0x1C2
#define CAN_FID_BOOT_NODE_3 0x1C3
#define CAN_FID_BOOT_NODE_4 0x1C4
#define CAN_FID_BOOT_NODE_5 0x1C5
#define CAN_FID_BOOT_NODE_6 0x1C6
#define CAN_FID_BOOT_NODE_7 0x1C7
#define CAN_FID_DEBUG_PRINTF 0x1E0

/* CAN Messages Lengths (DLC) */
#define CAN_DLC_SUPPLY_STATUS 5
#define CAN_DLC_SUPPLY_COMMAND 1
#define CAN_DLC_AVOIDANCE_OSIRIS 1
#define CAN_DLC_AVOIDANCE_ULTRASONIC 2
#define CAN_DLC_BEACON_STATUS 3
#define CAN_DLC_BEACON_COMMAND 1
#define CAN_DLC_BEACON_OPPONENT_1_ABS 6
#define CAN_DLC_BEACON_OPPONENT_1_REL 4
#define CAN_DLC_BEACON_OPPONENT_2_ABS 6
#define CAN_DLC_BEACON_OPPONENT_2_REL 4
#define CAN_DLC_BEACON_ROBOT_ABS 6
#define CAN_DLC_MOTION_FB_STATUS 3
#define CAN_DLC_MOTION_FB_POSITION 6
#define CAN_DLC_MOTION_FB_SPEED 4
#define CAN_DLC_MOTION_FB_ACCELERATION 4
#define CAN_DLC_MOTION_PARAM_SPEED 8
#define CAN_DLC_MOTION_PARAM_ACCEL 6
#define CAN_DLC_MOTION_COMMAND 7
#define CAN_DLC_MOTION_GOTO 4
#define CAN_DLC_MOTION_SET_SPEED 4
#define CAN_DLC_MOTION_MOVE_RELATIVE 4
#define CAN_DLC_MOTION_MOVE_FORWARD 2
#define CAN_DLC_MOTION_MOVE_BACKWARD 2
#define CAN_DLC_MOTION_TURN_RIGHT 2
#define CAN_DLC_MOTION_TURN_LEFT 2
#define CAN_DLC_ACTUATORS_BLOWER_LEFT 2
#define CAN_DLC_ACTUATORS_BLOWER_RIGHT 2
#define CAN_DLC_ACTUATORS_LOADER 2
#define CAN_DLC_ACTUATORS_LAUNCHER 2
#define CAN_DLC_ACTUATORS_DEFLECTOR 1
#define CAN_DLC_ACTUATORS_PUMP 1
#define CAN_DLC_SENSORS_LEFT_COLOR 1
#define CAN_DLC_SENSORS_RIGHT_COLOR 1
#define CAN_DLC_SENSORS_CHERRY_COLOR 1
#define CAN_DLC_SENSORS_PLATE 1
#define CAN_DLC_SYSTEM_STATUS 2
#define CAN_DLC_SYSTEM_MATCH 6
#define CAN_DLC_SYSTEM_BIST_LAUNCH 1
#define CAN_DLC_SYSTEM_BIST_STATUS 3
#define CAN_DLC_BOOT_NODE_0 8
#define CAN_DLC_BOOT_NODE_1 8
#define CAN_DLC_BOOT_NODE_2 8
#define CAN_DLC_BOOT_NODE_3 8
#define CAN_DLC_BOOT_NODE_4 8
#define CAN_DLC_BOOT_NODE_5 8
#define CAN_DLC_BOOT_NODE_6 8
#define CAN_DLC_BOOT_NODE_7 8
#define CAN_DLC_DEBUG_PRINTF 8

/* CAN Recurent-messages Frequency values */
#define CAN_FREQ_SUPPLY_STATUS 20
#define CAN_FREQ_AVOIDANCE_OSIRIS 20
#define CAN_FREQ_AVOIDANCE_ULTRASONIC 20
#define CAN_FREQ_BEACON_STATUS 5
#define CAN_FREQ_BEACON_OPPONENT_1_ABS 10
#define CAN_FREQ_BEACON_OPPONENT_1_REL 10
#define CAN_FREQ_BEACON_OPPONENT_2_ABS 10
#define CAN_FREQ_BEACON_OPPONENT_2_REL 10
#define CAN_FREQ_BEACON_ROBOT_ABS 5
#define CAN_FREQ_MOTION_FB_STATUS 20
#define CAN_FREQ_MOTION_FB_POSITION 10
#define CAN_FREQ_MOTION_FB_SPEED 10
#define CAN_FREQ_MOTION_FB_ACCELERATION 10
#define CAN_FREQ_SENSORS_LEFT_COLOR 5
#define CAN_FREQ_SENSORS_RIGHT_COLOR 5
#define CAN_FREQ_SENSORS_CHERRY_COLOR 5
#define CAN_FREQ_SENSORS_PLATE 5
#define CAN_FREQ_SYSTEM_STATUS 1

/* CAN Payload bitfields definition */
typedef union {

  struct {
    uint8_t fault;
    uint16_t battery_voltage;
    uint8_t fuses_state;
    uint8_t emergency_stop;
  } supply_status;

  struct {
    uint8_t shutdown;
  } supply_command;

  struct {
    uint8_t detection;
  } avoidance_osiris;

  struct {
    uint8_t dist_0;
    uint8_t dist_1;
  } avoidance_ultrasonic;

  struct {
    uint8_t errors;
    uint16_t turret;
  } beacon_status;

  struct {
    uint8_t turret;
  } beacon_command;

  struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t pos_a;
  } beacon_opponent_1_abs;

  struct {
    uint16_t pos_d;
    uint16_t pos_a;
  } beacon_opponent_1_rel;

  struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t pos_a;
  } beacon_opponent_2_abs;

  struct {
    uint16_t pos_d;
    uint16_t pos_a;
  } beacon_opponent_2_rel;

  struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t pos_a;
  } beacon_robot_abs;

  struct {
    uint8_t lock;
    uint8_t trajectory_near;
    uint8_t trajectory_finished;
  } motion_fb_status;

  struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t pos_a;
  } motion_fb_position;

  struct {
    uint16_t speed_d;
    uint16_t speed_a;
  } motion_fb_speed;

  struct {
    uint16_t accel_d;
    uint16_t accel_a;
  } motion_fb_acceleration;

  struct {
    uint16_t speed_pos_max_d;
    uint16_t speed_neg_max_d;
    uint16_t speed_pos_max_a;
    uint16_t speed_neg_max_a;
  } motion_param_speed;

  struct {
    uint16_t accel_max_d;
    uint16_t accel_max_a;
    uint16_t deccel_max_d;
    uint16_t deccel_max_a;
  } motion_param_accel;

  struct {
    uint8_t lock;
    uint8_t stall;
    uint16_t pos_reset_x;
    uint16_t pos_reset_y;
    uint8_t trajectory_stop;
  } motion_command;

  struct {
    uint16_t pos_x;
    uint16_t pos_y;
  } motion_goto;

  struct {
    uint16_t speed_d;
    uint16_t speed_a;
  } motion_set_speed;

  struct {
    uint16_t pos_rel_d;
    uint16_t pos_rel_a;
  } motion_move_relative;

  struct {
    uint16_t pos_fwd_d;
  } motion_move_forward;

  struct {
    uint16_t pos_bwd_d;
  } motion_move_backward;

  struct {
    uint16_t pos_r_a;
  } motion_turn_right;

  struct {
    uint16_t pos_l_a;
  } motion_turn_left;

  struct {
    uint8_t position;
    uint8_t speed;
  } actuators_blower_left;

  struct {
    uint8_t position;
    uint8_t speed;
  } actuators_blower_right;

  struct {
    uint8_t lift;
    uint8_t grab;
  } actuators_loader;

  struct {
    uint16_t speed;
  } actuators_launcher;

  struct {
    uint8_t deflect;
  } actuators_deflector;

  struct {
    uint8_t pump;
  } actuators_pump;

  struct {
    uint8_t color;
  } sensors_left_color;

  struct {
    uint8_t color;
  } sensors_right_color;

  struct {
    uint8_t color;
  } sensors_cherry_color;

  struct {
    uint8_t presence;
  } sensors_plate;

  struct {
    uint8_t node;
    uint8_t state;
  } system_status;

  struct {
    uint8_t state;
    uint8_t color;
    uint16_t points;
    uint16_t timestamp;
  } system_match;

  struct {
    uint8_t node;
  } system_bist_launch;

  struct {
    uint8_t node;
    uint16_t status;
  } system_bist_status;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_0;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_1;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_2;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_3;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_4;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_5;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_6;

  struct {
    uint8_t boot_cmd;
    uint8_t boot_data[7];
  } boot_node_7;

  struct {
    uint8_t node;
    uint8_t data[7];
  } debug_printf;

} payload_t;

#endif /* _IGREBOT_CAN_H_ */

