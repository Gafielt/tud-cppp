#ifndef BOARD_TEST_H
#define BOARD_TEST_H

/**
* @file board_test.h
* @brief <strong> You can use board_test.h to print all the periphery of the cppp board on the lc display.
* Just create the following code inside the main.c.</strong>
* <pre>
  #include "init.h"
  #include "board_test.h"
  int main(){
   initBoard();
   cppp_initBoardTest();
   cppp_boardTest();
   return 0;
  }
* </pre>
*/

#include "mcu.h"

/**
* @brief Controlling GPIO pins through changing registers.
*/
#define GPIO_REGISTER 0x00
/**
* @brief High level change of GPIO values.
*/
#define GPIO_METHOD 0x01

/**
* @brief Choosing how GPIOs should be changed.
*/
#define GPIO_SETTING GPIO_METHOD


/**
* @brief Holds the x,y,z acceleration values.
*/
static float accelerationValues[3];

/**
* @brief Initialization function that should be called before cppp_boardTest
* @param void
* @return void
*/
void cppp_initBoardTest(void);

/**
* @brief Should be called after cppp_initBoardTest 
* and prints all periphery data of the cppp board on the lc display.
* @param void
* @return void
*/
void cppp_boardTest(void);

/**
* @brief Checks if the Joystick 1 digital button is pressed.
* @param void
* @return 1 Joystick 1 digital button is pressed
* @return 0 Joystick 1 digital button is not pressed
*/
int cppp_isLeftJoystickButtonPressed(void);

/**
* @brief Checks if the Joystick 2 digital button is pressed.
* @param void
* @return 1 Joystick 2 digital button is pressed
* @return 0 Joystick 2 digital button is not pressed
*/
int cppp_isRightJoystickButtonPressed(void);

/**
* @brief Get the actual acceleration values and inserts them into the accelerationValues array. 
* @param void
* @return 
*/
uint8_t cppp_accelerationGetValues(void);

#endif