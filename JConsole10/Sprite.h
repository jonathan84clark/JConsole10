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
#include "Vector2D.h"

class Sprite
{
   public:
      Sprite();
      Sprite(Vector2D inPosition, Vector2D inScale, ILI9341* inLcd);
      bool move_sprite(Vector2D delta);
      void physics_update(float delta_t);
      void draw();
      void erase();
      void update();
      Vector2D velocity;
      
   


   private:
      Vector2D position;
      Vector2D scale;

      ILI9341* lcd;
      
};

#endif
