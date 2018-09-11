#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#define GPIO_CLASSIC 0x00
#define GPIO_NEW 0x01

#define GPIO_SETTING GPIO_NEW

#include <stdint.h>
#include "gfx.h"
#include "lcd.h"
#include "src/display.h"
#include "s6e2ccxj.h"
#include "analog.h"
#include "pins.h"


static float accelerationValues[3];

void cppp_initBoardTest();
void cppp_boardTest();
int cppp_isLeftJoystickButtonPressed();
int cppp_isRightJoystickButtonPressed();
uint8_t cppp_accelerationGetValues();

void dummyMethod();


#endif