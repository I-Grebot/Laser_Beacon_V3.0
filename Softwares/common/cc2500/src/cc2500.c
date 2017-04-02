/* -----------------------------------------------------------------------------
 * CC2500
 * I-Grebot RF Module CC2500 Library
 * -----------------------------------------------------------------------------
 * File        : cc2500.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-02-23
 * -----------------------------------------------------------------------------
 * Description
 *   This file is a library to be used with Microchip's dsPIC33F microcontroller
 *   familiy. This library contains necessary functions (not everything is
 *   supported/handled here) for managing a Radio-Frequency module CC2500.
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

#include "cc2500.h"

// Constant CC2500 registers configuration
// Declared in FLASH
const uint8_t cc2500_reg_cfg[CC2500_NB_REG] __attribute__((space(psv))) = {
  CC2500_CFG_IOCFG2
 ,CC2500_CFG_IOCFG1
 ,CC2500_CFG_IOCFG0
 ,CC2500_CFG_FIFOTHR
 ,CC2500_CFG_SYNC1
 ,CC2500_CFG_SYNC0
 ,CC2500_CFG_PKTLEN
 ,CC2500_CFG_PKTCTRL1
 ,CC2500_CFG_PKTCTRL0
 ,CC2500_CFG_ADDR
 ,CC2500_CFG_CHANNR
 ,CC2500_CFG_FSCTRL1
 ,CC2500_CFG_FSCTRL0
 ,CC2500_CFG_FREQ2
 ,CC2500_CFG_FREQ1
 ,CC2500_CFG_FREQ0
 ,CC2500_CFG_MDMCFG4
 ,CC2500_CFG_MDMCFG3
 ,CC2500_CFG_MDMCFG2
 ,CC2500_CFG_MDMCFG1
 ,CC2500_CFG_MDMCFG0
 ,CC2500_CFG_DEVIATN
 ,CC2500_CFG_MCSM2
 ,CC2500_CFG_MCSM1
 ,CC2500_CFG_MCSM0
 ,CC2500_CFG_FOCCFG
 ,CC2500_CFG_BSCFG
 ,CC2500_CFG_AGCTRL2
 ,CC2500_CFG_AGCTRL1
 ,CC2500_CFG_AGCTRL0
 ,CC2500_CFG_WOREVT1
 ,CC2500_CFG_WOREVT0
 ,CC2500_CFG_WORCTRL
 ,CC2500_CFG_FREND1
 ,CC2500_CFG_FREND0
 ,CC2500_CFG_FSCAL3
 ,CC2500_CFG_FSCAL2
 ,CC2500_CFG_FSCAL1
 ,CC2500_CFG_FSCAL0
 ,CC2500_CFG_RCCTRL1
 ,CC2500_CFG_RCCTRL0
};

const uint8_t cc2500_patable_cfg[CC2500_NB_PATABLE] __attribute__((space(psv))) = {
  CC2500_CFG_PATABLE0
 ,CC2500_CFG_PATABLE1
 ,CC2500_CFG_PATABLE2
 ,CC2500_CFG_PATABLE3
 ,CC2500_CFG_PATABLE4
 ,CC2500_CFG_PATABLE5
 ,CC2500_CFG_PATABLE6
 ,CC2500_CFG_PATABLE7
};

// Contains the buisness of each channel for the programmed base frequency
uint8_t chan_busy_cnt[CC2500_CHANNR_MAX] ;

// -----------------------------------------------------------------------------
// HARDWARE-RELATED FUNCTIONS
// -----------------------------------------------------------------------------

void cc2500_init_spi(void) {

  // Setup hardware I/Os configuration
  CC2500_SS_TRIS  = 0 ;
  CC2500_SCK_TRIS = 0 ;
  CC2500_SDO_TRIS = 0 ;
  CC2500_SDI_TRIS = 1 ;

  // Define I/Os remappable registers & values
  CC2500_SCK_RPN  = CC2500_SCK_PIN ;
  CC2500_SDO_RPN  = CC2500_SDO_PIN ;
  CC2500_SDI_RPN  = CC2500_SDI_PIN ;

  // Default un-active chip-select value
  CC2500_SS = 1 ;

  IFS0bits.SPI1IF = 0 ; // Clear interrupt flag
  IEC0bits.SPI1IE = 0 ; // Disable interrupt

  // Baudrate configuration
  SPI1CON1bits.PPRE   = CC2500_SPI_PPRE ;
  SPI1CON1bits.SPRE   = CC2500_SPI_SPRE ;

  SPI1CON1bits.DISSCK = 0 ; // Internal serial clock
  SPI1CON1bits.DISSDO = 0 ; // SDOx is controlled by the module
  SPI1CON1bits.MODE16 = 0 ; // 8 bit mode
  SPI1CON1bits.CKP    = 0 ; // SCK idle state is LOW level
  SPI1CON1bits.SMP    = 1 ; // Sample SDI on SCK rising edge (slave emits on falling)
  SPI1CON1bits.CKE    = 1 ; // Emits SDO on SCK falling edge (slave samples on rising)  
  SPI1CON1bits.MSTEN  = 1 ; // Master mode is enabled

  SPI1STATbits.SPIEN  = 1 ; // Enable SPI module

  SPI1BUF         = 0 ; // Clear data to be transmitted
  IFS0bits.SPI1IF = 0 ; // Clear interrupt flag
  IEC0bits.SPI1IE = 1 ; // Enable interrupt

}

// Setup External interrupt on SDI
void cc2500_init_sdi_isr(void) {
    
  // Just in case
  CC2500_SDI_TRIS = 1 ;

  // Map INT1 on SDI
  RPINR0bits.INT1R = CC2500_SDI_PIN ;

  // Interrupt on positive edge
  INTCON2bits.INT1EP = 1 ;
#warning "JST put at falling edge to trigger at end of packet reception instead start"

  // Define INT1 priority to middle
  //IPC5bits.INT1IP = 0b100 ;

  // Clear flag, enable interrupt
  IFS1bits.INT1IF = 0 ;
  IEC1bits.INT1IE = 1 ;
//
//    RPINR7bits.IC1R = CC2500_SDI_PIN ;
//
//    // Init Timer 2
//    T2CONbits.TON   = 0     ; // Disable Timer
//    T2CONbits.TCS   = 0     ; // Internal cycle clock selected
//    T2CONbits.TCKPS = 0b10  ; // Set prescaler = 1:64 ; TIM2 Freq = FCY / 64
//    TMR2            = 0     ; // Clear Timer
//    PR2             = 0xFFFF ; // Select TIM3 Periods
//
//    // Init Input Capture module 1
//    IC1CONbits.ICM      = 0b000 ; // Disable IC1
//    IC1CONbits.ICTMR    = 1     ; // Select TIM2 as time base
//    IC1CONbits.ICI      = 0b00  ; // Interrupt on the every captured event
//    IC1CONbits.ICM      = 0b001 ; // Edge capture mode
//
//    T2CONbits.TON   = 1 ;
  
}


// -----------------------------------------------------------------------------
// SPI LOW-LEVEL FUNCTIONS
// -----------------------------------------------------------------------------

// Single or Burst TX/RX transfer (depends on _size)
// Arrays endianness: data #0       is transfered/received at first
//                    data #_size-1 ...................... at last
void cc2500_spi_txrx(uint8_t* _wr_datas, uint8_t* _rd_datas, uint8_t _size) {

  uint8_t dummy ;
  uint8_t cnt ;

  // Size must be non-null
  if(_size == 0)
    return;

  // Inidicates to slave that TX/RX will start
  CC2500_SS = 0 ;

  // Loop on all data
  for(cnt = 0; cnt < _size ; cnt++) {

    // Wait until the previous TX data was transfered
    // in the SPIxTXB buffer
    while(SPI1STATbits.SPITBF);

    // Load TX buffer with next data
    SPI1BUF = _wr_datas[cnt] ; // Mapped on SPIxTXB during writes

    // Clear RX buffer before read
    dummy = SPI1BUF;

    // Wait until the RX buffer becomes full (data is received)
    // It will happen once interrupt will be generated
    // (cleared in dedicated ISR)
    while(!SPI1STATbits.SPIRBF);

    _rd_datas[cnt] = SPI1BUF ;

    // Wait until the TX buffer becomes free again
    while(SPI1STATbits.SPITBF);

  }

  // Stop TX/RX
  CC2500_SS = 1 ;

}

// -----------------------------------------------------------------------------
// CC2500 BASIC ACCESS ROUTINES
// -----------------------------------------------------------------------------

// Send a strobe and return chip status
uint8_t cc2500_send_strobe(uint8_t _strobe_addr) {

  uint8_t wr_datas[2];
  uint8_t rd_datas[2];

  // Build HEADER_strobe
  wr_datas[0] = CC2500_BUILD_HEADER(0, 0, _strobe_addr) ;
  wr_datas[1] = 0;
  
  // Send strobe and get status
  cc2500_spi_txrx(wr_datas, rd_datas, 2);

  return rd_datas[1] ;
}


// Write a single register and return chip status
uint8_t cc2500_write_reg(uint8_t _addr, uint8_t _value) {

  uint8_t wr_datas[2];
  uint8_t rd_datas[2];

  // Build HEADER_write
  wr_datas[0] = CC2500_BUILD_HEADER(0, 0, _addr) ;
  wr_datas[1] = _value;

  // Send strobe and get status
  cc2500_spi_txrx(wr_datas, rd_datas, 2);

  return rd_datas[1] ;
}

// Read a single status register
uint8_t cc2500_read_status(uint8_t _addr) {

  uint8_t wr_datas[2];
  uint8_t rd_datas[2];

  // Build HEADER_status (burst must be set!)
  wr_datas[0] = CC2500_BUILD_HEADER(1, 1, _addr) ;
  wr_datas[1] = 0;

  // Send strobe and get status
  cc2500_spi_txrx(wr_datas, rd_datas, 2);

  return rd_datas[1] ;
}

// Send some RF data
void cc2500_send_rf_data(uint8_t* _rf_datas, uint8_t _size) {

  uint8_t idx ;

  // +1 For Header byte
  uint8_t wr_datas[CC2500_FIFO_TX_DEPTH+1];
  uint8_t rd_datas[CC2500_FIFO_TX_DEPTH+1];

  if(_size > CC2500_FIFO_TX_DEPTH)
    _size = CC2500_FIFO_TX_DEPTH;
  else if(_size == 0)
    return ;

  // Build HEADER_fifo
  wr_datas[0] = CC2500_BUILD_HEADER(0, (_size==1?0:1), CC2500_ADDR_FIFO) ;
  for(idx = 1; idx <= _size ; idx++)
    wr_datas[idx] = _rf_datas[idx-1];

  // Send datas and get status
  cc2500_spi_txrx(wr_datas, rd_datas, _size+1);

}

// Receive some RF data
void cc2500_receive_rf_data(uint8_t* _rf_datas, uint8_t _size) {

  uint8_t idx ;

  // +1 For Header byte
  uint8_t wr_datas[CC2500_FIFO_TX_DEPTH+1];
  uint8_t rd_datas[CC2500_FIFO_TX_DEPTH+1];

  if(_size > CC2500_FIFO_TX_DEPTH)
    _size = CC2500_FIFO_TX_DEPTH;
  else if(_size == 0)
    return ;

  // Build HEADER_fifo
  wr_datas[0] = CC2500_BUILD_HEADER(1, (_size==1?0:1), CC2500_ADDR_FIFO) ;
  for(idx = 1; idx <= _size ; idx++)
    wr_datas[idx] = 0;

  // Send datas and get status
  cc2500_spi_txrx(wr_datas, rd_datas, _size+1);

  for(idx = 0; idx < _size ; idx++)
    _rf_datas[idx] = rd_datas[1+idx];

}

inline uint8_t cc2500_get_chip_state(void) {
  uint8_t status ;
  status = cc2500_send_strobe(CC2500_ADDR_STROBE_SNOP);
  return (status & CC2500_MASK_STATE) >> CC2500_SHIFT_STATE ;
}

inline uint8_t cc2500_get_partnum(void) {
  return cc2500_read_status(CC2500_ADDR_STATUS_PARTNUM);
}

inline uint8_t cc2500_get_version(void) {
  return cc2500_read_status(CC2500_ADDR_STATUS_VERSION);
}

inline sint8_t cc2500_get_rssi(void) {
  uint8_t rssi_reg ;
  rssi_reg = cc2500_read_status(CC2500_ADDR_STATUS_RSSI);
  return (((sint8_t) rssi_reg)>>1) - 70;
}

inline uint8_t cc2500_get_chip_marcstate(void) { 
  return cc2500_read_status(CC2500_ADDR_STATUS_MARCSTATE);
}

inline uint8_t cc2500_get_packet_status(void) {
  return cc2500_read_status(CC2500_ADDR_STATUS_PKTSTATUS);
}

// -----------------------------------------------------------------------------
// CONFIGURATION ROUTINES
// -----------------------------------------------------------------------------

void cc2500_write_cfg(void) {

  uint8_t idx ;

  // +1 For Header byte
  uint8_t wr_datas[CC2500_NB_REG+1];
  uint8_t rd_datas[CC2500_NB_REG+1];
  
  // Request IDLE state before writing any configuration
  cc2500_send_strobe(CC2500_ADDR_STROBE_SIDLE);
    
  // Wait for chip to be in IDLE
  while(cc2500_get_chip_state() != CC2500_STATE_IDLE);
  
  // Build HEADER_regburst, start from 1st address
  wr_datas[0] = CC2500_BUILD_HEADER(0, 1, 0) ;
  for(idx = 1; idx <= CC2500_NB_REG ; idx++)
    wr_datas[idx] = cc2500_reg_cfg[idx-1];

  // Write configuration registers
  cc2500_spi_txrx(wr_datas, rd_datas, CC2500_NB_REG+1);

  // Build HEADER_patable
  wr_datas[0] = CC2500_BUILD_HEADER(0, 1, CC2500_ADDR_PATABLE) ;
  for(idx = 1; idx <= CC2500_NB_PATABLE ; idx++)
    wr_datas[idx] = cc2500_patable_cfg[idx-1];

  // Write patable configuration
  cc2500_spi_txrx(wr_datas, rd_datas, CC2500_NB_PATABLE+1);

}

// Returns 0 if all configuration registers are correctly written
uint8_t cc2500_check_cfg(void) {

  uint8_t idx ;
  uint8_t wr_datas[CC2500_NB_PATABLE];
  uint8_t rd_datas[CC2500_NB_PATABLE];

  // Read-back all configuration registers 1 by 1
  for(idx = 0; idx < CC2500_NB_REG; idx++) {
    
    // Build header
    wr_datas[0] = CC2500_BUILD_HEADER(1, 0, idx) ;
    wr_datas[1] = 0 ;

    // Read register
    cc2500_spi_txrx(wr_datas, rd_datas, 2);

    // Check it against static configuration
    if(rd_datas[1] != cc2500_reg_cfg[idx])
      return 1;
  }

  // Prepare burst datas
  for(idx = 0; idx <= CC2500_NB_PATABLE; idx++) {
    wr_datas[idx] = CC2500_BUILD_HEADER(1, 1, CC2500_ADDR_PATABLE) ;
    rd_datas[idx] = 0;
  }

  // Send it
  cc2500_spi_txrx(wr_datas, rd_datas, CC2500_NB_PATABLE+1);

  // Check registers against static configuration
  for(idx = 1; idx < CC2500_NB_PATABLE+1; idx++)
    if(rd_datas[idx] != cc2500_patable_cfg[idx-1])
      return 2;

  // Everything is OK !
  return 0 ;

}

// -----------------------------------------------------------------------------
// SYSTEM ROUTINES
// -----------------------------------------------------------------------------

// Scan through all channels and return best (clearest) channel number
uint8_t cc2500_scan_channels(void) {

  uint16_t delay_cnt1 ;
  uint32_t delay_cnt2 ;
  
  uint16_t chan ;

  uint8_t packet_status ;

  // Scan through all channels
  for(chan=0; chan < CC2500_CHANNR_MAX; chan++) {
    // Reset channel's associated busy counter
    chan_busy_cnt[chan] = 0;

    // Set new channel address, calibrate again, clean RX buffer and go in RX
    cc2500_send_strobe(CC2500_ADDR_STROBE_SIDLE);
    while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);
    cc2500_write_reg(CC2500_ADDR_REG_CHANNR, chan);

    cc2500_send_strobe(CC2500_ADDR_STROBE_SCAL);
    while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);
    
    cc2500_send_strobe(CC2500_ADDR_STROBE_SFRX);
    while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_IDLE);

    cc2500_send_strobe(CC2500_ADDR_STROBE_SRX);
    while(cc2500_get_chip_marcstate() != CC2500_MARCSTATE_RX);

    for(delay_cnt1 = 0; delay_cnt1 < CC2500_CHANNEL_SCAN_RATE ; delay_cnt1++) {
      
      // Wait 1ms to make sure that RSSI / CCA are valid
      for(delay_cnt2 = 0xFFF; delay_cnt2; delay_cnt2--);

      packet_status = cc2500_get_packet_status() ;
      
      // Increment if CCA is cleared (channel is busy)
      if(!(packet_status & CC2500_MASK_CCA))
        chan_busy_cnt[chan] ++;

    } // delay_cnt1
  } // chan

}

uint8_t cc2500_find_best_channel(void) {
  
  uint16_t chan ;
  uint8_t lowest_busy_cnt ;
  uint8_t lowest_busy_cnt_chan ;

  // Maximum value for the poorest channel
  lowest_busy_cnt = CC2500_CHANNEL_SCAN_RATE ;

  for(chan = 0; chan < chan < CC2500_CHANNR_MAX; chan++) {

    // Return immediatly if there was absolutely no activity on
    // the given channel (best we can find)
    if(chan_busy_cnt[chan] == 0) {      
      return chan ;

    // Memorize minimum value between previous best and current
    } else if(chan_busy_cnt[chan] < lowest_busy_cnt) {
      lowest_busy_cnt = chan_busy_cnt[chan];
      lowest_busy_cnt_chan = chan ;
    }
  } // for chan

  return lowest_busy_cnt_chan ;
}

// -----------------------------------------------------------------------------
// INTERRUPT ROUTINES
// -----------------------------------------------------------------------------

// SPI RX ISR
void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void) {
  IFS0bits.SPI1IF = 0 ; // Clear interrupt flag
}

