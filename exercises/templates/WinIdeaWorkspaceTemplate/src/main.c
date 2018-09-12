#include "init.h"
#include "blink.h"

#include "board_test.h"
#include "acceleration_app.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();
  
  cppp_initBoardTest();
  cppp_boardTest();
  
  //cppp_testAccelerationSensor();
  
  return 0;
}
