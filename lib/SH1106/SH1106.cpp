#include "SH1106.h"
//made by Rick Overhorst
//varius handy dandy fuction for the atmel atmega 328 chip/Arduino
    void SH1106::init()
    {
      sendStart();
      sendAddr(SH1106_addr);
      sendCommand(0x0ae);
      sendCommand(0x0d5);
      sendCommand(0x80);
      sendCommand(0x08d);
      sendCommand(0x14);
      sendCommand(0x20);
      sendCommand(0x00);
      sendCommand(0xA1);
      sendCommand(0xC8);
      sendCommand(0xDA);
      sendCommand(0x12);
      sendCommand(0xA8); // set multiplex
      sendCommand(0x3f); // to 0
      sendCommand(0xD3); // set offset
      sendCommand(0x00); // to the top of the screen
      sendCommand(0x40); // set line to 0
      sendCommand(0xB0); // set page to 0
      sendCommand(0x02); // set collom lower to 2
      sendCommand(0x10); // set collom upper to 0
      sendCommand(0xAF); // turn screen on
      sendStop();
    }

    void SH1106::sendStart()
    {
      TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      //if(DEBUG){Serial.println(TWSR,HEX);};
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
      //if(DEBUG){Serial.println(TWSR,HEX);};
    }

    void SH1106::sendData(uint8_t data)
    {
      TWDR = data;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));

      //if(DEBUG){Serial.println(TWSR,HEX);};
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

    void SH1106::DrawBuffer(uint8_t buffer[])
    {

    }
    void SH1106::fillBuffer(uint8_t input)
    {
      if(input == 0 || input ==1)
      {
        for (size_t y = 0; y < oledHight; y++)
        {
            for (size_t x = 0; x < oledWidth; x++) {
              buffer[y * oledWidth + x] = input;
            }
        }
      }
    }
