/******************************************************************
* PRINTF.H
* DESCRIPTION: Contains function prototyopes for performing formatted
* text printing to the LCD display. Also contains a custom pause function.
* Author: Jonathan L Clark
* Date: 5/6/2015
******************************************************************/

#ifndef DRIVERS_PRINTF_H_
#define DRIVERS_PRINTF_H_
#include <stdint.h>

void _printf(char *characters, ...);
void unsigned_int_toStr(unsigned int input, char* printBuffer, char* printBufferRev);
void int_toStr(int input, char* printBuffer, char* printBufferRev);
void printf_setFont_properties(unsigned char inFontSize, unsigned char inFontRowSpacing, uint16_t inFontColor, uint16_t inFontBgColor);
void printf_setFont_location(uint16_t inStartX, uint16_t inStartY);
unsigned char getFontSize(void);
uint16_t getFontColor(void);
uint16_t getFontBackgroundColor(void);
uint16_t getFontRowSpacing(void);
char Pause(struct HighScore* highScores);
void printf_init(void);

/************************************************
* FONT SETTINGS
* DESCRIPTION: Struct contains the configuration
* settings for the font. 42 bytes
************************************************/
struct _font_settings
{
	unsigned char size;
	uint16_t color;
	uint16_t bg_color;
	uint16_t row_spacing;
	uint16_t x;
	uint16_t y;
};


#endif /* DRIVERS_PRINTF_H_ */
