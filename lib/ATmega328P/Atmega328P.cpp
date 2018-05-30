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

uint16_t Atmega328P::AR(uint8_t pin)
{
  ADMUX &= 0xf0;
  ADMUX |= pin;
  ADMUX |= (1<<REFS0);
  ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC));
  return ADC;
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
  if(DEBUG){println(TWSR);};
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
  if(DEBUG){println(TWSR);};
}

void Atmega328P::sendI2CData(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR &  (1<<TWINT)));
  if(DEBUG){println(TWSR);};
}

void Atmega328P::UARTInit(uint8_t dataBits, uint8_t parityBit, uint8_t stopBits, uint32_t baud, uint8_t speed, uint8_t RT)
{
  uint16_t ubrr = (clockspeed / ((speed + 1) * 8 * baud)) - 1;
  // binToLed(ubrr);
  UCSR0A |= (1 << U2X0);
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  // Enable receiver and transmitter
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1 stop bit */
  UCSR0C = (3<<UCSZ00);
}

void Atmega328P::UARTBegin(long int baud)//function to begin the UART with the defaul settings and a baudrate. returns an status code.
{
  UARTInit(0, 0, 0, baud, NORMALSPEED, 0);
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
 }

void Atmega328P::UARTSendBytes(uint8_t bytes[], uint8_t amountOfBytes)
{
  int index = 0;
  while(index < amountOfBytes - 1)
  {
    UARTSend(bytes[index]);
    index++;
  }
}
uint8_t Atmega328P::UARTRead()
{
  /* Wait for data to be received  for a max 50ms */
  int counter = 75;
  // println("blyat");
  while ( (!(UCSR0A & (1<<RXC0))) && counter >= 0 )
  {
    _delay_ms(1);
    counter--;
  }
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
  UARTSendBytes(bytes, index + 1 );
  UARTSend((uint8_t) 0x0A);
  UARTSend((uint8_t) 0x0D);
}

void Atmega328P::EEPROM_Write(uint32_t addr, uint8_t data)
{
  /* Wait for completion of previous write */
  while (EECR & (1<<EEPE));
  /* Set up address and Data Registers */
  EEAR = addr;
  EEDR = data;
  /* Write logical one to EEMPE */
  EECR |= (1<<EEMPE);
  /* Start eeprom write by setting EEPE */
  EECR |= (1<<EEPE);
}

void Atmega328P::EEPROM_WriteBytes(uint32_t addr, uint8_t data[], uint32_t amountOfBytes)
{
  for (size_t i = 0; i < amountOfBytes; i++)
  {
    EEPROM_Write(addr + i, data[i]);
  }
}

uint8_t Atmega328P::EEPROM_Read(uint32_t addr)
{
  /* Wait for completion of previous write */
  while (EECR & (1<<EEPE));
  /* Set up address register */
  EEAR = addr;
  /* Start eeprom read by writing EERE */
  EECR |= (1<<EERE);
  /* Return data from Data Register */
  return EEDR;
}

void Atmega328P::EEPROM_ReadBytes(uint32_t addr, uint8_t data[], uint32_t amountOfBytes)
{
  for (size_t i = 0; i < amountOfBytes; i++)
  {
    data[i] = EEPROM_Read(addr + i);
  }
}
