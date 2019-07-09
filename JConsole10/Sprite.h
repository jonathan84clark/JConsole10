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
      Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, bool inUseGravity, ILI9341* inLcd);
      bool move_sprite();
      bool check_collision(Sprite* other);
      void update(float delta_t);
      void draw();
      void erase();
      Vector2D velocity;
      
   


   private:
      Vector2D position;
      Vector2D scale;
      float gravityScaler;
      float bounciness;
      float friction;
      bool useGravity;

      ILI9341* lcd;
      
};

#endif
