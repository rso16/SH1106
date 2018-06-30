#ifndef SH1106_H
#define SH1106_H
//made by Rick Overhorst

//includes
#include <stdint.h>
#include<avr/io.h>
#include <stdio.h>
#include<math.h>
#include "Microcontroller.h"
#include <util/delay.h>
#define DEBUG 0
#define SH1106_ADDR 0x78
#define oledWidth 128
#define oledHight 64
#define maxPages 8
#define pageLength 8
#define size sizeof(uint8_t)
//#include<std.h>
class SH1106
  {
    private:
        Microcontroller *mic;
    public:
        void    init(Microcontroller *m);
        void    sendCommand(uint8_t command);
        void    sendRAM(uint8_t data);
        uint8_t readRAM();
        void    DrawBuffer(uint8_t buffer[]);
        void    fillBuffer(uint8_t input, uint8_t buffer[]);
        void    printBuffer(uint8_t buffer[]);
        void    transferRAM(uint8_t data);
        void    transferCommand(uint8_t data);
        void    setPixel(uint8_t x, uint8_t y, uint8_t data, uint8_t buffer[]);
        void    setletter(uint8_t x, uint8_t y, uint8_t height, uint8_t width, uint8_t data[], uint8_t buffer[]);
        uint8_t getBit(uint8_t data, uint8_t index);
  };
#endif
