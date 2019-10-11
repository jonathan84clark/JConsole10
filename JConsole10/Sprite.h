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
      // Public Functions
      Sprite();
      Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, float inFriction, bool inUseGravity, int color, ILI9341* inLcd);
      bool move_sprite();
      bool check_collision(Sprite* other);
      void update(float delta_t);
      void draw();
      void destroy() { isAlive = false; erase();}
      virtual void OnCollisionEnter(Sprite* other);

      // Accessors and Mutators
      void SetVelocity(Vector2D inVelocity) { velocity = inVelocity;}
      Vector2D GetVelocity() { return velocity;}
      Vector2D GetPosition() { return position;}
      bool GetIsAlive() { return isAlive;}
   
   private:
      // Internal update functions
      void update_friction();
      void erase();

      // State Variables
      Vector2D position;
      Vector2D velocity;
      Vector2D scale;
      float gravityScaler;
      float bounciness;
      float friction;
      bool isAlive;
      bool useGravity;

      // Internal Variables
      int framesSinceXCollision;
      int framesSinceYCollision;
      ILI9341* lcd;
      
};

#endif
