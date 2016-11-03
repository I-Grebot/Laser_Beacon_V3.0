#ifndef _IGRECAN_H_
#define _IGRECAN_H_

/*
 * CAN Library dependencies
 * ------------------------
 */

#ifndef __arm__

// Include the board-specific hardware configuration,
// such as clock frequencies definition, modules used etc.
#include "board_cfg.h"

#else

#include "arm_cfg.h"

#endif // __arm__ 

// Includes the auto-generated configuration file,
// containing various definition for IGrebot system.
#include "igrecan_cfg.h"

// The robot_system library is needed for custom payload/nodes definition
#include "robot_system.h"


/*
 * Check board config
 * ------------------
 */

#ifndef __arm__ 

#ifndef FCY
    #error "IGreCAN Library: Error - FCY must be defined in the board configuration header"
#endif

#ifndef ECAN1_RX_TRIS
    #error "IGreCAN Library: Error - ECAN1_RX_TRIS must be defined in the board configuration header"
#endif

#ifndef ECAN1_TX_TRIS
    #error "IGreCAN Library: Error - ECAN1_TX_TRIS must be defined in the board configuration header"
#endif

#ifndef ECAN1_RX_PIN
    #error "IGreCAN Library: Error - ECAN1_RX_PIN must be defined in the board configuration header"
#endif

#ifndef ECAN1_TX_RPN
    #error "IGreCAN Library: Error - ECAN1_TX_RPN must be defined in the board configuration header"
#endif

#endif

/*
 * CAN Modes constants
 * -------------------
 */

#define CAN_MODE_NORMAL   0b000
#define CAN_MODE_DISABLE  0b001
#define CAN_MODE_LOOPBACK 0b010
#define CAN_MODE_LISTEN   0b011
#define CAN_MODE_INIT     0b100

/*
 * CAN addressing macros
 * ---------------------
 * Format of CAN SID <10:0> :
 * <10:9> Priority : 4 different levels (see below)
 * <8:5>  Category : 16 categories also organized by priority
 * <4:0>  Message  : 32 possible messages per category.
 *
 * Mnemonics used :
 *   - 'SID' refers to the whole, 11 bits CAN Identifier
 *   - 'PID' refers to the 2 bits priority ID
 *   - 'CID' refers to the 4 bits category ID
 *   - 'MID' refers to the 5 bits message ID
 *   - 'FID' refers to the 4+5 bits frame (category+message) ID
 *
 * Thus :
 *    SID = (PID << 9) | (CID << 5) | MID
 *  or
 *    SID = (PID << 9) | FID
 * where
 *    FID = (CID << 5) | MID
 */

/* ID shifts */
#define CAN_SHIFT_PID 9 // <10:9>
#define CAN_SHIFT_CID 5 // <8:5>
#define CAN_SHIFT_MID 0 // <4:0>

/* IDs masks */
#define CAN_MASK_PID ((0x003) << CAN_SHIFT_PID)    // 2 bits
#define CAN_MASK_CID ((0x00F) << CAN_SHIFT_CID)    // 4 bits
#define CAN_MASK_MID 0x01F                         // 5 bits
#define CAN_MASK_FID (CAN_MASK_CID | CAN_MASK_MID) // 9 bits
#define CAN_MASK_SID (CAN_MASK_PID | CAN_MASK_FID) // 11 bits
#define CAN_MASK_NONE 0

/* Building macros */
#define CAN_MAKE_FULL_SID(__p, __c, __m) (((__p) << CAN_SHIFT_PID) | ((__c) << CAN_SHIFT_CID) | __m)
#define CAN_MAKE_SID(__p, __f) (((__p) << CAN_SHIFT_PID) | __f)

/* Retrieving macros */
#define CAN_GET_PID(__x) (((__x) & CAN_MASK_SID) >> CAN_SHIFT_PID)
#define CAN_GET_CID(__x) (((__x) & CAN_MASK_SID) >> CAN_SHIFT_CID)
#define CAN_GET_MID(__x) ((__x) & CAN_MASK_MID)
#define CAN_GET_FID(__x) ((__x) & CAN_MASK_FID)

/*
 * CAN priorities
 * --------------
 * CAN bus specification defines the ID 0x000 as the highest priority message.
 * Frames already have, by design, a given priority.
 * As all of them are emitted with the default priority during a normal session,
 * a single frame can overpass any other to become less or more prioritized.
 * Debug priority should be only used for debug purposes (i.e. never sent during
 * a match without debug interactions).
 */

#define CAN_PID_DEBUG   3
#define CAN_PID_LOW     2
#define CAN_PID_DEFAULT 1
#define CAN_PID_HIGH    0

/*
 * CAN Bus general configuration
 * -----------------------------
 */

// CAN Frequency is directly the peripheral frequency

#ifndef __arm__ 
#define FCAN FCY
#else
#define FCAN MCP2515_FOSC
#endif

#if (FCAN > 40000000)
    #error "IGreCAN Library : FCAN must be equal or smaller than 40MHz"
#endif

// CAN Bitrate
#define CAN_BITRATE 	  250000

