#include "igrecan.h"

// RAM Memory space reserved for DMA usage
// 8 int (16 bits) per buffer are needed to store
// a full CAN frame (doesn't contain only payload!)
uint16_t can_buffers[CAN_DMA_BUFFERS][8] __attribute__((space(dma), aligned(CAN_DMA_BUFFERS*16)));

// CAN Configuration structure : declared outside of this module
extern can_cfg_t can_cfg ;

// -----------------------------------------------------------------------------
// CONFIGURATION FUNCTIONS
// -----------------------------------------------------------------------------

/*
 * Small routine allowing CAN modes change
 */
inline void can_set_mode(uint8_t mode) {

    // Ensure that the mode is coded on 3 bits
    mode &= 0x7;

    // Request disered mode for CAN module 1
    C1CTRL1bits.REQOP = mode;
    while (C1CTRL1bits.OPMODE != mode);
}

/*
 * Setup the DMA configuration for CAN module
 */
void can_dma_config(void) {

    // Configure DMA Channel 0 for CAN TX
    DMACS0              = 0; // Clear read/write collision flags
    DMA0CONbits.SIZE    = 0; // Word transfer mode
    DMA0CONbits.AMODE   = 2; // Peripheral Indirect Addressing
    DMA0CONbits.MODE    = 0; // Continuous mode, single buffer
    DMA0CONbits.DIR     = 1; // RAM to Peripheral (CAN TX)
    DMA0PAD = (volatile uint16_t) &C1TXD  ; // ECAN1 Peripheral address
    DMA0CNT = 7            ; // Transfers 8 words at a time
    DMA0STA = __builtin_dmaoffset(&can_buffers);
    DMA0REQ = DMA_C1TX_REQ ; // ECAN1 TX Event
    DMA0CONbits.CHEN = 1   ; // Enable DMA Channel

    // Configure DMA Channel 2 for CAN RX
    DMACS0              = 0; // Clear read/write collision flags
    DMA2CONbits.SIZE    = 0; // Word transfer mode
    DMA2CONbits.AMODE   = 2; // Peripheral Indirect Addressing
    DMA2CONbits.MODE    = 0; // Continuous mode, single buffer
    DMA2CONbits.DIR     = 0; // RAM to Peripheral (CAN RX)
    DMA2PAD = (volatile uint16_t) &C1RXD ; // ECAN1 Peripheral address
    DMA2CNT = 7            ; // Transfers 8 words at a time
    DMA2STA = __builtin_dmaoffset(&can_buffers);
    DMA2REQ = DMA_C1RX_REQ ; // ECAN1 RX Event
    DMA2CONbits.CHEN = 1   ; // Enable DMA Channel
}

/*
 * Main CAN Setup function :
 * - Init. I/Os remapable pins and directions
 * - Init. clock parameters
 * - Init. buffers configuration
 */
