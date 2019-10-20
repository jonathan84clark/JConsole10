/***************************************************
  This is our library for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
  ******************************************************
  Ported to MSP432; JConsole8 by Jonathan L Clark, software was changed
  from cpp to c.
 ****************************************************/

#include <stdio.h>
#include <stddef.h>
#include <SPI.h>
#include "glcdfont.cpp"
#include "ILI9341_SPI.h"



uint16_t palette[18] = {COLOR_BLUE, COLOR_RED, COLOR_GOLDENROD, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW,
		                COLOR_LTGREY, COLOR_DRKGREY, COLOR_LTGREEN, COLOR_LIMEGREEN, COLOR_PURPLE, COLOR_ORANGE,
						COLOR_NAVY, COLOR_DARKGREEN, COLOR_DARKCYAN, COLOR_OLIVE, COLOR_GREENYELLOW, COLOR_PINK};

/********************************************************
* DRAW CHAR
* DESCRIPTION: Pulled this from the adafruit GFX library.
**********************************************************/
void ILI9341::draw_char(unsigned char c) {

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
           drawPixel(y_cursor-j, x_cursor+i, color);  //facing right
        }
        else 
        {
           fillRect(y_cursor-(j*text_size), x_cursor+(i*text_size), text_size, text_size, color);  //facing right
        }
      } 
      else if (background_color != color) 
      {
         if (text_size == 1)
         {
            drawPixel(y_cursor-j, x_cursor+i, background_color);  //facing right
         }
         else 
         {  // big size
            fillRect(y_cursor-j*text_size, x_cursor+i*text_size, text_size, text_size, background_color); //facing right
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

/********************************************************
* PRINT
* DESCRIPTION: The print function prints text to the LCD
**********************************************************/
void ILI9341::_print(char *characters)
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

/**************************************************
* SET BG COLOR
* DESCRIPTION: Sets the background color of the LCD and
* fills the screen.
**************************************************/
void ILI9341::setBgColor(uint16_t inColor)
{
   bg_color = inColor;
   fillScreen(bg_color);
}

/**************************************************
* GET PALETTE COLOR
* DESCRIPTION: Returns a static color from the color
* palette (for random purposes)
**************************************************/
uint16_t ILI9341::GetPaletteColor(char index)
{
    return COLOR_WHITE;
}

/**************************************************
* WRITE COMMAND
* DESCRIPTION: Write a command to the LCD
**************************************************/
void ILI9341::writecommand(uint8_t c)
{
  digitalWrite(TFT_DC, LOW);
  digitalWrite(TFT_CS, LOW);
  SPI.transfer(c);
  digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* WRITE DATA
* DESCRIPTION: Write data to the LCD
**************************************************/
void ILI9341::writedata(uint8_t c)
{
   digitalWrite(TFT_DC, HIGH);
   digitalWrite(TFT_CS, LOW);
   SPI.transfer(c);
   digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* INITIALIZE
* DESCRIPTION: Initializes the LCD
**************************************************/
void ILI9341::initialize(void)
{
   pinMode(TFT_DC, OUTPUT);
   pinMode(TFT_CS, OUTPUT);
   pinMode(TFT_RST, OUTPUT);
   digitalWrite(TFT_RST, HIGH);
   delay(5);
   digitalWrite(TFT_RST, LOW);
   delay(20);
   digitalWrite(TFT_RST, HIGH);
   delay(150);

   writecommand(0xEF);
   writedata(0x03);
   writedata(0x80);
   writedata(0x02);

   writecommand(0xCF);
   writedata(0x00);
   writedata(0XC1);
   writedata(0X30);

   writecommand(0xED);
   writedata(0x64);
   writedata(0x03);
   writedata(0X12);
   writedata(0X81);

   writecommand(0xE8);
   writedata(0x85);
   writedata(0x00);
   writedata(0x78);

   writecommand(0xCB);
   writedata(0x39);
   writedata(0x2C);
   writedata(0x00);
   writedata(0x34);
   writedata(0x02);

   writecommand(0xF7);
   writedata(0x20);

   writecommand(0xEA);
   writedata(0x00);
   writedata(0x00);

   writecommand(ILI9341_PWCTR1);    //Power control
   writedata(0x23);   //VRH[5:0]

   writecommand(ILI9341_PWCTR2);    //Power control
   writedata(0x10);   //SAP[2:0];BT[3:0]

   writecommand(ILI9341_VMCTR1);    //VCM control
   writedata(0x3e); //¶Ô±È¶Èµ÷½Ú
   writedata(0x28);

   writecommand(ILI9341_VMCTR2);    //VCM control2
   writedata(0x86);  //--

   writecommand(ILI9341_MADCTL);    // Memory Access Control
   writedata(0x48);

   writecommand(ILI9341_PIXFMT);
   writedata(0x55);

   writecommand(ILI9341_FRMCTR1);
   writedata(0x00);
   writedata(0x18);

   writecommand(ILI9341_DFUNCTR);    // Display Function Control
   writedata(0x08);
   writedata(0x82);
   writedata(0x27);

   writecommand(0xF2);    // 3Gamma Function Disable
   writedata(0x00);

   writecommand(ILI9341_GAMMASET);    //Gamma curve selected
   writedata(0x01);

   writecommand(ILI9341_GMCTRP1);    //Set Gamma
   writedata(0x0F);
   writedata(0x31);
   writedata(0x2B);
   writedata(0x0C);
   writedata(0x0E);
   writedata(0x08);
   writedata(0x4E);
   writedata(0xF1);
   writedata(0x37);
   writedata(0x07);
   writedata(0x10);
   writedata(0x03);
   writedata(0x0E);
   writedata(0x09);
   writedata(0x00);

   writecommand(ILI9341_GMCTRN1);    //Set Gamma
   writedata(0x00);
   writedata(0x0E);
   writedata(0x14);
   writedata(0x03);
   writedata(0x11);
   writedata(0x07);
   writedata(0x31);
   writedata(0xC1);
   writedata(0x48);
   writedata(0x08);
   writedata(0x0F);
   writedata(0x0C);
   writedata(0x31);
   writedata(0x36);
   writedata(0x0F);

   writecommand(ILI9341_SLPOUT);    //Exit Sleep
   delay(120);
   writecommand(ILI9341_DISPON);    //Display on

   setRotation(0);
}

/**************************************************
* ILI9341 BEGIN
* DESCRIPTION: Initializes the ILI9341 LCD and interface.
**************************************************/
ILI9341::ILI9341()
{
   text_size = 2;
   color = COLOR_BLACK;
   background_color = COLOR_WHITE;
   row_spacing = 0;
   x_cursor = 0;
   y_cursor = 200;
   indent_position = x_cursor;
   bg_color = COLOR_GREEN;

}

/**************************************************
* SET ADDR WINDOW
* DESCRIPTION: Set the address Window that will be written to
**************************************************/
void ILI9341::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

   writecommand(ILI9341_CASET); // Column addr set
   writedata(x0 >> 8);
   writedata(x0 & 0xFF);     // XSTART
   writedata(x1 >> 8);
   writedata(x1 & 0xFF);     // XEND

   writecommand(ILI9341_PASET); // Row addr set
   writedata(y0>>8);
   writedata(y0);     // YSTART
   writedata(y1>>8);
   writedata(y1);     // YEND

   writecommand(ILI9341_RAMWR); // write to RAM
}

/**************************************************
* DRAW PIXEL
**************************************************/
void ILI9341::drawPixel(int16_t x, int16_t y, uint16_t color)
{

   if((x < 0) ||(x >= ILI9341WIDTH) || (y < 0) || (y >= ILI9341HEIGHT)) return;

   setAddrWindow(x,y,x+1,y+1);
   digitalWrite(TFT_DC, HIGH);
   digitalWrite(TFT_CS, LOW);

   SPI.transfer(color >> 8);
   SPI.transfer(color);
   digitalWrite(TFT_CS, HIGH);

}

/**************************************************
* DRAW FAST V LINE
**************************************************/
void ILI9341::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{

  // Rudimentary clipping
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;

  if((y+h-1) >= ILI9341HEIGHT)
    h = ILI9341HEIGHT-y;

  setAddrWindow(x, y, x, y+h-1);

  uint8_t hi = color >> 8, lo = color;

  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_CS, LOW);

  while (h--)
  {
    SPI.transfer(hi);
    SPI.transfer(lo);
  }
  digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* DRAW FAST H LINE
**************************************************/
void ILI9341::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{

  // Rudimentary clipping
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;
  if((x+w-1) >= ILI9341WIDTH)  w = ILI9341WIDTH-x;
  setAddrWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;
  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_CS, LOW);
  while (w--)
  {
    SPI.transfer(hi);
    SPI.transfer(lo);
  }
  digitalWrite(TFT_CS, HIGH);
}

void ILI9341::fillScreen(uint16_t color)
{
   fillRect(0, 0,  ILI9341WIDTH, ILI9341HEIGHT, color);
}

/**************************************************
* FILL RECTANGLE
**************************************************/
void ILI9341::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;
  if((x + w - 1) >= ILI9341WIDTH)  w = ILI9341WIDTH  - x;
  if((y + h - 1) >= ILI9341HEIGHT) h = ILI9341HEIGHT - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  uint8_t hi = color >> 8, lo = color;

  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_CS, LOW);

  for(y=h; y>0; y--)
  {
    for(x=w; x>0; x--)
    {
      SPI.transfer(hi);
      SPI.transfer(lo);
    }
  }
  digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* DISPLAY PIXEL ARRAY REVERSE
* DESCRIPTION: Prints a 2D array of pixel to the LCD
**************************************************/
void ILI9341::display_image(int image[], int x, int y, int width, int height, int orientation, uint8_t clear)
{
  char hi;
  char lo;
  int i;
  int j;
  uint16_t currentColor = COLOR_WHITE;
  if (orientation == 0 || orientation == 1)
  {
	  int temp = width;
	  width = height;
	  height = temp;
  }

  // Set start write position
  setAddrWindow(x, y, x+width-1, y+height-1);

  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_CS, LOW);
  int position_index = 0;
  
  // Paint the object in the left or right orientation
  if (orientation < 3 || clear)
  {
	 if (orientation == 1)
	 {
		 position_index = (width * height) - 1;
	 }
     for (i = 0; i < height; i++)
     {
		if (orientation == 2)
	    {
		    position_index = i;
	    }
        for (j=0; j < width; j++)
        {
           if (clear)
           {
              currentColor = bg_color;
           }
           else
           {
              currentColor = image[position_index];
			  if (orientation == 0)
			  {
			     position_index++;
			  }
			  else if (orientation == 1)
			  {
				  position_index--;
			  }
			  else if (orientation == 2)
			  {
				  position_index += height;
			  }
           }
		   if (currentColor == COLOR_WHITE)
		   {
			   currentColor = bg_color;
		   }
           hi = currentColor >> 8;
           lo = currentColor;
           SPI.transfer(hi);
           SPI.transfer(lo);
        }
     }
  }
  else if (orientation == 3)
  {
     //Pixel paint the object
     for (i = height-1; i >= 0; i--)
     {
		position_index = i;
        for (j=0; j < width; j++)
        {
           currentColor = image[position_index];
		   position_index += height;
		   if (currentColor == COLOR_WHITE)
		   {
			   currentColor = bg_color;
		   }
           hi = currentColor >> 8;
           lo = currentColor;
           SPI.transfer(hi);
           SPI.transfer(lo);
        }
     }
  }
  digitalWrite(TFT_CS, HIGH);
}


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

