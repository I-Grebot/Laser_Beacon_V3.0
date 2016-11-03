#include "igrecan.h"

/* CAN Payload Set functions */

inline void can_get_pl_supply_status(can_msg_t* msg, payload_t* pl) {
  pl->supply_status.fault = msg->payload[0]; 
  pl->supply_status.battery_voltage = msg->payload[1] + (msg->payload[2]<<8); 
  pl->supply_status.fuses_state = msg->payload[3]; 
  pl->supply_status.emergency_stop = msg->payload[4]; 
}

inline void can_get_pl_supply_command(can_msg_t* msg, payload_t* pl) {
  pl->supply_command.shutdown = msg->payload[0]; 
}

inline void can_get_pl_avoidance_osiris(can_msg_t* msg, payload_t* pl) {
  pl->avoidance_osiris.detection = msg->payload[0]; 
}

inline void can_get_pl_avoidance_ultrasonic(can_msg_t* msg, payload_t* pl) {
  pl->avoidance_ultrasonic.dist_0 = msg->payload[0]; 
  pl->avoidance_ultrasonic.dist_1 = msg->payload[1]; 
}

inline void can_get_pl_beacon_status(can_msg_t* msg, payload_t* pl) {
  pl->beacon_status.errors = msg->payload[0]; 
  pl->beacon_status.turret = msg->payload[1] + (msg->payload[2]<<8); 
}

inline void can_get_pl_beacon_command(can_msg_t* msg, payload_t* pl) {
  pl->beacon_command.turret = msg->payload[0]; 
}

