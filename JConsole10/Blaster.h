/*******************************************************
* BLASTER SUB CLASS
* DESC: The blaster sub class is designed to behave like a blaster
* shot.
* Author: Jonathan L Clark
* Date: 10/21/2019
*******************************************************/
#ifndef _BLASTER_
#define _BLASTER_

#include "src/hal/ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"

class Blaster : public Sprite
{
   public:
      // Public Functions
      Blaster() : Sprite()
      {
         // Do nothing
      }
      Blaster(Vector2D inPosition, int inColor, ILI9341* inLcd) : Sprite(inPosition, Vector2D(10, 3), 0.0, 0.0, false, true, inColor, 0, inLcd)
      {
          // Do nothing
      }
      
   private:
      
};

#endif /* BLASTER */
