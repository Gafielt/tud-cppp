#include "init.h"
#include "lcd.h"
#include "src/display.h"
#include "gfx.h"
#include "acceleration_app.h"

void initBoard(){
  init();
  reset();
  setupLCD();
  initCursor_s();
  InitAdc();
  fillScreen(BLACK);
  setCursor_s(0,319);
  
  // Configure all used ports as inputs.
  LED_BLUE_DDR &= ~(1 << LED_BLUE_PIN);
  LED_RED_DDR &= ~(1 << LED_RED_PIN);
  LED_GREEN_DDR &= ~(1 << LED_GREEN_PIN);
  BUTTON_RIGHT_DDR &= ~(1 << BUTTON_RIGHT_PIN);
  BUTTON_LEFT_DDR &= ~(1 << BUTTON_RIGHT_PIN);

  bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  bFM4_GPIO_ADE_AN10 = 0; // Disable analog-digital channel 10
  bFM4_GPIO_ADE_AN18 = 0; // Disable analog-digital channel 18

  
  cppp_initAcceleration();
}
