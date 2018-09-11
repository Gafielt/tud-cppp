#include "acceleration.h"
#include "acceleration_app.h"
#include "rgb_led.h"
#include "display.h"
#include "gfx.h"

void cppp_rgbLEDAcceleration(){
  cppp_initLEDs();
  while(1u){
    if( cppp_accelerationDataAvailable == 1 ){
      cppp_orientationValues[0] = ((float)((AccelerationData[ACCELERATION_AXIS_X]))) / (float)Sensitivity[ACCELERATION_AXIS_X];
      cppp_orientationValues[1] = ((float)((AccelerationData[ACCELERATION_AXIS_Y]))) / (float)Sensitivity[ACCELERATION_AXIS_Y];
      cppp_orientationValues[2] = ((float)((AccelerationData[ACCELERATION_AXIS_Z]))) / (float)Sensitivity[ACCELERATION_AXIS_Z];
      cppp_accelerationDataAvailable = 0;


      // Write your code here ...
      // Exercise a) print actual sensor values on the LCD
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

      // Exercise b) use the orientation of the board to check if the board is on a leveled surface
      // change the LED color if the board is leveled to green and write a text on the screen
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
