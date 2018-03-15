#ifndef DS3231_H
#define DS3231_H

//includes
#include <stdint.h>

//defines
#define DEBUG 1

class DS3231
{
private:

public:
      void sendByteToRTC(uint8_t address, uint8_t reg, uint8_t data);
      uint8_t requestByteFromRTC(uint8_t address,uint8_t reg);
      uint8_t decodeMin(uint8_t data);
      uint8_t decodeSec(uint8_t data);
      uint8_t encodeMin(uint8_t data);
      uint8_t encodeSec(uint8_t data);
      void sendMin(uint8_t data);
      void sendSec(uint8_t data);
      void sendHour24(uint8_t data);
      void sendHour12(uint8_t data);
      uint8_t getHour24();
      uint8_t getMin();
      uint8_t getSec();
      void printTime();
      char* getTime();
      uint8_t decodeHour24(uint8_t data);
      uint8_t decodeHour12(uint8_t data);
      uint8_t encodeHour24(uint8_t data);
      uint8_t encodeHour12(uint8_t data, uint8_t amPm);
      char* getAmPm(uint8_t data);

};
#endif
