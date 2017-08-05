#ifndef FONT_H
#define FONT_H
//made by Rick Overhorst

#include <stdint.h>
#include <string.h>

class Font
{
  private:
    char    letter;
    uint8_t fontBuffer[];
    uint8_t height;
    uint8_t width;

  public:
    Font(char, uint8_t[], uint8_t, uint8_t);
    char    getLetter();
    uint8_t getFont();
    uint8_t getHeight();
    uint8_t getWidth();
};


#endif
