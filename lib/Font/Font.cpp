#include "Font.h"
//made by Rick Overhorst

Font::Font(char letter, uint8_t fontBuffer[], uint8_t height, uint8_t width)
{
  this->letter = letter;
  this->fontBuffer = fontBuffer;
  this->height = height;
  this->width = width;
}

char Font::getLetter()
{
 return letter;
}

uint8_t Font::getFont()
{
 return this->fontBuffer[];
}

uint8_t Font::getHeight()
{
  return height;
}

uint8_t Font::getWidth()
{
 return width;
}
