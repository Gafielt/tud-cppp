#include "init.h"
#include "blink.h"
#include "board_test.h"

int main(){
  initBoard();
  
  cppp_initBoardTest();
  cppp_boardTest();

  // Write your code here ...
  //BlinkMain();   
  return 0;
}
