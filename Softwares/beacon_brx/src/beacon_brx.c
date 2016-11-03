/* -----------------------------------------------------------------------------
 * Beacon [BRX]
 * I-Grebot Laser Beacon V3.0
 * -----------------------------------------------------------------------------
 * File        : beacon_brx.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2013-03-10
 * -----------------------------------------------------------------------------
 * Description
 *   This is the Laser Beacon V3 [BRX] board main module. This board handles:
 *     - Time-stamping of incoming laser pulses (measure time-delta)
 *     - Converts this value into mm unit
 *     - Arbitrate different detections between the 4 possible PDD board
 *     - Determines a very-rough orientation (N, NE, E, SE, S, SW, W, NW)
 *       (useful only with opponent beacons)
 *     - Send all this stuff quickly using the beacon_com (RF)
 * -----------------------------------------------------------------------------
 * Hardware ressources usage
 *   - TIM2/TIM3 for      PDD Timings
 *   - IC1  associated to N_B-A
 *   - IC2  associated to E_B-A
 *   - IC7  associated to S_B-A
 *   - IC8  associated to W_B-A
 *   - SPI1 for           RF Interface
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

#include "beacon_brx.h"

// -----------------------------------------------------------------------------
// CONFIGURATION
// -----------------------------------------------------------------------------

// Oscillator startup configuration, on internal fast RC
_FOSCSEL(FNOSC_FRC);

// Configure POSC in HS mode and enable clock switching.
// Also enable multiple remapping.
_FOSC(POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSECME);

// Watchdog is disabled
_FWDT(FWDTEN_OFF);

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// Software IRQ
uint8_t sw_irq;

// Board ID defined by the beacon_system
extern uint8_t board_id;

// Setup an UART, with the decicated baudrate
inline void uart_debug_setup(void)
{
    DEBUG_UART_RX_TRIS = 1 ; // DEBUG UART RX as input
    DEBUG_UART_TX_TRIS = 0 ; // DEBUG UART TX as output
    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // No parity, 8 data bit
    U1MODEbits.ABAUD = 0; // Auto-baud disabled
    U1MODEbits.BRGH  = 0; // Low-speed mode
    U1BRG = DEBUG_UART_BRG;    // Baud-rate config

    U1MODEbits.UARTEN = 1;// Enable UART
    U1STAbits.UTXEN = 1;  // Enable TX on UART

    // Configure UART1 RX ISR
    IFS0bits.U1RXIF = 0 ; // Clear interrupt
    IPC2bits.U1RXIP = 1 ; // Set priority to 1 (low)
    IEC0bits.U1RXIE = 0 ; // Enable interrupt

    // Clear Screen
    printf("\f");

}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

int main(void) {

  uint8_t err_code;
  uint32_t cnt;
  uint16_t fake_dist_mm;

  // Oscillator needs to be started first
  osc_init();

  // All I/Os are digital by default
  ADPCFG   = 0xFFFF;
  AD1PCFGL = 0xFFFF;

  // TEMP uart for debug
  uart_debug_setup();

  // Modules initializations
  led_init();  
  photo_detect_init();
  err_code = beacon_com_init();

  if(err_code)
    printf("An error occured during initializations!, err_code = %d\n", err_code);
  
  printf("Hello from BRX! Your board id is %d\n", board_id);

  beacon_com_startup();
  photo_detect_run();

  // Main loop... !
  fake_dist_mm = 0;
  while(1) {
    for(cnt=1000000;cnt;cnt--);
    if(DIL_1) {
      LED_2 = ~LED_2;

      beacon_com_send_dist(fake_dist_mm++);

    }

  }

} // main
