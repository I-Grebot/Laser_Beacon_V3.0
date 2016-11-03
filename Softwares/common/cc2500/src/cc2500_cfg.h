/* -----------------------------------------------------------------------------
 * CC2500
 * I-Grebot RF Module CC2500 Library
 * -----------------------------------------------------------------------------
 * File        : cc2500_cfg.h
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

#ifndef _CC2500_CFG_H_
#define _CC2500_CFG_H_

/*
 * CC2500 Library RF Configuration
 * -------------------------------
 */

// Registers linked to functionality, defaulted to a
// given value but which can be overwritten.
#define CC2500_CFG_IOCFG2       0x29 // CHIP_RDYn
#define CC2500_CFG_IOCFG1       0x06 // 
#define CC2500_CFG_IOCFG0       0x3F // CLK_XOSC/192
#define CC2500_CFG_FIFOTHR      0x00 // 4 RX Bytes, 61 TX Bytes
#define CC2500_CFG_PKTLEN       0x05 // Default packet length when fixed size is used
#define CC2500_CFG_PKTCTRL1     0x0E // Sync word always accepted, CRC autoflush, Append RSSI, Addr Check + 0 broadcast
#define CC2500_CFG_PKTCTRL0     0x04 // No whitening, normal packet format, CRC is ON, Fixed packet length
#define CC2500_CFG_ADDR         0x00 // Default device address
#define CC2500_CFG_CHANNR       0x00 // Default channel number
#define CC2500_CFG_MCSM1        0x2D // CCA asserted unless TX (to be changed!), Stay in RX after RX, Go to FSTXON after TX
#define CC2500_CFG_MCSM0        0x08 // Never auto-cal, XOSC Timeout =~150 us, no pin_ctrl, XOSC off in Sleep mode

// Registers linked with RF parameters
// -> XTAL @ 26.0 MHz
// -> Optimized for sensitivity
// -> Data Rate       = 500kbps
// -> Base Frequency  = 2433 MHz
// -> Channel Spacing = 200 kHz
// -> Modulation      = MSK
#define CC2500_CFG_SYNC1        0xD3
#define CC2500_CFG_SYNC0        0x91
#define CC2500_CFG_FSCTRL1      0x0C 
#define CC2500_CFG_FSCTRL0      0x00 
#define CC2500_CFG_FREQ2        0x5D 
#define CC2500_CFG_FREQ1        0x93 
#define CC2500_CFG_FREQ0        0xB1 
#define CC2500_CFG_MDMCFG4      0x0E
#define CC2500_CFG_MDMCFG3      0x3B
#define CC2500_CFG_MDMCFG2      0x73
#define CC2500_CFG_MDMCFG1      0x42
#define CC2500_CFG_MDMCFG0      0xF8
#define CC2500_CFG_DEVIATN      0x00
#define CC2500_CFG_MCSM2        0x07
#define CC2500_CFG_FOCCFG       0x1D
#define CC2500_CFG_BSCFG        0x1C
#define CC2500_CFG_AGCTRL2      0xC7
#define CC2500_CFG_AGCTRL1      0x40
#define CC2500_CFG_AGCTRL0      0xB0
#define CC2500_CFG_WOREVT1      0x87
#define CC2500_CFG_WOREVT0      0x6B
#define CC2500_CFG_WORCTRL      0xF8
#define CC2500_CFG_FREND1       0xB6
#define CC2500_CFG_FREND0       0x10
#define CC2500_CFG_FSCAL3       0xEA
#define CC2500_CFG_FSCAL2       0x0A
#define CC2500_CFG_FSCAL1       0x00
#define CC2500_CFG_FSCAL0       0x19
#define CC2500_CFG_RCCTRL1      0x41
#define CC2500_CFG_RCCTRL0      0x00

// Virtual registers for PATABLE
#define CC2500_CFG_PATABLE0     0xFF // + 0dB
#define CC2500_CFG_PATABLE1     0x00 // -55dB
#define CC2500_CFG_PATABLE2     0x00 // -55dB
#define CC2500_CFG_PATABLE3     0x00 // -55dB
#define CC2500_CFG_PATABLE4     0x00 // -55dB
#define CC2500_CFG_PATABLE5     0x00 // -55dB
#define CC2500_CFG_PATABLE6     0x00 // -55dB
#define CC2500_CFG_PATABLE7     0x00 // -55dB

// Maximum Channel number so that
// base_freq + chann_nr * chan_spacing is
// within the valid range [2400.0 ; 2483.5] MHz
#define CC2500_CHANNR_MAX       0xFC

#endif /* ! _CC2500_CFG_H_ */
