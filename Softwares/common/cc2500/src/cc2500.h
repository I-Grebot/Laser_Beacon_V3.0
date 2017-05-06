/* -----------------------------------------------------------------------------
 * CC2500
 * I-Grebot RF Module CC2500 Library
 * -----------------------------------------------------------------------------
 * File        : cc2500.h
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
 * $Rev:: 873                                                                  $
 * $LastChangedBy:: Paul.M                                                     $
 * $LastChangedDate:: 2013-03-28 00:12:33 +0100 (jeu., 28 mars 2013)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2013-02-23
 * -----------------------------------------------------------------------------
 */

#ifndef _CC2500_H_
#define _CC2500_H_

/*
 * CC2500 Library dependencies
 * ---------------------------
 */

// Include the board-specific hardware configuration,
// such as clock frequencies definition, modules used etc.
#include "board_cfg.h"

// Configuration used by the lib (RF settings and stuff)
#include "cc2500_cfg.h"

/*
 * Check board config
 * ------------------
 */

#ifndef FCY
    #error "CC2500 Library: Error - FCY must be defined in the board configuration header"
#endif


/*
 * SPI Baudrate
 * ------------
 */

// fSCK = FCY /(PPRE*SPRE)
// Desired baudrate is 1MHz

// fSCK = FCY / 32
#define CC2500_SPI_PPRE 0b01  // 16:1
#define CC2500_SPI_SPRE 0b110 //  2:1

/*
 * Macros
 * ------
 */

// SPI Header byte:
// bit no |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
//        +-------+-------+-----------------------------------------------+
//        |  R/nW | Burst |             Address[5:0]                      |

#define CC2500_BUILD_HEADER(_RnW, _burst, _addr) ((((_RnW)&1)<<7) | (((_burst)&1)<<6) | ((_addr)&0x3F))

/*
 * Hardware-Related Constants
 * --------------------------
 */


#ifndef CC2500_USE_SPI2

// PPS I/Os
#define CC2500_SCK_PIN 0b01000 //TODO there are defines for that (_RPOUT_SCK1OUT)
#define CC2500_SDO_PIN 0b00111
#define CC2500_SDI_RPN (RPINR20bits.SDI1R)

#else

// PPS I/Os
#define CC2500_SCK_PIN 0b01011
#define CC2500_SDO_PIN 0b01010
#define CC2500_SDI_RPN (RPINR22bits.SDI2R)

#endif

/*
 * Register address constants
 * --------------------------
 */

// Values without R/W nor BURST bits

// Configuration Registers addresses
#define CC2500_NB_REG                  41 // Without test registers
#define CC2500_ADDR_REG_IOCFG2       0x00
#define CC2500_ADDR_REG_IOCFG1       0x01
#define CC2500_ADDR_REG_IOCFG0       0x02
#define CC2500_ADDR_REG_FIFOTHR      0x03
#define CC2500_ADDR_REG_SYNC1        0x04
#define CC2500_ADDR_REG_SYNC0        0x05
#define CC2500_ADDR_REG_PKTLEN       0x06
#define CC2500_ADDR_REG_PKTCTRL1     0x07
#define CC2500_ADDR_REG_PKTCTRL0     0x08
#define CC2500_ADDR_REG_ADDR         0x09
#define CC2500_ADDR_REG_CHANNR       0x0A
#define CC2500_ADDR_REG_FSCTRL1      0x0B
#define CC2500_ADDR_REG_FSCTRL0      0x0C
#define CC2500_ADDR_REG_FREQ2        0x0D
#define CC2500_ADDR_REG_FREQ1        0x0E
#define CC2500_ADDR_REG_FREQ0        0x0F
#define CC2500_ADDR_REG_MDMCFG4      0x10
#define CC2500_ADDR_REG_MDMCFG3      0x11
#define CC2500_ADDR_REG_MDMCFG2      0x12
#define CC2500_ADDR_REG_MDMCFG1      0x13
#define CC2500_ADDR_REG_MDMCFG0      0x14
#define CC2500_ADDR_REG_DEVIATN      0x15
#define CC2500_ADDR_REG_MCSM2        0x16
#define CC2500_ADDR_REG_MCSM1        0x17
#define CC2500_ADDR_REG_MCSM0        0x18
#define CC2500_ADDR_REG_FOCCFG       0x19
#define CC2500_ADDR_REG_BSCFG        0x1A
#define CC2500_ADDR_REG_AGCTRL2      0x1B
#define CC2500_ADDR_REG_AGCTRL1      0x1C
#define CC2500_ADDR_REG_AGCTRL0      0x1D
#define CC2500_ADDR_REG_WOREVT1      0x1E
#define CC2500_ADDR_REG_WOREVT0      0x1F
#define CC2500_ADDR_REG_WORCTRL      0x20
#define CC2500_ADDR_REG_FREND1       0x21
#define CC2500_ADDR_REG_FREND0       0x22
#define CC2500_ADDR_REG_FSCAL3       0x23
#define CC2500_ADDR_REG_FSCAL2       0x24
#define CC2500_ADDR_REG_FSCAL1       0x25
#define CC2500_ADDR_REG_FSCAL0       0x26
#define CC2500_ADDR_REG_RCCTRL1      0x27
#define CC2500_ADDR_REG_RCCTRL0      0x28
#define CC2500_ADDR_REG_FSTEST       0x29
#define CC2500_ADDR_REG_PTEST        0x2A
#define CC2500_ADDR_REG_AGCTEST      0x2B
#define CC2500_ADDR_REG_TEST2        0x2C
#define CC2500_ADDR_REG_TEST1        0x2D
#define CC2500_ADDR_REG_TEST0        0x2E

