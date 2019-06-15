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
#include "ILI9341_SPI.h"

#define ARDUINO 1

uint16_t bg_color = COLOR_GREEN;

uint16_t palette[18] = {COLOR_BLUE, COLOR_RED, COLOR_GOLDENROD, COLOR_CYAN, COLOR_MAGENTA, COLOR_YELLOW,
		                COLOR_LTGREY, COLOR_DRKGREY, COLOR_LTGREEN, COLOR_LIMEGREEN, COLOR_PURPLE, COLOR_ORANGE,
						COLOR_NAVY, COLOR_DARKGREEN, COLOR_DARKCYAN, COLOR_OLIVE, COLOR_GREENYELLOW, COLOR_PINK};

/**************************************************
* SET BG COLOR
* DESCRIPTION: Sets the background color of the LCD and
* fills the screen.
**************************************************/
void setBgColor(uint16_t inColor)
{
   bg_color = inColor;
   ILI9341_fillScreen(bg_color);
}

/**************************************************
* GET PALETTE COLOR
* DESCRIPTION: Returns a static color from the color
* palette (for random purposes)
**************************************************/
uint16_t GetPaletteColor(unsigned char index)
{
    if (index < NUM_COLORS)
    {
        return palette[index];
    }
    return COLOR_WHITE;
}

/**************************************************
* GET BG COLOR
* DESCRIPTION: Returns the background color.
**************************************************/
uint16_t GetBgColor(void)
{
	return bg_color;
}

/**************************************************
* SPI WRITE NON BLOCKING
* DESCRIPTION: Non-blocking spi write operation
**************************************************/
void spiwrite_non_blocking(uint8_t c)
{
   SPI.transfer(c);
   //while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
   //   UCB0TXBUF = c;                     // Transmit data
}

/**************************************************
* SPI WRITE
* DESCRIPTION: Preforms a blocking SPI write operation
**************************************************/
uint8_t spiwrite(uint8_t c)
{
   SPI.transfer(c);
   //while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	 //     UCB0TXBUF = c;                     // Transmit data
   //Wait for RX to be available (tx is finished)
   //while  (!(UCB0IFG&UCRXIFG));
	      //received_ch = UCA0RXBUF;
   //return UCB0RXBUF;
   return 0;

}

/**************************************************
* WRITE COMMAND
* DESCRIPTION: Write a command to the LCD
**************************************************/
void writecommand(uint8_t c)
{
  digitalWrite(TFT_DC, LOW);
  digitalWrite(TFT_CS, LOW);
  spiwrite(c);
  digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* WRITE DATA
* DESCRIPTION: Write data to the LCD
**************************************************/
void writedata(uint8_t c)
{
   digitalWrite(TFT_DC, HIGH);
   digitalWrite(TFT_CS, LOW);
   spiwrite(c);
   digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* ILI9341 BEGIN
* DESCRIPTION: Initializes the ILI9341 LCD and interface.
**************************************************/
void ILI9341_begin(void)
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

  ILI9341_setRotation(0);

}

/**************************************************
* SET ADDR WINDOW
* DESCRIPTION: Set the address Window that will be written to
**************************************************/
void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
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
* PUSH COLOR
* DESCRIPTION: Push a color to the LCD
**************************************************/
void ILI9341_pushColor(uint16_t color)
{
  digitalWrite(TFT_DC, HIGH);
  digitalWrite(TFT_CS, LOW);
  spiwrite(color >> 8);
  spiwrite(color);
  digitalWrite(TFT_CS, HIGH);
}

/**************************************************
* DRAW PIXEL
**************************************************/
void ILI9341_drawPixel(int16_t x, int16_t y, uint16_t color)
{

  if((x < 0) ||(x >= ILI9341WIDTH) || (y < 0) || (y >= ILI9341HEIGHT)) return;

  setAddrWindow(x,y,x+1,y+1);
  SET_DC;
  CLEAR_CS;

  spiwrite(color >> 8);
  spiwrite(color);
  SET_CS;

}

/**************************************************
* DRAW FAST V LINE
**************************************************/
void ILI9341_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{

  // Rudimentary clipping
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;

  if((y+h-1) >= ILI9341HEIGHT)
    h = ILI9341HEIGHT-y;

  setAddrWindow(x, y, x, y+h-1);

  uint8_t hi = color >> 8, lo = color;

  SET_DC;
  CLEAR_CS;

  while (h--)
  {
    spiwrite(hi);
    spiwrite(lo);
  }
  SET_CS;
}

/**************************************************
* DRAW FAST H LINE
**************************************************/
void ILI9341_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{

  // Rudimentary clipping
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;
  if((x+w-1) >= ILI9341WIDTH)  w = ILI9341WIDTH-x;
  setAddrWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;
  SET_DC;
  CLEAR_CS;
  while (w--)
  {
    spiwrite(hi);
    spiwrite(lo);
  }
  SET_CS;
}

void ILI9341_fillScreen(uint16_t color)
{
   ILI9341_fillRect(0, 0,  ILI9341WIDTH, ILI9341HEIGHT, color);
}

/**************************************************
* FILL RECTANGLE
**************************************************/
void ILI9341_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= ILI9341WIDTH) || (y >= ILI9341HEIGHT)) return;
  if((x + w - 1) >= ILI9341WIDTH)  w = ILI9341WIDTH  - x;
  if((y + h - 1) >= ILI9341HEIGHT) h = ILI9341HEIGHT - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  uint8_t hi = color >> 8, lo = color;

  SET_DC;
  CLEAR_CS;

  for(y=h; y>0; y--)
  {
    for(x=w; x>0; x--)
    {
    	spiwrite_non_blocking(hi);
    	spiwrite_non_blocking(lo);
    }
  }
  SET_CS;
}

