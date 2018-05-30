#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

//includes
#include <stdint.h>


//defines
#define FAILED      0
#define SUCCES      1

#define NOPARITY    0
#define EVENPARITY  1
#define ODDPARITY   2

#define NORMALSPEED 0
#define DOUBLESPEED 1

class Microcontroller
{
  private:

  public:
     virtual void    setDPM(uint8_t pin, uint8_t value) = 0;// set pin mode value = 0 or 1 for the digital pins
     virtual void    setAPM(uint8_t pin, uint8_t value) = 0;// set pin mode value = 0 or 1 for the analog pins
     virtual void    DW(uint8_t pin, uint8_t value)     = 0;//digital write(dw) value = 0 or 1
     virtual uint8_t DR(uint8_t pin)                    = 0;//digital read
     virtual void    AW(uint8_t pin, uint8_t value)     = 0;//same as dw but with analog pin
     virtual uint16_t AR(uint8_t pin) = 0;
     virtual uint8_t getPinStat(uint8_t pin)            = 0;
     virtual void    toggleDP(uint8_t pin)              = 0;
     virtual void    binToLed(uint8_t byte)             = 0;

     virtual uint8_t getBit(uint8_t data, uint8_t index) = 0;//gets the bit for the data (a byte) at the index

     virtual void    sendI2CStart()            = 0;
     virtual void    sendI2CStop()             = 0;
     virtual void    sendI2CAddr(uint8_t addr) = 0;
     virtual void    sendI2CData(uint8_t data) = 0;

     virtual void    UARTInit(uint8_t dataBits, uint8_t parityBit, uint8_t stopBits, uint32_t baud, uint8_t speed, uint8_t RT) = 0; //fuction to initialize the UART, takes the amount of data bits (5,6,6,8 or 9 bits), no, even or an odd parity bit, the amound of stop bits (1 or 2) and the baudrate returns the status code
     virtual void    UARTBegin(long int baud)   = 0; //function to begin the UART with the defaul settings and a baudrate. returns an status code.
     virtual void    UARTSend(uint16_t data)    = 0;
     virtual void    UARTSend(uint8_t data)     = 0;
     virtual void    UARTSendBytes(uint8_t bytes[], uint8_t amountOfBytes) = 0;
     virtual uint8_t UARTRead() = 0;
     virtual void    UARTREADBytes(uint8_t *bytes, uint8_t amountOfBytes) = 0;
     virtual void    println(uint8_t *bytes) = 0;

     virtual void    EEPROM_Write(uint32_t addr, uint8_t data) = 0;
     virtual void    EEPROM_WriteBytes(uint32_t addr, uint8_t data[], uint32_t amountOfBytes) = 0;
     virtual uint8_t EEPROM_Read(uint32_t addr) = 0;
     virtual void    EEPROM_ReadBytes(uint32_t addr, uint8_t data[], uint32_t amountOfBytes) = 0;





};

#endif
