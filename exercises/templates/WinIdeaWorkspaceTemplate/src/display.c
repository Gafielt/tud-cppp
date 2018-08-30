#include "display.h"

#include "gfx.h"
#include "glcdfont.h"

static int16_t cursorX, cursorY;
static uint16_t textColor;
static uint8_t textSize;
static int textBackground;

uint16_t color565(const uint8_t r, const uint8_t g, const uint8_t b){
  // your code here...
  return 65535;
}

void printPattern(const uint16_t backgroundColor, const uint16_t foregroundColor) {
  // your code here...
}

void initCursor(){
  // your code here...

}

void setCursor(const int16_t x, int16_t y) {
  // your code here...
}

void setTextColor(const uint16_t c) {
  // For 'transparent' background, we'll set the bg to the same as the rest of the display
  // your code here...
}

void setTextSize(const uint8_t s) {
  // your code here...
}

void setBackgroundColor(const int bg){
  // your code here...
}

void drawChar(const int x, const int y, const char c, const int color, const int bg, const char size) {
  // If (x,y) is not inside the display return

  char i, j;
  for(i=0; i<6; i++ ) { // Draw in x-direction
    char line; // Line (i,j) ... (i,j+7)
    // save the i.x-line from (i,j) to (i,j+7) in the char line

    for(j=0; j<8; j++, line >>= 1) {  // draw in y-direction
      // Check whether the j'th bit in line is set

    }
  }
}

void writeAuto(const char c) {
  // if char c == '\n' then jump cursor to next line

  // else
  // check for end of line and reset cursor. in the case of end of the display set cursorY to the starting point.
  // draw the char
  // move cursorX
}

void writeText(const char *text){
    // your code here ...
}

void writeTextln(const char *text){
    // your code here ...
}

void writeNumberOnDisplay(const uint8_t *value){
    // your code here...
}

void writeNumberOnDisplayRight(const uint8_t *value){
    // your code here...
}
