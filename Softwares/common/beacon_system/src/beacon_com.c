/* -----------------------------------------------------------------------------
 * Beacon System Library
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_com.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-23
 * -----------------------------------------------------------------------------
 * Description
 *   ... TO BE COMPLETED ...
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 899                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-04-14 18:48:22 +0200 (dim., 14 avr. 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-03-10
 * -----------------------------------------------------------------------------
 */

#include "beacon_system.h"
#include <stdio.h>
#warning "remove stdio"

// Constant IDs of beacons
const uint8_t beacon_com_ids[BEACON_COM_NB_SLAVE] __attribute__((space(psv))) = {
    0b0001, // Static TOP    beacon
    0b0010, // Static BOTTOM beacon (same side than Top)
    0b0011, // Static MIDDLE beacon (other side than Top)
    0b0100, // friend secondary
    0b0101, // Opponent main      robot
    0b0110, // Opponent secondary robot
};

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// Board ID used to differentiate beacons
uint8_t board_id;

//#ifdef BEACON_COM_IS_MASTER
beacon_info_t beacon_infos[BEACON_COM_NB_SLAVE];
//#endif


// -----------------------------------------------------------------------------
// CONFIGURATION ROUTINES
// -----------------------------------------------------------------------------

// Board ID depends on master or slave
inline uint8_t beacon_com_get_board_id(void) {
  #ifdef BEACON_COM_IS_MASTER
    return BEACON_COM_ADDR_MASTER;
  #else // SLAVE
    return (BEACON_COM_DIL_B2 << 2) | (BEACON_COM_DIL_B1 << 1) | (BEACON_COM_DIL_B0);
  #endif // BEACON_COM_IS_MASTER
}

inline void active_delay_ms(uint16_t _del_ms) {
  uint32_t del;
  while(--_del_ms)
    for(del=NCY_FOR_ONE_MS; del; del--);
}

// Init all the necessary stuff
uint8_t beacon_com_init(void) {

  // Initiate DIL switchs tristates only for slave
  #ifndef BEACON_COM_IS_MASTER
  BEACON_COM_DIL_B2_TRIS = 1 ;
  BEACON_COM_DIL_B1_TRIS = 1 ;
  BEACON_COM_DIL_B0_TRIS = 1 ;
  #endif

  // Get the board id and write it in the global variable, so
  // it'll stick to these value even if DIL switchs change.
  // It also prevent wrong read cases
  board_id = beacon_com_get_board_id();
  
  // Init the CC2500 spi
  cc2500_init_spi();

  // Soft-reset the CC2500 chip
  cc2500_send_strobe(CC2500_ADDR_STROBE_SRES);

  // Write the CC2500 default configuration
  cc2500_write_cfg();

  // Check that the device is correctly responding
  if(cc2500_get_partnum() != BEACON_COM_EXP_RF_PARTNUM)
    return BEACON_COM_ERR_PARTNUM ;
  if(cc2500_get_version() != BEACON_COM_EXP_RF_VERSION)
    return BEACON_COM_ERR_VERSION ;

  // Check that all configuration registers are effectively written
  if(cc2500_check_cfg())
    return BEACON_COM_ERR_CONFIG ;

  // Overwrite a couple of registers
  cc2500_write_reg(CC2500_ADDR_REG_ADDR   , BEACON_COM_BUILD_HEADER(board_id));
  cc2500_write_reg(CC2500_ADDR_REG_PKTLEN , BEACON_COM_PACKET_LENGTH);
  // Others are already OK (set in CC2500 default config file)

  // No error occured
  return 0 ;
  
}

// -----------------------------------------------------------------------------
// PROCESSING FUNCTIONS
// -----------------------------------------------------------------------------

// Handle a packet TX
void beacon_com_send_packet(uint8_t _dest_addr, uint8_t _command, uint16_t _data) {

  uint8_t rf_datas[BEACON_COM_PACKET_LENGTH] ;

  // Receipient, check if broadcast is used (no header in this case)
  if(_dest_addr == BEACON_COM_ADDR_BROADCAST)
    rf_datas[0] = BEACON_COM_ADDR_BROADCAST ;
  else
    rf_datas[0] = BEACON_COM_BUILD_HEADER(_dest_addr) ; 
  
  rf_datas[1] = BEACON_COM_BUILD_HEADER(board_id) ; // Emitter
  rf_datas[2] = _command ;
  rf_datas[3] = (uint8_t) (_data >> 8)   ; // MSW
  rf_datas[4] = (uint8_t) (_data & 0xFF) ; // LSW

  // Fill the TX FIFO with data and send them
  cc2500_send_rf_data(rf_datas, BEACON_COM_PACKET_LENGTH);
  cc2500_send_strobe(CC2500_ADDR_STROBE_STX);  
}

