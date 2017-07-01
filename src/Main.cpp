#include <Arduino.h>
#include <util/delay.h>
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

//#define RTC_ADDRESS 0x68
int main() {
  init();
  Serial.begin(9600);
  SH1106 s;
  s.sendStart();
  s.sendAddr(SH1106_addr);
  s.sendCommand(0x0ae);
  s.sendCommand(0x0d5);
  s.sendCommand(0x80);
  s.sendCommand(0x08d);
  s.sendCommand(0x14);
  s.sendCommand(0x20);
  s.sendCommand(0x00);
  s.sendCommand(0xA1);
  s.sendCommand(0xC8);
  // s.sendCommand();
  // s.sendCommand();
  // s.sendCommand();
  // s.sendCommand();
  // s.sendCommand();
  s.sendCommand(0xDA);
  s.sendCommand(0x12);
  s.sendCommand(0xA8); // set multiplex
  s.sendCommand(0x3f); // to 0
  s.sendCommand(0xD3); // set offset
  s.sendCommand(0x00); // to the top of the screen
  s.sendCommand(0x40); // set line to 0
  s.sendCommand(0xB0); // set page to 0
  s.sendCommand(0x02); // set collom lower to 2
  s.sendCommand(0x10); // set collom upper to 0
  s.sendCommand(0xAF); // turn screen on

// should draw 5 lines but only the first is drawn.
    for (size_t j = 0; j <=7; j++)
    {
      s.sendCommand(0xB0+j);
      s.sendCommand(0x02); // set collom lower to 2
      s.sendCommand(0x10); // set collom upper to 0

      for (size_t i = 0; i < 128; i++)
      {
        s.sendRAM(0xAA);
        _delay_ms(50);
      }
      _delay_ms(500);
    }
    _delay_ms(1000);
    s.sendStop();
  return 1;
}
