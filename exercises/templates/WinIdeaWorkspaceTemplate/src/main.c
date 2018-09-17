#include "init.h"
#include "blink.h"

#include "board_test.h"
#include "acceleration_app.h"
#include "delay.h"
#include "gfx.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();
  
  //scppp_initBoardTest();
  //cppp_boardTest();
  
  //cppp_testAccelerationSensor();
  
  //testGraphics();
  

  writeGRAM();
  
  
  return 0;
}
