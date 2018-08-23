#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include "gfx.h"
#include "lcd.h"
#include "src/display.h"
#include "s6e2ccxj.h"
#include "analog.h"
#include "pins.h"

void initDebug();
int isLeftJoystickButtonPressed();
int isRightJoystickButtonPressed();
void debugCPPPBoard();


#endif