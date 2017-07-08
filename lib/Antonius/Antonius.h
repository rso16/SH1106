#ifndef ANTONIUS_H
#define ANTONIUS_H
//made by Rick Overhorst
//basic funcitions for the Arduino UNO



//includes
#include <stdint.h>
#include<avr/io.h>
#include<Arduino.h>
#include<math.h>
#define RTC_ADDRESS 0x68
#define SEC 0x00
#define MIN 0x01
#define HOUR 0x02
#define DEBUG 1
#define SH1106_ADDR 0x78
//#include<std.h>
class Antonius
  {
    private:

    public:
        void setDPM(uint8_t pin, uint8_t value);// set pin mode value = 0 or 1 for the digital pins
        void setAPM(uint8_t pin, uint8_t value);// set pin mode value = 0 or 1 for the analog pins
        void DW(uint8_t pin, uint8_t value);//digital write(dw) value = 0 or 1
        uint8_t DR(uint8_t pin);//digital read
        void AW(uint8_t pin, uint8_t value);//same as dw but with analog pin
        uint8_t getBit(uint8_t data, uint8_t index);//gets the bit for the data (a byte) at the index
        void sendByteToRTC(uint8_t address, uint8_t reg, uint8_t data);
        uint8_t requestByteFromRTC(uint8_t address,uint8_t reg);
        uint8_t decodeMin(uint8_t data);
        uint8_t decodeSec(uint8_t data);
        uint8_t encodeMin(uint8_t data);
        uint8_t encodeSec(uint8_t data);
        uint8_t getMin();
        uint8_t getSec();
        void printTime();
        char* getTime();
        uint8_t decodeHour24(uint8_t data);
        uint8_t decodeHour12(uint8_t data);
        uint8_t encodeHour24(uint8_t data);
        uint8_t encodeHour12(uint8_t data, uint8_t amPm);
        char*   getAmPm(uint8_t data);
        void    sendStart();
        void    sendStop();
        void    sendAddr(uint8_t addr);
        void    sendCommand(uint8_t command);
        void    sendData(uint8_t data);
        void    sendRAM(uint8_t data);
  };
#endif
