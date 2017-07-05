#include "Antonius.h"
//made by Rick Overhorst
//varius handy dandy fuction for the atmel atmega 328 chip/Arduino

    void Antonius::setDPM(uint8_t pin, uint8_t value)
    {
      if(value==0)
      {
        if(pin >=0 && pin<=7)
        {
          DDRD&= ~(1 << pin);
        }
        else if(pin>=8 && pin<=13)
        {
          DDRB&= ~(1 << (pin-8));
        }
      }
      else if(value==1)
      {
        if(pin >=0 && pin<=7)
        {
          DDRD|=1<<pin;
        }
        else if(pin>=8 && pin<=13)
        {
          DDRB|=1<<(pin-8);
        }
      }
    }

    void Antonius::setAPM(uint8_t pin, uint8_t value)
    {
      if(value==0)
      {
          DDRC&= ~(1 << pin);
      }
      else if(value==1)
      {
          DDRC|=1<<pin;
      }
    }

    void Antonius::DW(uint8_t pin, uint8_t value)
    {
      if(value==0)
      {
        if(pin >=0 && pin<=7)
        {
          PORTD&= ~(1 << pin);
        }
        else if(pin>=8 && pin<=13)
        {
          PORTB&= ~(1 << (pin-8));
        }
      }
      else if(value==1)
      {
        if(pin >=0 && pin<=7)
        {
            PORTD|=1<<pin;
        }
        else if(pin>=8 && pin<=13)
        {
          PORTB|=1<<(pin-8);
        }
      }
    }

    uint8_t Antonius::getBit(uint8_t data, uint8_t index)
    {
      //data HEX number from which the bit is asked
      //index is from lsb to msb ie. 0100 is 2 (3210)
      uint8_t bit = 0B0;
      data &= 1 << index;
      bit = data >> index;
      return bit;
    }

    uint8_t Antonius::DR(uint8_t pin)
    {
        uint8_t bit=0B0;
        if(pin >=0 && pin<=7)
        {
          bit =getBit(PIND,pin);
        }
        else if(pin>=8 && pin<=13)
        {
          bit = getBit(PINB,pin-8);
        }
        return bit;
    }

    void Antonius::AW(uint8_t pin, uint8_t value)
    {
      if(value==0)
      {
        PORTC&= ~(1 << pin);
      }
      else if(value==1)
      {
        PORTC|=1<<pin;
      }
    }
    void Antonius::sendByteToRTC(uint8_t address, uint8_t reg, uint8_t data)
    {

      uint8_t SLA_W = address<<1;
      uint8_t SLA_R=SLA_W|1;
      sendStart();
      TWDR = SLA_W;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWDR = reg;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWDR=data;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWCR = (1<<TWINT) | (1<<TWEN)|(1<<TWSTO)|(1<<TWSTA);
      //while (!(TWCR &  (1<<TWINT)));
      //Serial.println(TWSR,HEX);

    }
    uint8_t Antonius::requestByteFromRTC(uint8_t address, uint8_t reg)
    {
      uint8_t SLA_W = address<<1;
      uint8_t SLA_R=SLA_W|1;
      uint8_t data;
      sendStart();
    //  Serial.println(TWSR,HEX);
    //  if ((TWSR & 0xF8) !=START) ERROR();
      TWDR = SLA_W;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR & (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      //if ((TWSR & 0xF8) != MT_SLA_ACK) ERROR();
      TWDR = reg;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWCR|= (1<<TWINT)|(1<<TWSTA);
      TWCR&=~(1<<TWSTO);
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWDR=SLA_R;
      TWCR|=(1<<TWINT);
      TWCR&=~((1<<TWSTO)|(1<<TWSTA));
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWCR&=~((1<<TWSTO)|(1<<TWSTA)|(1<<TWEA));
      TWCR|=(1<<TWINT);
      while (!(TWCR &  (1<<TWINT)));
      // Serial.println(TWSR,HEX);
      TWCR&=~((1<<TWSTA));
      TWCR&=~((1<<TWSTO)|(1<<TWINT));
      data=TWDR;
      while (!(TWCR &  (1<<TWINT)));
      //Serial.println(TWSR,HEX);
      //Serial.println(data,HEX);
      return data;
    }
    uint8_t  Antonius::decodeMin(uint8_t input)
    {
      //fuction to decode the minutes and seconds from a DS3231 rtc module
      //takes the data byte recived from the rtc, eighter minutes or secondes, they are encoded the sameway
      //for more details see the DS3231 datasheet fig 1.
      //data0 to data3 represent 0-9 en ten0 to ten2 represent the tens
      uint8_t data0=getBit(input,0);
      uint8_t data1=getBit(input,1);
      uint8_t data2=getBit(input,2);
      uint8_t data3=getBit(input,3);
      uint8_t ten0=getBit(input,4);
      uint8_t ten1=getBit(input,5);
      uint8_t ten2=getBit(input,6);
      uint8_t secTotal=(data0*pow(2,0))+(data1*pow(2,1))+(data2*pow(2,2))+(data3*pow(2,3));
      uint8_t tenTotal=((ten0*pow(2,0))+(ten1*pow(2,1))+(ten2*pow(2,2)))*10;
      uint8_t total=tenTotal+secTotal;
      return total;
    }
    uint8_t  Antonius::decodeSec(uint8_t input)
    {
      return decodeMin(input);
    }

    uint8_t Antonius::encodeMin(uint8_t data)
    {
      if(data>=0 && data<=59)
      {
        uint8_t digit0;
        digit0=floor(data/10);  //first digit = data /10 then floor
        uint8_t digit1=data%10;//second digit = data mod 10
        return (digit0*16)+digit1;
      }
      else
      {
        return 0;
      }
    }

    uint8_t Antonius::encodeSec(uint8_t data)
    {
      return encodeMin(data);
    }

    uint8_t Antonius::decodeHour24(uint8_t input)
    {
      uint8_t data0=getBit(input,0);
      uint8_t data1=getBit(input,1);
      uint8_t data2=getBit(input,2);
      uint8_t data3=getBit(input,3);
      uint8_t data4=getBit(input,4);
      uint8_t data5=getBit(input,5);
      return (data5*20)+(data4*10)+(data3*pow(2,3))+(data2*pow(2,2))+(data1*pow(2,1))+(data0*pow(2,0));

    }

    uint8_t Antonius::decodeHour12(uint8_t input)
    {
      // Serial.println("blyat");
      uint8_t data0=getBit(input,0);
      uint8_t data1=getBit(input,1);
      uint8_t data2=getBit(input,2);
      uint8_t data3=getBit(input,3);
      uint8_t data4=getBit(input,4);
      return (data4*10)+(data3*pow(2,3))+(data2*pow(2,2))+(data1*pow(2,1))+(data0*pow(2,0));
    }
    uint8_t Antonius::encodeHour24(uint8_t data)
    {
      uint8_t hour=0;
      hour&=~1<<7;
      if(data>=20 && data<=24)
      {
        hour|=1<<5;
        hour+=data%10;
      }
      else if(data>=10 && data<20)
      {
        hour|=1<<4;
        hour+=data%10;
      }
      else if(data>=0 && data<=9)
      {
        hour=data;
      }
      else
      {
        hour=0;
      }

      return hour;
    }
    uint8_t Antonius::encodeHour12(uint8_t data, uint8_t amPm)
    {
      //the amPm defines am(low) or pm(high)
      uint8_t hour=1<<6;
      if(amPm==1)//pm
      {
        hour|=1<<5;
      }
      if(data>=10 && data<=12)
      {
        hour|=1<<4;
        hour+=data%10;
      }
      else if(data<10)
      {
        hour+=data;
      }
      else
      {
        hour=0;
      }
      return hour;
    }


    char* Antonius::getAmPm(uint8_t data)
    {
      if(getBit(data,5)==0)
      {
        return "AM";
      }
      else
      {
        return "PM";
      }
    }


    uint8_t Antonius::getMin()
    {
      uint8_t min=requestByteFromRTC(RTC_ADDRESS,MIN);
      min=decodeMin(min);
      return min;
    }
    uint8_t Antonius::getSec()
    {
    //  Serial.println("blin");
      uint8_t sec=requestByteFromRTC(RTC_ADDRESS,SEC);
    //  Serial.println("blin");
      sec=decodeSec(sec);
  //  Serial.println("blin");
      return sec;
    }

    char* Antonius::getTime()
    {
      char* timeStr=(void*)malloc(sizeof(char) * 50);
      char buffer[50];
      // Serial.println("pizdec");
      uint8_t sec=getSec();
      // Serial.println("pizdec");
      uint8_t min=getMin();
      // Serial.println("pizdec");
      uint8_t hour = requestByteFromRTC(RTC_ADDRESS, HOUR);

      if(getBit(hour,6)==0)
      {
        // Serial.println(hour,HEX);
        hour=decodeHour24(hour);
        // Serial.println(hour,HEX);
        sprintf(buffer,"%d:%d:%d",hour,min,sec);
        strcpy(timeStr,buffer);
      }
      else
      {
        char* amPm = malloc(sizeof(char)*3);
        amPm=getAmPm(hour);
        hour=decodeHour12(hour);
        sprintf(buffer,"%d:%d:%d ",hour,min,sec);
        strcpy(timeStr,buffer);
        strcat(timeStr,amPm);
      }
      return timeStr;
    }
    void Antonius::sendStart()
    {
      TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      if(DEBUG){Serial.println(TWSR,HEX);};
    }
    void Antonius::sendStop()
    {
      TWCR = (1<<TWINT) |(1<<TWSTA);
    }

    void Antonius::sendAddr(uint8_t addr)
    {
      TWDR = addr;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &(1<<TWINT)));
      if(DEBUG){Serial.println(TWSR,HEX);};
    }

    void Antonius::sendData(uint8_t data)
    {
      TWDR = data;
      TWCR = (1<<TWINT) | (1<<TWEN);
      while (!(TWCR &  (1<<TWINT)));

      if(DEBUG){Serial.println(TWSR,HEX);};
    }

    void Antonius::sendCommand(uint8_t command)
    {
      sendData(0x80);
      sendData(command);
    }

    void Antonius::sendRAM(uint8_t data)
    {
      sendData(0xC0);
      sendData(data);
    }

    /*uint8_t Antonius::getDay(uint8_t)
    {
      uint

    }*/
