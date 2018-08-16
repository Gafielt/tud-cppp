#ifndef UART_MULTICON_H
#define UART_MULTICON_H

#include "mcu.h"
#include "pdl_header.h"
#include "pins.h"
#include "gfx.h"
#include "src/display.h"
#include "lib/uart_usb.h"
#include <string.h>


static char txBuf[] = "test"; 

void initUART3();

int uartMulticon(void);

void uartMulticonListen();

void initRGBLED();

void setRGBLED(uint8_t color);

void uartListenRainbowLED();

void uartMulticonWrite();

#endif