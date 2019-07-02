/******************************************************************
* PRINTF.C
* DESCRIPTION: Contains function definitions for performing formatted
* text printing to the LCD display. Also contains a custom pause function.
* Author: Jonathan L Clark
* Date: 5/6/2015
* Ported by: Jonathan L Clark
* Date: 4/30/2015, Ported to C code for the MSP430 intended for JConsole6.
* Update: 7/1/2018, Encapsulated the print function into it's own class
******************************************************************/
#include "ILI9341_Printf.h"
#include<stdio.h>
#include "ILI9341_SPI.h"
#include "stdarg.h"
#include "glcdfont.cpp"

/*****************************************************
* PRINTF INIT
* DESCRIPTION: Initialize the printf system.
****************************************************/
TextPrinter::TextPrinter(void)
{
   text_size = 2;
   color = COLOR_BLACK;
   background_color = COLOR_WHITE;
   row_spacing = 0;
   x_cursor = 0;
   y_cursor = 200;
   indent_position = x_cursor;
}

/********************************************************
* DRAW CHAR
* DESCRIPTION: Pulled this from the adafruit GFX library.
**********************************************************/
void TextPrinter::draw_char(unsigned char c) {

  int16_t i;
  int16_t j;

  for (i=5; i>=0; i-- ) 
  {
    char line;
    if (i == 5)
    {
      line = 0x0;
    }
    else
    {
      line = font[c][i];
    }
    for (j = 0; j<8; j++) 
    {
      if (line & 0x1) 
      {
        if (text_size == 1)
        {
           ILI9341_drawPixel(y_cursor-j, x_cursor+i, color);  //facing right
        }
        else 
        {
           ILI9341_fillRect(y_cursor-(j*text_size), x_cursor+(i*text_size), text_size, text_size, color);  //facing right
        }
      } 
      else if (background_color != color) 
      {
         if (text_size == 1)
         {
            ILI9341_drawPixel(y_cursor-j, x_cursor+i, background_color);  //facing right
         }
         else 
         {  // big size
            ILI9341_fillRect(y_cursor-j*text_size, x_cursor+i*text_size, text_size, text_size, background_color); //facing right
         }
      }
      line >>= 1;
    }
   }
   x_cursor+=6*text_size;
   if (x_cursor >= ILI9341WIDTH +55)
   {
      y_cursor -= 6*text_size + text_size + 1;
      x_cursor = indent_position;
   }
}


void TextPrinter::_print(char *characters)
{
   while(*characters)
   {
      if (*characters == '\n')
      {
         y_cursor -= 6*text_size + text_size + 1;
         x_cursor = indent_position;
      }
      else
      {
         draw_char(*characters);
      }
      characters++;
   }
}
