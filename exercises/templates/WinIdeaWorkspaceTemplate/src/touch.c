#include "touch.h"

#include <stdint.h>
#include "gfx.h"
#include "lcd.h"
#include "display.h"
#include "analog.h"

#define BOXSIZE 40
#define PENRADIUS 3

static uint16_t oldcolor, currentcolor; 

void debugTouch(){
  // Get analog values
  
  // Set cursor to (480,320)
  
  // Write headline on the display with 1 linebreak before and 4 afterwards
  
  // Get analog values of the touchscreen by using the readTouch methods
  
  // Write x,y, and z-values on the screen
   
}

void paintTouch(){
  // Your code here ...
  
  while(1){
    // Your code here ...
  }
}

/** 
 * Initializes the paint studio.
 */
static void initPaintTouch(){
  cppp_fillScreen(BLACK);
  cppp_fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  cppp_fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  cppp_fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  cppp_fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  cppp_fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
  cppp_fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
  
  cppp_drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  
  setCursor(260, 25);
  setTextSize(2);
  char text[] = "BILD ERNEUERN";
  writeText(text);
}

/**
 * Loop of paintTouch.
 */
static void loopPaintTouch(){
  // Save the actual touchpoint in the struct touchpoint
  
  // Correct touchpoint
  if (touchPoint.z > TOUCHZMIN && touchPoint.z < TOUCHZMAX) {
    // Erase
   
    // Change color
    
    // Draw a point on the screen
  
  }
}
