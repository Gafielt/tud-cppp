#ifndef GFX_H
#define GFX_H

#include <stdlib.h>
#include <stdio.h>
#include "pins.h"
#include "pdl_header.h"
#include "glcdfont.h"

/*
 * Dimensions of the touchsreen display
 */
#define WIDTH   480 // pixel
#define HEIGHT  320 // pixel


/**
 * Fills the screen with a given color
 * @param color as defined in lcd.h
 * 
 * Minimal example

#include "init.h"
#include "gfx.h"


int main(){
  initBoard();
  fillScreen(RED);
  return 0;
}
 */ 
void fillScreen(int16_t color);

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


void write8BitValueOnLCD(const uint8_t *value);
void write16BitValueOnLCD(const uint16_t *value);
void write32BitValueOnLCD(const uint32_t *value);
void write3Digits8Bit(const uint8_t *value);
void write3Digits16Bit(const uint16_t *value);
void write16BitDigit(const uint16_t *value, uint8_t mode);
void writeFloat(float number, uint8_t precision, uint8_t width);
#endif
