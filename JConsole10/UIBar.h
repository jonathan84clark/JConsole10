/*******************************************************
* SPRITE CLASS
* DESC: The sprite class handles the behavior of a 2D sprite
* Gameobject. The class is desinged to be inherited and subclasses
* can be used to emulate different behaviors.
* Author: Jonathan L Clark
* Date: 7/2/2019
*******************************************************/
#ifndef _UIBAR_
#define _UIBAR_

#include "src/hal/ILI9341_SPI.h"
#include "Vector2D.h"

class UIBar
{
   public:
      // Public Functions
      UIBar();
      UIBar(Vector2D inPosition, float inLength, float inWidth, int inColor, int inContrast, ILI9341* inLcd);
      void update(float newValue);
      void draw();
      void destroy() { erase();}

      // Accessors and Mutators
      Vector2D GetPosition() { return position;}
   
   private:
      float value;
      void erase();
      Vector2D position;
      float width;
      float length;
      int color;
      int contrast;
      ILI9341* lcd;
      
};

#endif /*_UIBAR_*/
