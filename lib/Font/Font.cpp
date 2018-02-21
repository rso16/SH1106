#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst
// Font::Font()
// {
//   Serial.begin(9600);
//
// }

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


Character Font::getChar(char c)
{

}

void Font::printChars()
{

}
