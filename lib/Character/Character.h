#ifndef  CHARACTER_H

  #define CHARACTER_H
  #include <stdint.h>
  #include <string.h>
  class Character
  {
    private:
      char character;
      uint8_t buff[];
      int size;
    public:
      Character(char character, uint8_t buff[],int size);
      char getCharacter();
      uint8_t *getBuff();
      int getSize();
  };



#endif
