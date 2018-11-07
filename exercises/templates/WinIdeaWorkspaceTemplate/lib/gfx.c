#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gfx.h"
#include "lcd.h"
#include "src/display.h"
#include "glcdfont.h"
#include "pins.h"

static const char *WHITESPACE = " ";

// Fix for the missing declaration of itoa in stdlib.h.
char* itoa(int, char* , int);

void cppp_fillScreen(int16_t color){
    cppp_setAddrWindow(0, 0, 480 - 1, 320 - 1);
    cppp_floodLCD(color, 480 * 320);
}

void cppp_drawFastHLine(int x, int y, int length, int16_t color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int x2;
    
    // Initial off-screen clipping
    if((length <= 0     ) ||
       (y      <  0     ) || ( y                  >= _height) ||
       (x      >= _width) || ((x2 = (x+length-1)) <  0      )) return;
    
    if(x < 0) {        // Clip left
        length += x;
        x       = 0;
    }
    if(x2 >= _width) { // Clip right
        x2      = _width - 1;
        length  = x2 - x + 1;
    }
    
    cppp_setAddrWindow(x, y, x2, y);
    cppp_floodLCD(color, length);
    cppp_setLR();
}

void cppp_drawFastVLine(int x, int y, int length, int16_t color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int y2;
    
    // Initial off-screen clipping
    if((length <= 0      ) ||
       (x      <  0      ) || ( x                  >= _width) ||
       (y      >= _height) || ((y2 = (y+length-1)) <  0     )) return;
    if(y < 0) {         // Clip top
        length += y;
        y       = 0;
    }
    if(y2 >= _height) { // Clip bottom
        y2      = _height - 1;
        length  = y2 - y + 1;
    }
    
    cppp_setAddrWindow(x, y, x, y2);
    cppp_floodLCD(color, length);
    cppp_setLR();
}

void cppp_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    cppp_drawFastHLine(x, y, w, color);
    cppp_drawFastHLine(x, y+h-1, w, color);
    cppp_drawFastVLine(x, y, h, color);
    cppp_drawFastVLine(x+w-1, y, h, color);
}

void cppp_fillRect(int x1, int y1, int w, int h, int16_t fillcolor) {
    int _width = WIDTH;
    int _height = HEIGHT;
    int  x2, y2;
    
    // Initial off-screen clipping
    if( (w            <= 0     ) ||  (h             <= 0      ) ||
       (x1           >= _width) ||  (y1            >= _height) ||
       ((x2 = x1+w-1) <  0     ) || ((y2  = y1+h-1) <  0      )) return;
    if(x1 < 0) { // Clip left
        w += x1;
        x1 = 0;
    }
    if(y1 < 0) { // Clip top
        h += y1;
        y1 = 0;
    }
    if(x2 >= _width) { // Clip right
        x2 = _width - 1;
        w  = x2 - x1 + 1;
    }
    if(y2 >= _height) { // Clip bottom
        y2 = _height - 1;
        h  = y2 - y1 + 1;
    }
    
    cppp_setAddrWindow(x1, y1, x2, y2);
    cppp_floodLCD(fillcolor, (long)w * (long)h);
    cppp_setLR();
}

void cppp_drawPixel(int16_t x, int16_t y, uint16_t color) {
    int _width = WIDTH;
    int _height = HEIGHT;
    // Clip
    if((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) return;
    
    LCD_CS = 0u;
 
    cppp_setAddrWindow(x, y, _width-1, _height-1);
    LCD_CS = 0u;
    LCD_CD = 0u;
    cppp_write8(0x2C);
    LCD_CD = 1u;
    cppp_write8(color >> 8); cppp_write8(color);
    
    LCD_CS = 1u;
}

void cppp_drawCircle(int x0, int y0, int r, unsigned int color) {
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;
    
    cppp_drawPixel(x0  , y0+r, color);
    cppp_drawPixel(x0  , y0-r, color);
    cppp_drawPixel(x0+r, y0  , color);
    cppp_drawPixel(x0-r, y0  , color);
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        cppp_drawPixel(x0 + x, y0 + y, color);
        cppp_drawPixel(x0 - x, y0 + y, color);
        cppp_drawPixel(x0 + x, y0 - y, color);
        cppp_drawPixel(x0 - x, y0 - y, color);
        cppp_drawPixel(x0 + y, y0 + x, color);
        cppp_drawPixel(x0 - y, y0 + x, color);
        cppp_drawPixel(x0 + y, y0 - x, color);
        cppp_drawPixel(x0 - y, y0 - x, color);
    }
}