/**************************************************
* SET ROTATION
* DESCRIPTION: Set the rotation of the LCD
**************************************************/
void ILI9341::setRotation(uint8_t m)
{
  writecommand(ILI9341_MADCTL);
  uint8_t rotation = m % 4; // can't be higher than 3
  switch (rotation) {
   case 0:
     writedata(MADCTL_MX | MADCTL_BGR);
     break;
   case 1:
     writedata(MADCTL_MV | MADCTL_BGR);
     break;
  case 2:
    writedata(MADCTL_MY | MADCTL_BGR);
    break;
   case 3:
     writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
     break;
  }
}

/**************************************************
* INVERT DISPLAY
* DESCRIPTION: Invert the colors on the LCD
**************************************************/
void ILI9341::invertDisplay(char i)
{
  writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
}


////////// stuff not actively being used, but kept for posterity

/**************************************************
* SPI READ
* DESCRIPTION: Read spi data from the LCD
**************************************************/
uint8_t ILI9341::spiread(void)
{
   return SPI.transfer(0);
}

/**************************************************
* READ DATA
* DESCRIPTION: Read a single byte from the LCD.
**************************************************/
uint8_t ILI9341::readdata(void)
{
   //SET_DC;
   //CLEAR_CS;
   //uint8_t r = spiread();
   //SET_CS;
   return 0;
}

