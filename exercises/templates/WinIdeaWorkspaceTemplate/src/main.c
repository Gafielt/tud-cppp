#include "init.h"
#include "blink.h"


#include "kxcjk1013_debug.h"
#include "rgb_led.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();
  /*
  initDebug();
  debugCPPPBoard();
  */
  
  cppp_initLEDs();
  cppp_redLEDOn();
  cppp_debugAccelerationSensor();
  
  return 0;
}
