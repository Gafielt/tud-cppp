#include "src/joystick.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "analog.h"
#include "delay.h"
#include "src/display.h"

void controlLedsInit_s(){
  // turn off analog Pins
  bFM4_GPIO_ADE_AN08 = 0u; // Analog 8 off
  bFM4_GPIO_ADE_AN18 = 0u; // Analog 18 off
  bFM4_GPIO_ADE_AN10 = 0u; // Analog 10 off

  // Define Pins as outputs
  FM4_GPIO->DDRB_f.P2 = 1u; // Pin 104(B2)
  FM4_GPIO->DDR1_f.P8 = 1u; // Pin 106(18)
  FM4_GPIO->DDR1_f.PA = 1u; // Pin 108(1A)
  
  // turn all LEDs down
  FM4_GPIO->PDORB_f.P2 = 1u; // green off
  FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
  FM4_GPIO->PDOR1_f.PA = 1u; // red off
}

void controlLeds_s(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  const uint32_t sleepTime = 10000; // 0,01s
  // green => Pin104 PB2/A18    blue => Pin106 P18/A08     red => Pin108 P1A/A10
  // JS1X is analog16
  
  // left: JS1 X < 255 && >= 200    => green
  // middle: JS1 X < 200 && >= 180  => blue
  // right: JS1 X <180 && >= 0      => red
  
  // joystick left
  if(analog16 >= 220){
      FM4_GPIO->PDORB_f.P2 = 0u; // green on
      FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
      FM4_GPIO->PDOR1_f.PA = 1u; // red off
  }
  // joystick middle
  else if(analog16 < 220 && analog16 >= 180){
      FM4_GPIO->PDORB_f.P2 = 1u; // green off
      FM4_GPIO->PDOR1_f.P8 = 0u; // blue on
      FM4_GPIO->PDOR1_f.PA = 1u; // red off
  }
  // joystick right
  else if(analog16 < 180){
      FM4_GPIO->PDORB_f.P2 = 1u; // green off
      FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
      FM4_GPIO->PDOR1_f.PA = 0u; // red on
  }
  cppp_microDelay(sleepTime); 
}

void printValues_s(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);

  
  setCursor_s(0, 319); // set to top-left corner
  char freeSpace[] = " ";
  char headlineText[] = "  DEBUG";
  writeTextln_s(freeSpace);
  writeTextln_s(headlineText);
  writeTextln_s(freeSpace);
  
  writeText_s("  Joystick 1 X-Achse: ");
  writeNumberOnDisplayRight_s(&analog16);
  writeTextln_s("");
  writeText_s("  Joystick 1 Y-Achse: ");
  writeNumberOnDisplayRight_s(&analog19);
  writeTextln_s("");
  
  writeText_s("  Joystick 2 X-Achse: ");
  writeNumberOnDisplayRight_s(&analog13);
  writeTextln_s("");
  writeText_s("  Joystick 2 Y-Achse: ");
  writeNumberOnDisplayRight_s(&analog23);
  writeTextln_s("");
}
