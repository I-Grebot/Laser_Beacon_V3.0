/* -----------------------------------------------------------------------------
 * Beacon System Library
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_system.h
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

#ifndef _BEACON_SYSTEM_H_
#define _BEACON_SYSTEM_H_

// Include the board-specific hardware configuration,
// such as clock frequencies definition, modules used etc.
#include "board_cfg.h"

// The beacon system library uses the cc2500 library
#include "cc2500.h"

// -----------------------------------------------------------------------------
// GENERAL BEACON CONFIGURATION
// -----------------------------------------------------------------------------

// Speed target in Rotation per Second (RPS)
#define DRUM_MOTOR_SPEED_TARGET_RPS 30

// -----------------------------------------------------------------------------
// BEACON COMMUNICATION SYSTEM
// -----------------------------------------------------------------------------

// RF Packet format, very simple and consist of 5 bytes
#define BEACON_COM_PACKET_LENGTH 5

//      +-----------+-----------+-----------+-----------+-----------+
// Byte |     4     |     3     |     2     |     1     |     0     |
//      +-----------+-----------+-----------+-----------+-----------+
//      | Rcp. Addr | Emt. Addr | Command   | Data MSW  | Data LSW  |
//      +-----------+-----------+-----------+-----------+-----------+

// Rcp. Addr : Corresponds to the CC2500 recipient device address, will be filtered
//           directly by the module depending on the filtering configuration.
//           0 is used for broadcasting to comply with CC2500 broadcast addr.
//           Otherwise the address is formed as followed:
//           * The 1st Nibble is a specific and arbitrary value used by IGrebot
//             It is useful in case we receive a packet from another source.
//           * The 2nd Nibble is the board ID (see bellow for addresses).
// Emt. Addr : Corresponds to the Emitter device address, mostly useful for the
//           master so he knowes where a message comes from.
//           The same logic is applied than for the Rcp. Address but there is no
//           possible broadcast address.
// Command : RF Messages and Commands.
// Data    : The payload data used in some certain commands.

// Addresses
// ---------

// Broadcast value
#define BEACON_COM_ADDR_BROADCAST   0x00

// 1st Nibble for Header
#define BEACON_COM_ADDR_HEADER 0b1010

// Master address
#define BEACON_COM_ADDR_MASTER 0b1111

// Slave addresses, up to 15 with addresses ranging from 0b0000 to 0b1110
#define BEACON_COM_NB_SLAVE 6

// Macro to build a header if not broadcasting
#define BEACON_COM_BUILD_HEADER(_addr) ((BEACON_COM_ADDR_HEADER << 4) | (_addr & 0xF))

// Macro to decode address from header
#define BEACON_COM_DECODE_HEADER(_head) (_head & 0xF)

// Commands
// --------

// PING
//   Send the used channel number. This act as the very first sync from
//   master to slave, after the master decided which channel number is meant to be
//   used.
//   If the current channel number is different than the specified channel in the
//   packet, it means that the master wants to change the channel so the slaves
//   don't have to look up over the whole channel range.
// * Data[MSW]: unused
// * Data[LSW]: Channel number
#define BEACON_COM_CMD_PING 0x00

// SYNC
//   Synchronization acknowledge from the slaves to the master. It indicates
//   that the slave device is ready.
// * Data[MSW]: unused
// * Data[LSW]: unused
#define BEACON_COM_CMD_SYNC 0x01

// READY
//   Personnal message (no broadcast allowed) sent from the master to a slave
//   to indicate that the master knows about the slave.
// * Data[MSW]: unused
// * Data[LSW]: unused
#define BEACON_COM_CMD_READY 0x02

// The PING -> SYNC -> READY sequence corresponds to the communication init.
// After the sequence is done for all slaves, devices are ready to communicate
// between each others.
// The Master always stay in RX mode, waiting for slaves timestampes
// The Slaves stay in FSTXON, ready to TX once a laser pulse is detected
// In case of suspected communication loss, the master can initiate again the
// PING -> SYNC -> READY sequence.

// DISTANCE
//   Feedback from a slave which gives the measured distance in mm on 16 bit.
//   It is time-stamped by the master to know precisly when the message arrive,
//   so the turret position at the time is known. Then the relative angle between
//   the turret and the slave beacon can be computed.
// * Data[MSW]: Distance MSW
// * Data[LSW]: Distance LSW
#define BEACON_COM_CMD_DIST 0x03

// -----------------------------------------------------------------------------
// CHECKS AND ERROR CODES
// -----------------------------------------------------------------------------

// Expected values for static checks
#define BEACON_COM_EXP_RF_PARTNUM 0x80
#define BEACON_COM_EXP_RF_VERSION 0x03

// Error codes
#define BEACON_COM_ERR_PARTNUM 0x01
#define BEACON_COM_ERR_VERSION 0x02
#define BEACON_COM_ERR_CONFIG  0x03

// -----------------------------------------------------------------------------
// BEACONS MANAGMENT
// -----------------------------------------------------------------------------

// Beacon state type
typedef enum {
    BEACON_OFF     // Slave beacon has never been seen
   ,BEACON_SYNC    // Slave respond with the SYNC after the PING
   ,BEACON_READY   // Slave sent at least 1 distance data
   ,BEACON_LOST    // Slave was not seen for too long and is considered LOST
} beacon_state_t ;


// Type used to represent a beacon and its associated informations (master side only)
typedef struct {
    uint8_t id           : 4 ; // Equivalent to the board ID
    beacon_state_t state : 4 ; // Beacon current state
    uint16_t timestamp       ; // Last activity timestamp
    uint16_t distance        ; // Relative distance in mm from the turret
    sint16_t angle           ; // Relative angle in 10th of degree relative to the turret
    sint16_t X               ; // Position in mm
    sint16_t Y               ; // Position in mm
    sint16_t absAngle        ; // Absolute angle in 10th of degree
} beacon_info_t ;

// Burst size when sending data during startup procedure
#define BEACON_COM_BURST_SIZE  20

// Time between the send of 2 data when bursting
#define BEACON_COM_BURST_DELAY  1

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

// Configuration, returns 0 if OK
uint8_t beacon_com_init(void);

// Processing functions
void beacon_com_send_packet(uint8_t _dest_addr, uint8_t _command, uint16_t _data);
void beacon_com_receive_packet(sint16_t _angle, uint16_t _timestamp);
void beacon_com_startup(void); 

#endif // _BEACON_SYSTEM_H_

