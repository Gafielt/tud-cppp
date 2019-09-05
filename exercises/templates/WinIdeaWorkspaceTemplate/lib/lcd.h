#ifndef LCD_H
#define LCD_H
/**
 * @file lcd.h 
 * @brief <strong>This code is based on:  https://github.com/adafruit/Adafruit-GFX-Library &  https://github.com/adafruit/TFTLCD-Library
 * The code has been adjusted for the Cypress FM4  microcontroller.</strong>
 */
#include "mcu.h"


//uint8_t cppp_lcdArray[480][320];

/**
 * @brief Represents a point where the touchscreen was touched
 */
struct TouchPoint{
  uint16_t x;
  uint16_t y;
  uint16_t z;
} touchPoint;  

/** 
 * @brief Delays the programm for n cycles. 
 * @param n number of cycles
 * @return void
 */
void cppp_delay(int n);

/**
 * @brief Toggles between LCD_WR_ACTIVE and LCD_WRITE_IDLE.
 * @return void
 */
void cppp_writeStrobe(void);

/**
 * @brief Writes 8 Bits parallel on the data pins 0-7.
 * @param d the 8 bit data
 * @return void
 */
void cppp_write8(char d);

/**
 * @brief 32 Bits 4 times serial on the parallel data pins 0-7.
 * @param r 
 * @param d 32 bit data
 * @return void
 */
void cppp_write32(char r, long d);

/**
 * @brief Set Value of the TFT 8-bit registers aH and aL with the low and high parts 
 * of the 16 bit value d.   
 * @param aH register with the highest 8 bits of d
 * @param aL register with the lowest 8 bits of d
 * @param d value
 * @return void
 */
void cppp_writeRegisterPair(char aH, char aL, int d);


/**
 * @brief Writes command and data on 8 data pins.
 * @param a address of register to write onto
 * @param d data that will be written onto the register
 * @return void
 */
void cppp_writeRegister8(char a, char d);

/**
 * @brief Sets the window of coordinates from (x1,y1) to (x2,y2), that are going to be manipulated by a method.
 * @param x1 start point
 * @param y1 start point
 * @param x2 end point
 * @param y2 end point
 * @return void
 */
void cppp_setAddrWindow(int x1, int y1, int x2, int y2);

/**
 * @brief Initialization of the direction and start value of 8 data and 5 control pins.
 * @return void
 */
void cppp_initLCDPins(void);

/**
 * @brief Resets the lc display.
 * @return void
 */
void cppp_resetLCD(void);

/**
 * @brief Runs the configuration methods of the LCD-Controller.
 * @return void
 */
void cppp_setupLCD(void);

/**
 * @brief Kind of a reset for cppp_setAddrWindow().
 * @return void
 */
void cppp_setLR(void);

/**
 * @brief Writes on the GRAM color len-times. 
 * @param color 565 rgb color 
 * @param len length of pixels of the GRAM that are going to be changed
 * @return void
 */
void cppp_floodLCD(int color, long len);


/**
 * @brief Fill the cppp_LCDArray with a chess pattern.
 * @return void
 */
void cppp_testFillLCDArray(void);

/**
 * @brief Through this function the array cppp_LCDArray will be pushed to the GRAM of the LCD.
 * @return void
 */
void cppp_writeGRAM(void);

#endif /* LCD_H */
