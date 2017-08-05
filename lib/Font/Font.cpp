#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst

Font::Font(char letter, uint8_t fontBuffer[], uint8_t height, uint8_t width)
{
  this->letter = letter;
  Serial.println(this->fontBuffer[0]);
  uint8_t  *pointer = 2284;
  Serial.print("pointer1 ");
  Serial.println(*pointer);
  memcpy(this->fontBuffer, fontBuffer,sizeof(fontBuffer));
  Serial.println(this->fontBuffer[0]);
  Serial.print("pointer2 ");
  Serial.println(*pointer);

  this->height = height;
  this->width = width;
}

char Font::getLetter()
{
  return letter;
}

uint8_t Font::getFont()
{
  Serial.print("buffer ");
  uint8_t  *pointer = 2284;
  Serial.println(*pointer);
  Serial.println((int)&fontBuffer[0]);
  return &(fontBuffer[0]);
}

uint8_t Font::getHeight()
{
  return height;
}

uint8_t Font::getWidth()
{
  return width;
}
