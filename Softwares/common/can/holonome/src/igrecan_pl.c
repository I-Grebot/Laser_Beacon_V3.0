#include "igrecan.h"

/* CAN Payload Set functions */

inline void can_get_pl_supply_status(can_msg_t* msg, payload_t* pl) {
  pl->supply_status.fault = msg->payload[0]; 
  pl->supply_status.battery_voltage = msg->payload[1] + (msg->payload[2]<<8); 
  pl->supply_status.emergency_stop = msg->payload[4]; 
}

inline void can_get_pl_supply_command(can_msg_t* msg, payload_t* pl) {
  pl->supply_command.shutdown = msg->payload[0]; 
}

inline void can_get_pl_avoidance_corner_1(can_msg_t* msg, payload_t* pl) {
  pl->avoidance_corner_1.sharps1 = msg->payload[0] + (msg->payload[1]<<8); 
  pl->avoidance_corner_1.sharps2 = msg->payload[2] + (msg->payload[3]<<8); 
  pl->avoidance_corner_1.sharps3 = msg->payload[4] + (msg->payload[5]<<8); 
  pl->avoidance_corner_1.us = msg->payload[6] + (msg->payload[7]<<8); 
}

inline void can_get_pl_avoidance_corner_2(can_msg_t* msg, payload_t* pl) {
  pl->avoidance_corner_2.sharps1 = msg->payload[0] + (msg->payload[1]<<8); 
  pl->avoidance_corner_2.sharps2 = msg->payload[2] + (msg->payload[3]<<8); 
  pl->avoidance_corner_2.sharps3 = msg->payload[4] + (msg->payload[5]<<8); 
  pl->avoidance_corner_2.us = msg->payload[6] + (msg->payload[7]<<8); 
}

inline void can_get_pl_avoidance_corner_3(can_msg_t* msg, payload_t* pl) {
  pl->avoidance_corner_3.sharps1 = msg->payload[0] + (msg->payload[1]<<8); 
  pl->avoidance_corner_3.sharps2 = msg->payload[2] + (msg->payload[3]<<8); 
  pl->avoidance_corner_3.sharps3 = msg->payload[4] + (msg->payload[5]<<8); 
  pl->avoidance_corner_3.us = msg->payload[6] + (msg->payload[7]<<8); 
}

inline void can_get_pl_beacon_opponent(can_msg_t* msg, payload_t* pl) {
  pl->beacon_opponent.opponent_main_pos_x = msg->payload[0]; 
  pl->beacon_opponent.opponent_main_pos_y = msg->payload[1]; 
  pl->beacon_opponent.opponent_main_pos_a = msg->payload[2]; 
  pl->beacon_opponent.opponent_second_pos_x = msg->payload[3]; 
  pl->beacon_opponent.opponent_second_pos_y = msg->payload[4]; 
  pl->beacon_opponent.opponent_second_pos_a = msg->payload[5]; 
}

inline void can_get_pl_motion_fb_wheel_1(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_wheel_1.pos_x = msg->payload[0]; 
  pl->motion_fb_wheel_1.pos_y = msg->payload[1]; 
}

inline void can_get_pl_motion_fb_wheel_2(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_wheel_2.pos_x = msg->payload[0]; 
  pl->motion_fb_wheel_2.pos_y = msg->payload[1]; 
}

inline void can_get_pl_motion_fb_wheel_3(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_wheel_3.pos_x = msg->payload[0]; 
  pl->motion_fb_wheel_3.pos_y = msg->payload[1]; 
}

inline void can_get_pl_motion_fb_motor_1(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_motor_1.motor_speed = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_motor_1.fault = msg->payload[2]; 
}

inline void can_get_pl_motion_fb_motor_2(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_motor_2.motor_speed = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_motor_2.fault = msg->payload[2]; 
}

inline void can_get_pl_motion_fb_motor_3(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_motor_3.motor_speed = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_motor_3.fault = msg->payload[2]; 
}