/**************************************************
* DISPLAY PIXEL ARRAY REVERSE
* DESCRIPTION: Prints a 2D array of pixel to the LCD
**************************************************/
void ILI9341_displaySprite(struct Sprite* sprite, uint8_t clear)
{
  char hi;
  char lo;
  int i;
  int j;
  uint16_t h = sprite->height;
  uint16_t w = sprite->width;
  uint16_t currentColor = COLOR_WHITE;
  if((sprite->y_pos >= ILI9341WIDTH) || (sprite->x_pos >= ILI9341HEIGHT)) return;
  if((sprite->y_pos + h - 1) >= ILI9341WIDTH)  h = ILI9341WIDTH  - sprite->y_pos;
  if((sprite->x_pos + w - 1) >= ILI9341HEIGHT)  w = ILI9341HEIGHT - sprite->x_pos;

  setAddrWindow(sprite->y_pos, sprite->x_pos, sprite->y_pos+h, sprite->x_pos+w-1);

  SET_DC;
  CLEAR_CS;

  if (sprite->direction == Right)
  {
     //Pixel paint the object
     for (i = 0; i < w; i++)
     {
        for (j=h; j >= 0; j--)
        {
           if (clear)
           {
               currentColor = bg_color;
           }
           else if (sprite->getPixelColorFunc != NULL)
           {
               currentColor = sprite->getPixelColorFunc(i, j, sprite->specialColor, sprite->animationNum);
           }
           hi = currentColor >> 8;
           lo = currentColor;
           spiwrite_non_blocking(hi);
           spiwrite_non_blocking(lo);
        }
     }
  }
  else
  {
     //Pixel paint the object
     for (i = w; i > 0; i--)
     {
        for (j=h; j >= 0; j--)
        {
           if (clear)
           {
               currentColor = bg_color;
           }
           else if (sprite->getPixelColorFunc != NULL)
           {
               currentColor = sprite->getPixelColorFunc(i, j, sprite->specialColor, sprite->animationNum);
           }
           hi = currentColor >> 8;
           lo = currentColor;
           spiwrite_non_blocking(hi);
           spiwrite_non_blocking(lo);
        }
     }
  }
  SET_CS;
}

/**************************************************
* COLOR 565
* DESCRIPTION: Convert an RGB value to a uint16_t color value
**************************************************/
uint16_t ILI9341_color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
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
void ILI9341_setRotation(uint8_t m)
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
void ILI9341_invertDisplay(unsigned char i)
{
  writecommand(i ? ILI9341_INVON : ILI9341_INVOFF);
}


////////// stuff not actively being used, but kept for posterity

/**************************************************
* SPI READ
* DESCRIPTION: Read spi data from the LCD
**************************************************/
uint8_t spiread(void)
{
   while (!(UCB0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
	        UCB0TXBUF = 0xFF;                     // Dummy write

   //May need delay here
   while  (!(UCB0IFG&UCRXIFG));

   return UCB0RXBUF;
}

/**************************************************
* READ DATA
* DESCRIPTION: Read a single byte from the LCD.
**************************************************/
uint8_t ILI9341_readdata(void)
{
   SET_DC;
   CLEAR_CS;
   uint8_t r = spiread();
   SET_CS;
   return r;
}

/**************************************************
* READ COMMAND
* DESCRIPTION: Read one of the LCD registers.
**************************************************/
uint8_t ILI9341_readcommand8(uint8_t c, uint8_t index)
{
   CLEAR_DC;
   CLEAR_CS;
   spiwrite(0xD9);  // woo sekret command?
   SET_DC;
   spiwrite(0x10 + index);
   SET_CS;

   CLEAR_DC;
   CLEAR_CS;
   spiwrite(c);

   SET_DC;
   uint8_t r = spiread();
   SET_CS;

   return r;
}

/**************************************************
* READ COMMAND 16
* DESCRIPTION: Reads 16 bits from the LCD
**************************************************/
uint16_t ILI9341_readcommand16(uint8_t c) 
{
   CLEAR_DC;
   CLEAR_CS;

   spiwrite(c);
   uint16_t r = spiread();
   r <<= 8;
   r |= spiread();
   SET_CS;
   
   return r;
}

 /**************************************************
* READ COMMAND 32
* DESCRIPTION: Reads 32 bits from the LCD
**************************************************/
uint32_t ILI9341_readcommand32(uint8_t c) 
{
   CLEAR_DC;
   CLEAR_CS;
   spiwrite(c);

   //dummyclock();
   //dummyclock();

   uint32_t r = spiread();
   r <<= 8;
   r |= spiread();
   r <<= 8;
   r |= spiread();
   r <<= 8;
   r |= spiread();
   SET_CS;

   return r;
 }