/**************************************************
* READ COMMAND
* DESCRIPTION: Read one of the LCD registers.
**************************************************/
uint8_t ILI9341::readcommand8(uint8_t c, uint8_t index)
{
   digitalWrite(TFT_DC, LOW);
   digitalWrite(TFT_CS, LOW);
   SPI.transfer(0xD9);  // woo sekret command?
   digitalWrite(TFT_DC, HIGH);
   SPI.transfer(0x10 + index);
   digitalWrite(TFT_CS, HIGH);

   digitalWrite(TFT_DC, LOW);
   digitalWrite(TFT_CS, LOW);
   SPI.transfer(c);

   digitalWrite(TFT_DC, HIGH);
   uint8_t r = spiread();
   digitalWrite(TFT_CS, HIGH);

   return r;
}

/**************************************************
* READ COMMAND 16
* DESCRIPTION: Reads 16 bits from the LCD
**************************************************/
uint16_t ILI9341::readcommand16(uint8_t c) 
{
   digitalWrite(TFT_DC, LOW);
   digitalWrite(TFT_CS, LOW);

   SPI.transfer(c);
   uint16_t r = spiread();
   r <<= 8;
   r |= spiread();
   digitalWrite(TFT_CS, HIGH);
   
   return r;
}

 /**************************************************
* READ COMMAND 32
* DESCRIPTION: Reads 32 bits from the LCD
**************************************************/
uint32_t ILI9341::readcommand32(uint8_t c) 
{
   digitalWrite(TFT_DC, LOW);
   digitalWrite(TFT_CS, LOW);
   SPI.transfer(c);

   //dummyclock();
   //dummyclock();

   uint32_t r = spiread();
   r <<= 8;
   r |= spiread();
   r <<= 8;
   r |= spiread();
   r <<= 8;
   r |= spiread();
   digitalWrite(TFT_CS, HIGH);

   return r;
 }
