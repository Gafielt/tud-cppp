#ifndef RGB_LED_H
#define RGB_LED_H

/*
 *  RGB_LED offers functions to control the RGB LED of the cppp board
 *
 */

/*
 * This function should be called before anything is done, to initialize the pins of the RGB LED
 */
void cppp_initLEDs();

/*
 * Turn RED LED on
 */
void cppp_redLEDOn();

/*
 * Turn RED LED off
 */
void cppp_redLEDOff();

/*
 * Turn GREEN LED on
 */
void cppp_greenLEDOn();

/*
 * Turn GREEN LED off
 */
void cppp_greenLEDOff();

/*
 * Turn BLUE LED on
 */
void cppp_blueLEDOn();

/*
 * Turn BLUE LED off
 */
void cppp_blueLEDOff();



#endif