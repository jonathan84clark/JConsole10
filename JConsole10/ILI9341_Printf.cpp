/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!

Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Ported by: Jonathan L Clark
Date: 4/30/2015, Ported to C code for the MSP430 intended for JConsole6.
Update: 12/1/2015, Ported from JConsole7 to JConsole8
*/
/******************************************************************
* PRINTF.C
* DESCRIPTION: Contains function definitions for performing formatted
* text printing to the LCD display. Also contains a custom pause function.
* Author: Jonathan L Clark
* Date: 5/6/2015
******************************************************************/

#include "ILI9341_Printf.h"

#include<stdio.h>
#include "ILI9341_SPI.h"
#include "stdarg.h"
#include "glcdfont.c"

struct _font_settings font_config;
unsigned char getFontSize(void){return font_config.size;}
uint16_t getFontColor(void){return font_config.color;}
uint16_t getFontBackgroundColor(void){return font_config.bg_color;}
uint16_t getFontRowSpacing(void){return font_config.row_spacing;}

/*****************************************************
* PRINTF INIT
* DESCRIPTION: Initialize the printf system.
****************************************************/
void printf_init(void)
{
	font_config.size = 3;
	font_config.color = COLOR_BLACK;
	font_config.bg_color = COLOR_WHITE;
	font_config.row_spacing = 0;
	font_config.x = 30;
	font_config.y = 250;
}

/********************************************************
* DRAW CHAR
* DESCRIPTION: Pulled this from the adafruit GFX library.
**********************************************************/
void printf_drawChar(int16_t x, int16_t y, uint16_t yOriginal, unsigned char c) {

  if((x >= ILI9341WIDTH)            || // Clip right
     (y >= ILI9341HEIGHT)           || // Clip bottom
     ((x + 6 * font_config.size - 1) < 0) || // Clip left
     ((y + 8 * font_config.size - 1) < 0))   // Clip top
    return;
  int16_t i;
  int16_t j;

  for (i=0; i<6; i++ ) {
    char line;
    if (i == 5)
      line = 0x0;
    else
      line = font[c][i];//pgm_read_byte(font+(c*5)+i);
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (font_config.size == 1) // default size
            ILI9341_drawPixel(x+j, y-i, font_config.color);  //facing right
        else {  // big size
        	ILI9341_fillRect(x+(j*font_config.size), y-(i*font_config.size), font_config.size, font_config.size, font_config.color);  //facing right
        }
      } else if (font_config.bg_color != font_config.color) {
        if (font_config.size == 1) // default size
            ILI9341_drawPixel(x+j, y-i, font_config.bg_color);  //facing right
        else {  // big size
        	ILI9341_fillRect(x+j*font_config.size, y-i*font_config.size, font_config.size, font_config.size, font_config.bg_color); //facing right
        }
      }
      line >>= 1;
    }
  }
  font_config.x-=6*font_config.size;
  //Wrap the line
  if (font_config.x - 6 < 0)
  {
     font_config.x = yOriginal;
     font_config.y+=8*font_config.size + font_config.row_spacing;
  }
}

/***********************************************
* SET FONT PROPERTIES
* DESCRIPTION: Setup the properties of the font that is to be printed.
************************************************/
void printf_setFont_properties(unsigned char inFontSize, unsigned char inFontRowSpacing, uint16_t inFontColor, uint16_t inFontBgColor)
{
   font_config.size = inFontSize;
   font_config.row_spacing = inFontRowSpacing;
   font_config.color = inFontColor;
   font_config.bg_color = inFontBgColor;

}

/****************************************************
* PRINTF SET FONT LOCATION
* DESCRIPTION: Sets the start location of the text
* to be printed to the screen.
****************************************************/
void printf_setFont_location(uint16_t inStartX, uint16_t inStartY)
{
	font_config.x = inStartY;
	font_config.y = inStartX;
}


/**********************************************
* _printf
* DESCRIPTION: Writes a formatted string to the LCD.
**********************************************/
void _printf(char *characters, ...)
{
   va_list arg;
   va_start(arg, characters);
   char* tempStr;
   unsigned int tempArg = 0;
   uint16_t i;
   uint16_t xOriginal = font_config.x;
   uint16_t yOriginal = font_config.y;
   char printBuffer[15];
   char printBufferRev[15];

   while (*characters)
   {
	  //Move to the next line
	  if (*characters == '\n')
	  {
         font_config.y+=8*font_config.size + font_config.row_spacing;
	  }
	  //Carrage return
	  else if (*characters == '\r')
	  {
		  font_config.x = xOriginal;
	  }
	  else if (*characters == '%' && (*characters) && *(characters+1) == 's')
	  {
		  tempStr = va_arg(arg, char*);
		  while (*tempStr)
		  {
			 printf_drawChar(font_config.y, font_config.x, yOriginal, *tempStr);
		     tempStr++;
		  }
		  characters++;
	  }
	  else if (*characters == '%' && (*characters) && *(characters+1) == 'c')
	  {
		  tempStr = va_arg(arg, char*);
		  printf_drawChar(font_config.y, font_config.x, yOriginal, *tempStr);
		  characters++;
	  }
	  else if (*characters == '%' && (*characters) && *(characters+1) == 'u')
	  {
		  tempArg = va_arg(arg, unsigned long);
		  unsigned_int_toStr(tempArg, printBuffer, printBufferRev);
		  for (i = 0; i < 15; i++)
		  {
			 if (printBuffer[i] == '\0')
			 {
				 break;
			 }
			 printf_drawChar(font_config.y, font_config.x, yOriginal, printBuffer[i]);
		  }
		  characters++;
	  }
	  else if (*characters == '%' && (*characters) && *(characters+1) == 'd')
	  {
		  tempArg = va_arg(arg, int);
		  int_toStr(tempArg, printBuffer, printBufferRev);
		  for (i = 0; i < 15; i++)
		  {
			 if (printBuffer[i] == '\0')
			 {
				 break;
			 }
			 printf_drawChar(font_config.y, font_config.x, yOriginal, printBuffer[i]);
		  }
		  characters++;
	  }
	  //Print the next character in the string
	  else
	  {
		 printf_drawChar(font_config.y, font_config.x, yOriginal, *characters);
	  }
	  characters++;
   }
   va_end(arg);
}

