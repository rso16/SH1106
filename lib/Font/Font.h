#ifndef FONT_H
#define FONT_H
//made by Rick Overhorst

#include <stdint.h>
#include <string.h>
#include "Character.h"
class Font
{
  private:
    Character font[];
    struct CharNode
    {
      Character nChar;
      CharNode *next;
      bool isInit = false;
    }*charNode;
    CharNode *head;
  public:
    Font();
    void addChar(Character c);
    Character getChar(char c);
    void printChars();
};


#endif
