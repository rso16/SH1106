#include "SH1106.h"
//made by Rick Overhorst
//varius handy dandy fuction for the atmel atmega 328 chip/Arduino
void SH1106::init(Microcontroller *m)
{
  // Serial.begin(9600);
  Serial.println("init oled");
  mic = m;
  mic->sendI2CStart();
  mic->sendI2CAddr(SH1106_ADDR);
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
  mic->sendI2CStop();
}



    void SH1106::sendCommand(uint8_t command)
    {
      mic->sendI2CData(0x80);
      mic->sendI2CData(command);
    }

    void SH1106::sendRAM(uint8_t data)
    {
      mic->sendI2CData(0xC0);
      mic->sendI2CData(data);
    }

    void SH1106::transferRAM(uint8_t data)
    {
      mic->sendI2CStart();
      mic->sendI2CAddr(SH1106_ADDR);
      mic->sendI2CData(0xC0);
      mic->sendI2CData(data);
      mic->sendI2CStop();
    }

    void SH1106::transferCommand(uint8_t data)
    {
      mic->sendI2CStart();
      mic->sendI2CAddr(SH1106_ADDR);
      mic->sendI2CData(0x80);
      mic->sendI2CData(data);
      mic->sendI2CStop();
    }

    void SH1106::DrawBuffer(uint8_t buffer[])
    {
      for (size_t page = 0; page < maxPages; page++)
      {
          transferCommand(0x02);
          transferCommand(0x10);
          transferCommand(0xB0 + page);
          for (size_t x = 0; x < oledWidth; x++)
          {
            transferRAM(buffer[x + (oledWidth * page)]);
          }
      }
    }

    void SH1106::fillBuffer(uint8_t input, uint8_t buffer[])
    {
      for (size_t i = 0; i < (oledHight * oledWidth) / 8; i++)
      {
        // Serial.println(i);
        buffer[i]=input;
      }
    }

    void SH1106::printBuffer(uint8_t buffer[])
    {
      int counter = 0;

        for (size_t i = 0; i < (oledHight * oledWidth) / 8; i++)
        {
          if(counter <= oledWidth)
          {
            Serial.print(buffer[i],HEX);
            Serial.print(", ");
            ++counter;
          }
          else
          {
            Serial.println("");
            counter = 0;
          }
        }
    }

    void SH1106::setPixel(uint8_t x, uint8_t y, uint8_t data, uint8_t buffer[])
    {
      int buffAddr = x + (oledWidth * floor(y/pageLength));
      if (data == 0x00)
      {
        buffer[buffAddr] &= ~(1 << (y % 8));
      } else if (data == 0x01)
      {
        buffer[buffAddr]|= 1 << (y % 8);
      }
    }

    void SH1106::setletter(uint8_t x, uint8_t y, uint8_t height, uint8_t width, uint8_t data[], uint8_t buffer[])
    {
      int buffAddr = x + (oledWidth * floor(y/pageLength));
      for (size_t y = 0; y < height; y++)
      {
        for (size_t x = 0; x < width; x++)
        {
          //Serial.println("stuff");
        //  Serial.println(data[x]);
          buffer[buffAddr+x] = data[x];
        }
      }
    }

    uint8_t SH1106::getBit(uint8_t data, uint8_t index)
    {
      //data HEX number from which the bit is asked
      //index is from lsb to msb ie. 0100 is 2 (3210)
      uint8_t bit = 0B0;
      data &= 1 << index;
      bit = data >> index;
      return bit;
    }
