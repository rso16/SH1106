#ifndef SH1106_H
#define SH1106_H
//made by Rick Overhorst




//includes
#include <stdint.h>
#include<avr/io.h>
#include<Arduino.h>
#include<math.h>
#define DEBUG 1
#define SH1106_addr 0x78
//#include<std.h>
class SH1106
  {
    private:

    public:
        void    sendStart();
        void    sendStop();
        void    sendAddr(uint8_t addr);
        void    sendCommand(uint8_t command);
        void    sendData(uint8_t data);
        void    sendRAM(uint8_t data);
  };
#endif
