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
  isAlive = false;
}

/****************************************************
*
****************************************************/
Sprite::Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, float inFriction, bool inUseGravity, int color, ILI9341* inLcd)
{
   position = inPosition;
   lcd = inLcd;
   bounciness = inBounciness;
   friction = inFriction;
   useGravity = inUseGravity;
   gravityScaler = 0.2;
   scale.x = inScale.x;
   scale.y = inScale.y;
   framesSinceXCollision = 0;
   framesSinceYCollision = 0;
   isAlive = true;
}

void Sprite::OnCollisionEnter(Sprite* other)
{
    // Custom collision handle
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
   update_friction();
}

void Sprite::update_friction()
{
   if (friction > 0.0)
   {
      if (velocity.x > 0.0)
      {
          velocity.x -= friction;
      }
      else if (velocity.x < 0.0)
      {
          velocity.x += friction;
      }
      if (velocity.y > 0.0)
      {
         velocity.y -= friction;
      }
      else if (velocity.y < 0.0)
      {
         velocity.y += friction;
      }
   }
}

bool Sprite::check_collision(Sprite* other)
{
  bool collision = false;
  // Calculate all the edges
  int myTopEdge = position.y + scale.y;
  int otherTopEdge = other->position.y + other->scale.y;
  int myRightEdge = position.x + scale.x;
  int otherRightEdge = other->position.x + other->scale.x;
  
   // Handle x direction collisions
   if (framesSinceXCollision > 4 && position.y < otherTopEdge && myTopEdge > other->position.y)
   {
       // Object collided with the other on its right edge
       if (myRightEdge > other->position.x && myRightEdge < otherRightEdge)
       {
          velocity.x = velocity.x * -1.0 * bounciness;
          framesSinceXCollision = 0;
          collision = true;
       }
       // Object collided with the other on its left edge
       if (position.x < otherRightEdge && position.x > other->position.x)
       {
           velocity.x = velocity.x * -1.0 * bounciness;
          framesSinceXCollision = 0;
          collision = true;
       }
   }

   // Handle y direction collisions
   if (framesSinceYCollision > 4 && position.x < otherRightEdge && myRightEdge > other->position.x)
   {
      // Hitting an object on the bottom edge
      if (position.y < otherTopEdge && position.y > other->position.y)
      {
         velocity.y = velocity.y * -1.0 * bounciness;
         framesSinceYCollision = 0;
         collision = true;
      }
      // Hitting an object on the top edge
      if (myTopEdge > other->position.y && myTopEdge < otherTopEdge)
      {
         velocity.y = velocity.y * -1.0 * bounciness;
         framesSinceYCollision = 0;
         collision = true;
      }
   }
   // Objects are not allowed to collide every frame (this prevents them from getting stuck)
   framesSinceYCollision++;
   framesSinceXCollision++;
   if (collision)
   {
      OnCollisionEnter(other);
   }
   return collision;
}

/******************************************************
* MOVE SPRITE
* DESC: Moves the sprite by the input vector.
*******************************************************/
bool Sprite::move_sprite()
{
   //Computations to determine if we are at the edge of the screen.
   float newRightEdge = position.x + velocity.x + scale.x;
   float newLeftEdge = position.x + velocity.x;
   float newTopEdge = position.y + velocity.y + scale.y;
   float newBottomEdge = position.y + velocity.y;
   Vector2D newPosition = position;
   
   // Move the sprite in the x direction but only if it won't leave the screen
   if (newRightEdge < ILI9341HEIGHT && newLeftEdge > 0.0)
   {
       newPosition.x += velocity.x;
   }
   else
   {
      // Take us all the way to the edge of the screen
      if (newRightEdge >= ILI9341HEIGHT)
      {
         newPosition.x = ILI9341HEIGHT - scale.x;
      }
      else
      {
         newPosition.x = 0;
      }
      velocity.x = velocity.x * -1.0 * bounciness;
   }
   // Move the sprite in the y direction but only if it won't leave the screen.
   if (newTopEdge < ILI9341WIDTH && newBottomEdge > 0.0)
   {
      newPosition.y += velocity.y;
   }
   else
   {
      if (newTopEdge >= ILI9341WIDTH)
      {
         newPosition.y = ILI9341WIDTH - scale.y;
      }
      else
      {
         newPosition.y = 0;
      }
      velocity.y = velocity.y * -1.0 * bounciness;
   }
   // Drawing the sprite is VERY expensive, only do it if we have moved by at least one pixel position
   if ((int)newPosition.x != (int)position.x || (int)newPosition.y != (int)position.y)
   {
      erase();
      position = newPosition;
      draw();
      return true;
   }
   // In all other cases we still want to move but we don't need to draw if we didn't move 1 pixel position
   else
   {
      position = newPosition;
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
