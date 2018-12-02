#include "src/touch.h"

#include <stdint.h>
#include "analog.h"
#include "gfx.h"
#include "lcd.h"
#include "src/display.h"

#define BOXSIZE 40
#define PENRADIUS 3

static uint16_t oldcolor, currentcolor; 

/** 
 * Initializes the paint studio.
 */
static void initPaintTouch();

/**
 * Loop of paintTouch.
 */
static void loopPaintTouch();

void debugTouch_s(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  // Write headline on the display
  setCursor_s(480,320);
  char freeSpace[] = " ";
  char headlineText[] = "      DEBUG TOUCHSCREEN";
  writeTextln_s(freeSpace);
  writeTextln_s(freeSpace);
  writeTextln_s(freeSpace);
  writeTextln_s(headlineText);
  writeTextln_s(freeSpace);
  
  // Get analog values of the touchscreen
  uint16_t touchZ = cppp_readTouchZ();
  uint16_t touchX = touchZ != 0 ? cppp_readTouchX() : 0;
  uint16_t touchY = touchZ != 0 ? cppp_readTouchY() : 0;
  
  if(touchX > 480 || touchY>320){
    touchX = 0;
    touchY = 0;
    touchZ = 0;
  }
  
  // Write x,y, and z-values on the screen
  char touchXText[] = "  Touch X: ";
  char touchYText[] = "  Touch Y: ";
  char touchZText[] = "  Touch Z: ";
  writeText_s(touchXText);
  cppp_write3Digits16Bit(&touchX);
  writeTextln_s("");
  writeText_s(touchYText);
  cppp_write3Digits16Bit(&touchY);
  writeTextln_s("");
  writeText_s(touchZText);
  cppp_write3Digits16Bit(&touchZ);
  writeTextln_s("");
}

void paintTouch_s(){
  initPaintTouch();
  while(1){
    loopPaintTouch();
  }
}

static void initPaintTouch() {
  cppp_fillScreen(BLACK);
  cppp_fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  cppp_fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  cppp_fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  cppp_fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  cppp_fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
  cppp_fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  
  cppp_drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  
  setCursor_s(260, 25);
  setTextSize_s(2);
  char text[] = "BILD ERNEUERN";
  writeText_s(text);
}

static void loopPaintTouch() {
  touchPoint.x = cppp_readTouchX();
  touchPoint.y = cppp_readTouchY();
  touchPoint.z = cppp_readTouchZ();

  if (touchPoint.z > TOUCHZMIN && touchPoint.z < TOUCHZMAX) {
    // Erase
    if (touchPoint.y < BOXSIZE && touchPoint.x > BOXSIZE*7) {
      cppp_fillRect(0, BOXSIZE, 480, 320-BOXSIZE, BLACK);
    }
    
    // change color
    if (touchPoint.y < BOXSIZE) {
      oldcolor = currentcolor;
      
      if (touchPoint.x < BOXSIZE) {
        currentcolor = RED;
        cppp_drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (touchPoint.x < BOXSIZE*2) {
        currentcolor = YELLOW;
        cppp_drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (touchPoint.x < BOXSIZE*3) {
        currentcolor = GREEN;
        cppp_drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (touchPoint.x < BOXSIZE*4) {
        currentcolor = CYAN;
        cppp_drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (touchPoint.x < BOXSIZE*5) {
        currentcolor = BLUE;
        cppp_drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (touchPoint.x < BOXSIZE*6) {
        currentcolor = MAGENTA;
        cppp_drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
      }
      
      if (oldcolor != currentcolor) {
        if (oldcolor == RED) cppp_fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
        if (oldcolor == YELLOW) cppp_fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
        if (oldcolor == GREEN) cppp_fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
        if (oldcolor == CYAN) cppp_fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
        if (oldcolor == BLUE) cppp_fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
        if (oldcolor == MAGENTA) cppp_fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
      }
    }
    
    // draw a point on the screen
    if (((touchPoint.y-PENRADIUS) > BOXSIZE) && ((touchPoint.y+PENRADIUS) < 480)) {
      cppp_fillCircle(touchPoint.x, touchPoint.y, PENRADIUS, currentcolor);
    }
  }
}