// CC2500 Strobe commands
#define CC2500_ADDR_STROBE_SRES          0x30     // Software-Reset of the chip
#define CC2500_ADDR_STROBE_SFSTXON       0x31     // Enable and calibrate Freq. synth.
#define CC2500_ADDR_STROBE_SXOFF         0x32     // Turn OFF Crystal Oscillator
#define CC2500_ADDR_STROBE_SCAL          0x33     // Calibrate Freq. synth. and turn it OFF
#define CC2500_ADDR_STROBE_SRX           0x34     // Enable RX. Perform cal. if coming from IDLE
#define CC2500_ADDR_STROBE_STX           0x35     // Enable TX. Perform cal. if coming from IDLE
#define CC2500_ADDR_STROBE_SIDLE         0x36     // Exit RX/TX, turn OFF Freq. synt.
//                                    no 0x37
#define CC2500_ADDR_STROBE_SWOR          0x38     // Start automatic RX polling sequence (Wake-On-Radio)
#define CC2500_ADDR_STROBE_SPWD          0x39     // Enter power-down
#define CC2500_ADDR_STROBE_SFRX          0x3A     // Flush the RX FIFO
#define CC2500_ADDR_STROBE_SFTX          0x3B     // Flush the TX FIFO
#define CC2500_ADDR_STROBE_SWORRST       0x3C     // Reset RTC to event 1 value
#define CC2500_ADDR_STROBE_SNOP          0x3D     // No operation. Useful for only reading status byte.

// Status Registers Addresses
#define CC2500_NB_STATUS                   14
#define CC2500_ADDR_STATUS_PARTNUM         0x30
#define CC2500_ADDR_STATUS_VERSION         0x31
#define CC2500_ADDR_STATUS_FREQEST         0x32
#define CC2500_ADDR_STATUS_LQI             0x33
#define CC2500_ADDR_STATUS_RSSI            0x34
#define CC2500_ADDR_STATUS_MARCSTATE       0x35
#define CC2500_ADDR_STATUS_WORTIME1        0x36
#define CC2500_ADDR_STATUS_WORTIME0        0x37
#define CC2500_ADDR_STATUS_PKTSTATUS       0x38
#define CC2500_ADDR_STATUS_VCO_VC_DAC      0x39
#define CC2500_ADDR_STATUS_TXBYTES         0x3A
#define CC2500_ADDR_STATUS_RXBYTES         0x3B
#define CC2500_ADDR_STATUS_RCCTRL1_STATUS  0x3C
#define CC2500_ADDR_STATUS_RCCTRL0_STATUS  0x3D

// FIFO TX and RX Depths in bytes
#define CC2500_FIFO_TX_DEPTH 64
#define CC2500_FIFO_RX_DEPTH 64

// PATABLE Address
#define CC2500_NB_PATABLE                  8
#define CC2500_ADDR_PATABLE                0x3E

// RX/TX FIFO Address
#define CC2500_ADDR_FIFO                   0x3F

/*
 * Register bitfields meanings constants
 * -------------------------------------
 */

// Shifts and Masks

// Chip state is bitfield [6:4] in STATUS register
#define CC2500_MASK_STATE           0x70
#define CC2500_SHIFT_STATE             4

// CCA is bit 6 in PKTSTATUS register
#define CC2500_MASK_CS              0x40
#define CC2500_SHIFT_CS                6

