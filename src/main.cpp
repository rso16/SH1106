#include <Arduino.h>
#include <util/delay.h>
#include "Atmega328P.h"
#include "Character.h"
#include "Font.h"
#define IDLENGTH 6
//#include "Font.h"
//#include <avr/iom328p.h>

Atmega328P a;
//#define RTC_ADDRESS 0x68
int main()
{
  Serial.begin(9600);
  a.setDPM(13,1);
  a.setDPM(12,1);
  a.setDPM(11,1);
  a.setDPM(10,1);
  a.setDPM(9,1);
  a.setDPM(8,1);
  a.setDPM(7,1);
  a.setDPM(6,1);

  uint8_t id[IDLENGTH];


  a.UARTBegin(9600);
  while(1)
  {
      // a.binToLed(a.UARTREAD());
      a.binToLed(0xAA);
      a.UARTREADBytes(id, IDLENGTH);
      _delay_ms(1000);
      a.binToLed(0xAA);
      _delay_ms(1000);
      a.binToLed(id[0]);
      _delay_ms(1000);
      a.UARTSend((uint8_t) id[0]);
      a.UARTSend((uint8_t) id[1]);
  }

  return 0;
}