void can_init(void) {

    // Setup CAN pins
    UNLOCK_PPS
    RPINR26bits.C1RXR = ECAN1_RX_PIN ;    
    ECAN1_TX_RPN      = 0x10         ; // 0x10 : C1TX
    ECAN1_RX_TRIS     = 1            ; // Input
    ECAN1_TX_TRIS     = 0            ; // Output
    LOCK_PPS

    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);

    // FCAN is selected to be FCY
    C1CTRL1bits.CANCKS = 0x1;

    // Baudrate value
    C1CFG1bits.BRP = CAN_BRP_VAL;

    // Define quantication timings
    C1CFG1bits.SJW      = CAN_SJW    -1; // Synchronization Jump Width
    C1CFG2bits.SEG1PH   = CAN_SEG1PH -1; // Phase Segment 1
    C1CFG2bits.SEG2PHTS = 1            ; // Phase Segment 2 time is set to be programmable
    C1CFG2bits.SEG2PH   = CAN_SEG2PH -1; // Phase Segment 2
    C1CFG2bits.PRSEG    = CAN_PRSEG  -1; // Propagation Segment time
    C1CFG2bits.SAM      = 1            ; // Bus line is sampled three times at the sample point

    // Assign DMA buffers and fifo RX starting buffer
    C1FCTRLbits.DMABS = CAN_DMA_DMABS ;
    C1FCTRLbits.FSA   = CAN_DMA_RX_START ;

    // Assign buffers TX enables
    // Up to 8 buffers are available
    // All other buffers from 8 to 31 are RX
    if(CAN_DMA_RX_START>0) C1TR01CONbits.TXEN0 = 1; else C1TR01CONbits.TXEN0 = 0;
    if(CAN_DMA_RX_START>1) C1TR01CONbits.TXEN1 = 1; else C1TR01CONbits.TXEN1 = 0;
    if(CAN_DMA_RX_START>2) C1TR23CONbits.TXEN2 = 1; else C1TR23CONbits.TXEN2 = 0;
    if(CAN_DMA_RX_START>3) C1TR23CONbits.TXEN3 = 1; else C1TR23CONbits.TXEN3 = 0;
    if(CAN_DMA_RX_START>4) C1TR45CONbits.TXEN4 = 1; else C1TR45CONbits.TXEN4 = 0;
    if(CAN_DMA_RX_START>5) C1TR45CONbits.TXEN5 = 1; else C1TR45CONbits.TXEN5 = 0;
    if(CAN_DMA_RX_START>6) C1TR67CONbits.TXEN6 = 1; else C1TR67CONbits.TXEN6 = 0;
    if(CAN_DMA_RX_START>7) C1TR67CONbits.TXEN7 = 1; else C1TR67CONbits.TXEN7 = 0;

    // Define CAN TX buffers priorities, specifically
    // used regarding the message priority which has to be sent.
    // If more or less TX buffers are used, they will have the default Priority
    C1TR01CONbits.TX0PRI = 0b11; // Define Highest priority for TX buffer 0
    C1TR01CONbits.TX1PRI = 0b10; // Define Default priority for TX buffer 1
    C1TR23CONbits.TX2PRI = 0b01; // Define Low     priority for TX buffer 2
    C1TR23CONbits.TX3PRI = 0b00; // Define Lowest  priority for TX buffer 3

    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);

    // Ensure correct programming of filters
    C1CTRL1bits.WIN = 1;

    // Match only message types that correspond to EXID
    C1RXM0SIDbits.MIDE = 1 ;
    C1RXM1SIDbits.MIDE = 1 ;
    C1RXM2SIDbits.MIDE = 1 ;

    // Bits EIDx are don't care in filter comparisons
    C1RXM0SIDbits.EID = 0 ;
    C1RXM1SIDbits.EID = 0 ;
    C1RXM2SIDbits.EID = 0 ;

    // Clear EXID bits to accept only standard messages
    C1RXF0SIDbits.EXIDE  = 0 ;
    C1RXF1SIDbits.EXIDE  = 0 ;
    C1RXF2SIDbits.EXIDE  = 0 ;
    C1RXF3SIDbits.EXIDE  = 0 ;
    C1RXF4SIDbits.EXIDE  = 0 ;
    C1RXF5SIDbits.EXIDE  = 0 ;
    C1RXF6SIDbits.EXIDE  = 0 ;
    C1RXF7SIDbits.EXIDE  = 0 ;
    C1RXF8SIDbits.EXIDE  = 0 ;
    C1RXF9SIDbits.EXIDE  = 0 ;
    C1RXF10SIDbits.EXIDE = 0 ;
    C1RXF11SIDbits.EXIDE = 0 ;
    C1RXF12SIDbits.EXIDE = 0 ;
    C1RXF13SIDbits.EXIDE = 0 ;
    C1RXF14SIDbits.EXIDE = 0 ;
    C1RXF15SIDbits.EXIDE = 0 ;

    // All acceptance filters use the FIFO
    C1BUFPNT4bits.F15BP = 0xF;
    C1BUFPNT4bits.F14BP = 0xF;
    C1BUFPNT4bits.F13BP = 0xF;
    C1BUFPNT4bits.F12BP = 0xF;
    C1BUFPNT3bits.F11BP = 0xF;
    C1BUFPNT3bits.F10BP = 0xF;
    C1BUFPNT3bits.F9BP  = 0xF;
    C1BUFPNT3bits.F8BP  = 0xF;
    C1BUFPNT2bits.F7BP  = 0xF;
    C1BUFPNT2bits.F6BP  = 0xF;
    C1BUFPNT2bits.F5BP  = 0xF;
    C1BUFPNT2bits.F4BP  = 0xF;
    C1BUFPNT1bits.F3BP  = 0xF;
    C1BUFPNT1bits.F2BP  = 0xF;
    C1BUFPNT1bits.F1BP  = 0xF;
    C1BUFPNT1bits.F0BP  = 0xF;

    // End of filters register programming
    C1CTRL1bits.WIN = 0;

    // Clear RX and Overflow flags
    C1RXFUL1 = 0;
    C1RXFUL2 = 0;
    C1RXOVF1 = 0;
    C1RXOVF2 = 0;
}

