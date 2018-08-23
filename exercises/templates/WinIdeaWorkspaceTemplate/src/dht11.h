#ifndef DHT11_H
#define DHT11_H

#include "mcu.h"
#include "pdl_header.h"
#include "analog.h"
#include "delay.h"
#include "gfx.h"
#include "display.h"

uint8_t data[5];

uint8_t readDHT11(uint8_t *feuchtigkeit, uint8_t *temperatur);
uint8_t readDHT11_s(uint8_t *feuchtigkeit, uint8_t *temperatur);
void rauminformationen();
void rauminformationen_s();

#endif /* DHT11_H */