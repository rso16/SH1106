#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst

Font::Font(char letter, uint8_t fontBuffer[], uint8_t height, uint8_t width)
{
  this->letter = letter;
  memcpy(this->fontBuffer, fontBuffer,sizeof(fontBuffer));
  this->height = height;
  this->width = width;
}

char Font::getLetter()
{
  return letter;
}

uint8_t Font::getFont()
{
  Serial.println(letter);
  Serial.print("eey ");
  Serial.println(this->fontBuffer[0]);
  return &fontBuffer[0];
}

uint8_t Font::getHeight()
{
  return height;
}

uint8_t Font::getWidth()
{
  return width;
}
