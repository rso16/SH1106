#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst
Font::Font()
{
  Serial.begin(9600);
  Serial.println("head created");
  head = malloc(sizeof(charNode));
  head = NULL;
}

void Font::addChar(Character c)
{
  Serial.println("adding char");
    if (head == NULL)
    {
      Serial.println("filling head");
      //fill head
      Serial.println(c.getSize());
      uint8_t *tmp = c.getBuff();
      head->nChar = c;
      Serial.println(c.getSize());
      // for (size_t i = 0; i < c.getSize(); i++)
      // {
      //   Serial.println(tmp[i],HEX);
      // }
      Serial.println(head->nChar.getCharacter());
      head->next  = malloc(sizeof(charNode));
    }
    else
    {
      Serial.println("head already exist");
      // loop through list till last and then add
      CharNode *curNode = head;
      while(curNode != 0)
      {
        if(curNode->next = 0)
        {
          //create new node and set next to new node
          Serial.println("creating new node");
          CharNode *newNode;
          newNode->nChar = c;
          newNode->next  = 0;
          curNode->next = newNode;
          break;
        }
        Serial.println("node alread exist, going to new node");
        curNode = curNode->next;
      }
    }
    if (head == NULL)
    {
      Serial.println("head is null");
    }
    else
    {
      Serial.println("head is not null");
    }
}

Character Font::getChar(char c)
{
  CharNode *curNode;
  if (head == 0)
  {
    Serial.println("head is empty");
  }
  else
  {
    curNode = head;
    while(curNode != 0)
    {
      Serial.println("c is ");
      Serial.println(c);
      if(strcmp(c, curNode->nChar.getCharacter()) == 0)
      {
        Serial.print("node found ");
        Serial.println(curNode->nChar.getCharacter());
        return curNode->nChar;
      }
      curNode = curNode->next;
    }
  }
  return curNode->nChar;
}
