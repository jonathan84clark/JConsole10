/******************************************************************
* PRINTF.H
* DESCRIPTION: Contains function prototyopes for performing formatted
* text printing to the LCD display. Also contains a custom pause function.
* Author: Jonathan L Clark
* Date: 5/6/2015
* Update: 7/1/2019, Modified the Text printer to be in it's own class
******************************************************************/
#ifndef DRIVERS_PRINTF_H_
#define DRIVERS_PRINTF_H_
#include <stdint.h>

class TextPrinter
{
   public:
      TextPrinter();
      void draw_char(unsigned char c);
      void _print(char *characters);

   private:
      int text_size;
      uint16_t color;
      uint16_t background_color;
      uint16_t row_spacing;
      uint16_t x_cursor;
      uint16_t y_cursor;
      uint16_t indent_position;
   
};

#endif /* DRIVERS_PRINTF_H_ */
