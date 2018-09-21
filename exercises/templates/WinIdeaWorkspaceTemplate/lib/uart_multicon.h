#ifndef UART_MULTICON_H
#define UART_MULTICON_H

#include "mcu.h"
#include "pdl_header.h"
#include "pins.h"
#include "gfx.h"
#include "src/display.h"
#include "lib/uart_usb.h"
#include "rgb_led.h"
#include <string.h>


static char txBuf[] = "test"; 

void initUART3();

int uartMulticon(void);

void uartMulticonListen();

void initRGBLED();

void setRGBLED(uint8_t color);

void uartListenRainbowLED();

void uartMulticonWriteTest();

void uartMulticonWrite(uint8_t data);

void uartSendJoystick1XValue();

void cppp_uartSendBoardTest();

#endif