void cppp_drawCircleHelper( int x0, int y0, int r, char cornername, unsigned int color) {
    int f     = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x     = 0;
    int y     = r;
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            cppp_drawPixel(x0 + x, y0 + y, color);
            cppp_drawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            cppp_drawPixel(x0 + x, y0 - y, color);
            cppp_drawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            cppp_drawPixel(x0 - y, y0 + x, color);
            cppp_drawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            cppp_drawPixel(x0 - y, y0 - x, color);
            cppp_drawPixel(x0 - x, y0 - y, color);
        }
    }
}


void cppp_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    
    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        
        if (cornername & 0x1) {
            cppp_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
            cppp_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
            cppp_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
            cppp_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

void cppp_fillCircle(int x0, int y0, int r, unsigned int color) {
    cppp_drawFastVLine(x0, y0-r, 2*r+1, color);
    cppp_fillCircleHelper(x0, y0, r, 3, 0, color);
}

void cppp_drawRoundRect(int x, int y, int w, int h, int r, unsigned int color) {
    cppp_drawFastHLine(x+r  , y    , w-2*r, color); // top line
    cppp_drawFastHLine(x+r  , y+h-1, w-2*r, color); // bottom line
    cppp_drawFastVLine(x    , y+r  , h-2*r, color); // left line
    cppp_drawFastVLine(x+w-1, y+r  , h-2*r, color); // right line
    
    // draw four corners
    cppp_drawCircleHelper(x+r    , y+r    , r, 1, color);
    cppp_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    cppp_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    cppp_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

void cppp_fillRoundRect(int x, int y, int w, int h, int r, unsigned color) {
    cppp_fillRect(x+r, y, w-2*r, h, color);
    
    // draw four corners
    cppp_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    cppp_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

void cppp_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int16_t temp = x0;
        x0 = y0;
        y0 = temp;
        //_swap_int16_t(x0, y0);
        temp = x1;
        x1 = y1;
        y1 = temp;
        //_swap_int16_t(x1, y1);
    }
    
    if (x0 > x1) {
        int16_t temp = x0;
        x0 = x1;
        x1 = temp;
        //_swap_int16_t(x0, x1);
        temp = y0;
        y0 = y1;
        y1 = temp;
        //_swap_int16_t(y0, y1);
    }
    
    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);
    
    int16_t err = dx / 2;
    int16_t ystep;
    
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }
    
    for (; x0<=x1; x0++) {
        if (steep) {
            cppp_drawPixel(y0, x0, color);
        } else {
            cppp_drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}


void cppp_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    cppp_drawLine(x0, y0, x1, y1, color);
    cppp_drawLine(x1, y1, x2, y2, color);
    cppp_drawLine(x2, y2, x0, y0, color);
}


void cppp_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  
  int16_t a, b, y, last;
  
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    int16_t temp = y0;
    y0 = y1;
    y1 = temp;
    temp = x0;
    x0 = x1;
    x1 = temp;
  }
  if (y1 > y2) {
    int16_t temp = y1;
    y1 = y2;
    y2 = temp;
    temp = x1;
    x1 = x2;
    x2 = temp;
  }
  if (y0 > y1) {
    int16_t temp = y0;
    y0 = y1;
    y1 = y0;
    temp = x0;
    x0 = x1;
    x1 = temp;
  }
  
  if(y0 == y2) { 
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    cppp_drawFastHLine(a, y0, b-a+1, color);
    return;
  }
  
  int16_t
  dx01 = x1 - x0,
  dy01 = y1 - y0,
  dx02 = x2 - x0,
  dy02 = y2 - y0,
  dx12 = x2 - x1,
  dy12 = y2 - y1;
  int32_t
  sa   = 0,
  sb   = 0;
  
  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it
  
  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
     a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
     b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
     */
    if(a > b) {
      int16_t temp = a;
      a = b;
      b = temp;                   
    }
    cppp_drawFastHLine(a, y, b-a+1, color);
  }
  
  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
     a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
     b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
     */
    if(a > b) {
      int16_t temp = a;
      a = b;
      b = temp;
    }
    cppp_drawFastHLine(a, y, b-a+1, color);
  }
}



