#ifndef DELAY_H
#define DELAY_H
/**
* @file delay.h
* @brief You can use delay.h to set delays in microseconds.
*/
#include "mcu.h"

/**
* @brief Synchronous function that blocks for the given amount of microseconds.
* @param timeInMicroseconds time that the delay should take in microseconds
* @return void
*/
void cppp_microDelay(uint32_t timeInMicroseconds);

#endif