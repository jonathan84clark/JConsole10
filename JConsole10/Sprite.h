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

#include "src/hal/ILI9341_SPI.h"
#include "Vector2D.h"

enum Orientation {RIGHT=2, LEFT=3, UP=0, DOWN=1};

class Sprite
{
   public:
      // Public Functions
      Sprite();
      Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, float inFriction, bool inUseGravity, bool inDestroyOnEdge, int inColor, int *inImage, ILI9341* inLcd);
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
      Vector2D GetScale() { return scale; }
      bool GetIsAlive() { return isAlive;}
      int GetOrientation() { return orientation; }
   
   private:

      // Helper functions
      bool move_one_direction(float edge1, float edge2, float highEdge, float scale, float &position, float &velocity);
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
      bool destroyOnEdge;

      // Internal Variables
      int framesSinceXCollision;
      int framesSinceYCollision;
      int color;
      int orientation;
      int* image;
      ILI9341* lcd;
      
};

#endif
