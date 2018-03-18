#include <Arduino.h>
#include <util/delay.h>
#include "Atmega328P.h"
#include "Character.h"
#include "Font.h"
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
  uint8_t byte = 0;


  a.UARTBegin(9600);
  while(1)
  {
      a.UARTSend((uint8_t) 0x41);
      a.UARTSend((uint8_t) 0x412);
      a.UARTSend((uint8_t) 0xA);
      // a.UARTSend((uint8_t)'\0');
  }

  return 0;
}
