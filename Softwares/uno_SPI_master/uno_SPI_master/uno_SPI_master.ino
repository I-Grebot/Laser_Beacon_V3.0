#include <SPI.h>
#include "beacon_regs.h"

#define CS_PIN_NB 10


int readRegister(byte thisRegister) {
  unsigned int result = 0;   // result to return
  Serial.print("\t");
 
  int dataToSend = thisRegister | 0x8000; //read command
  // take the chip select low to select the device:
  digitalWrite(CS_PIN_NB, LOW);
  // send the device the register you want to read:
  SPI.transfer16(dataToSend);

  delay(1); //be sure the ISR can be treated on device side
  
  // send a value of 0 to read the first byte returned:
  result = SPI.transfer16(0x0000);
  
  // take the chip select high to de-select:
  digitalWrite(CS_PIN_NB, HIGH);
  // return the result:
  return (result);
}


// TODO read multiple registers

/*void writeRegister(byte thisRegister, int thisValue) {

  // SCP1000 expects the register address in the upper 6 bits
  // of the byte. So shift the bits left by two bits:
  thisRegister = thisRegister << 2;
  // now combine the register address and the command into one byte:
  byte dataToSend = thisRegister & 0b01111111;

  // take the chip select low to select the device:
  digitalWrite(CS_PIN_NB, LOW);

  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(CS_PIN_NB, HIGH);
}
*/



void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);

  SPI.begin();
  pinMode(CS_PIN_NB, OUTPUT);
  SPI.beginTransaction(SPISettings(1000, MSBFIRST, SPI_MODE0));
  
}


void loop() {
  // put your main code here, to run repeatedly:
  char reg;
  for(reg=BEACON_SPI_STATE_RW ; reg<BEACON_SPI_T3_R + 1 ; reg++)
  {
    int val = readRegister(reg);
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.println(val);
  }

  delay(1000);
  
}




