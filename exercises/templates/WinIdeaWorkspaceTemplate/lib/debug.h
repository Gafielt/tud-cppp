#ifndef DEBUG_H
#define DEBUG_H

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

void initDebug();
void debugCPPPBoard();
int isLeftJoystickButtonPressed();
int isRightJoystickButtonPressed();


#endif