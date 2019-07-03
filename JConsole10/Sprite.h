/*******************************************************
* SPRITE CLASS
* DESC: The sprite class handles the behavior of a 2D sprite
* Gameobject. The class is desinged to be inherited and subclasses
* can be used to emulate different behaviors.
* Author: Jonathan L Clark
* Date: 7/2/2019
*******************************************************/
#ifndef _SPRITE_
#define _SPRITE_

#include "ILI9341_SPI.h"

class Sprite
{
   public:
      Sprite();
      Sprite(uint16_t inX, uint16_t inY, ILI9341* inLcd);
      void draw();
      void update();
   


   private:
      uint16_t x;
      uint16_t y;
      ILI9341* lcd;
      
};

#endif
