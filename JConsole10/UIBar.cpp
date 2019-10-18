/*******************************************************
* UI BAR CLASS
* DESC: The UI Bar class is designed to provide a basic 
* health bar to display in the game.
* Author: Jonathan L Clark
* Date: 10/17/2019
*******************************************************/
#include <stdio.h>
#include "src/hal/ILI9341_SPI.h"
#include "UIBar.h"

UIBar::UIBar()
{
  
}

/****************************************************
* UI BAR CONSTRUCTOR
****************************************************/
UIBar::UIBar(Vector2D inPosition, bool inVertical, float inLength, float inWidth, int inColor, int inContrast, ILI9341* inLcd)
{
   position = inPosition;
   lcd = inLcd;
   width = inWidth;
   length = inLength;
   contrast = inContrast;
   vertical = inVertical;
}

/****************************************************
* UI BAR UPDATE
* DESC: Updates the UI bar with a new float value
****************************************************/
void UIBar::update(float newValue)
{
   if (newValue > 1.0)
   {
      newValue = 1.0;
   }
   if (newValue < 0.0)
   {
      newValue = 0.0;
   }
   float colorWidth = newValue * width;
   float contrastWidth = (1.0 - newValue) * width;

   if (vertical)
   {
      lcd->fillRect(position.y, position.x,  colorWidth, length, color);
      lcd->fillRect(position.y+colorWidth, position.x,  contrastWidth, length, contrast);
   }
   else
   {
      lcd->fillRect(position.y, position.x,  length, colorWidth, color);
      lcd->fillRect(position.y, position.x+colorWidth,  length, contrastWidth, contrast);
   }
}

/****************************************************
* ERASE
* DESC: Erases the UI bar from the screen.
****************************************************/
void UIBar::erase()
{
   if (vertical)
   {
      lcd->fillRect(position.y, position.x,  width, length, lcd->GetBgColor());
   }
   else
   {
      lcd->fillRect(position.y, position.x, length, width, lcd->GetBgColor());
   }
}