inline void can_get_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) {
  pl->motion_param_speed.motor1_speed = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_param_speed.motor2_speed = msg->payload[2] + (msg->payload[3]<<8); 
  pl->motion_param_speed.motor3_speed = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_actuators_command(can_msg_t* msg, payload_t* pl) {
  pl->actuators_command.load = msg->payload[0]; 
  pl->actuators_command.unload = msg->payload[1]; 
  pl->actuators_command.lift_left = msg->payload[2]; 
  pl->actuators_command.lift_right = msg->payload[3]; 
  pl->actuators_command.arm_left = msg->payload[4]; 
  pl->actuators_command.arm_right = msg->payload[5]; 
}

inline void can_get_pl_robot_position(can_msg_t* msg, payload_t* pl) {
  pl->robot_position.x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->robot_position.y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->robot_position.a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_robot_speed(can_msg_t* msg, payload_t* pl) {
  pl->robot_speed.x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->robot_speed.y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->robot_speed.a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_robot_acceleration(can_msg_t* msg, payload_t* pl) {
  pl->robot_acceleration.x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->robot_acceleration.y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->robot_acceleration.a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_system_sync(can_msg_t* msg, payload_t* pl) {
  pl->system_sync.timestamp = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) {
  pl->system_bist_launch.node = msg->payload[0]; 
}

inline void can_get_pl_boot_node_0(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_0.boot_cmd = msg->payload[0]; 
  pl->boot_node_0.boot_data[0] = msg->payload[1]; 
  pl->boot_node_0.boot_data[1] = msg->payload[2]; 
  pl->boot_node_0.boot_data[2] = msg->payload[3]; 
  pl->boot_node_0.boot_data[3] = msg->payload[4]; 
  pl->boot_node_0.boot_data[4] = msg->payload[5]; 
  pl->boot_node_0.boot_data[5] = msg->payload[6]; 
  pl->boot_node_0.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_1(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_1.boot_cmd = msg->payload[0]; 
  pl->boot_node_1.boot_data[0] = msg->payload[1]; 
  pl->boot_node_1.boot_data[1] = msg->payload[2]; 
  pl->boot_node_1.boot_data[2] = msg->payload[3]; 
  pl->boot_node_1.boot_data[3] = msg->payload[4]; 
  pl->boot_node_1.boot_data[4] = msg->payload[5]; 
  pl->boot_node_1.boot_data[5] = msg->payload[6]; 
  pl->boot_node_1.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_2(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_2.boot_cmd = msg->payload[0]; 
  pl->boot_node_2.boot_data[0] = msg->payload[1]; 
  pl->boot_node_2.boot_data[1] = msg->payload[2]; 
  pl->boot_node_2.boot_data[2] = msg->payload[3]; 
  pl->boot_node_2.boot_data[3] = msg->payload[4]; 
  pl->boot_node_2.boot_data[4] = msg->payload[5]; 
  pl->boot_node_2.boot_data[5] = msg->payload[6]; 
  pl->boot_node_2.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_3(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_3.boot_cmd = msg->payload[0]; 
  pl->boot_node_3.boot_data[0] = msg->payload[1]; 
  pl->boot_node_3.boot_data[1] = msg->payload[2]; 
  pl->boot_node_3.boot_data[2] = msg->payload[3]; 
  pl->boot_node_3.boot_data[3] = msg->payload[4]; 
  pl->boot_node_3.boot_data[4] = msg->payload[5]; 
  pl->boot_node_3.boot_data[5] = msg->payload[6]; 
  pl->boot_node_3.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_4(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_4.boot_cmd = msg->payload[0]; 
  pl->boot_node_4.boot_data[0] = msg->payload[1]; 
  pl->boot_node_4.boot_data[1] = msg->payload[2]; 
  pl->boot_node_4.boot_data[2] = msg->payload[3]; 
  pl->boot_node_4.boot_data[3] = msg->payload[4]; 
  pl->boot_node_4.boot_data[4] = msg->payload[5]; 
  pl->boot_node_4.boot_data[5] = msg->payload[6]; 
  pl->boot_node_4.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_5(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_5.boot_cmd = msg->payload[0]; 
  pl->boot_node_5.boot_data[0] = msg->payload[1]; 
  pl->boot_node_5.boot_data[1] = msg->payload[2]; 
  pl->boot_node_5.boot_data[2] = msg->payload[3]; 
  pl->boot_node_5.boot_data[3] = msg->payload[4]; 
  pl->boot_node_5.boot_data[4] = msg->payload[5]; 
  pl->boot_node_5.boot_data[5] = msg->payload[6]; 
  pl->boot_node_5.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_6(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_6.boot_cmd = msg->payload[0]; 
  pl->boot_node_6.boot_data[0] = msg->payload[1]; 
  pl->boot_node_6.boot_data[1] = msg->payload[2]; 
  pl->boot_node_6.boot_data[2] = msg->payload[3]; 
  pl->boot_node_6.boot_data[3] = msg->payload[4]; 
  pl->boot_node_6.boot_data[4] = msg->payload[5]; 
  pl->boot_node_6.boot_data[5] = msg->payload[6]; 
  pl->boot_node_6.boot_data[6] = msg->payload[7]; 
}

inline void can_get_pl_boot_node_7(can_msg_t* msg, payload_t* pl) {
  pl->boot_node_7.boot_cmd = msg->payload[0]; 
  pl->boot_node_7.boot_data[0] = msg->payload[1]; 
  pl->boot_node_7.boot_data[1] = msg->payload[2]; 
  pl->boot_node_7.boot_data[2] = msg->payload[3]; 
  pl->boot_node_7.boot_data[3] = msg->payload[4]; 
  pl->boot_node_7.boot_data[4] = msg->payload[5]; 
  pl->boot_node_7.boot_data[5] = msg->payload[6]; 
  pl->boot_node_7.boot_data[6] = msg->payload[7]; 
}

/* CAN Payload Get functions */

inline void can_set_pl_supply_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->supply_status.fault;
  msg->payload[1] = pl->supply_status.battery_voltage & 0xFF;
  msg->payload[2] = pl->supply_status.battery_voltage >> 8;
  msg->payload[4] = pl->supply_status.emergency_stop;
}

inline void can_set_pl_supply_command(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->supply_command.shutdown;
}

inline void can_set_pl_avoidance_corner_1(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->avoidance_corner_1.sharps1 & 0xFF;
  msg->payload[1] = pl->avoidance_corner_1.sharps1 >> 8;
  msg->payload[2] = pl->avoidance_corner_1.sharps2 & 0xFF;
  msg->payload[3] = pl->avoidance_corner_1.sharps2 >> 8;
  msg->payload[4] = pl->avoidance_corner_1.sharps3 & 0xFF;
  msg->payload[5] = pl->avoidance_corner_1.sharps3 >> 8;
  msg->payload[6] = pl->avoidance_corner_1.us & 0xFF;
  msg->payload[7] = pl->avoidance_corner_1.us >> 8;
}

inline void can_set_pl_avoidance_corner_2(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->avoidance_corner_2.sharps1 & 0xFF;
  msg->payload[1] = pl->avoidance_corner_2.sharps1 >> 8;
  msg->payload[2] = pl->avoidance_corner_2.sharps2 & 0xFF;
  msg->payload[3] = pl->avoidance_corner_2.sharps2 >> 8;
  msg->payload[4] = pl->avoidance_corner_2.sharps3 & 0xFF;
  msg->payload[5] = pl->avoidance_corner_2.sharps3 >> 8;
  msg->payload[6] = pl->avoidance_corner_2.us & 0xFF;
  msg->payload[7] = pl->avoidance_corner_2.us >> 8;
}

inline void can_set_pl_avoidance_corner_3(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->avoidance_corner_3.sharps1 & 0xFF;
  msg->payload[1] = pl->avoidance_corner_3.sharps1 >> 8;
  msg->payload[2] = pl->avoidance_corner_3.sharps2 & 0xFF;
  msg->payload[3] = pl->avoidance_corner_3.sharps2 >> 8;
  msg->payload[4] = pl->avoidance_corner_3.sharps3 & 0xFF;
  msg->payload[5] = pl->avoidance_corner_3.sharps3 >> 8;
  msg->payload[6] = pl->avoidance_corner_3.us & 0xFF;
  msg->payload[7] = pl->avoidance_corner_3.us >> 8;
}

inline void can_set_pl_beacon_opponent(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_opponent.opponent_main_pos_x;
  msg->payload[1] = pl->beacon_opponent.opponent_main_pos_y;
  msg->payload[2] = pl->beacon_opponent.opponent_main_pos_a;
  msg->payload[3] = pl->beacon_opponent.opponent_second_pos_x;
  msg->payload[4] = pl->beacon_opponent.opponent_second_pos_y;
  msg->payload[5] = pl->beacon_opponent.opponent_second_pos_a;
}

inline void can_set_pl_motion_fb_wheel_1(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_wheel_1.pos_x;
  msg->payload[1] = pl->motion_fb_wheel_1.pos_y;
}

inline void can_set_pl_motion_fb_wheel_2(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_wheel_2.pos_x;
  msg->payload[1] = pl->motion_fb_wheel_2.pos_y;
}

inline void can_set_pl_motion_fb_wheel_3(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_wheel_3.pos_x;
  msg->payload[1] = pl->motion_fb_wheel_3.pos_y;
}

inline void can_set_pl_motion_fb_motor_1(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_motor_1.motor_speed & 0xFF;
  msg->payload[1] = pl->motion_fb_motor_1.motor_speed >> 8;
  msg->payload[2] = pl->motion_fb_motor_1.fault;
}

inline void can_set_pl_motion_fb_motor_2(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_motor_2.motor_speed & 0xFF;
  msg->payload[1] = pl->motion_fb_motor_2.motor_speed >> 8;
  msg->payload[2] = pl->motion_fb_motor_2.fault;
}

inline void can_set_pl_motion_fb_motor_3(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_motor_3.motor_speed & 0xFF;
  msg->payload[1] = pl->motion_fb_motor_3.motor_speed >> 8;
  msg->payload[2] = pl->motion_fb_motor_3.fault;
}

inline void can_set_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_param_speed.motor1_speed & 0xFF;
  msg->payload[1] = pl->motion_param_speed.motor1_speed >> 8;
  msg->payload[2] = pl->motion_param_speed.motor2_speed & 0xFF;
  msg->payload[3] = pl->motion_param_speed.motor2_speed >> 8;
  msg->payload[4] = pl->motion_param_speed.motor3_speed & 0xFF;
  msg->payload[5] = pl->motion_param_speed.motor3_speed >> 8;
}

inline void can_set_pl_actuators_command(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_command.load;
  msg->payload[1] = pl->actuators_command.unload;
  msg->payload[2] = pl->actuators_command.lift_left;
  msg->payload[3] = pl->actuators_command.lift_right;
  msg->payload[4] = pl->actuators_command.arm_left;
  msg->payload[5] = pl->actuators_command.arm_right;
}

inline void can_set_pl_robot_position(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->robot_position.x & 0xFF;
  msg->payload[1] = pl->robot_position.x >> 8;
  msg->payload[2] = pl->robot_position.y & 0xFF;
  msg->payload[3] = pl->robot_position.y >> 8;
  msg->payload[4] = pl->robot_position.a & 0xFF;
  msg->payload[5] = pl->robot_position.a >> 8;
}

inline void can_set_pl_robot_speed(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->robot_speed.x & 0xFF;
  msg->payload[1] = pl->robot_speed.x >> 8;
  msg->payload[2] = pl->robot_speed.y & 0xFF;
  msg->payload[3] = pl->robot_speed.y >> 8;
  msg->payload[4] = pl->robot_speed.a & 0xFF;
  msg->payload[5] = pl->robot_speed.a >> 8;
}

inline void can_set_pl_robot_acceleration(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->robot_acceleration.x & 0xFF;
  msg->payload[1] = pl->robot_acceleration.x >> 8;
  msg->payload[2] = pl->robot_acceleration.y & 0xFF;
  msg->payload[3] = pl->robot_acceleration.y >> 8;
  msg->payload[4] = pl->robot_acceleration.a & 0xFF;
  msg->payload[5] = pl->robot_acceleration.a >> 8;
}

inline void can_set_pl_system_sync(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_sync.timestamp & 0xFF;
  msg->payload[1] = pl->system_sync.timestamp >> 8;
}

inline void can_set_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_bist_launch.node;
}

inline void can_set_pl_boot_node_0(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_0.boot_cmd;
  msg->payload[1] = pl->boot_node_0.boot_data[0];
  msg->payload[2] = pl->boot_node_0.boot_data[1];
  msg->payload[3] = pl->boot_node_0.boot_data[2];
  msg->payload[4] = pl->boot_node_0.boot_data[3];
  msg->payload[5] = pl->boot_node_0.boot_data[4];
  msg->payload[6] = pl->boot_node_0.boot_data[5];
  msg->payload[7] = pl->boot_node_0.boot_data[6];
}

inline void can_set_pl_boot_node_1(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_1.boot_cmd;
  msg->payload[1] = pl->boot_node_1.boot_data[0];
  msg->payload[2] = pl->boot_node_1.boot_data[1];
  msg->payload[3] = pl->boot_node_1.boot_data[2];
  msg->payload[4] = pl->boot_node_1.boot_data[3];
  msg->payload[5] = pl->boot_node_1.boot_data[4];
  msg->payload[6] = pl->boot_node_1.boot_data[5];
  msg->payload[7] = pl->boot_node_1.boot_data[6];
}

inline void can_set_pl_boot_node_2(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_2.boot_cmd;
  msg->payload[1] = pl->boot_node_2.boot_data[0];
  msg->payload[2] = pl->boot_node_2.boot_data[1];
  msg->payload[3] = pl->boot_node_2.boot_data[2];
  msg->payload[4] = pl->boot_node_2.boot_data[3];
  msg->payload[5] = pl->boot_node_2.boot_data[4];
  msg->payload[6] = pl->boot_node_2.boot_data[5];
  msg->payload[7] = pl->boot_node_2.boot_data[6];
}

inline void can_set_pl_boot_node_3(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_3.boot_cmd;
  msg->payload[1] = pl->boot_node_3.boot_data[0];
  msg->payload[2] = pl->boot_node_3.boot_data[1];
  msg->payload[3] = pl->boot_node_3.boot_data[2];
  msg->payload[4] = pl->boot_node_3.boot_data[3];
  msg->payload[5] = pl->boot_node_3.boot_data[4];
  msg->payload[6] = pl->boot_node_3.boot_data[5];
  msg->payload[7] = pl->boot_node_3.boot_data[6];
}

inline void can_set_pl_boot_node_4(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_4.boot_cmd;
  msg->payload[1] = pl->boot_node_4.boot_data[0];
  msg->payload[2] = pl->boot_node_4.boot_data[1];
  msg->payload[3] = pl->boot_node_4.boot_data[2];
  msg->payload[4] = pl->boot_node_4.boot_data[3];
  msg->payload[5] = pl->boot_node_4.boot_data[4];
  msg->payload[6] = pl->boot_node_4.boot_data[5];
  msg->payload[7] = pl->boot_node_4.boot_data[6];
}

inline void can_set_pl_boot_node_5(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_5.boot_cmd;
  msg->payload[1] = pl->boot_node_5.boot_data[0];
  msg->payload[2] = pl->boot_node_5.boot_data[1];
  msg->payload[3] = pl->boot_node_5.boot_data[2];
  msg->payload[4] = pl->boot_node_5.boot_data[3];
  msg->payload[5] = pl->boot_node_5.boot_data[4];
  msg->payload[6] = pl->boot_node_5.boot_data[5];
  msg->payload[7] = pl->boot_node_5.boot_data[6];
}

inline void can_set_pl_boot_node_6(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_6.boot_cmd;
  msg->payload[1] = pl->boot_node_6.boot_data[0];
  msg->payload[2] = pl->boot_node_6.boot_data[1];
  msg->payload[3] = pl->boot_node_6.boot_data[2];
  msg->payload[4] = pl->boot_node_6.boot_data[3];
  msg->payload[5] = pl->boot_node_6.boot_data[4];
  msg->payload[6] = pl->boot_node_6.boot_data[5];
  msg->payload[7] = pl->boot_node_6.boot_data[6];
}

inline void can_set_pl_boot_node_7(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->boot_node_7.boot_cmd;
  msg->payload[1] = pl->boot_node_7.boot_data[0];
  msg->payload[2] = pl->boot_node_7.boot_data[1];
  msg->payload[3] = pl->boot_node_7.boot_data[2];
  msg->payload[4] = pl->boot_node_7.boot_data[3];
  msg->payload[5] = pl->boot_node_7.boot_data[4];
  msg->payload[6] = pl->boot_node_7.boot_data[5];
  msg->payload[7] = pl->boot_node_7.boot_data[6];
}
