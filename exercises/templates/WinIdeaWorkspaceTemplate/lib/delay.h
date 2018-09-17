#ifndef DELAY_H
#define DELAY_H
/**
* @file delay.h
* @brief <strong> You can use delay.h to set delays in microseconds. For example if you want to stop the 
* controller for 1 seconds you can call cppp_microDelay(1000000). You can use the following example
* to test the microDelay function to blink the blue led.</strong> 
<pre>
#include <stdint.h>
#include "s6e2ccxj.h"
#include "pins.h"
#include "delay.h"

int main(){
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
  
  const uint32_t sleepTime = 1000000;
  
  // Main loop
  while (1) {
    // Clear bit -> Switch LED on
    LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
    cppp_microDelay(sleepTime); 
  	
    // Set bit -> Switch LED off
    LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
    cppp_microDelay(sleepTime);
  }
}
</pre>
*/
#include "mcu.h"

/**
* @brief Synchronous function that blocks for the given amount of microseconds.
* @param timeInMicroseconds time that the delay should take in microseconds
* @return void
*/
void cppp_microDelay(uint32_t timeInMicroseconds);

#endif