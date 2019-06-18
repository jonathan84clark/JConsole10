/***************************************************
  This is our library for the Adafruit  ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _ADAFRUIT_ILI9341H_
#define _ADAFRUIT_ILI9341H_

#include <stdint.h>

#define ILI9341WIDTH  240
#define ILI9341HEIGHT 320

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0D
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_MADCTL  0x36
#define ILI9341_PIXFMT  0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1
/*
#define ILI9341_PWCTR6  0xFC

*/


uint16_t GetBgColor(void);

void ILI9341_begin(void);
void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void ILI9341_pushColor(uint16_t color);
void ILI9341_fillScreen(uint16_t color);
void ILI9341_drawPixel(int16_t x, int16_t y, uint16_t color);
void ILI9341_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void ILI9341_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void ILI9341_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void ILI9341_setRotation(uint8_t r);
void ILI9341_invertDisplay(char i);
void ILI9341_displaySprite(struct Sprite* sprite, uint8_t clear);
uint16_t ILI9341_color565(uint8_t r, uint8_t g, uint8_t b);

  /* These are not for current use, 8-bit protocol only! */
uint8_t ILI9341_readdata(void);
uint8_t  ILI9341_readcommand8(uint8_t reg, uint8_t index);
uint16_t readcommand16(uint8_t);
uint32_t readcommand32(uint8_t);
//void     dummyclock(void);

uint8_t spiwrite(uint8_t data);
void writecommand(uint8_t c);
void writedata(uint8_t d);
uint8_t spiread(void);
uint16_t GetPaletteColor(char index);
void setBgColor(uint16_t inColor);


#define TFT_CLK 27
#define TFT_MISO 25
#define TFT_MOSI 26
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

#define NUM_COLORS 18
#define COLOR_NAVY        0x000F      /*   0,   0, 128 */
#define COLOR_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define COLOR_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define COLOR_MAROON      0x7800      /* 128,   0,   0 */
#define COLOR_PURPLE      0x780F      /* 128,   0, 128 */
#define COLOR_OLIVE       0x7BE0      /* 128, 128,   0 */
#define COLOR_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define COLOR_ORANGE      0xFD20      /* 255, 165,   0 */
#define COLOR_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define COLOR_PINK        0xF81F
#define	COLOR_BLACK   0x0000
#define	COLOR_BLUE    0x001F
#define	COLOR_RED     0xF800
#define	COLOR_GREEN   0x07E0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_YELLOW  0xFFE0
#define COLOR_WHITE   0xFFFF
#define COLOR_LTGREY  0xC618
#define COLOR_DRKGREY 0x630C
#define COLOR_LTGREEN 0x04C0
#define COLOR_LIMEGREEN 0x87E0
#define COLOR_FORESTGREEN 0x2444
#define COLOR_GOLDENROD 0xDD24
#define COLOR_GREEN2 0x0400
#define COLOR_LIGHTSEAGREEN 0x2595
#define COLOR_MLRYGREEN 0x4A84
#define COLOR_SKYBLUE 0x867F


#endif
