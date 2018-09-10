#include "src\acceleration.h"
#include "lib\acceleration_app.h"
#include "lib\rgb_led.h"
#include "src\display.h"
#include "lib\gfx.h"

void cppp_rgbLEDAcceleration_s(){
  cppp_initLEDs();
  while(1u){
    if( data_available == 1 ){
      cppp_orientationValues[0] = ((float)((AccelerationData[ACCELERATION_AXIS_X]))) / (float)Sensitivity[ACCELERATION_AXIS_X];
      cppp_orientationValues[1] = ((float)((AccelerationData[ACCELERATION_AXIS_Y]))) / (float)Sensitivity[ACCELERATION_AXIS_Y];
      cppp_orientationValues[2] = ((float)((AccelerationData[ACCELERATION_AXIS_Z]))) / (float)Sensitivity[ACCELERATION_AXIS_Z];
      data_available = 0;
      
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
      writeFloat(cppp_orientationValues[0], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Orientierung Y: ");
      writeFloat(cppp_orientationValues[1], 4, 10);
      writeTextln_s(freeSpace);
      writeText_s("  Orientierung Z: ");
      writeFloat(cppp_orientationValues[2], 4, 10);
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