// PQT_REACHED is bit 5 in PKTSTATUS register
#define CC2500_MASK_PQT_REACHED     0x20
#define CC2500_SHIFT_PQT_REACHED       5

// CCA is bit 4 in PKTSTATUS register
#define CC2500_MASK_CCA             0x10
#define CC2500_SHIFT_CCA               4

// SFD is bit 3 in PKTSTATUS register
#define CC2500_MASK_SFD             0x08
#define CC2500_SHIFT_SFD               3

// RXFIFO_OVERFLOW is bit 7 in STATUS_RXBYTES register
#define CC2500_MASK_RXFIFO_OVF      0x80
// RXBYTES are 7 first bit in STATUS_RXBYTES register
#define CC2500_MASK_RXBYTES         0x7F

// CC2500 chip states
#define CC2500_STATE_IDLE           0b000   // Idle state
#define CC2500_STATE_RX             0b001   // Receive mode
#define CC2500_STATE_TX             0b010   // Transmitt mode
#define CC2500_STATE_FSTXON         0b011   // Freq. synth. is ON, ready to TX
#define CC2500_STATE_CALIBRATE      0b100   // Freq. synth. calibration is running
#define CC2500_STATE_SETTLING       0b101   // PLL is settling
#define CC2500_STATE_RXFIFO_OVF     0b110   // RX FIFO has overflowed (too many data)
#define CC2500_STATE_TXFIFO_UDF     0b111   // TX FIFO has underflowed (not enough data)

#define CC2500_MARCSTATE_SLEEP          0
#define CC2500_MARCSTATE_IDLE           1
#define CC2500_MARCSTATE_XOFF           2
#define CC2500_MARCSTATE_VCOON_MC       3
#define CC2500_MARCSTATE_REGON_MC       4
#define CC2500_MARCSTATE_MANCAL         5
#define CC2500_MARCSTATE_VCOON          6
#define CC2500_MARCSTATE_REGON          7
#define CC2500_MARCSTATE_STARTCAL       8
#define CC2500_MARCSTATE_BWBOOST        9
#define CC2500_MARCSTATE_FS_LOCK       10
#define CC2500_MARCSTATE_IFADCON       11
#define CC2500_MARCSTATE_ENDCAL        12
#define CC2500_MARCSTATE_RX            13
#define CC2500_MARCSTATE_RX_END        14
#define CC2500_MARCSTATE_RX_RST        15
#define CC2500_MARCSTATE_TXRX_SWITCH   16
#define CC2500_MARCSTATE_RXFIFO_OVF    17
#define CC2500_MARCSTATE_FSTXON        18
#define CC2500_MARCSTATE_TX            19
#define CC2500_MARCSTATE_TX_END        20
#define CC2500_MARCSTATE_RXTX_SWITCH   21
#define CC2500_MARCSTATE_TXFIFO_UDF    22

/*
 * Other constants
 * ---------------
 */

// Number of times a given channel is tested to check
// its CCA value.
#define CC2500_CHANNEL_SCAN_RATE 10

/*
 * Structures definition
 * ---------------------
 */

// CC2500 register definition
typedef union {

    // ------------------------------------
    // Header status byte
    // ------------------------------------
    struct {
        uint8_t CHIP_RDYn              :1 ;
        uint8_t STATE                  :3 ;
        uint8_t FIFO_BYTES_AVAILABLE   :4 ;
    } STATUS;
    // ------------------------------------

    // ------------------------------------
    // Configuration Registers
    // ------------------------------------
    struct {
        uint8_t reserved   :1 ;
        uint8_t GDO2_INV   :1 ;
        uint8_t GDO2_CFG   :6 ;
    } IOCFG2;

    // ------------------------------------
    // Status Registers
    // ------------------------------------
    uint8_t PATABLE ;

    uint8_t PARTNUM ;
    uint8_t VERSION ;
    

} cc2500_reg_t;


/*
 * CC2500 Functions Prototypes
 * ---------------------------
 */

// Configuration functions
void cc2500_init_spi(void);
void cc2500_init_sdi_isr(void);

void cc2500_write_cfg(void);
uint8_t cc2500_check_cfg(void);

// Low-level functions
void cc2500_spi_txrx(uint8_t* _wr_datas, uint8_t* _rd_datas, uint8_t _size);

// High-level functions
void cc2500_send_rf_data(uint8_t* _rf_datas, uint8_t _size);
void cc2500_receive_rf_data(uint8_t* _rf_datas, uint8_t _size);

uint8_t cc2500_scan_channels(void);
uint8_t cc2500_find_best_channel(void);

#endif /* ! _CC2500_H_ */