/**
 * Write a 8 bit variable on the display
 */
void write8BitValueOnLCD(const uint8_t *value){
  char buffer[20];
  itoa(*value, buffer, 10);
  writeText_s(buffer);
}

/**
 * Write a 16 bit variable on the display
 */
void write16BitValueOnLCD(const uint16_t *value){
  char buffer[20];
  itoa(*value, buffer, 10);
  writeText_s(buffer);
}

/**
 * Write a 32 bit variable on the display
 */
void write32BitValueOnLCD(const uint32_t *value){
  char buffer[20];
  itoa(*value, buffer, 10);
  writeText_s(buffer);
}

/**
 * Write 3 digits long 8 bit variable on the screen with automatic freespace if number is smaller than 3 digits
 */
void write3Digits8Bit(const uint8_t *value){
  if(*value < 10){
    writeText_s(WHITESPACE);
  }
  if(*value < 100){
    writeText_s(WHITESPACE);
  }
  write8BitValueOnLCD(value);
}

/**
 * Write 3 digits long 16 bit variable on the screen with automatic freespace if number is smaller than 3 digits
 */
void write3Digits16Bit(const uint16_t *value){
  if(*value < 10){
    writeText_s(WHITESPACE);
  }
  if(*value < 100){
    writeText_s(WHITESPACE);
  }
  write16BitValueOnLCD(value);
}


void write16BitDigit(const uint16_t *value, uint8_t mode){
  if(mode == 1){
    const uint8_t base = 10;
    char buffer[6];
    char *bufferStart = buffer;
    if(*value < 100000){
      *bufferStart = ' ';
      bufferStart++;
      if (*value < 10000) {
        *bufferStart = ' ';
        bufferStart++;
        if (*value < 1000) {
          *bufferStart = ' ';
          bufferStart++;
          if (*value < 100) {
            *bufferStart = ' ';
            bufferStart++;
            if (*value < 10) {
              *bufferStart = ' ';
              bufferStart++;
            }
          }
        }
      }
    }
    itoa(*value, bufferStart, base);
    writeText_s(buffer);
  }
  else if(mode == 2){
  const uint8_t base = 10;
    uint8_t numberOfDigits = 0;
    if(*value < 100000){
      numberOfDigits = 5;
      if (*value < 10000) {
       numberOfDigits = 4;
        if (*value < 1000) {
          numberOfDigits = 3;
          if (*value < 100) {
            numberOfDigits = 2;
            if (*value < 10) {
             numberOfDigits = 1;
            }
          }
        }
      }
    }
    char buffer[numberOfDigits];
    itoa(*value, buffer, base);
    writeText_s(buffer);
  }
}

void write8BitDigit(const uint8_t *value){
  const uint8_t base = 10;
    uint8_t numberOfDigits = 0;
    if (*value < 1000) {
      numberOfDigits = 3;
      if (*value < 100) {
        numberOfDigits = 2;
        if (*value < 10) {
         numberOfDigits = 1;
        }
      }
    }
    char buffer[numberOfDigits];
    itoa(*value, buffer, base);
    writeText_s(buffer);  
}

void writeFloat(float number, uint8_t precision, uint8_t width){
  char buffer[width];
  
  char settings[4];
  strcpy(settings, "%.");
  char widthBuffer[1];
  itoa(precision, widthBuffer, 10);
  strcat(settings, widthBuffer);
  strcat(settings, "f");

  int test = sprintf(buffer, settings, number);
  writeText_s(buffer);
}

char cppp_565to8BitColor(int color){
  uint8_t red   = (color&0xE000)>>8;
  uint8_t green = (color&0x0700)>>6;               
  uint8_t blue  = (color&0x0018)>>3;  
  return (red | green | blue); 
}

int cppp_8BitColorTo565(char color){
  uint16_t red    = (color&0xE0)<<8; 
  uint16_t green  = (color&0x1C)<<6;
  uint16_t blue   = (color&0x03)<<3;
  return (red|green|blue);
}