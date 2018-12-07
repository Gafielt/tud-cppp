#ifndef RGB_LED_H
#define RGB_LED_H

/*
 * @file rgb_led.h
 * @brief <strong>RGB_LED offers functions to control the RGB LED of the cppp board.
 * You can for example activate the red LED like in this example:</strong>
 * <pre>
#include "init.h"
#include "rgb_led.h"
int main(){
 initBoard();
 cppp_initLEDs();
 cppp_redLEDOn();
 return 0;
}
 * </pre> 
 */

/*
 * @brief This function should be called before anything is done, to initialize the pins of the RGB LED
 */
void cppp_initLEDs(void);

/*
 * @brief Turn RED LED on
 * @return void
 */
void cppp_redLEDOn(void);

/*
 * @brief Turn RED LED off
 * @return void
 */
void cppp_redLEDOff(void);

/*
 * @brief Turn GREEN LED on
 * @return void
 */
void cppp_greenLEDOn(void);

/*
 * @brief Turn GREEN LED off
 * @return void
 */
void cppp_greenLEDOff(void);

/*
 * @brief Turn BLUE LED on
 * @return void
 */
void cppp_blueLEDOn(void);

/*
 * @brief Turn BLUE LED off
 * @return void
 */
void cppp_blueLEDOff(void);



#endif