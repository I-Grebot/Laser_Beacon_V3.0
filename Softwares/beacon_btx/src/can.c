/* -----------------------------------------------------------------------------
 * Beacon [BTX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : can.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-02-23
 * -----------------------------------------------------------------------------
 * Description
 *   See main module header file for a full description
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 899                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-04-14 18:48:22 +0200 (dim., 14 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-02-23
 * -----------------------------------------------------------------------------
 */

#include "beacon_btx.h"

// CAN Configuration Structure
can_cfg_t can_cfg;

// Infos from CAN for beacon control
uint8_t can_match_state ;
uint8_t can_turret_cmd ;

// Infos to CAN for others (general state)
uint8_t can_state ;

// Beacon Infos
extern volatile beacon_info_t beacon_infos[BEACON_COM_NB_SLAVE];

// -----------------------------------------------------------------------------
// CAN CONFIGURATION
// -----------------------------------------------------------------------------

void beacon_can_init(void) {

  // Define the CAN Processing function for RX messages
  can_cfg.can_process_rx = beacon_can_rx;

  // Setup CAN configuration and inits
  can_dma_config();
  can_init();
  can_isr_config();

  // TEMP
  // All ID can be matched for filters using mask 0
  can_set_mask(CAN_MASK_0, CAN_MASK_NONE);

  // Associate each filter with a mask
  can_assoc_filter(0, CAN_MASK_0);

  // Enable the required filters
  can_enable_filter(0);

  /*
  // Category ID has to be matched for filters using mask 0
  can_set_mask(CAN_MASK_0, CAN_MASK_CID);

  // Category and Message ID (Frame ID) must be matched for filters using mask 1
  can_set_mask(CAN_MASK_1, CAN_MASK_FID);

  // Exact SID must be matched for filters using mask 2
  can_set_mask(CAN_MASK_2, CAN_MASK_SID);

  // Define the different filters to use (up to 16)
  can_set_filter(0, CAN_CID_SUPPLY);
  can_set_filter(1, CAN_CID_MOTION);
  can_set_filter(2, CAN_CID_ACTUATORS);
  can_set_filter(3, CAN_CID_AVOIDANCE);

  // Associate each filter with a mask
  can_assoc_filter(0, CAN_MASK_0);
  can_assoc_filter(1, CAN_MASK_0);
  can_assoc_filter(2, CAN_MASK_0);
  can_assoc_filter(3, CAN_MASK_0);
*/
  // Enable the required filters
//can_enable_filter(0);
//can_enable_filter(1);
//can_enable_filter(2);
//can_enable_filter(3);

  // Initialize default CAN commands
  can_match_state = CAN_SYSTEM_MATCH_STATE_IDLE ;
  can_turret_cmd = 1 ; // Turret is requested to be 'ON'

}

// -----------------------------------------------------------------------------
// CAN TX HANDLERS
// -----------------------------------------------------------------------------

// Send data related to opponent_1
void beacon_can_send_opponent_1(void) {

    // CAN TX message structures
    can_msg_t tx_msg;
    payload_t pl;

    // Handle opponent_1 relative position
    // -----------------------------------

    tx_msg.pid = CAN_PID_DEFAULT;
    tx_msg.fid = CAN_FID_BEACON_OPPONENT_1_REL;
    tx_msg.rtr = 0 ;
    tx_msg.dlc = CAN_DLC_BEACON_OPPONENT_1_REL;

    pl.beacon_opponent_1_rel.pos_d = beacon_infos[0].distance;
    pl.beacon_opponent_1_rel.pos_a = beacon_infos[0].angle;
    
    can_set_pl_beacon_opponent_1_rel(&tx_msg, &pl);
    can_send(&tx_msg);

}


// Send "alive" message
void beacon_can_send_status(void) {

    // CAN TX message structures
    can_msg_t tx_msg;
    payload_t pl;

    tx_msg.pid = CAN_PID_LOW;
    tx_msg.fid = CAN_FID_SYSTEM_STATUS;
    tx_msg.rtr = 0 ;
    tx_msg.dlc = CAN_DLC_SYSTEM_STATUS;

    pl.system_status.node  = CAN_NODE_ID ;
    pl.system_status.state = can_state ;

    can_set_pl_system_status(&tx_msg, &pl);
    can_send(&tx_msg);

}

// -----------------------------------------------------------------------------
// CAN RX HANDLER
// -----------------------------------------------------------------------------

void beacon_can_rx (void) {

    // Payload
    payload_t pl;
    uint8_t idx;

/*
#ifdef DEBUG
    printf("Received CAN!\n");
    printf("FID : 0x%x\n", can_cfg.rx_msg.fid);
    printf("DLC : %d\n", can_cfg.rx_msg.dlc);
    printf("PL : ");
    for(idx=0; idx<can_cfg.rx_msg.dlc; idx++)
        printf("%02X ", can_cfg.rx_msg.payload[idx]);
    printf("\n");
#endif

    // Associate payload to structure data
    if(can_cfg.rx_msg.fid == CAN_FID_SYSTEM_BIST_LAUNCH) {
        can_get_pl_system_bist_launch(&can_cfg.rx_msg, &pl);
#ifdef DEBUG
        printf(" PL fetched : %d", pl.system_bist_launch.node);
#endif
 *
    }*/
}