/*
 * CAN Interrupt-Sub-Routines configuration
 */
void can_isr_config(void) {

    IEC2bits.C1IE     = 1; // Enable CAN 1 Interrupts
  //C1INTEbits.TBIE   = 1; // Enable Transmit Interrupts
    C1INTEbits.RBIE   = 1; // Enable Receive Interrupts
  //C1INTEbits.FIFOIE = 1; // Enable FIFO Almost-Full Receive Interrupts
  //IEC0bits.DMA0IE   = 1; // Enable DMA channel 0 (TX) Interrupts
  //IEC1bits.DMA2IE   = 1; // Enable DMA channel 2 (RX) Interrupts

    // Clear flags
    C1INTFbits.RBIF   = 0;
    C1INTFbits.TBIF   = 0;
    IFS2bits.C1IF     = 0;
    IFS0bits.DMA0IF   = 0;
    IFS1bits.DMA2IF   = 0;
}

// -----------------------------------------------------------------------------
// MASK AND ACCEPTANCE FILTERS CONFIGURATION
// -----------------------------------------------------------------------------

/*
 * Define a mask SID for a given mask
 */
void can_set_mask(uint8_t mask_no, uint16_t mask_cfg) {
    
    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);
    
    // To ensure correct programming of filters
    C1CTRL1bits.WIN = 1;

    // Affect the correct mask SID with configuration
    switch(mask_no) {
        case CAN_MASK_2 : C1RXM2SIDbits.SID = mask_cfg; break;
        case CAN_MASK_1 : C1RXM1SIDbits.SID = mask_cfg; break;
        default         : C1RXM0SIDbits.SID = mask_cfg; break;
    }

    // To ensure correct usage of buffers control registers
    C1CTRL1bits.WIN = 0;

    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);
}

/*
 * Define an acceptance filter SID for a given filter
 */
void can_set_filter(uint8_t filter_no, uint16_t sid) {

    // Ensure that SID is on 11 bits
    sid &= CAN_MASK_SID;

    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);

    // To ensure correct programming of filters
    C1CTRL1bits.WIN = 1;

    // Affect the correct filter SID with filtering value
    switch(filter_no) {
        case 15: C1RXF15SIDbits.SID = sid; break;
        case 14: C1RXF14SIDbits.SID = sid; break;
        case 13: C1RXF13SIDbits.SID = sid; break;
        case 12: C1RXF12SIDbits.SID = sid; break;
        case 11: C1RXF11SIDbits.SID = sid; break;
        case 10: C1RXF10SIDbits.SID = sid; break;
        case  9: C1RXF9SIDbits.SID  = sid; break;
        case  8: C1RXF8SIDbits.SID  = sid; break;
        case  7: C1RXF7SIDbits.SID  = sid; break;
        case  6: C1RXF6SIDbits.SID  = sid; break;
        case  5: C1RXF5SIDbits.SID  = sid; break;
        case  4: C1RXF4SIDbits.SID  = sid; break;
        case  3: C1RXF3SIDbits.SID  = sid; break;
        case  2: C1RXF2SIDbits.SID  = sid; break;
        case  1: C1RXF1SIDbits.SID  = sid; break;
        default: C1RXF0SIDbits.SID  = sid; break;
    }

    // To ensure correct usage of buffers control registers
    C1CTRL1bits.WIN = 0;

    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);
}

