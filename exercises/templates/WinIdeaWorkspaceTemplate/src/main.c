#include "init.h"
#include "blink.h"

#include "board_test.h"
#include "acceleration_app.h"
#include "delay.h"
#include "gfx.h"
#include "uart_multicon.h"
#include "solution\graphicstest.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();
  
  //cppp_initBoardTest();
  //cppp_boardTest();
  
  //cppp_testAccelerationSensor();
  
  testGraphics();
  

  //writeGRAM();
  
  //cppp_uartSendBoardTest();
  
  return 0;
}
