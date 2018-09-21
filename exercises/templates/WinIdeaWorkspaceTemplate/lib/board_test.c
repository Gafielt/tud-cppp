#include "board_test.h"
#include "acceleration_app.h"
#include "gfx.h"
#include "src/display.h"
#include "analog.h"
#include "pins.h"

void cppp_initBoardTest(void){
  #if (GPIO_SETTING == GPIO_REGISTER)
  // Initialize left button as input and activate pullup resistor
  BUTTON_LEFT_DDR &= ~(1 << BUTTON_LEFT_PIN);
  BUTTON_LEFT_PCR |= (1 << BUTTON_LEFT_PIN);
  
  // Initialize right button as input and activate pullup resistor
  BUTTON_RIGHT_DDR &= ~(1 << BUTTON_RIGHT_PIN);
  BUTTON_RIGHT_PCR |= (1 << BUTTON_RIGHT_PIN);
 #elif(GPIO_SETTING == GPIO_METHOD)
  Gpio1pin_InitIn(GPIO1PIN_PF5, Gpio1pin_InitPullup(1u));
  Gpio1pin_InitIn(GPIO1PIN_PF3, Gpio1pin_InitPullup(1u));
 #endif
}

int cppp_isLeftJoystickButtonPressed(void){
#if (GPIO_SETTING == GPIO_REGISTER)
  return !(BUTTON_LEFT_DIR & (1 << BUTTON_LEFT_PIN)); 
#elif (GPIO_SETTING == GPIO_METHOD)
  return !Gpio1pin_Get(GPIO1PIN_PF5);
#endif
}

int cppp_isRightJoystickButtonPressed(void){
 #if (GPIO_SETTING == GPIO_REGISTER)
  return !(BUTTON_RIGHT_DIR & (1 << BUTTON_RIGHT_PIN)); 
 #elif (GPIO_SETTING == GPIO_METHOD)
  return !Gpio1pin_Get(GPIO1PIN_PF3);
 #endif
}

uint8_t cppp_accelerationGetValues(void){
  float x_out, y_out, z_out;
  float x_deg, y_deg, z_deg;
  
  if( cppp_accelerationDataAvailable == 1 ){
    x_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_X]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_X];
    y_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Y]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Y];
    z_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Z]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Z];
    accelerationValues[0] = x_out;
    accelerationValues[1] = y_out;
    accelerationValues[2] = z_out;
    cppp_accelerationDataAvailable = 0;
    return 1;
  }
  return 0;           
}

void cppp_boardTest(void){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  
  while(1u){
    cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  
    setCursor_s(0,319); 
    char freeSpace[] = " ";
    char headlineText[] = "  *** BOARD TEST ***";
    setTextColor_s(YELLOW);
    writeTextln_s(freeSpace);
    writeTextln_s(headlineText);
    setTextColor_s(WHITE);
    writeTextln_s(freeSpace);
    
    // Get analog values of the touchscreen
    uint16_t touchZ = cppp_readTouchZ();
    uint16_t touchX = touchZ != 0 ? cppp_readTouchX() : 0;
    uint16_t touchY = touchZ != 0 ? cppp_readTouchY() : 0;
    
    if(touchX > 480 || touchY>320){
       touchX = 0;
       touchY = 0;
       touchZ = 0;
    }
    
    // Write x,y, and z-values on the screen
    char touchXText[] = "  Touch X: ";
    char touchYText[] = "  Touch Y: ";
    char touchZText[] = "  Touch Z: ";
    
    // Write brightness sensor on the screen
    char lightSensor[] = "    Brightness: "; 
    
    writeText_s(touchXText);
    write3Digits16Bit(&touchX);
    writeText_s(lightSensor);
    writeNumberOnDisplayRight_s(&analog17);
    writeTextln_s("");
    writeText_s(touchYText);
    write3Digits16Bit(&touchY);
    writeTextln_s("");
    writeText_s(touchZText);
    write3Digits16Bit(&touchZ);
    writeTextln_s("");
    
    writeTextln_s(freeSpace);
    
    // Display joystick values
    writeText_s("  Joystick 1 X: ");
    writeNumberOnDisplayRight_s(&analog16);
    writeTextln_s("");
    writeText_s("  Joystick 1 Y: ");
    writeNumberOnDisplayRight_s(&analog19);
    writeTextln_s("");
    writeText_s("  Joystick 1 Button: ");
    if(cppp_isLeftJoystickButtonPressed()){
      writeText_s("X");
    }
    else
      writeText_s("_");
    writeTextln_s("");
    
    writeTextln_s("");
    
    writeText_s("  Joystick 2 X: ");
    writeNumberOnDisplayRight_s(&analog13);
    writeTextln_s("");
    writeText_s("  Joystick 2 Y: ");
    writeNumberOnDisplayRight_s(&analog23);
    writeTextln_s("");
    writeText_s("  Joystick 2 Button: "); 
    if(cppp_isRightJoystickButtonPressed()){
      writeText_s("X"); 
    }
    else
      writeText_s("_");
    writeTextln_s("");
    writeTextln_s("");
    if(cppp_accelerationGetValues() == 1){
      writeText_s("  Acceleration X: ");
      writeFloat(accelerationValues[0], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Acceleration Y: ");
      writeFloat(accelerationValues[1], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Acceleration Z: ");
      writeFloat(accelerationValues[2], 4, 10);
    }
  }
}