/*
 * Associate a CAN acceptance filter to a mask
 */
void can_assoc_filter(uint8_t filter_no, uint8_t mask_no) {
    
    // Ensure that mask_no is on 2 bits
    mask_no &= 0b11;

    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);

    // To ensure correct programming of filters
    C1CTRL1bits.WIN = 1;

    // Clear previous association and set the new one
    // in the dedicated register.
    if(filter_no <= 7) {
        // CiFMSKSEL1 : F7MSK<1:0>, F6MSK<1:0> ... F0MSK<1:0>
        filter_no <<= 1;
        C1FMSKSEL1 &= ~(0b11 << ((uint16_t) filter_no));
        C1FMSKSEL1 |= (mask_no << ((uint16_t) filter_no));
    } else if(filter_no <=15) {
        // CiFMSKSEL2 : F15MSK<1:0>, F14MSK<1:0> ... F8MSK<1:0>
        filter_no = (filter_no-8) << 1;
        C1FMSKSEL2 &= ~(0b11 << ((uint16_t) filter_no));
        C1FMSKSEL2 |= (mask_no << ((uint16_t) filter_no));
    }

    // To ensure correct usage of buffers control registers
    C1CTRL1bits.WIN = 0;

    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);
}

/*
 * Enable a given CAN acceptance filter
 */
void can_enable_filter(uint8_t filter_no) {

    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);

    // To ensure correct programming of filters
    C1CTRL1bits.WIN = 1;
    
    // Enable specified filter
    // Cast in int is required since destination is a 16 bits register
    C1FEN1bits.FLTEN |= (1<<((uint16_t) filter_no));

    // To ensure correct usage of buffers control registers
    C1CTRL1bits.WIN = 0;
    
    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);
}

/*
 * Disable a given CAN acceptance filter
 */
void can_disable_filter(uint8_t filter_no) {

    // Switch to configuration mode
    can_set_mode(CAN_MODE_INIT);

    // To ensure correct programming of filters
    C1CTRL1bits.WIN = 1;

    // Disable specified filter
    // Cast in int is required since destination is a 16 bits register
    C1FEN1bits.FLTEN &= ~(1<<((uint16_t) filter_no));

    // To ensure correct usage of buffers control registers
    C1CTRL1bits.WIN = 0;

    // Switch back to normal mode
    can_set_mode(CAN_MODE_NORMAL);
}

// -----------------------------------------------------------------------------
// PROCESSING FUNCTIONS
// -----------------------------------------------------------------------------

/*
 * CAN Transmit function :
 *  Select the correct priority buffer before starting anything.
 *  Messages dont only have a high priority regarding
 *  their ID: they are also handled faster using the
 *  prioritized buffers mean (see dma configuration).
 *  However, if a lower-priority buffer is free while the
 *  actual message's priority buffer is busy, it'll also be used
 *  to improve the global throughput without affecting
 *  higher-priority messages.
 */
