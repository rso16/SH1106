#include <Arduino.h>
#include <util/delay.h>
#include "Antonius.h"
#include "Character.h"
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
uint8_t buffCol[] = {0x24};
uint8_t* buffFont[] = {buff0, buff1 , buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9};
uint8_t buffer[(oledHight * oledWidth)/8];

SH1106 s;
Antonius a;


//#define RTC_ADDRESS 0x68
int main()
{
  init();
  s.init();
  Serial.begin(9600);
  Serial.println("start");
  Serial.println(sizeof(buff0));
  Character char0('1',buff0,sizeof(buff0));
  Serial.println(char0.getCharacter());
  s.setletter(0, 0, 1, 6, char0.getBuff(), buffer);

  s.DrawBuffer(buffer);
  a.sendHour24(7);
  a.sendMin(35);
  a.sendSec(30);
  uint8_t buffBlyat[sizeof(char0.getBuff())];
  memcpy(buffBlyat, char0.getBuff(), sizeof(char0.getBuff()));
  for (size_t i = 0; i < sizeof(buffBlyat)/sizeof(buffBlyat[0]); i++)
  {
    Serial.println(buffBlyat[i],HEX);
  }

  // s.printBuffer(aBuf);
  //Font a ('A', aBuf, 3, 6);
  //
  // Serial.println("blyat");
  // uint8_t hour, min, sec;
  // while(1)
  // {
  //   hour = a.getHour24();
  //   min = a.getMin();
  //   sec = a.getSec();
  //   s.fillBuffer(0x00,buffer);
  //   s.setletter(0, 0, 1, 6, buffAll[hour / 10], buffer);
  //   s.setletter(7, 0, 1, 6, buffAll[hour % 10], buffer);
  //   s.setletter(17, 0, 1, 1, buffCol, buffer);
  //   s.setletter(21, 0, 1, 6, buffAll[min / 10], buffer);
  //   s.setletter(28, 0, 1, 6, buffAll[min % 10], buffer);
  //   s.setletter(38, 0, 1, 1, buffCol, buffer);
  //   s.setletter(42, 0, 1, 6, buffAll[sec / 10], buffer);
  //   s.setletter(49, 0, 1, 6, buffAll[sec % 10], buffer);
  //   s.DrawBuffer(buffer);
  //   _delay_ms(100);
  // }
  // s.transferRAM(0x00);

  // s.setletter(0,  0, 1, 6, buf0, buffer);
  // s.setletter(7,  0, 1, 6, buf1, buffer);
  // s.setletter(14, 0, 1, 6, buf2, buffer);
  // s.setletter(21, 0, 1, 6, buf3, buffer);
  // s.setletter(28, 0, 1, 6, buf4, buffer);
  // s.setletter(35, 0, 1, 6, buf5, buffer);
  // s.setletter(42, 0, 1, 6, buf6, buffer);
  // s.setletter(49, 0, 1, 6, buf7, buffer);
  // s.setletter(56, 0, 1, 6, buf8, buffer);
  // s.setletter(63, 0, 1, 6, buf9, buffer);
  // s.setletter(70, 0, 1, 1, bufCol, buffer);
  // s.setPixel(0, 7, 1, buffer);

  Serial.println("blyat");


  // s.setPixel(0, 8, 1, buffer);
  // s.setPixel(8, 0, 1, buffer);
  // s.setPixel(8, 8, 1, buffer);
  // s.DrawBuffer(buffer);
  // s.setPixel(10, 10, 0, buffer);
  // s.setPixel(11, 10, 0, buffer);
  // s.setPixel(9, 10, 0, buffer);
  // s.setPixel(10, 9, 0, buffer);
  // s.setPixel(10, 11, 0, buffer);
  //s.DrawBuffer(buffer);
  //s.printBuffer(buffer);
  _delay_ms(1000);
  return 0;
}