/****************************************************
* INT TO STR
* DESCRIPTION: Converts an integer to a string
* placing it in the printf_buffer for later use.
****************************************************/
void int_toStr(int input, char* printBuffer, char* printBufferRev)
{
    int i;
    int j = 0;
    if (input < 0)
    {
    	input *= -1;
    	printBuffer[j] = '-';
    	j++;

    }
    for (i = 0; i < 15; i++)
    {
        printBufferRev[i] = input % 10 + 48;
    	input = input / 10;
    	if (input == 0)
    	{
    		i++;
    		printBufferRev[i] = '\0';
    		break;
    	}
    }
    i--;
    while (i >= 0)
    {
        printBuffer[j] = printBufferRev[i];
    	i--;
    	j++;
    }
    printBuffer[j] = '\0';

}

/****************************************************
* UNSIGNED INT TO STR
* DESCRIPTION: Converts an unsigned integer to a string
* placing it in the printf_buffer for later use.
****************************************************/
void unsigned_int_toStr(unsigned int input, char* printBuffer, char* printBufferRev)
{
    int i;
    int j = 0;
    for (i = 0; i < 15; i++)
    {
        printBufferRev[i] = input % 10 + 48;
    	input = input / 10;
    	if (input == 0)
    	{
    		i++;
    		printBufferRev[i] = '\0';
    		break;
    	}
    }
    i--;
    while (i >= 0)
    {
        printBuffer[j] = printBufferRev[i];
    	i--;
    	j++;
    }
    printBuffer[j] = '\0';

}

/*******************************************************
* PAUSE
* DESCRIPTION: Places a menu over the current screen, this menu
* contains user options. If we return 0 the resume option
* has been hit if we return 1 the quit option has been hit.
*******************************************************/
char Pause(struct HighScore* highScores)
{
	struct Solid cursor;
    uint16_t bgColorTemp = GetBgColor();
	unsigned char selection = 0;
	unsigned char tempFontSize = getFontSize();
	uint16_t tempFontColor = getFontColor();
	uint16_t tempFontBgColor = getFontBackgroundColor();
	int tempFontRowSpacing = getFontRowSpacing();

    printf_setFont_properties(2, 0, COLOR_RED, GetBgColor());

    printf_setFont_location(40, 220);
	_printf("* Pause *\r\n Resume\r\n High Scores\r\n Sound: %s\r\n White LEDs\r\n UV LEDs\r\n Quit", getSoundState());
	build_solid(&cursor, 60, 222, 8, 8, COLOR_RED);

	StartTimer(0, 200);
    StartTimer(1, 200);
	for (;;)
	{
		if (CheckTimer(0))
		{
			if (GetUp() && GetJoystickYMag() > 4)
			{
			   if (selection > 0)
			   {
			      solid_moveLocation(&cursor, cursor.y_pos - 15, cursor.x_pos);
			      selection--;
			      StartTimer(0, 200);
			   }
			}
			else if (GetDown() && GetJoystickYMag() > 4)
			{
			   if (selection < 5)
			   {
			      solid_moveLocation(&cursor, cursor.y_pos + 15, cursor.x_pos);
			      selection++;
			      StartTimer(0, 200);
			   }
			}
		}
		if (CheckTimer(1))
		{
            if (GetTopLeft() || GetTopRight())
            {
            	//Resume game
            	if (selection == 0)
            	{
            	    display_solid(&cursor, 1);
            	    ILI9341_fillRect(40, 78, 100, 151, GetBgColor());
            		printf_setFont_properties(tempFontSize, tempFontRowSpacing, tempFontColor, tempFontBgColor);
            		return 0;
            	}
            	else if (selection == 1)
            	{
            	    HighScorePause(highScores, 255, 0x0000);
            		setBgColor(bgColorTemp); //Trigger a screen clear
            		printf_setFont_properties(tempFontSize, tempFontRowSpacing, tempFontColor, tempFontBgColor);
            		return 0;
            	}
            	else if (selection == 2)
            	{
            		toggle_sound();
            		printf_setFont_location(40, 220);
            		_printf("* Pause *\r\n Resume\r\n High Scores\r\n Sound: %s\r\n White LEDs\r\n UV LEDs\r\n Quit", getSoundState());
            	}
            	else if (selection == 3)
            	{
            		ToggleSuperWhite();
            	}
            	else if (selection == 4)
            	{
            		ToggleUVLeds();
            	}
            	//Quit game
            	else if (selection == 5)
            	{
            	    printf_setFont_location(40, 220);
            	    display_solid(&cursor, 1);
            		printf_setFont_properties(tempFontSize, tempFontRowSpacing, tempFontColor, tempFontBgColor);
            		return 1;
            	}
            	StartTimer(1, 200);
            }
		}
	}
}
