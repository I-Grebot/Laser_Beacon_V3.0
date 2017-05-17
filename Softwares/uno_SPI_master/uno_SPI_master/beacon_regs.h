/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: Julien Staub
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BEACON_SPI_CFG_H
#define	BEACON_SPI_CFG_H



// 1-----------------------------------------
//  |                                       |
//  |                                       |
//  |                                       |
//  |                                       | 3
//  |                        +              |
//  |                      x--->A=          |
//  |                                       |
// 2x----------------------------------------
//(0,0)

//-------------------------------------------------------------
// R/W |                    ADDR 6-0                          |
//-------------------------------------------------------------
// 1 for read, 0 for write
// all registers are signed 16 bits
// registers can be accessed by burst

#define BEACON_SPI_STATE_RW         0x10

#define BEACON_SPI_REF1_X_RW        0x11  // position of the right photodiode for each reference turret
#define BEACON_SPI_REF1_Y_RW        0x12
#define BEACON_SPI_REF2_X_RW        0x13
#define BEACON_SPI_REF2_Y_RW        0x14
#define BEACON_SPI_REF3_X_RW        0x15
#define BEACON_SPI_REF3_Y_RW        0x16

#define BEACON_SPI_RPS_RW           0x17  // rotation speed
#define BEACON_SPI_LASER_DX_RW      0x18  // distance between lasers
#define BEACON_SPI_LASER_DA_RX      0x19  // angle between lasers

#define BEACON_SPI_MAIN_ABS_X_R     0x1A
#define BEACON_SPI_MAIN_ABS_Y_R     0x1B
#define BEACON_SPI_MAIN_ABS_A_R     0x1C

#define BEACON_SPI_R1_ABS_X_R       0x1D
#define BEACON_SPI_R1_ABS_Y_R       0x1E
#define BEACON_SPI_R1_ABS_A_R       0x1F  // absolute angle of rebot
#define BEACON_SPI_R1_REL_D_R       0x20
#define BEACON_SPI_R1_REL_A_R       0x21  // relative angle to front of btx

#define BEACON_SPI_R2_ABS_X_R       0x22
#define BEACON_SPI_R2_ABS_Y_R       0x23
#define BEACON_SPI_R2_ABS_A_R       0x24
#define BEACON_SPI_R2_REL_D_R       0x25
#define BEACON_SPI_R2_REL_A_R       0x26

#define BEACON_SPI_R3_ABS_X_R       0x27
#define BEACON_SPI_R3_ABS_Y_R       0x28
#define BEACON_SPI_R3_ABS_A_R       0x29
#define BEACON_SPI_R3_REL_D_R       0x2A
#define BEACON_SPI_R3_REL_A_R       0x2B
//for debug
#define BEACON_SPI_D1_R             0x2C
#define BEACON_SPI_A1_R             0x2D
#define BEACON_SPI_T1_R             0x2E

#define BEACON_SPI_D2_R             0x2F
#define BEACON_SPI_A2_R             0x30
#define BEACON_SPI_T2_R             0x31

#define BEACON_SPI_D3_R             0x32
#define BEACON_SPI_A3_R             0x33
#define BEACON_SPI_T3_R             0x34


//error value
#define BEACON_SPI_ERROR_VALUE      0x8000

#endif	/* BEACON_SPI_CFG_H */

