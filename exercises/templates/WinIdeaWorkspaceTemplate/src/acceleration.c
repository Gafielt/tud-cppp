#include "acceleration.h"
#include "acceleration_app.h"
#include "rgb_led.h"
#include "display.h"
#include "gfx.h"

static float cppp_orientationValues[3];

void cppp_rgbLEDAcceleration(){
  cppp_initLEDs();
  while(1u){
    if( cppp_accelerationDataAvailable == 1 ){
      cppp_orientationValues[0] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_X]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_X];
      cppp_orientationValues[1] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Y]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Y];
      cppp_orientationValues[2] = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Z]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Z];
      cppp_accelerationDataAvailable = 0;


      // Exercise a) print actual sensor values on the LCD
      
      // Write your code here ...

      // Exercise b) use the orientation of the board to check if the board is on a leveled surface
      // change the LED color if the board is leveled to green and write a text on the screen
      
      // Write your code here ...
      
    }
  }
}
