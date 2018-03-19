#include <util/delay.h>
#include "Atmega328P.h"
#include "Character.h"
#include "Font.h"
#define IDLENGTH 12
uint8_t id[IDLENGTH + 1];
//#include "Font.h"
//#include <avr/iom328p.h>
void readRFID(uint8_t *bytes, uint8_t lengthOfID);
Atmega328P a;
//#define RTC_ADDRESS 0x68
int main()
{
  a.setDPM(13,1);
  a.setDPM(12,1);
  a.setDPM(11,1);
  a.setDPM(10,1);
  a.setDPM(9,1);
  a.setDPM(8,1);
  a.setDPM(7,1);
  a.setDPM(6,1);




  a.UARTBegin(9600);
  while(1)
  {
      readRFID(id, IDLENGTH);
      id[IDLENGTH + 1] = '\0';
      a.println(id);
      // a.UARTREADBytes(id, IDLENGTH);
      // a.UARTSend((uint8_t) (id[0] + '0'));
      // a.UARTSendBytes(id, IDLENGTH);
      // id[IDLENGTH + 1] = '\0';
      // a.binToLed(id[0]);
      // a.println(id);

  }

  return 0;
}

void readRFID(uint8_t *bytes, uint8_t lengthOfID)
{
  bool tagRead = false;
  while(!tagRead)
  {
    if(a.UARTRead() == 0x02)
    {
      a.UARTREADBytes(bytes, lengthOfID);
      tagRead = true;
    }
  }

}
