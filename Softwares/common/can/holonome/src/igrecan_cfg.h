#ifndef _IGREBOT_CAN_H_
#define _IGREBOT_CAN_H_

#include "board_cfg.h"

/* CAN Category ID Definition */
#define CAN_CID_SUPPLY 0x000
#define CAN_CID_AVOIDANCE 0x020
#define CAN_CID_BEACON 0x040
#define CAN_CID_MOTION 0x060
#define CAN_CID_ACTUATORS 0x080
#define CAN_CID_ROBOT 0x0A0
#define CAN_CID_SYSTEM 0x0C0
#define CAN_CID_BOOT 0x1C0

/* CAN Frame ID Definition */
#define CAN_FID_SUPPLY_STATUS 0x000
#define CAN_FID_SUPPLY_COMMAND 0x001
#define CAN_FID_AVOIDANCE_CORNER_1 0x020
#define CAN_FID_AVOIDANCE_CORNER_2 0x021
#define CAN_FID_AVOIDANCE_CORNER_3 0x022
#define CAN_FID_BEACON_OPPONENT 0x040
#define CAN_FID_MOTION_FB_WHEEL_1 0x060
#define CAN_FID_MOTION_FB_WHEEL_2 0x061
#define CAN_FID_MOTION_FB_WHEEL_3 0x062
#define CAN_FID_MOTION_FB_MOTOR_1 0x063
#define CAN_FID_MOTION_FB_MOTOR_2 0x064
#define CAN_FID_MOTION_FB_MOTOR_3 0x065
#define CAN_FID_MOTION_PARAM_SPEED 0x066
#define CAN_FID_ACTUATORS_COMMAND 0x080
#define CAN_FID_ROBOT_POSITION 0x0A0
#define CAN_FID_ROBOT_SPEED 0x0A1
#define CAN_FID_ROBOT_ACCELERATION 0x0A2
#define CAN_FID_SYSTEM_SYNC 0x0C0
#define CAN_FID_SYSTEM_BIST_LAUNCH 0x0C1
#define CAN_FID_BOOT_NODE_0 0x1C0
#define CAN_FID_BOOT_NODE_1 0x1C1
#define CAN_FID_BOOT_NODE_2 0x1C2
#define CAN_FID_BOOT_NODE_3 0x1C3
#define CAN_FID_BOOT_NODE_4 0x1C4
#define CAN_FID_BOOT_NODE_5 0x1C5
#define CAN_FID_BOOT_NODE_6 0x1C6
#define CAN_FID_BOOT_NODE_7 0x1C7

/* CAN Messages Lengths (DLC) */
#define CAN_DLC_SUPPLY_STATUS 4
#define CAN_DLC_SUPPLY_COMMAND 1
#define CAN_DLC_AVOIDANCE_CORNER_1 8
#define CAN_DLC_AVOIDANCE_CORNER_2 8
#define CAN_DLC_AVOIDANCE_CORNER_3 8
#define CAN_DLC_BEACON_OPPONENT 6
#define CAN_DLC_MOTION_FB_WHEEL_1 2
#define CAN_DLC_MOTION_FB_WHEEL_2 2
#define CAN_DLC_MOTION_FB_WHEEL_3 2
#define CAN_DLC_MOTION_FB_MOTOR_1 3
#define CAN_DLC_MOTION_FB_MOTOR_2 3
#define CAN_DLC_MOTION_FB_MOTOR_3 3
#define CAN_DLC_MOTION_PARAM_SPEED 6
#define CAN_DLC_ACTUATORS_COMMAND 6
#define CAN_DLC_ROBOT_POSITION 6
#define CAN_DLC_ROBOT_SPEED 6
#define CAN_DLC_ROBOT_ACCELERATION 6
#define CAN_DLC_SYSTEM_SYNC 2
#define CAN_DLC_SYSTEM_BIST_LAUNCH 1
#define CAN_DLC_BOOT_NODE_0 8
#define CAN_DLC_BOOT_NODE_1 8
#define CAN_DLC_BOOT_NODE_2 8
#define CAN_DLC_BOOT_NODE_3 8
#define CAN_DLC_BOOT_NODE_4 8
#define CAN_DLC_BOOT_NODE_5 8
#define CAN_DLC_BOOT_NODE_6 8
#define CAN_DLC_BOOT_NODE_7 8

