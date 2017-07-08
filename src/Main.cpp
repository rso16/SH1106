#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0
//uint8_t buffer[oledHight * oledWidth];
//#define RTC_ADDRESS 0x68
int main() {
  init();
  Serial.begin(9600);
  Serial.println("blyat");
  //SH1106 s;
  Serial.println("blyat");
//  s.init();
//   s.sendStart();
//   s.sendAddr(SH1106_ADDR);
// // should draw 5 lines but only the first is drawn.
//     for (size_t j = 0; j <=0; j++)
//     {
//       s.sendCommand(0xB0+j);
//       s.sendCommand(0x12); // set collom lower to 2
//       s.sendCommand(0x10); // set collom upper to 0
//
//       for (size_t i = 0; i < 128; i++)
//       {
//         s.sendRAM(0x00);
//         //_delay_ms(100);
//       }
//       // _delay_ms(00);
//     }
//     //_delay_ms(1000);
//     s.sendStop();
Serial.println("blyat");
//s.fillBuffer(0x00,buffer);
//s.sendStart();
Serial.println("blyat");
//s.DrawBuffer(buffer);
//s.sendStop();
_delay_ms(1000);
  return 1;
}
