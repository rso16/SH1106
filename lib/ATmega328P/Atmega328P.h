#ifndef Atmega328P_H
#define Atmega328P_H
//made by Rick Overhorst
//basic funcitions for the Arduino UNO



//includes
#include <stdint.h>
#include <avr/io.h>
#include <Arduino.h>
#include <math.h>
#include "Microcontroller.h"

#define DEBUG 0
#define clockspeed 16000000
//#include<std.h>
class Atmega328P : public Microcontroller
{
    private:

    public:
       void    UARTInit(uint8_t dataBits, uint8_t parityBit, uint8_t stopBits, uint32_t baud, uint8_t speed, uint8_t RT); //fuction to initialize the UART, takes the amount of data bits (5,6,6,8 or 9 bits), no, even or an odd parity bit, the amound of stop bits (1 or 2) and the baudrate returns the status code
       void    UARTBegin(long int baud); //function to begin the UART with the defaul settings and a baudrate. returns an status code.
       void    UARTSend(uint16_t data);
       void    UARTSend(uint8_t data);
       void    UARTSendBytes(uint8_t bytes[], uint8_t amountOfBytes);
       uint8_t UARTREAD();
       void    UARTREADBytes(uint8_t *bytes, uint8_t amountOfBytes);

       void    setDPM(uint8_t pin, uint8_t value);// set pin mode value = 0 or 1 for the digital pins
       void    setAPM(uint8_t pin, uint8_t value);// set pin mode value = 0 or 1 for the analog pins
       void    DW(uint8_t pin, uint8_t value);//digital write(dw) value = 0 or 1
       uint8_t DR(uint8_t pin);//digital read
       void    AW(uint8_t pin, uint8_t value);//same as dw but with analog pin
       void    toggleDP(uint8_t pin);
       uint8_t getPinStat(uint8_t pin);
       void    binToLed(uint8_t byte);

       uint8_t getBit(uint8_t data, uint8_t index);//gets the bit for the data (a byte) at the index
       void    sendI2CStart();
       void    sendI2CStop();
       void    sendI2CAddr(uint8_t addr);
       void    sendI2CData(uint8_t data);

  };
#endif
