/*******************************************************
* SPRITE CLASS
* DESC: The sprite class handles the behavior of a 2D sprite
* Gameobject. The class is desinged to be inherited and subclasses
* can be used to emulate different behaviors.
* Author: Jonathan L Clark
* Date: 7/2/2019
*******************************************************/

#include <stdio.h>
#include "src/hal/ILI9341_SPI.h"
#include "Sprite.h"

Sprite::Sprite()
{
  isAlive = false;
}

/****************************************************
* SPRITE CONSTRUCTOR
****************************************************/
Sprite::Sprite(Vector2D inPosition, Vector2D inScale, float inBounciness, float inFriction, bool inUseGravity, bool inDestroyOnEdge, int inColor, ILI9341* inLcd)
{
   position = inPosition;
   lcd = inLcd;
   bounciness = inBounciness;
   friction = inFriction;
   useGravity = inUseGravity;
   destroyOnEdge = inDestroyOnEdge;
   gravityScaler = 0.2;
   scale.x = inScale.x;
   scale.y = inScale.y;
   color = inColor;
   framesSinceXCollision = 0;
   framesSinceYCollision = 0;
   isAlive = true;
}

/****************************************************
* ON COLLISION ENTER
* DESC: A user-defined function to handle collision events
****************************************************/
void Sprite::OnCollisionEnter(Sprite* other)
{
    // Custom collision handle
}


/****************************************************
* UPDATE
* DESC: Updates the sprite object, allowing it to move
* and redraw according to it's specs
****************************************************/
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

/******************************************************
* UPDATE FRICTION
* DESC: Handles applying friction to the gameobject
*******************************************************/
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

/******************************************************
* CHECK COLLISION
* DESC: Checks the current object against the input object
* to determine if they collided.
*******************************************************/
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
* MOVE ONE DIRECTION
* DESC: Moves the sprite in a single direction either x or y.
*******************************************************/
bool Sprite::move_one_direction(float edge1, float edge2, float highEdge, float scale, float &position, float &velocity)
{
   // Move the sprite in the x direction but only if it won't leave the screen
   if (edge1 < highEdge && edge2 > 0.0)
   {
       position += velocity;
   }
   else
   {
      // Take us all the way to the edge of the screen
      position = ((edge1 >= highEdge) ? (highEdge - scale) : 0);
      if (destroyOnEdge)
      {
         destroy();
         return false;
      }
      velocity = velocity * -1.0 * bounciness;
   }
   return true;
}

/******************************************************
* MOVE SPRITE
* DESC: Moves the sprite by the input vector.
*******************************************************/
bool Sprite::move_sprite()
{
   //Computations to determine if we are at the edge of the screen.
   Vector2D newPosition = position;

   // Compute the new x position
   if (!move_one_direction((position.x + velocity.x + scale.x), (position.x + velocity.x), ILI9341HEIGHT, scale.x, newPosition.x, velocity.x))
   {
      return false;
   }

   // Compute the new y position
   if (!move_one_direction((position.y + velocity.y + scale.y), (position.y + velocity.y), ILI9341WIDTH, scale.y, newPosition.y, velocity.y))
   {
      return false;
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
   lcd->fillRect(position.y, position.x,  scale.y, scale.x, color);
}

void Sprite::erase()
{
   lcd->fillRect(position.y, position.x, scale.y, scale.x, lcd->GetBgColor());
}
