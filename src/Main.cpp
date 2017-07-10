#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

uint8_t buffer[oledHight * oledWidth];
//#define RTC_ADDRESS 0x68
int main() {
<<<<<<< HEAD
  init();
  Serial.begin(9600);
  SH1106 s;
  s.init();
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
  while(1){
    s.fillBuffer(0x00, buffer);
    s.sendStart();
    s.DrawBuffer(buffer);
    s.sendStop();
  }
=======
init();
Serial.begin(9600);
// Serial.println("blyat");
SH1106 s;
Serial.println("blyat");
s.init();
s.transferRAM(0x00);
// Serial.println("blyat");
s.fillBuffer(0xFF,buffer);
//s.sendStart();
s.printBuffer(buffer);
Serial.println("blyat");
// s.DrawBuffer(buffer);
//s.sendStop();
_delay_ms(1000);
  return 0;
>>>>>>> d05450beae4087e05a7bbd09c58fb803daeaa4ab
}
