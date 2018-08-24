#include "init.h"
#include "blink.h"
#include "blinkrainbow.h"
#include "uart_usb.h"

int main(){
  initBoard();
  
  UART_USB_Init();
  UART_USB();
  
  // Write your code here ...
  //BlinkMain();
  debugCPPPBoard();

  return 0;
}
