#include "init.h"
#include "uart_usb.h"


int main(){
  initBoard();

  UART_USB_Init();

  UART_USB();

  return 0;
}