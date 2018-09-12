#ifndef ANALOG_H
#define ANALOG_H
/**
* @file analog.h
* @brief This header file initializes the analog digtal changer (ADC) of the fm4 chip 
  and reads out the analog values of the light sensor, the analog joysticks and the touch surface of the lcd.
*/
#include "mcu.h"


#define TOUCHXMIN   22 
#define TOUCHXMAX   220
#define TOUCHYMIN   50
#define TOUCHYMAX   192
#define TOUCHZMIN   5
#define TOUCHZMAX   185


/**
* @brief Initializes and starts A/D conversion for all relevant channels.
* @param void
* @return void
*/
void cppp_initAdc(void);

/**
* @brief Initializes and starts A/D conversion for all relevant channels.
* @param u32Data array where the data should be saved
* @return void
*/
void cppp_adcPollData(uint32_t *u32Data);

/**
* @brief Reads in all relevant analog channels (8 bit precision) and stores the results in the given output parameters.
* The parameter names refer to the analog channel numbers.
* For example, analog11 refers to channel AN11.
* @param analog11 LCD_TOUCH_X_MINUS analog port
* @param analog12 LCD_TOUCH_Y_PLUS analog port
* @param analog13 JOYSTICK_2_X analog port
* @param analog16 JOYSTICK_1_X analog port
* @param analog17 LIGHT_SENSOR
* @param analog19 JOYSTICK_1_Y analog port
* @param analog23 JOYSTICK_2_Y analog port
* @return void
*/
void cppp_getAnalogValues(uint8_t *analog11, uint8_t *analog12, uint8_t *analog13, uint8_t *analog16, uint8_t *analog17,  uint8_t *analog19, uint8_t *analog23);

/**
* @brief Maps the given value 'x' (with min./max. possible values in_min/in_max) to the given output value range (out_min/out_max)
* @param x value that should be mapped into a new value range
* @param in_min minimal input value of x value range for example 0 for (0 .. 100)
* @param in_max maximal input value of x value range for example 100 for (0 .. 100)
* @param out_min minimal output value of x value range for example 0 for (0 .. 255)
* @param out_max maximal output value of x value range for example 255 for (0 .. 255)
* @return x mapped to the new value range (out_min, out_max)
*/
uint16_t cppp_mapValueRange(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

/**
* @brief Reads the X-position of the currently detected touch point.
* The return value is in the range of 0 to 480
* @param void
* @return x value of the (x,y,z) touchpoint
*/
uint16_t cppp_readTouchX(void);

/**
* @brief Reads the Y-position of the currently detected touch point.
* The return value is in the range of 0 to 320.
* @param void
* @return y value of the (x,y,z) touchpoint
*/
uint16_t cppp_readTouchY(void);

/**
* @brief Reads the Z-position (=pressure) of the currently detected touch point.
* The return value is in the range of 0 to 255.
* @param void
* @return z value of the (x,y,z) touchpoint
*/
uint16_t cppp_readTouchZ(void);

#endif