#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst
Font::Font()
{
  Serial.begin(9600);

}

void Font::addChar(Character c)
{
  if(fontCounter<=maxChars)
  {
    font[fontCounter] = c;
    fontCounter++;
  }
  else
  {
    Serial.println("Maxium amount of characters reached, no new character added");
  }
}

int Font::findFontIndex(char c)
{
  for (size_t i = 0; i < fontCounter; i++)
  {
    if(font[i].getCharacter() == c)
    {
      return i;
    }
  }
  return err;
}
Character Font::getChar(char c)
{
  return font[findFontIndex(c)];
}

void Font::printChars()
{
  for (size_t i = 0; i < fontCounter; i++)
  {
    Serial.println(font[i].getCharacter());
  }
}
