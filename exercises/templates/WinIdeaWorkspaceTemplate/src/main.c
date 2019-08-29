#include "init.h"
#include "blink.h"
#include "acceleration_app.h"
int main(){
  initBoard();

  // Write your code here ...
  cppp_rgbLEDAcceleration_s();
  
  return 0;
}
