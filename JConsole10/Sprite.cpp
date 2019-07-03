/*******************************************************
* SPRITE CLASS
* DESC: The sprite class handles the behavior of a 2D sprite
* Gameobject. The class is desinged to be inherited and subclasses
* can be used to emulate different behaviors.
* Author: Jonathan L Clark
* Date: 7/2/2019
*******************************************************/

#include <stdio.h>
#include "ILI9341_SPI.h"
#include "Sprite.h"

Sprite::Sprite()
{
  
}


Sprite::Sprite(uint16_t inX, uint16_t inY, ILI9341* inLcd)
{
   x = inX;
   y = inY;
   lcd = inLcd;
   //lcd->_print("testtesttesttesttest");
}

void Sprite::draw()
{
   lcd->fillRect(y, x,  10, 10, COLOR_RED);
}

void Sprite::update()
{
   lcd->fillRect(y, x, 10, 10, lcd->GetBgColor());
   x += 4;
   y -= 4;
   if (x >= 200)
   {
      x = 0;
   }
   if (y <= 11)
   {
      y = 200;
   }
   draw();
}
