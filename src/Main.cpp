#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

uint8_t *pointerbuffer = (uint8_t) malloc(sizeof(uint8_t) * (oledHight * oledWidth));


//#define RTC_ADDRESS 0x68
int main() {
init();
Serial.begin(9600);
Serial.println("start");
SH1106 s;
s.init();
s.fillBuffer(0x00,pointerbuffer);
s.printBuffer(pointerbuffer);
_delay_ms(1000);
  return 0;
}
