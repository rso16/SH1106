#include "SH1106.h"
//made by Rick Overhorst
//varius handy dandy fuction for the atmel atmega 328 chip/Arduino


    void SH1106::sendStart()
    {
      TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      if(DEBUG){Serial.println(TWSR,HEX);};
    }
    void SH1106::sendStop()
    {
      TWCR = (1<<TWINT) |(1<<TWSTA);
    }

    void SH1106::sendAddr(uint8_t addr)
    {
      TWDR = addr;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      if(DEBUG){Serial.println(TWSR,HEX);};
    }

    void SH1106::sendData(uint8_t data)
    {
      TWDR = data;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));

      if(DEBUG){Serial.println(TWSR,HEX);};
    }

    void SH1106::sendCommand(uint8_t command)
    {
      sendData(0x80);
      sendData(command);
    }

    void SH1106::sendRAM(uint8_t data)
    {
      sendData(0xC0);
      sendData(data);
    }
