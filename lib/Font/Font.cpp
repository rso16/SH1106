#include "Font.h"
#include <Arduino.h>
//made by Rick Overhorst
Font::Font()
{
  Serial.begin(9600);
  Serial.println("head created");
  head = (CharNode*) malloc(sizeof(CharNode));
  head->isInit = false;
}

void Font::addChar(Character c)
{
  Serial.println("bool");
  Serial.println(head->isInit);
  if(!head->isInit)
  {
    Serial.println("head is null");
    head->nChar = c;
    uint8_t *tmp1 = (uint8_t *) malloc(50* sizeof(uint8_t));
    memcpy(tmp1, c.getBuff(), c.getSize());
    for (size_t i = 0; i < c.getSize(); i++)
    {
      Serial.println(tmp1[i],HEX);
    }
    head->isInit = true;
    // head->next = (CharNode*) malloc(sizeof(charNode));
  }
  else
  {
    Serial.println("head aint null");
    uint8_t *tmp1 = (uint8_t *) malloc(50* sizeof(uint8_t));
    memcpy(tmp1, c.getBuff(), c.getSize());
    for (size_t i = 0; i < c.getSize(); i++)
    {
      Serial.println(tmp1[i],HEX);
    }
    CharNode *curNode = (CharNode*) malloc(sizeof(charNode));
    curNode = head;
    bool newNodeCreated = false;
    while(newNodeCreated == false)
    {
        Serial.println("blyat");
        Serial.println(curNode->next->nChar.getCharacter());
        if (curNode->next->isInit == false)
        {
          Serial.println("blin");
          CharNode *nextNode = (CharNode*) malloc(sizeof(charNode));
          nextNode->nChar = c;
          nextNode->isInit = true;
          curNode->next = nextNode;
          newNodeCreated = true;
        }
        curNode = curNode->next;
    }
  }
}


Character Font::getChar(char c)
{
  Serial.println("getting node");
  CharNode *curNode;
  if (head == 0)
  {
    Serial.println("head is empty");
  }
  else
  {
    curNode = head;
    bool nodeFound = false;
    while(nodeFound == false)
    {
      Serial.print("c is ");
      Serial.println(c);
      if(c == curNode->nChar.getCharacter())
      {
        Serial.print("node found ");
        Serial.println(curNode->nChar.getCharacter());
        return curNode->nChar;
        nodeFound = true;
      }
      curNode = curNode->next;
    }
  }
  return curNode->nChar;
}

void Font::printChars()
{
  CharNode *curNode;
  curNode = head;
  int counter = 0;
  while(curNode != NULL)
  {
    Serial.print("character ");
    Serial.print(counter);
    Serial.print(" = ");
    Serial.println(curNode->nChar.getCharacter());
    ++counter;
    curNode = curNode->next;
  }
}

/*

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
      head->next  =(CharNode*)  malloc(sizeof(charNode));
    }
    else
    {
      Serial.println("head already exist");
      // loop through list till last and then add
      CharNode *curNode = head;
      while(curNode != 0)
      {
        if(curNode->next == 0)
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
*/
