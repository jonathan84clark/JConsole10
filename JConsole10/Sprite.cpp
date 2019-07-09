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


Sprite::Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, bool inUseGravity, ILI9341* inLcd)
{
   position = inPosition;
   lcd = inLcd;
   bounciness = inBounciness;
   friction = 0.0;
   useGravity = inUseGravity;
   gravityScaler = 0.2;
   scale.x = inScale.x;
   scale.y = inScale.y;
}

void Sprite::update(float delta_t)
{
   if (useGravity)
   {
      float vo = velocity.y;
      delta_t = delta_t * gravityScaler; // Apply a gravity scaler to scale it for the screen size
      float vf = vo + -9.81 * delta_t;
      velocity.y = vf;
   }
   move_sprite();
}

bool Sprite::check_collision(Sprite* other)
{
   // Object collided with the other on its right edge
   if (position.x + scale.x + 1 >= other->position.x)
   {
      //velocity.x = velocity.x * -1.0 * bounciness;
      //erase();
      //position.x -= 2;
   }
   // Object collided with the other on its left edge
   if (position.x <= (other->scale.x + other->position.x) && position.y )
   {
      velocity.x = velocity.x * -1.0 * bounciness;
      //erase();
      //position.x += 2;
      return true;
   }
   return false;
}

/******************************************************
* MOVE SPRITE
* DESC: Moves the sprite by the input vector.
*******************************************************/
bool Sprite::move_sprite()
{
   bool moved = false;
   Vector2D previousPos = position;
   // Move the sprite in the x direction but only if it won't leave the screen
   if (position.x + velocity.x + scale.x < ILI9341HEIGHT && (position.x + velocity.x) > 0)
   {
       if (velocity.x != 0.0)
       {
          erase();
          moved = true;
       }
       position.x += velocity.x;
   }
   else
   {
      // Take us all the way to the edge of the screen
      if (position.x + velocity.x + scale.x >= ILI9341HEIGHT)
      {
         position.x = ILI9341HEIGHT - scale.x;
      }
      else
      {
         position.x = 0;
      }
      velocity.x = velocity.x * -1.0 * bounciness;
   }
   // Move the sprite in the y direction but only if it won't leave the screen.
   if (position.y + velocity.y + scale.y < ILI9341WIDTH && position.y + velocity.y > 0)
   {
      // If we already moved in the x direction we already erased and shoul'nt do it again
      if (!moved && velocity.y != 0.0)
      {
         erase();
         moved = true;
      }
      position.y += velocity.y;
   }
   else
   {
      if (position.y + velocity.y + scale.y >= ILI9341WIDTH)
      {
         position.y = ILI9341WIDTH - scale.y;
      }
      else
      {
         position.y = 0;
      }
      velocity.y = velocity.y * -1.0 * bounciness;
   }
   // Only re-draw the sprite if we were able to move
   if (moved || previousPos.x != position.x || previousPos.y != position.y)
   {
       draw();
       return true;
   }
   return false;
}

void Sprite::draw()
{
   lcd->fillRect(position.y, position.x,  scale.y, scale.x, COLOR_RED);
}

void Sprite::erase()
{
   lcd->fillRect(position.y, position.x, scale.y, scale.x, lcd->GetBgColor());
}
