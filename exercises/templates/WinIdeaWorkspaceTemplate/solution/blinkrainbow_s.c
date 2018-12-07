#include "src/blinkrainbow.h"

#include <stdint.h>
#include "delay.h"
#include "s6e2ccxj.h"
#include "mcu.h"

#include "pins.h"

int BlinkRainbowMain_s() {
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.

  LED_RED_DDR |= (1 << LED_RED_PIN); // Configure red LED pin as output.
  LED_RED_DOR |= (1 << LED_RED_PIN); // Turn LED off.

  LED_GREEN_DDR |= (1 << LED_GREEN_PIN); // Configure green LED pin as output.
  LED_GREEN_DOR |= (1 << LED_GREEN_PIN); // Turn LED off.
  
  const uint32_t sleepTime = 1000000;
  // Main loop. Color order: red, green, blue
  while (1) {
    
    // Switch blue LED off
    LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
    // Switch red LED on
    LED_RED_DOR &= ~(1 << LED_RED_PIN);
    
    cppp_microDelay(sleepTime);
    
    // Switch red LED off
    LED_RED_DOR |= (1 << LED_RED_PIN);
    // Switch green LED on
    LED_GREEN_DOR &= ~(1 << LED_GREEN_PIN);
    
    cppp_microDelay(sleepTime);
    
    // Switch green LED off
    LED_GREEN_DOR |= (1 << LED_GREEN_PIN);
    // Switch blue LED on
    LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
    
    cppp_microDelay(sleepTime); 
    
  }
}

