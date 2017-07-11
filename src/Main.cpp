#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

uint8_t buffer = malloc((oledHight * oledWidth)*sizeof(uint8_t));
//#define RTC_ADDRESS 0x68
int main() {
init();
Serial.begin(9600);
// Serial.println("blyat");
SH1106 s;
//Serial.println("blyat");
s.init();
//s.transferRAM(0x00);
// Serial.println("blyat");
s.fillBuffer(0x00,buffer);
//s.sendStart();
s.printBuffer(buffer);
//Serial.println("blyat");
// s.DrawBuffer(buffer);
//s.sendStop();
_delay_ms(1000);
  return 0;
}
