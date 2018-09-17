#ifndef GFX_H
#define GFX_H
/**
* @brief This code is based on:  https://github.com/adafruit/Adafruit-GFX-Library &  
* https://github.com/adafruit/TFTLCD-Library
* The code is converted by the cppp team for the Cypress FM4  microcontroller. In the comments of every function there are code examples. 
*/
#include "mcu.h"


/*
 * @brief X dimension of the lc display: 480 pixels.
 */
#define WIDTH   480 // pixel
/*
 * @brief Y dimension of the lc display: 320 pixels.
 */
#define HEIGHT  320 // pixel

/**
 * @brief Fills the screen with a given color.
  * Minimal example
<pre>
#include "init.h"
#include "gfx.h"

int main(){
  initBoard();
  fillScreen(RED);
  return 0;
}
<pre>
 * @param color the new background color of the screen
 * @return void
 */
void cppp_fillScreen(int16_t color);

void drawFastHLine(int x, int y, int length, int16_t color);
void drawFastVLine(int x, int y, int length, int16_t color);
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fillRect(int x1, int y1, int w, int h, int16_t fillcolor);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void drawCircle(int x0, int y0, int r, unsigned int color);
void drawCircleHelper( int x0, int y0, int r, char cornername, unsigned int color);
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void fillCircle(int x0, int y0, int r, unsigned int color);
void drawRoundRect(int x, int y, int w, int h, int r, unsigned int color);
void fillRoundRect(int x, int y, int w, int h, int r, unsigned color);
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
char cppp_565to8BitColor(int color);
int cppp_8BitColorTo565(char color);

void write8BitValueOnLCD(const uint8_t *value);
void write16BitValueOnLCD(const uint16_t *value);
void write32BitValueOnLCD(const uint32_t *value);
void write3Digits8Bit(const uint8_t *value);
void write3Digits16Bit(const uint16_t *value);
void write16BitDigit(const uint16_t *value, uint8_t mode);
void write8BitDigit(const uint8_t *value);
void writeFloat(float number, uint8_t precision, uint8_t width);
#endif