inline void can_get_pl_beacon_opponent_1_abs(can_msg_t* msg, payload_t* pl) {
  pl->beacon_opponent_1_abs.pos_x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->beacon_opponent_1_abs.pos_y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->beacon_opponent_1_abs.pos_a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_beacon_opponent_1_rel(can_msg_t* msg, payload_t* pl) {
  pl->beacon_opponent_1_rel.pos_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->beacon_opponent_1_rel.pos_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_beacon_opponent_2_abs(can_msg_t* msg, payload_t* pl) {
  pl->beacon_opponent_2_abs.pos_x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->beacon_opponent_2_abs.pos_y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->beacon_opponent_2_abs.pos_a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_beacon_opponent_2_rel(can_msg_t* msg, payload_t* pl) {
  pl->beacon_opponent_2_rel.pos_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->beacon_opponent_2_rel.pos_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_beacon_robot_abs(can_msg_t* msg, payload_t* pl) {
  pl->beacon_robot_abs.pos_x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->beacon_robot_abs.pos_y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->beacon_robot_abs.pos_a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_motion_fb_status(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_status.lock = msg->payload[0]; 
  pl->motion_fb_status.trajectory_near = msg->payload[1]; 
  pl->motion_fb_status.trajectory_finished = msg->payload[2]; 
}

inline void can_get_pl_motion_fb_position(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_position.pos_x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_position.pos_y = msg->payload[2] + (msg->payload[3]<<8); 
  pl->motion_fb_position.pos_a = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_motion_fb_speed(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_speed.speed_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_speed.speed_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_motion_fb_acceleration(can_msg_t* msg, payload_t* pl) {
  pl->motion_fb_acceleration.accel_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_fb_acceleration.accel_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) {
  pl->motion_param_speed.speed_pos_max_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_param_speed.speed_neg_max_d = msg->payload[2] + (msg->payload[3]<<8); 
  pl->motion_param_speed.speed_pos_max_a = msg->payload[4] + (msg->payload[5]<<8); 
  pl->motion_param_speed.speed_neg_max_a = msg->payload[6] + (msg->payload[7]<<8); 
}

inline void can_get_pl_motion_param_accel(can_msg_t* msg, payload_t* pl) {
  pl->motion_param_accel.accel_max_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_param_accel.deccel_max_d = msg->payload[2] + (msg->payload[3]<<8); 
  pl->motion_param_accel.deccel_max_a = msg->payload[6] + (msg->payload[7]<<8); 
}

inline void can_get_pl_motion_command(can_msg_t* msg, payload_t* pl) {
  pl->motion_command.lock = msg->payload[0]; 
  pl->motion_command.stall = msg->payload[1]; 
  pl->motion_command.pos_reset_x = msg->payload[3] + (msg->payload[4]<<8); 
  pl->motion_command.pos_reset_y = msg->payload[5] + (msg->payload[6]<<8); 
  pl->motion_command.trajectory_stop = msg->payload[7]; 
}

inline void can_get_pl_motion_goto(can_msg_t* msg, payload_t* pl) {
  pl->motion_goto.pos_x = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_goto.pos_y = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_motion_set_speed(can_msg_t* msg, payload_t* pl) {
  pl->motion_set_speed.speed_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_set_speed.speed_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_motion_move_relative(can_msg_t* msg, payload_t* pl) {
  pl->motion_move_relative.pos_rel_d = msg->payload[0] + (msg->payload[1]<<8); 
  pl->motion_move_relative.pos_rel_a = msg->payload[2] + (msg->payload[3]<<8); 
}

inline void can_get_pl_motion_move_forward(can_msg_t* msg, payload_t* pl) {
  pl->motion_move_forward.pos_fwd_d = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_motion_move_backward(can_msg_t* msg, payload_t* pl) {
  pl->motion_move_backward.pos_bwd_d = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_motion_turn_right(can_msg_t* msg, payload_t* pl) {
  pl->motion_turn_right.pos_r_a = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_motion_turn_left(can_msg_t* msg, payload_t* pl) {
  pl->motion_turn_left.pos_l_a = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_actuators_blower_left(can_msg_t* msg, payload_t* pl) {
  pl->actuators_blower_left.position = msg->payload[0]; 
  pl->actuators_blower_left.speed = msg->payload[1]; 
}

inline void can_get_pl_actuators_blower_right(can_msg_t* msg, payload_t* pl) {
  pl->actuators_blower_right.position = msg->payload[0]; 
  pl->actuators_blower_right.speed = msg->payload[1]; 
}

inline void can_get_pl_actuators_loader(can_msg_t* msg, payload_t* pl) {
  pl->actuators_loader.lift = msg->payload[0]; 
  pl->actuators_loader.grab = msg->payload[1]; 
}

inline void can_get_pl_actuators_launcher(can_msg_t* msg, payload_t* pl) {
  pl->actuators_launcher.speed = msg->payload[0] + (msg->payload[1]<<8); 
}

inline void can_get_pl_actuators_deflector(can_msg_t* msg, payload_t* pl) {
  pl->actuators_deflector.deflect = msg->payload[0]; 
}

inline void can_get_pl_actuators_pump(can_msg_t* msg, payload_t* pl) {
  pl->actuators_pump.pump = msg->payload[0]; 
}

inline void can_get_pl_sensors_left_color(can_msg_t* msg, payload_t* pl) {
  pl->sensors_left_color.color = msg->payload[0]; 
}

inline void can_get_pl_sensors_right_color(can_msg_t* msg, payload_t* pl) {
  pl->sensors_right_color.color = msg->payload[0]; 
}

inline void can_get_pl_sensors_cherry_color(can_msg_t* msg, payload_t* pl) {
  pl->sensors_cherry_color.color = msg->payload[0]; 
}

inline void can_get_pl_sensors_plate(can_msg_t* msg, payload_t* pl) {
  pl->sensors_plate.presence = msg->payload[0]; 
}

inline void can_get_pl_system_status(can_msg_t* msg, payload_t* pl) {
  pl->system_status.node = msg->payload[0]; 
  pl->system_status.state = msg->payload[1]; 
}

inline void can_get_pl_system_match(can_msg_t* msg, payload_t* pl) {
  pl->system_match.state = msg->payload[0]; 
  pl->system_match.color = msg->payload[1]; 
  pl->system_match.points = msg->payload[2] + (msg->payload[3]<<8); 
  pl->system_match.timestamp = msg->payload[4] + (msg->payload[5]<<8); 
}

inline void can_get_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) {
  pl->system_bist_launch.node = msg->payload[0]; 
}

inline void can_get_pl_system_bist_status(can_msg_t* msg, payload_t* pl) {
  pl->system_bist_status.node = msg->payload[0]; 
  pl->system_bist_status.status = msg->payload[1] + (msg->payload[2]<<8); 
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

inline void can_get_pl_debug_printf(can_msg_t* msg, payload_t* pl) {
  pl->debug_printf.node = msg->payload[0]; 
  pl->debug_printf.data[0] = msg->payload[1]; 
  pl->debug_printf.data[1] = msg->payload[2]; 
  pl->debug_printf.data[2] = msg->payload[3]; 
  pl->debug_printf.data[3] = msg->payload[4]; 
  pl->debug_printf.data[4] = msg->payload[5]; 
  pl->debug_printf.data[5] = msg->payload[6]; 
  pl->debug_printf.data[6] = msg->payload[7]; 
}

/* CAN Payload Get functions */

inline void can_set_pl_supply_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->supply_status.fault;
  msg->payload[1] = pl->supply_status.battery_voltage & 0xFF;
  msg->payload[2] = pl->supply_status.battery_voltage >> 8;
  msg->payload[3] = pl->supply_status.fuses_state;
  msg->payload[4] = pl->supply_status.emergency_stop;
}

inline void can_set_pl_supply_command(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->supply_command.shutdown;
}

inline void can_set_pl_avoidance_osiris(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->avoidance_osiris.detection;
}

inline void can_set_pl_avoidance_ultrasonic(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->avoidance_ultrasonic.dist_0;
  msg->payload[1] = pl->avoidance_ultrasonic.dist_1;
}

inline void can_set_pl_beacon_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_status.errors;
  msg->payload[1] = pl->beacon_status.turret & 0xFF;
  msg->payload[2] = pl->beacon_status.turret >> 8;
}

inline void can_set_pl_beacon_command(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_command.turret;
}

inline void can_set_pl_beacon_opponent_1_abs(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_opponent_1_abs.pos_x & 0xFF;
  msg->payload[1] = pl->beacon_opponent_1_abs.pos_x >> 8;
  msg->payload[2] = pl->beacon_opponent_1_abs.pos_y & 0xFF;
  msg->payload[3] = pl->beacon_opponent_1_abs.pos_y >> 8;
  msg->payload[4] = pl->beacon_opponent_1_abs.pos_a & 0xFF;
  msg->payload[5] = pl->beacon_opponent_1_abs.pos_a >> 8;
}

inline void can_set_pl_beacon_opponent_1_rel(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_opponent_1_rel.pos_d & 0xFF;
  msg->payload[1] = pl->beacon_opponent_1_rel.pos_d >> 8;
  msg->payload[2] = pl->beacon_opponent_1_rel.pos_a & 0xFF;
  msg->payload[3] = pl->beacon_opponent_1_rel.pos_a >> 8;
}

inline void can_set_pl_beacon_opponent_2_abs(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_opponent_2_abs.pos_x & 0xFF;
  msg->payload[1] = pl->beacon_opponent_2_abs.pos_x >> 8;
  msg->payload[2] = pl->beacon_opponent_2_abs.pos_y & 0xFF;
  msg->payload[3] = pl->beacon_opponent_2_abs.pos_y >> 8;
  msg->payload[4] = pl->beacon_opponent_2_abs.pos_a & 0xFF;
  msg->payload[5] = pl->beacon_opponent_2_abs.pos_a >> 8;
}

inline void can_set_pl_beacon_opponent_2_rel(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_opponent_2_rel.pos_d & 0xFF;
  msg->payload[1] = pl->beacon_opponent_2_rel.pos_d >> 8;
  msg->payload[2] = pl->beacon_opponent_2_rel.pos_a & 0xFF;
  msg->payload[3] = pl->beacon_opponent_2_rel.pos_a >> 8;
}

inline void can_set_pl_beacon_robot_abs(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->beacon_robot_abs.pos_x & 0xFF;
  msg->payload[1] = pl->beacon_robot_abs.pos_x >> 8;
  msg->payload[2] = pl->beacon_robot_abs.pos_y & 0xFF;
  msg->payload[3] = pl->beacon_robot_abs.pos_y >> 8;
  msg->payload[4] = pl->beacon_robot_abs.pos_a & 0xFF;
  msg->payload[5] = pl->beacon_robot_abs.pos_a >> 8;
}

inline void can_set_pl_motion_fb_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_status.lock;
  msg->payload[1] = pl->motion_fb_status.trajectory_near;
  msg->payload[2] = pl->motion_fb_status.trajectory_finished;
}

inline void can_set_pl_motion_fb_position(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_position.pos_x & 0xFF;
  msg->payload[1] = pl->motion_fb_position.pos_x >> 8;
  msg->payload[2] = pl->motion_fb_position.pos_y & 0xFF;
  msg->payload[3] = pl->motion_fb_position.pos_y >> 8;
  msg->payload[4] = pl->motion_fb_position.pos_a & 0xFF;
  msg->payload[5] = pl->motion_fb_position.pos_a >> 8;
}

inline void can_set_pl_motion_fb_speed(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_speed.speed_d & 0xFF;
  msg->payload[1] = pl->motion_fb_speed.speed_d >> 8;
  msg->payload[2] = pl->motion_fb_speed.speed_a & 0xFF;
  msg->payload[3] = pl->motion_fb_speed.speed_a >> 8;
}

inline void can_set_pl_motion_fb_acceleration(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_fb_acceleration.accel_d & 0xFF;
  msg->payload[1] = pl->motion_fb_acceleration.accel_d >> 8;
  msg->payload[2] = pl->motion_fb_acceleration.accel_a & 0xFF;
  msg->payload[3] = pl->motion_fb_acceleration.accel_a >> 8;
}

inline void can_set_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_param_speed.speed_pos_max_d & 0xFF;
  msg->payload[1] = pl->motion_param_speed.speed_pos_max_d >> 8;
  msg->payload[2] = pl->motion_param_speed.speed_neg_max_d & 0xFF;
  msg->payload[3] = pl->motion_param_speed.speed_neg_max_d >> 8;
  msg->payload[4] = pl->motion_param_speed.speed_pos_max_a & 0xFF;
  msg->payload[5] = pl->motion_param_speed.speed_pos_max_a >> 8;
  msg->payload[6] = pl->motion_param_speed.speed_neg_max_a & 0xFF;
  msg->payload[7] = pl->motion_param_speed.speed_neg_max_a >> 8;
}

inline void can_set_pl_motion_param_accel(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_param_accel.accel_max_d & 0xFF;
  msg->payload[1] = pl->motion_param_accel.accel_max_d >> 8;
  msg->payload[2] = pl->motion_param_accel.deccel_max_d & 0xFF;
  msg->payload[3] = pl->motion_param_accel.deccel_max_d >> 8;
  msg->payload[6] = pl->motion_param_accel.deccel_max_a & 0xFF;
  msg->payload[7] = pl->motion_param_accel.deccel_max_a >> 8;
}

inline void can_set_pl_motion_command(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_command.lock;
  msg->payload[1] = pl->motion_command.stall;
  msg->payload[3] = pl->motion_command.pos_reset_x & 0xFF;
  msg->payload[4] = pl->motion_command.pos_reset_x >> 8;
  msg->payload[5] = pl->motion_command.pos_reset_y & 0xFF;
  msg->payload[6] = pl->motion_command.pos_reset_y >> 8;
  msg->payload[7] = pl->motion_command.trajectory_stop;
}

inline void can_set_pl_motion_goto(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_goto.pos_x & 0xFF;
  msg->payload[1] = pl->motion_goto.pos_x >> 8;
  msg->payload[2] = pl->motion_goto.pos_y & 0xFF;
  msg->payload[3] = pl->motion_goto.pos_y >> 8;
}

inline void can_set_pl_motion_set_speed(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_set_speed.speed_d & 0xFF;
  msg->payload[1] = pl->motion_set_speed.speed_d >> 8;
  msg->payload[2] = pl->motion_set_speed.speed_a & 0xFF;
  msg->payload[3] = pl->motion_set_speed.speed_a >> 8;
}

inline void can_set_pl_motion_move_relative(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_move_relative.pos_rel_d & 0xFF;
  msg->payload[1] = pl->motion_move_relative.pos_rel_d >> 8;
  msg->payload[2] = pl->motion_move_relative.pos_rel_a & 0xFF;
  msg->payload[3] = pl->motion_move_relative.pos_rel_a >> 8;
}

inline void can_set_pl_motion_move_forward(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_move_forward.pos_fwd_d & 0xFF;
  msg->payload[1] = pl->motion_move_forward.pos_fwd_d >> 8;
}

inline void can_set_pl_motion_move_backward(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_move_backward.pos_bwd_d & 0xFF;
  msg->payload[1] = pl->motion_move_backward.pos_bwd_d >> 8;
}

inline void can_set_pl_motion_turn_right(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_turn_right.pos_r_a & 0xFF;
  msg->payload[1] = pl->motion_turn_right.pos_r_a >> 8;
}

inline void can_set_pl_motion_turn_left(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->motion_turn_left.pos_l_a & 0xFF;
  msg->payload[1] = pl->motion_turn_left.pos_l_a >> 8;
}

inline void can_set_pl_actuators_blower_left(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_blower_left.position;
  msg->payload[1] = pl->actuators_blower_left.speed;
}

inline void can_set_pl_actuators_blower_right(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_blower_right.position;
  msg->payload[1] = pl->actuators_blower_right.speed;
}

inline void can_set_pl_actuators_loader(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_loader.lift;
  msg->payload[1] = pl->actuators_loader.grab;
}

inline void can_set_pl_actuators_launcher(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_launcher.speed & 0xFF;
  msg->payload[1] = pl->actuators_launcher.speed >> 8;
}

inline void can_set_pl_actuators_deflector(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_deflector.deflect;
}

inline void can_set_pl_actuators_pump(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->actuators_pump.pump;
}

inline void can_set_pl_sensors_left_color(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->sensors_left_color.color;
}

inline void can_set_pl_sensors_right_color(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->sensors_right_color.color;
}

inline void can_set_pl_sensors_cherry_color(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->sensors_cherry_color.color;
}

inline void can_set_pl_sensors_plate(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->sensors_plate.presence;
}

inline void can_set_pl_system_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_status.node;
  msg->payload[1] = pl->system_status.state;
}

inline void can_set_pl_system_match(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_match.state;
  msg->payload[1] = pl->system_match.color;
  msg->payload[2] = pl->system_match.points & 0xFF;
  msg->payload[3] = pl->system_match.points >> 8;
  msg->payload[4] = pl->system_match.timestamp & 0xFF;
  msg->payload[5] = pl->system_match.timestamp >> 8;
}

inline void can_set_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_bist_launch.node;
}

inline void can_set_pl_system_bist_status(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->system_bist_status.node;
  msg->payload[1] = pl->system_bist_status.status & 0xFF;
  msg->payload[2] = pl->system_bist_status.status >> 8;
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

inline void can_set_pl_debug_printf(can_msg_t* msg, payload_t* pl) {
  msg->payload[0] = pl->debug_printf.node;
  msg->payload[1] = pl->debug_printf.data[0];
  msg->payload[2] = pl->debug_printf.data[1];
  msg->payload[3] = pl->debug_printf.data[2];
  msg->payload[4] = pl->debug_printf.data[3];
  msg->payload[5] = pl->debug_printf.data[4];
  msg->payload[6] = pl->debug_printf.data[5];
  msg->payload[7] = pl->debug_printf.data[6];
}
