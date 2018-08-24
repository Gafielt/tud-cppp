#include "init.h"
#include "blink.h"
#include "blinkrainbow.h"
#include "uart_usb.h"
#include "debug.h"

int main(){
  initBoard();
  
  // Write your code here ...
  BlinkMain();

  return 0;
}
