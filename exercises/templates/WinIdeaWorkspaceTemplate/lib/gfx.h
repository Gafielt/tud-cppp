#ifndef GFX_H
#define GFX_H
/**
 * @file gfx.h
 * @brief <strong> This code is based on:  https://github.com/adafruit/Adafruit-GFX-Library &  
 * https://github.com/adafruit/TFTLCD-Library
 * The code is converted by the cppp team for the Cypress FM4  microcontroller. 
 * In the comments of every function there are code examples. </strong> 
 */
#include "mcu.h"


/**
 * @brief X dimension of the lc display: 480 pixels.
 */
#define WIDTH   480 // pixel

/**
 * @brief Y dimension of the lc display: 320 pixels.
 */
#define HEIGHT  320 // pixel

/**
 * @brief Black 565 color.
 */
#define	BLACK   0x0000

/**
 * @brief Blue 565 color.
 */
#define	BLUE    0x001F

/**
 * @brief Red 565 color.
 */
#define	RED     0xF800

/**
 * @brief Green 565 color.
 */
#define	GREEN   0x07E0

/**
 * @brief Cyan 565 color.
 */
#define CYAN    0x07FF

/**
 * @brief Magenta 565 color.
 */
#define MAGENTA 0xF81F

/**
 * @brief Yellow 565 color.
 */
#define YELLOW  0xFFE0

/**
 * @brief White 565 color.
 */
#define WHITE   0xFFFF

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
</pre>
 * @param color the new background color of the screen
 * @return void
 */
void cppp_fillScreen(int16_t color);

/**
 * @brief Draws a horizontal line from (x,y) to (x+length,y) in the choosen 565 rgb color.
 * @param x start point
 * @param y start point
 * @param length of the horizontal line
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawFastHLine(int x, int y, int length, int16_t color);

/**
 * @brief Draws a vertical line starting at (x,y) and ending at (x,y+length).
 * @param x start point
 * @param y start point
 * @param length of the vertical line
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawFastVLine(int x, int y, int length, int16_t color);

/**
 * @brief Draw the borders of a rectangle. So the rectangle is not filled. 
 * @param x start point in the left down corner
 * @param y start point in the left down corner
 * @param w width 
 * @param h height
 * @param color 565 color
 * @return void
 */
void cppp_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

/**
 * @brief Draw a filled rectangle at (x,y) to (x+w,y+h).
 * @param x1 start point in the left down corner
 * @param y1 start point in the left down corner
 * @param w width 
 * @param h height
 * @param fillcolor 565 rgb fill color
 * @return void
 */
void cppp_fillRect(int x1, int y1, int w, int h, int16_t fillcolor);

/**
 * @brief Draw a pixel at (x,y) with the wished color.
 * @param x coordinate
 * @param y coordinate
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawPixel(int16_t x, int16_t y, uint16_t color);

/**
 * @brief Draw a circle outline.
 * @param x0 center point
 * @param y0 center point
 * @param r radius
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawCircle(int x0, int y0, int r, unsigned int color);

/**
 * @brief Used by round rectangles to draw round corners.
 * @param x0 center point
 * @param y0 center point
 * @param r radius
 * @param cornername corner of the round rectangle
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawCircleHelper( int x0, int y0, int r, char cornername, unsigned int color);

/**
 * @brief Used by filled round rectangles to draw round corners.
 * @param x0 center point
 * @param y0 center point
 * @param r radius
 * @param cornername corner of the round rectangle
 * @param color 565 rgb color
 * @return void
 */
void cppp_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

/**
 * @brief Draw a filled circle.
 * @param x0 center point
 * @param y0 center point
 * @param r radius
 * @param color 565 rgb color
 * @return void
 */
void cppp_fillCircle(int x0, int y0, int r, unsigned int color);

/**
 * @brief Draw outline of a round rectangle.
 * @param x center point
 * @param y center point
 * @param w width
 * @param h height
 * @param r corner radius
 * @param color 565 rgb color
 * @return void
 */
void cppp_drawRoundRect(int x, int y, int w, int h, int r, unsigned int color);

/**
 * @brief Draw a filled round rectangle.
 * @param x center point
 * @param y center point
 * @param w width
 * @param h height
 * @param r corner radius
 * @param color 565 rgb color
 * @return void
 */
void cppp_fillRoundRect(int x, int y, int w, int h, int r, unsigned color);

/**
 * @brief Draw a line with bresenham algorithm.
 * @param x0 start point
 * @param y0 start point
 * @param x1 end point
 * @param y1 end point
 * @param color 565 rgb color
 * @return void
 */  
void cppp_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

/**
 * @brief Draw an outline of a triangle.
 * @param x0 point 0
 * @param y0 point 0
 * @param x1 point 1
 * @param y1 point 1
 * @param x2 point 2
 * @param y2 point 2
 * @param color 565 rgb color
 * @return void
 */ 
void cppp_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

/**
 * @brief Draw a filled triangle.
 * @param x0 point 0
 * @param y0 point 0
 * @param x1 point 1
 * @param y1 point 1
 * @param x2 point 2
 * @param y2 point 2
 * @param color 565 rgb color
 * @return void
 */
void cppp_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);


/**
 * @brief Write a 8 bit variable on the display aligned to the left.
 * @param value 8 bit number
 * @return void
 */
void cppp_write8BitValueOnLCD(const uint8_t *value);

/**
 * @brief Write a 16 bit variable on the display aligned to the left.
 * @param value 16 bit number
 * @return void
 */
void cppp_write16BitValueOnLCD(const uint16_t *value);

/**
 * @brief Write a 32 bit variable on the display aligned to the left.
 * @param value 32 bit number
 * @return void
 */
void cppp_write32BitValueOnLCD(const uint32_t *value);

/**
 * @brief Write 3 digits long 8 bit variable on the screen left aligned with automatic freespace if number is smaller than 3 digits.
 * @param value 8 bit number
 * @return void
 */
void cppp_write3Digits8Bit(const uint8_t *value);

/**
 * @brief Write 3 digits long 16 bit variable on the screen left aligned with automatic freespace if number is smaller than 3 digits.
 * @param value 16 bit number
 * @return void
 */
void cppp_write3Digits16Bit(const uint16_t *value);

/**
 * @brief Write 16 bit variable on the screen left or right aligned with automatic freespace if number is smaller than 3 digits.
 * @param value 16 bit number
 * @param mode if 1 right aligned else if 2 left aligned
 * @return void
 */
void cppp_write16BitDigit(const uint16_t *value, uint8_t mode);

/**
 * @brief Write 8 bit digit on the screen with the minimum length of the char array.
 
 * @param value 8 bit number
 */
void cppp_write8BitDigit(const uint8_t *value);

/**
 * @brief Write a float number on the screen.
 * @param number float number
 * @param precision float precision
 * @param width length of char array
 */
void cppp_writeFloat(float number, uint8_t precision, uint8_t width);

/**
 * @brief Convert a 16 bit 565 rgb color to a 8 bit rgb color.
 * @param color 16 bit input color
 * @return 8 bit output color
 */
char cppp_565to8BitColor(int color);

/**
 * @brief Convert a 8 bit rgb color to a 16 bit 565 rgb color.
 * @param 8 bit input color
 * @return color 16 bit output color
 */
int cppp_8BitColorTo565(char color);

#endif