// NTQ is the bit time in number of quantization time
// CAN TQ segments/p?ase overall length must meet the formulae:
// 1 + SEG1PH + SEG2PH + PRSEG = NTQ
// NTQ Must divide evenly (FCAN/CAN_BITRATE)
// 16 is ok since it can work for a common array of frequencies:
// FCAN = 4, 8, 16, 20, 32, and 40 MHz
// which respectly values half of the quartz frequency.
#define CAN_NTQ   16 // Bit-time
#define CAN_SJW    3 // Synchronization Jump Width must be < than CAN_SEG2PH
#define CAN_SEG1PH 5 // Phase Segment 1
#define CAN_SEG2PH 5 // Phase Segment 2
#define CAN_PRSEG  5 // Propagation Segment

// Register baudrate value
#define CAN_BRP_VAL (((FCAN)/(2*CAN_NTQ*CAN_BITRATE))-1)

/*
 * CAN Masks configurations
 * ------------------------
 */

// Mask indexes
#define CAN_MASK_2    2
#define CAN_MASK_1    1
#define CAN_MASK_0    0

/*
 * DMA Configuration for CAN
 * -------------------------
 */

// N DMA Buffers are used:
//  - Buffers 0 to 3   used for TX
//  - Buffers 4 to N-1 used for RX
// (Only the 8th first can be used for TX)
// Number of TX buffers must be tight to 4
// (Tx function used it to prioritize messages).

// Number of RX buffers used for the FIFO
// This can be parametric
#define CAN_DMA_RX_BUFFERS 4

// Also Change it if more RX buffers are needed
#define CAN_DMA_DMABS 0b010

// Index of first RX buffer within the CAN DMA space
#define CAN_DMA_RX_START 4

// Total number of DMA buffers
#define CAN_DMA_BUFFERS (CAN_DMA_RX_START+CAN_DMA_RX_BUFFERS)

// Events indexes for DMA configuration
#define DMA_C1RX_REQ 0x0022
#define DMA_C1TX_REQ 0x0046

/*
 * Structures definition
 * ---------------------
 */

// Message structure in RAM
// Only Standard Frames are used
 typedef struct {
    uint8_t  pid : 2;    // Priority ID : SID<10:9>
    uint16_t fid : 9;    // Frame ID    : SID<8:0>
    uint8_t  rtr : 1;    // RTR message or data message
    uint8_t  dlc    ;    // CAN Data-Length
    uint8_t  payload[8]; // CAN Payload content
} can_msg_t;

// CAN Status and Config structure, used to interact with
// user application.
typedef struct {
    can_msg_t rx_msg ;              // RX message which needs to be processed
    void (* can_process_rx) (void); // Processing function for RX messages
} can_cfg_t;

/*
 * CAN Functions Prototypes
 */

#ifndef __arm__

// Configuration functions
void can_dma_config(void);
void can_init(void);
void can_isr_config(void);

// Mask and Filters functions
void can_set_mask(uint8_t mask_no, uint16_t mask_cfg);
void can_set_filter(uint8_t filter_no, uint16_t sid);
void can_assoc_filter(uint8_t filter_no, uint8_t mask_no);
void can_enable_filter(uint8_t filter_no);
void can_disable_filter(uint8_t filter_no);

// Processing functions
void can_send(can_msg_t * message);
void can_receive(uint8_t buffer_index);

// Toolkit and debug
void can_send_msg(uint8_t _len, char* _str);

inline void can_set_mode(uint8_t mode);

// Variadic macro to output a message on CAN exactly like with printf().
// The only requirement is to declare a global "can_msg" char array, sized
// large enough to acomodate the biggest message.
#define can_printf(_format, ...) {sprintf(can_msg, (_format), __VA_ARGS__);\
                                  can_send_msg(strlen(can_msg), can_msg);}

//#else
#endif

void can_get_pl_supply_status(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_supply_command(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_avoidance_osiris(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_avoidance_ultrasonic(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_status(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_command(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_opponent_1_abs(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_opponent_1_rel(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_opponent_2_abs(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_opponent_2_rel(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_beacon_robot_abs(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_fb_status(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_fb_position(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_fb_speed(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_fb_acceleration(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_param_accel(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_command(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_goto(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_set_speed(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_move_relative(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_move_forward(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_move_backward(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_turn_right(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_motion_turn_left(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_blower_left(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_blower_right(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_loader(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_launcher(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_deflector(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_actuators_pump(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_sensors_left_color(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_sensors_right_color(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_sensors_cherry_color(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_sensors_plate(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_system_status(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_system_match(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_system_bist_status(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_0(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_1(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_2(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_3(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_4(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_5(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_6(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_boot_node_7(can_msg_t* msg, payload_t* pl) ;
void can_get_pl_debug_printf(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_supply_status(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_supply_command(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_avoidance_osiris(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_avoidance_ultrasonic(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_status(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_command(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_opponent_1_abs(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_opponent_1_rel(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_opponent_2_abs(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_opponent_2_rel(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_beacon_robot_abs(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_fb_status(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_fb_position(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_fb_speed(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_fb_acceleration(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_param_speed(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_param_accel(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_command(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_goto(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_set_speed(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_move_relative(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_move_forward(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_move_backward(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_turn_right(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_motion_turn_left(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_blower_left(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_blower_right(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_loader(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_launcher(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_deflector(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_actuators_pump(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_sensors_left_color(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_sensors_right_color(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_sensors_cherry_color(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_sensors_plate(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_system_status(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_system_match(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_system_bist_launch(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_system_bist_status(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_0(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_1(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_2(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_3(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_4(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_5(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_6(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_boot_node_7(can_msg_t* msg, payload_t* pl) ;
void can_set_pl_debug_printf(can_msg_t* msg, payload_t* pl) ;


#endif /* ! _IGRECAN_H_ */
