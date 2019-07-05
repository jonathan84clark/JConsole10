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


Sprite::Sprite(Vector2D inPosition, Vector2D inScale, ILI9341* inLcd)
{
   position = inPosition;
   lcd = inLcd;
   scale.x = inScale.x;
   scale.y = inScale.y;
}

/******************************************************
* MOVE SPRITE
* DESC: Moves the sprite by the input vector.
*******************************************************/
bool Sprite::move_sprite(Vector2D delta)
{
   bool moved = false;
   // Move the sprite in the x direction but only if it won't leave the screen
   if (position.x + delta.x + scale.x < ILI9341HEIGHT && position.x + delta.x > 0)
   {
       erase();
       position.x += delta.x;
       moved = true;
   }
   // Move the sprite in the y direction but only if it won't leave the screen.
   if (position.y + delta.y + scale.y < ILI9341WIDTH && position.y + delta.y > 0)
   {
      // If we already moved in the x direction we already erased and shoul'nt do it again
      if (!moved)
      {
         erase();
      }
      position.y += delta.y;
   }
   // Only re-draw the sprite if we were able to move
   if (moved)
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

void Sprite::update()
{
   lcd->fillRect(position.y, position.x, scale.y, scale.x, lcd->GetBgColor());
   position.x += 4;
   position.y -= 4;
   if (position.x >= 200)
   {
      position.x = 0;
   }
   if (position.y <= 11)
   {
      position.y = 200;
   }
   draw();
}
