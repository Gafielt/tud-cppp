#include "init.h"
#include "blink.h"


#include "acceleration_app.h"
#include "rgb_led.h"

#include "board_test.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();   
  
  /*
  cppp_initLEDs();
  cppp_testAccelerationSensor();
  */
  cppp_initBoardTest();
  cppp_boardTest();
  return 0;
}
