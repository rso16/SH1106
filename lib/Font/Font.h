#ifndef FONT_H
#define FONT_H
//made by Rick Overhorst

#include <stdint.h>
#include <string.h>
#include "Character.h"

#define maxChars 50
class Font
{
  private:
    Character font[maxChars];
    int fontCounter = 0;
  public:
    Font();
    void addChar(Character c);
    Character getChar(char c);
    int findFontIndex(char c);
    void printChars();
};


#endif
