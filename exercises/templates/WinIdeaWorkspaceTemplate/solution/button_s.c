#include "src/button.h"

#include "delay.h"
#include "pdl_header.h"
#include "s6e2ccxj.h"

#include "pins.h"

static uint8_t ledStatus;

/**
 * Initializes ports and pins of the LEDs
 */
static void initLED();

/**
 * Returns true (1) if the button is pressed
 */
static int isButtonPressed();

/**
 *  Changes the status of the blue LED.
 */
static void toggleBlueLED();

/**
 *  Sets the blue LED to its status.
 */
static void setBlueLED(uint8_t status);


void ButtonToggleBlueLED_s(){
  initLED();
  const uint32_t sleepTime = 100000;
   
  while(1){
    if(isButtonPressed()){
      toggleBlueLED();
      setBlueLED(ledStatus);
      while(isButtonPressed());
    }
    cppp_microDelay(sleepTime);
  }  
}
                          
void ButtonHoldBlueLEDOn_s() {
  initLED();
  const uint32_t sleepTime = 100000;
  while(1){
    
    while(isButtonPressed()){
      setBlueLED(1u); 
      cppp_microDelay(sleepTime);
    }
    
    setBlueLED(0u);
    cppp_microDelay(sleepTime);
    
  }
}

static void initLED() {
  ledStatus = 0u;
  
  // Initialize left button as input and activate pullup resistor
  BUTTON_LEFT_DDR &= ~(1 << BUTTON_LEFT_PIN);
  BUTTON_LEFT_PCR |= (1 << BUTTON_LEFT_PIN); 
  
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue led as output pin
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Switch LED off
}


static int isButtonPressed() {
  // Inverted logic as input is pulled up
  return !(BUTTON_LEFT_DIR & (1 << BUTTON_LEFT_PIN));                             
}

static void toggleBlueLED(){
  if(ledStatus)
    ledStatus = 0u;
  else
    ledStatus = 1u;
}

static void setBlueLED(uint8_t status) {
  if(status)
    LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN); 
  else
    LED_BLUE_DOR |= (1 << LED_BLUE_PIN); 
}
                  
