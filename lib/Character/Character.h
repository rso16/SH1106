#ifndef  CHARACTER_H

  #define CHARACTER_H
  #include <stdint.h>
  #include <string.h>
  class Character
  {
    private:
      char character;
      uint8_t *buff;
      long int size;
      uint8_t height;
      uint8_t width;
      //Character *next;
    public:
      Character();
      Character(char character, uint8_t buff[],long int size);
      Character(char character, uint8_t buff[],long int  size,uint8_t height, uint8_t width);
      char getCharacter();
      uint8_t *getBuff();
      uint8_t getHeight();
      uint8_t getWidth();
      long int  getSize();
  };



#endif
