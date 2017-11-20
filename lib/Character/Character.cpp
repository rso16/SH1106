#include "Character.h"
#include <Arduino.h>
//made by Rick Overhorst

Character::Character(char character, uint8_t buff[], long int size)
{
  // Serial.println(sizeof(buff));
  this->character = character;
  // this->buff = (uint8_t*) malloc(sizeof(buff)*sizeof(uint8_t));
  // memcpy(this->buff, buff,size+1);
  this->buff = buff;
  // Serial.println("constructor");
  // for (size_t i = 0; i < size; i++)
  // {
  //   Serial.println(this->buff[i],HEX);
  // }

  this->size  = size;
  // Serial.print("size ");
  // Serial.println(size);
  this->height = 0;
  this->width  = 0;

}

Character::Character(char character, uint8_t buff[],long size,uint8_t height, uint8_t width)
{
  Character(character, buff, size);
  this->height = height;
  this->width  = width;
}

char Character::getCharacter()
{
  return character;
}

uint8_t* Character::getBuff()
{
  // Serial.print("stuffsize ");
  // Serial.println(size);
  // for (size_t i = 0; i < size; i++)
  // {
  //   Serial.println(this->buff[i],HEX);
  // }
  return this->buff;
}

uint8_t Character::getHeight()
{
  return height;
}

  uint8_t Character::getWidth()
  {
    return width;
  }

long int Character::getSize()
{
  // Serial.print("blyat ");
  // Serial.println(size);
  return size;
}