void can_send(can_msg_t * message) {

    // Pointer on buffer used to send data
    uint16_t * can_buffer;

    // Memorize selected CAN buffer
    uint16_t buffer_no;
 
    // Wait for previous transmission to end and define the emitting buffer.
    switch(message->pid) {
        case CAN_PID_HIGH :

            // Wait until one buffer is free.
            while((0xF7F7 | C1TR01CON | C1TR23CON) == 0xFFFF);

            // Its now required to check which'll be used.
            if     (!C1TR01CONbits.TXREQ0) buffer_no = 0;
            else if(!C1TR01CONbits.TXREQ1) buffer_no = 1;
            else if(!C1TR23CONbits.TXREQ2) buffer_no = 2;
            else                           buffer_no = 3;

        break;
        
        case CAN_PID_DEFAULT :

            // Buffer 0 can't be used.
            while( (C1TR01CONbits.TXREQ1) && ((0xF7F7 | C1TR23CON) == 0xFFFF));

            // Its now required to check which'll be used.
            if     (!C1TR01CONbits.TXREQ1) buffer_no = 1;
            else if(!C1TR23CONbits.TXREQ2) buffer_no = 2;
            else                           buffer_no = 3;

        break;

        case CAN_PID_LOW :

            // Buffers 0 and 1 can't be used.
            while((0xF7F7 | C1TR23CON) == 0xFFFF);

            // Its now required to check which'll be used.
            if(!C1TR23CONbits.TXREQ2) buffer_no = 2;
            else                      buffer_no = 3;

        break;

        case CAN_PID_DEBUG :
        default :

            // Buffers 0, 1 and 2 can't be used.
            while(C1TR23CONbits.TXREQ3);

            buffer_no = 3;

        break;
    }

    // Select correct DMA buffer
    can_buffer = (uint16_t *) (can_buffers + buffer_no);
    
    // Now ready to setup message content
    can_buffer[0] = ((CAN_MAKE_SID(message->pid, message->fid)) << 2) | ((message->rtr) << 1);
    can_buffer[1] = 0;
    
    // Process DLC and PAYLOAD only if message is not RTR
    if(!(message->rtr)) {
        can_buffer[2] = (message->dlc) & 0xF;
        can_buffer[3] = (((uint16_t) message->payload[1]) << 8) | message->payload[0];
        can_buffer[4] = (((uint16_t) message->payload[3]) << 8) | message->payload[2];
        can_buffer[5] = (((uint16_t) message->payload[5]) << 8) | message->payload[4];
        can_buffer[6] = (((uint16_t) message->payload[7]) << 8) | message->payload[6];
    }

    // Set the send request
    switch(buffer_no) {
        case  0: C1TR01CONbits.TXREQ0 = 1; break;
        case  1: C1TR01CONbits.TXREQ1 = 1; break;
        case  2: C1TR23CONbits.TXREQ2 = 1; break;
        default: C1TR23CONbits.TXREQ3 = 1; break;
    }

}

/*
 * CAN Receive function :
 * Match all CAN parameters assuming that it's a standard frame.
 * Fill the configuration structure RX message so it can be
 * dealt later by the processing function.
 */
void can_receive(uint8_t buffer_index) {

    // Read the DMA space and retrieve the CAN message
    can_cfg.rx_msg.pid        = ((can_buffers[buffer_index][0] >> 2) & CAN_MASK_PID) >> CAN_SHIFT_PID;
    can_cfg.rx_msg.fid        =  (can_buffers[buffer_index][0] >> 2) & CAN_MASK_FID;
    can_cfg.rx_msg.rtr        =  (can_buffers[buffer_index][0] >> 1) & 0x0001 ;
    can_cfg.rx_msg.dlc        =  (can_buffers[buffer_index][2]) & 0xF ;
    // Read all the payload even if dlc is smaller.
    can_cfg.rx_msg.payload[0] = (uint8_t) (can_buffers[buffer_index][3]     );
    can_cfg.rx_msg.payload[1] = (uint8_t) (can_buffers[buffer_index][3] >> 8);
    can_cfg.rx_msg.payload[2] = (uint8_t) (can_buffers[buffer_index][4]     );
    can_cfg.rx_msg.payload[3] = (uint8_t) (can_buffers[buffer_index][4] >> 8);
    can_cfg.rx_msg.payload[4] = (uint8_t) (can_buffers[buffer_index][5]     );
    can_cfg.rx_msg.payload[5] = (uint8_t) (can_buffers[buffer_index][5] >> 8);
    can_cfg.rx_msg.payload[6] = (uint8_t) (can_buffers[buffer_index][6]     );
    can_cfg.rx_msg.payload[7] = (uint8_t) (can_buffers[buffer_index][6] >> 8);
}

