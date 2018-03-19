#include "Atmega328P.h"
//made by Rick Overhorst
//varius handy dandy fuction for the atmel atmega 328 chip/Arduino

void Atmega328P::setDPM(uint8_t pin, uint8_t value)
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

void Atmega328P::setAPM(uint8_t pin, uint8_t value)
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

void Atmega328P::DW(uint8_t pin, uint8_t value)
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

uint8_t Atmega328P::DR(uint8_t pin)
{
    uint8_t bit=0B0;
    if(pin >=0 && pin<=7)
    {
      bit = getBit(PIND,pin);
    }
    else if(pin>=8 && pin<=13)
    {
      bit = getBit(PINB,pin-8);
    }
    return bit;
}

void Atmega328P::AW(uint8_t pin, uint8_t value)
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


void Atmega328P::toggleDP(uint8_t pin)
{
  uint8_t value = getPinStat(pin);
  DW(pin,!value);
}

uint8_t Atmega328P::getPinStat(uint8_t pin)
{
  uint8_t bit=0B0;
  if(pin >=0 && pin<=7)
  {
    bit = getBit(PORTD,pin);
  }
  else if(pin>=8 && pin<=13)
  {
    bit = getBit(PORTB,pin-8);
  }
  return bit;
}

void Atmega328P::binToLed(uint8_t byte)
{
    int index = 7;
    int pin = 13;
    while(index >= 0)
    {
      // Serial.print(getBit(byte, pin-(pin-7)));
      DW(pin,getBit(byte, index));
      index--;
      pin--;
    }
    // Serial.println();
}

uint8_t Atmega328P::getBit(uint8_t data, uint8_t index)
{
  //data HEX number from which the bit is asked
  //index is from lsb to msb ie. 0100 is 2 (3210)
  uint8_t bit = 0B0;
  data &= 1 << index;
  bit = data >> index;
  return bit;
}

void Atmega328P::sendI2CStart()
{
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while (!(TWCR &(1<<TWINT)));
  if(DEBUG){Serial.println(TWSR,HEX);};
}

void Atmega328P::sendI2CStop()
{
  TWCR = (1<<TWINT) |(1<<TWSTA);
}

void Atmega328P::sendI2CAddr(uint8_t addr)
{
  TWDR = addr;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR &(1<<TWINT)));
  if(DEBUG){Serial.println(TWSR,HEX);};
}

void Atmega328P::sendI2CData(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR &  (1<<TWINT)));
  if(DEBUG){Serial.println(TWSR,HEX);};
}

void Atmega328P::UARTInit(uint8_t dataBits, uint8_t parityBit, uint8_t stopBits, uint32_t baud, uint8_t speed, uint8_t RT)
{
  uint16_t ubrr = (clockspeed / ((speed + 1) * 8 * baud)) - 1;
  // binToLed(ubrr);
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  // Enable receiver and transmitter
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1 stop bit */
  UCSR0C = (3<<UCSZ00);
}

void Atmega328P::UARTBegin(long int baud)//function to begin the UART with the defaul settings and a baudrate. returns an status code.
{
  UARTInit(0, 0, 0, 9600, NORMALSPEED, 0);
}

void Atmega328P::UARTSend(uint16_t data)
{
  // /* Wait for empty transmit buffer */
  // while ( !( UCSR0A & (1<<UDRE0)) );
  // /* Put data into buffer, sends the data */
  // UDR0 = data;
}

void Atmega328P::UARTSend(uint8_t data)
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
 //  /* Wait for empty transmit buffer */
 // while ( !( UCSR0A & (1<<UDRE0)));
 // /* Copy 9th bit to TXB8 */
 // UCSR0B &= ~(1<<TXB80);
 // if ( data & 0x0100 )
 // UCSR0B |= (1<<TXB80);
 // /* Put data into buffer, sends the data */
 // UDR0 = data;
}

void Atmega328P::UARTSendBytes(uint8_t bytes[], uint8_t amountOfBytes)
{
  int index = 0;
  while(index < amountOfBytes)
  {
    UARTSend(bytes[index]);
    index++;
  }
}
uint8_t Atmega328P::UARTRead()
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}

void Atmega328P::UARTREADBytes(uint8_t *bytes, uint8_t amountOfBytes)
{
  int index = 0;
  uint8_t* temp = bytes;
  temp = bytes + (sizeof(uint8_t));
    while(index <= amountOfBytes)
    {
      temp = bytes + (sizeof(uint8_t) * index);
      *temp =  UARTRead();
      // binToLed(*temp);
      index++;
    }
    // binToLed((uint8_t) 0xff);
}

void Atmega328P::println(uint8_t *bytes)
{
  int index = 0;
  while (bytes[index] != '\0')
  {
    index++;
  }
  binToLed(index);
  UARTSendBytes(bytes, 13);
  // UARTSend((uint8_t) 0x0D);
}