// Handle a packet RX (called back after RX isr)
// This function updates the given packet_info
void beacon_com_receive_packet(sint16_t _angle, uint16_t _timestamp) {

  uint8_t rx_nb_bytes ;
  uint8_t rf_datas[BEACON_COM_PACKET_LENGTH + 2]; //+2  for RSSI and LQI
  uint8_t dest_addr ;
  uint8_t emt_addr ;
  uint8_t command ;
  uint16_t data ;
  uint8_t rx_status;
  uint8_t rssi;
  uint8_t lqi;
  
  do {
    rx_status  = cc2500_read_status(CC2500_ADDR_STATUS_RXBYTES);
    rx_nb_bytes = rx_status & CC2500_MASK_RXBYTES;
    
    if(rx_status & CC2500_MASK_RXFIFO_OVF)
    {
        printf("TODO RX_OVF\n");
#warning "TODO"
    }
    // Handles the data only if enough ware received
    else if(rx_nb_bytes >= BEACON_COM_PACKET_LENGTH+2) {
        
            
      // Read data from chip
      cc2500_receive_rf_data(rf_datas, BEACON_COM_PACKET_LENGTH+2);

      // Decode it and update the associated beacon_info
      dest_addr = rf_datas[0];
      emt_addr = rf_datas[1] ;
      command = rf_datas[2] ;
      data = rf_datas[3] << 8 | rf_datas[4];
      rssi = rf_datas[5];
      lqi = rf_datas[6];
      
      // Broadcast
      //if(dest_addr == BEACON_COM_ADDR_BROADCAST) {

        // TBD.

      // Personnal (me or for someone else)
     // } else {

        switch(command) {
          case BEACON_COM_CMD_PING: break;
          case BEACON_COM_CMD_SYNC: break;
          case BEACON_COM_CMD_READY: break;

          case BEACON_COM_CMD_DIST:
          {
              uint8_t emt = BEACON_COM_DECODE_HEADER(emt_addr);
              if(emt>0 && emt <= BEACON_COM_NB_SLAVE)
              {
                beacon_infos[emt-1].id        = emt ;
                beacon_infos[emt-1].state     = BEACON_READY ;
                beacon_infos[emt-1].distance  = data ;
                beacon_infos[emt-1].angle     = _angle ;
                beacon_infos[emt-1].timestamp = _timestamp ;
                break;
              }
          }
        }

     // }

        rx_nb_bytes -= BEACON_COM_PACKET_LENGTH+2;
        
    } // if rx_bytes
    else
    {
#warning "TODO"
        printf("TODO strange\n");
    }
    // Continue to read if there is still something!
  } while(rx_nb_bytes >= BEACON_COM_PACKET_LENGTH+2);

}

// Implement messages handlers
// --------------------------

// PING, from master to slaves, sending selected channel number
inline void beacon_com_send_ping(uint8_t _channr) {
  beacon_com_send_packet(BEACON_COM_ADDR_BROADCAST, BEACON_COM_CMD_PING, (uint16_t) _channr);
}

// SYNC, from slaves to master, acknowledging the PING
inline void beacon_com_send_sync(void) {
  beacon_com_send_packet(BEACON_COM_ADDR_MASTER, BEACON_COM_CMD_SYNC, 0);
}

// READY, from master to a specific slave, ack of ack and start of operations
inline void beacon_com_send_ready(uint8_t _dest) {
  beacon_com_send_packet(_dest, BEACON_COM_CMD_READY, 0);
}

// DIST, from slaves to master, measured distance in mm
inline void beacon_com_send_dist(uint16_t _dist) {
  beacon_com_send_packet(BEACON_COM_ADDR_MASTER, BEACON_COM_CMD_DIST, _dist);
}

// Startup procedures, depending on master or slave
// ------------------------------------------------

void beacon_com_startup(void) {
  uint8_t idx;
  uint16_t burst_idx;
  uint8_t selected_channel;
  uint8_t nb_found_beacon;

  // TEMP for first testings
  selected_channel = 0x42 ;
  cc2500_write_reg(CC2500_ADDR_REG_CHANNR, selected_channel);
  
#ifdef BEACON_COM_IS_MASTER
  // Initialize the beacon infos
  for(idx=0; idx<BEACON_COM_NB_SLAVE; idx++) {
    beacon_infos[idx].state = BEACON_OFF ;
    beacon_infos[idx].id    = beacon_com_ids[idx];
    // others set to 0 already
  }

  // Start to scan channels
  //cc2500_scan_channels();

  // Define the channel which is going to be used as the best (clearest) match

  //cc2500_find_best_channel();

  // Calibrate Freq. synth. and turn it OFF
  cc2500_send_strobe(CC2500_ADDR_STROBE_SCAL);
  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);

  // flush Rx FIFO
  cc2500_send_strobe(CC2500_ADDR_STROBE_SFRX);
  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);

  // Enable RX. Perform cal. if coming from IDLE
  cc2500_send_strobe(CC2500_ADDR_STROBE_SRX);
  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_RX);

//  // Go to IDLE state
//  cc2500_send_strobe(CC2500_ADDR_STROBE_SIDLE);
//  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);
//
//  // Loop until all the beacons are sync'ed
//  nb_found_beacon = 0 ;
//  while(nb_found_beacon < BEACON_COM_NB_SLAVE) {
//
//    // Send a burst of PING commands
//    burst_idx = BEACON_COM_BURST_SIZE;
//    while(burst_idx--) {
//      beacon_com_send_ping(selected_channel);
//      active_delay_ms(BEACON_COM_BURST_DELAY);
//    }
//
//    // Switch back to RX mode and listen for incomming SYNC response
//    cc2500_send_strobe(CC2500_ADDR_STROBE_SRX);
//    while(cc2500_get_chip_marcstate() != CC2500_ADDR_STROBE_SRX);
//
//  }
  

  cc2500_init_sdi_isr();
  
#else // SLAVE

  // CAL and ready to TX from now
  cc2500_send_strobe(CC2500_ADDR_STROBE_SCAL);
  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);

  cc2500_send_strobe(CC2500_ADDR_STROBE_SFSTXON);
  while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_FSTXON);


#endif // BEACON_COM_IS_MASTER
}

