#ifndef FONT_H
#define FONT_H
//made by Rick Overhorst

#include <stdint.h>
#include <string.h>
#include "Character.h"
class Font
{
  private:
    Character font[50];
    int fontCounter;
  public:
    Font();
    void addChar(Character c);
    Character getChar(char c);
    void printChars();
};


#endif
