#include "src\acceleration.h"
#include "lib\acceleration_app.h"
#include "lib\rgb_led.h"
#include "src\display.h"
#include "lib\gfx.h"

static float cppp_orientationValues[3];

void cppp_rgbLEDAcceleration_s(){
  cppp_initLEDs();
  while(1u){
    if( cppp_accelerationDataAvailable == 1 ){
      cppp_orientationValues[0] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_X]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_X];
      cppp_orientationValues[1] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Y]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Y];
      cppp_orientationValues[2] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Z]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Z];
      cppp_accelerationDataAvailable = 0;
      
      setCursor_s(0,319); 
      char freeSpace[] = " ";
      char headlineText[] = "  *** Beschleunigungssensor ***";
      setTextSize_s(2);
      setTextColor_s(YELLOW);
      writeTextln_s(freeSpace);
      writeTextln_s(headlineText);
      setTextColor_s(WHITE);
      writeTextln_s(freeSpace);
      writeText_s("  Orientierung X: ");
      cppp_writeFloat(cppp_orientationValues[0], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Orientierung Y: ");
      cppp_writeFloat(cppp_orientationValues[1], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Orientierung Z: ");
      cppp_writeFloat(cppp_orientationValues[2], 4, 10);
      writeTextln_s("");
      writeTextln_s("");
      
      if(cppp_orientationValues[0] > 0 && cppp_orientationValues[1] > 0 && cppp_orientationValues[2] >= 1
         && cppp_orientationValues[0] < 0.04 && cppp_orientationValues[1] < 0.04){
        cppp_redLEDOff();
        cppp_greenLEDOn();
        cppp_blueLEDOff();
        setTextColor_s(GREEN);
        setTextSize_s(2);
        writeText_s("  Die Ebene ist waagrecht.      ");
      }
      else {
        cppp_redLEDOn();
        cppp_greenLEDOff();
        cppp_blueLEDOff();
        setTextColor_s(RED);
        setTextSize_s(2);
        writeText_s("  Die Ebene ist nicht waagrecht.");
      }
    } 
  }
}