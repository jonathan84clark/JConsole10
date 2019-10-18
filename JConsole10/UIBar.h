/*******************************************************
* UI BAR CLASS
* DESC: The UI Bar class is designed to provide a basic 
* health bar to display in the game.
* Author: Jonathan L Clark
* Date: 10/17/2019
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
      UIBar(Vector2D inPosition, bool inVertical, float inLength, float inWidth, int inColor, int inContrast, ILI9341* inLcd);
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
      bool vertical;
      ILI9341* lcd;
      
};

#endif /*_UIBAR_*/
