/*
 * File:   beacon_SPI.c
 * Author: Julien
 *
 * Created on 30 avril 2017, 13:26
 */


#include "xc.h"
#include "beacon_SPI.h"
#include "board_cfg.h"



sint16_t beacon_SPI_regs[BEACON_SPI_T3_R - BEACON_SPI_STATE_RW];
volatile uint8_t isrCnt;


static void init_regs(void)
{
    uint8_t i;
    for(i=BEACON_SPI_STATE_RW; i <BEACON_SPI_T3_R ; i++) 
    {
        beacon_SPI_regs[i] = BEACON_SPI_ERROR_VALUE + i;
    }
    
    /*beacon_SPI_regs =
    {
        
    }*/
}

void beacon_SPI_init(void)
{
    init_regs();
    isrCnt = 0;
    
    // Setup hardware I/Os configuration
    SPI_SLAVE_CSN_TRIS = 1; //input
    SPI_SLAVE_CLK_TRIS = 1;
    SPI_SLAVE_MOSI_TRIS = 1;
    SPI_SLAVE_MISO_TRIS = 0; //output

    // Setup remapable pins
    SPI_SLAVE_MISO_RPN  = _RPOUT_SDO2; // configure RP output
    RPINR22bits.SDI2R   = SPI_SLAVE_MOSI_RP_NUMBER; //configure inputs
    RPINR22bits.SCK2R   = SPI_SLAVE_CLK_RP_NUMBER;
    RPINR23bits.SS2R    = SPI_SLAVE_CSN_RP_NUMBER;

    IFS2bits.SPI2IF = 0; // Clear interrupt flag
    IEC2bits.SPI2IE = 0; // Disable interrupt

    // Baudrate configuration (unused in slave mode)
    //SPIxCON1bits.PPRE   = CC2500_SPI_PPRE ;
    //SPIXCON1bits.SPRE   = CC2500_SPI_SPRE ;

    SPI2CON1bits.DISSCK = 0; // Internal serial clock
    SPI2CON1bits.DISSDO = 0; // SDOx is controlled by the module
    SPI2CON1bits.MODE16 = 0; // 8 bit mode  //TODO check if 16 bit fit's better
  
    SPI2CON1bits.SMP    = 0; // 0 when slave
    SPI2CON1bits.CKE    = 1; // Emits SDO on SCK falling edge (slave samples on rising)  
    SPI2CON1bits.CKP    = 0; // SCK idle state is LOW level
    SPI2CON1bits.SSEN   = 1; // CSN  pin used for slave mode
    SPI2CON1bits.MSTEN  = 0; // Slave mode is enabled

    SPI2STATbits.SPIEN = 1; // Enable SPI module
    
    //TODO ISR priority 
    // Write the SPIx Interrupt Priority Control (SPIxIP) bits in the respective IPCx register to set the interrupt priority
    SPI2BUF         = 0xf3; // Clear data to be transmitted
    IFS2bits.SPI2IF = 0; // Clear interrupt flag
    IEC2bits.SPI2IE = 1; // Enable interrupt
}

// SPI2 RX ISR
void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void) {
    
    //get reg number
    //ger R/W bit
    // do necessary with following byte(s)
    isrCnt++;
    
    IFS2bits.SPI2IF = 0 ; // Clear interrupt flag
}