/* CAN Recurent-messages Frequency values */
#define CAN_FREQ_SUPPLY_STATUS 20
#define CAN_FREQ_AVOIDANCE_CORNER_1 5
#define CAN_FREQ_AVOIDANCE_CORNER_2 5
#define CAN_FREQ_AVOIDANCE_CORNER_3 5
#define CAN_FREQ_BEACON_OPPONENT 5
#define CAN_FREQ_MOTION_FB_WHEEL_1 20
#define CAN_FREQ_MOTION_FB_WHEEL_2 20
#define CAN_FREQ_MOTION_FB_WHEEL_3 20
#define CAN_FREQ_MOTION_FB_MOTOR_1 5
#define CAN_FREQ_MOTION_FB_MOTOR_2 5
#define CAN_FREQ_MOTION_FB_MOTOR_3 5
#define CAN_FREQ_MOTION_PARAM_SPEED 20
#define CAN_FREQ_ROBOT_POSITION 20
#define CAN_FREQ_ROBOT_SPEED 5
#define CAN_FREQ_ROBOT_ACCELERATION 5

/* CAN Payload bitfields definition */
typedef union {

  struct {
    uint8_t fault;
    uint16_t battery_voltage;
    uint8_t emergency_stop;
  } supply_status;

  struct {
    uint8_t shutdown;
  } supply_command;

  struct {
    uint16_t sharps1;
    uint16_t sharps2;
    uint16_t sharps3;
    uint16_t us;
  } avoidance_corner_1;

  struct {
    uint16_t sharps1;
    uint16_t sharps2;
    uint16_t sharps3;
    uint16_t us;
  } avoidance_corner_2;

  struct {
    uint16_t sharps1;
    uint16_t sharps2;
    uint16_t sharps3;
    uint16_t us;
  } avoidance_corner_3;

  struct {
    uint8_t opponent_main_pos_x;
    uint8_t opponent_main_pos_y;
    uint8_t opponent_main_pos_a;
    uint8_t opponent_second_pos_x;
    uint8_t opponent_second_pos_y;
    uint8_t opponent_second_pos_a;
  } beacon_opponent;

  struct {
    uint8_t pos_x;
    uint8_t pos_y;
  } motion_fb_wheel_1;

  struct {
    uint8_t pos_x;
    uint8_t pos_y;
  } motion_fb_wheel_2;

  struct {
    uint8_t pos_x;
    uint8_t pos_y;
  } motion_fb_wheel_3;

  struct {
    uint16_t motor_speed;
    uint8_t fault;
  } motion_fb_motor_1;

  struct {
    uint16_t motor_speed;
    uint8_t fault;
  } motion_fb_motor_2;

  struct {
    uint16_t motor_speed;
    uint8_t fault;
  } motion_fb_motor_3;

  struct {
    uint16_t motor1_speed;
    uint16_t motor2_speed;
    uint16_t motor3_speed;
  } motion_param_speed;

  struct {
    uint8_t load;
    uint8_t unload;
    uint8_t lift_left;
    uint8_t lift_right;
    uint8_t arm_left;
    uint8_t arm_right;
  } actuators_command;

  struct {
    uint16_t x;
    uint16_t y;
    uint16_t a;
  } robot_position;

  struct {
    uint16_t x;
    uint16_t y;
    uint16_t a;
  } robot_speed;

  struct {
    uint16_t x;
    uint16_t y;
    uint16_t a;
  } robot_acceleration;

  struct {
    uint16_t timestamp;
  } system_sync;

  struct {
    uint8_t node;
  } system_bist_launch;

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

} payload_t;

#endif /* _IGREBOT_CAN_H_ */

