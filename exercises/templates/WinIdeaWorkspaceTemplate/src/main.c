#include "init.h"
#include "blink.h"
#include "kxcjk1013_debug.h"

int main(){
  initBoard();

  // Write your code here ...
  //BlinkMain();

  cppp_debugAccelerationSensor();
  return 0;
}