/*
 * Abort all transmissions
 */
inline void can_abort_all(void) {

    // Set the Abort All Pending Transmission bit,
    // will be cleared back when abortion is finished.
    C1CTRL1bits.ABAT = 1;
    while(C1CTRL1bits.ABAT);
}

// -----------------------------------------------------------------------------
// TOOLKIT AND DEBUG
// -----------------------------------------------------------------------------

/*
 * CAN Send Message function
 * Basic send of an unconstrained char array over CAN.
 * It does not work like printf directly and only output const strings.
 * In order to get a full debug capability, simply use sprintf() to
 * generate the static string you want to send (<stdio> is heavy).
 * This can provoque multiple consecutive CAN send as the string is
 * split in bloc of 7 bytes.
 */

void can_send_msg(uint8_t _len, char* _str) {

  uint8_t idx;
  char* p_str;

  // CAN TX message structures
  can_msg_t tx_msg;
  payload_t pl;

  // Define constant message values
  tx_msg.pid = CAN_PID_DEBUG;
  tx_msg.fid = CAN_FID_DEBUG_PRINTF;
  tx_msg.rtr = 0 ;
  tx_msg.dlc = CAN_DLC_DEBUG_PRINTF;
  pl.debug_printf.node = CAN_NODE_ID; // You can't talk anonymously!

  // Init pointer on first data to send
  p_str = _str;

  // Send all data
  while(_len) {

    // Define payload, pad with 0 is no more data
    for(idx = 0; idx<7; idx++, p_str++) {
      if(_len) {
        pl.debug_printf.data[idx] = (uint8_t) (*p_str);
        _len--;
      } else {
        pl.debug_printf.data[idx] = 0;
      }
    }

    // Set PL and send message
    can_set_pl_debug_printf(&tx_msg, &pl);
    can_send(&tx_msg);
  }

}


// -----------------------------------------------------------------------------
// ISRs
// -----------------------------------------------------------------------------

/*
 * Main ECAN1 Interrupt-Sub-Routine
 * Deal with TX IRQ (doesn't do much) and RX IRQ
 * It'll look recursively to process all un-treated messages,
 * in case the FIFO get filled by more than 1 message.
 */
void __attribute__((__interrupt__, no_auto_psv)) _C1Interrupt(void) {
    
    uint16_t buf_idx;
    
    // Clear TX interrupt
    if (C1INTFbits.TBIF) {
        C1INTFbits.TBIF = 0;
    }

    // Clear RX interrupt
    if (C1INTFbits.RBIF) {
        C1INTFbits.RBIF = 0;
    
        // Process all RX buffers
        // /!\ Handles maximum 16 buffers
        // If more is needed, then add to this function the support
        // of C1RXFUL2 handling
        for(buf_idx = CAN_DMA_RX_START; buf_idx<CAN_DMA_BUFFERS; buf_idx++) {

            // Current buffer needs to be processed
            if(C1RXFUL1 & (1 << ((uint16_t) buf_idx))) {

                // Copy the received message from DMA RAM into message buffer
                can_receive(buf_idx);
                
                // Process it with application function
                can_cfg.can_process_rx();

                // Clear the current buffer
                C1RXFUL1 &= ~(1<< ((uint16_t) buf_idx));
            }
        }
    }

    // Clear CAN1 global interrupt
    IFS2bits.C1IF = 0;
    
}

/*
 * DMA ISRs
 * Unused.
 */
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {
    IFS0bits.DMA0IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void) {
    IFS1bits.DMA2IF = 0;
}
