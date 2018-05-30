// #include <Arduino.h>
#include <util/delay.h>
#include "Atmega328P.h"
#include "Character.h"
#include "Font.h"
//#include "Font.h"
//#include <avr/iom328p.h>
#include "SH1106.h"
#define dTime 100
#define SLA_R 0xD1
#define SLA_W 0xD0

uint8_t buff0[] = {0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E};
uint8_t buff1[] = {0x82, 0x83, 0x83, 0xFF, 0x80, 0x80};
uint8_t buff2[] = {0xF1, 0x91, 0x91, 0x91, 0x91, 0x9F};
uint8_t buff3[] = {0x89, 0x89, 0x89, 0x89, 0x89, 0xFF};
uint8_t buff4[] = {0x0F, 0x08, 0x08, 0x08, 0x08, 0xFF};
uint8_t buff5[] = {0x8F, 0x89, 0x89, 0x89, 0x89, 0xF9};
uint8_t buff6[] = {0xFF, 0x91, 0x91, 0x91, 0x91, 0xF1};
uint8_t buff7[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0xFF};
uint8_t buff8[] = {0xFF, 0x91, 0x91, 0x91, 0x91, 0xff};
uint8_t buff9[] = {0x9F, 0x91, 0x91, 0x91, 0x91, 0xFF};
uint8_t buffA[] = {0xF8, 0x16, 0x11, 0x11, 0x16, 0xF8};

// uint8_t buffA[] = {};
uint8_t buffCol[] = {0x24};
uint8_t buffSpace[] = {0x00};
// uint8_t buffA[] = {0x3F};

uint8_t* buffAll[] = {buff0, buff1 , buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9};
uint8_t buffer[(oledHight * oledWidth)/8];

// Microcontroller m;


//#define RTC_ADDRESS 0x68
int main()
{
  // init();
  // Serial.begin(9600);
  // Serial.println("start");
  // _delay_ms(1000);

  Atmega328P a;
  a.UARTBegin(9600);
  a.println("blyat");
  // Serial.println("pointer");
  // _delay_ms(1000);
  SH1106 s;
  // Serial.println("oled");
  // _delay_ms(1000);
  Font f;
  s.init(&a);


  // s.printBuffer(buffer);


  //Serial.println(sizeof(buff0));


  Character char0('0',buff0,sizeof(buff0));
  Character char1('1',buff1,sizeof(buff1));
  Character char2('2',buff2,sizeof(buff2));
  Character charA('A',buffA,sizeof(buffA));
  // Serial.print("char = ");
  // Serial.println(char1.getCharacter());

  // Serial.println("stuff");
  f.addChar(char1);
  f.addChar(char2);
  f.addChar(char0);
  f.addChar(charA);

  // f.addChar(char1);
  f.printChars();

  s.setletter(7, 0, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(0, 8, 1, 6, f.getChar('2').getBuff(), buffer);
  s.setletter(0, 16, 1, 6, f.getChar('2').getBuff(), buffer);
  s.setletter(0, 0, 1, 6, f.getChar('1').getBuff(), buffer);
  s.setletter(7, 16, 1, 6, f.getChar('A').getBuff(), buffer);
  s.setletter(7, 24, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(7, 32, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(7, 40, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(7, 48, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(7, 56, 1, 6, f.getChar('0').getBuff(), buffer);
  s.setletter(0, 56, 1, 6, f.getChar('0').getBuff(), buffer);
  s.DrawBuffer(buffer);


  // Serial.println("blyat");

  _delay_ms(1000);
  return 0;
}
