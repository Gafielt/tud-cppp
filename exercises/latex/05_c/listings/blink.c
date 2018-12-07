#include "blink.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"

#include "pins.h"

int BlinkMain() {
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

