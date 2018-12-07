#include "rgb_led.h"
#include <stdint.h>
#include "s6e2ccxj.h"
#include "mcu.h"
#include "pins.h"

void cppp_initLEDs(void){
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.

  LED_RED_DDR |= (1 << LED_RED_PIN); // Configure red LED pin as output.
  LED_RED_DOR |= (1 << LED_RED_PIN); // Turn LED off.

  LED_GREEN_DDR |= (1 << LED_GREEN_PIN); // Configure green LED pin as output.
  LED_GREEN_DOR |= (1 << LED_GREEN_PIN); // Turn LED off.
}

void cppp_redLEDOn(void){
  LED_RED_DOR &= ~(1 << LED_RED_PIN);
}

void cppp_redLEDOff(void){
  LED_RED_DOR |= (1 << LED_RED_PIN);
}

void cppp_greenLEDOn(void){
  LED_GREEN_DOR &= ~(1 << LED_GREEN_PIN);
}

void cppp_greenLEDOff(void){
  LED_GREEN_DOR |= (1 << LED_GREEN_PIN);
}

void cppp_blueLEDOn(void){
  LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
}

void cppp_blueLEDOff(void){
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
}