#ifndef TOUCH_H
#define TOUCH_H

/**
 * Prints the x,y and z-value of the touchscreen on the display.
 */
void debugTouch();
void debugTouch_s();

/**
 * Painting application
 */
void paintTouch();
void paintTouch_s();

/** 
 * Initializes the paint studio.
 */
static void initPaintTouch();

/**
 * Loop of paintTouch.
 */
static void loopPaintTouch();

#endif
