#include "Atmega328P.h"
#include "functions.h"
Atmega328P a;
int main(int argc, char const *argv[])
{
  a.UARTBegin(9600);
  uint8_t bytes[2];
  a.setDPM(13, 1);
  a.setAPM(0, 0);
  uint16_t counter = 0x3FF;
  while(1)
  {
    a.DW(13,0);
    uint16_tTOuint8_t(bytes,a.AR(0));
    a.DW(13,1);
    a.UARTSend((uint8_t)toAscii(bytes[0]));
    a.UARTSend((uint8_t)toAscii(bytes[1]));
    a.UARTSend((uint8_t)0x0D);
    counter--;
    _delay_ms(500);
  }
  return 0;
}
