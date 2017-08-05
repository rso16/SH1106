#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
#include "Font.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

uint8_t buffer[(oledHight * oledWidth)/8];


//#define RTC_ADDRESS 0x68
int main() {
init();
Serial.begin(9600);
Serial.println("start");
SH1106 s;
uint8_t aBuf[] = {0x31};
//s.printBuffer(aBuf);
Font a ('A', aBuf, 3, 6);
s.init();
Serial.println("blyat");
// s.transferRAM(0x00);
s.fillBuffer(0xFF,buffer);
s.setletter(0, 0, a.getHeight(), a.getWidth(), a.getFont(), buffer);
// s.setPixel(0, 0, 1, buffer);
// s.setPixel(0, 8, 1, buffer);
// s.setPixel(8, 0, 1, buffer);
// s.setPixel(8, 8, 1, buffer);
// s.DrawBuffer(buffer);
// s.setPixel(10, 10, 0, buffer);
// s.setPixel(11, 10, 0, buffer);
// s.setPixel(9, 10, 0, buffer);
// s.setPixel(10, 9, 0, buffer);
// s.setPixel(10, 11, 0, buffer);
//s.DrawBuffer(buffer);
//s.printBuffer(buffer);
_delay_ms(1000);
  return 0;
}
