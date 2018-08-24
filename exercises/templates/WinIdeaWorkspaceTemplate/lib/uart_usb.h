#ifndef UART_USB_H
#define UART_USB_H

#include "mcu.h"
#include "pdl_header.h"
#include <string.h>

/*
 * The following code is a minimal working example.
 * 1. Create main.c with the following content
#include "uart_usb.h"
int main(){
  initBoard();
  UART_USB_Init();
  UART_USB();
  return 0;
}
 * 2. Install Cypress Serial Port Viewer from http://www.cypress.com/documentation/software-and-drivers/serial-port-viewer-and-terminal
 * 3. Run the Serial Port Viewer
 * 4. Adjust the baud rate to the value of Cppp_DefaultBaudRate
 * 5. Press the Disconnected button to connect
 * 6. Reset the evaluation board.
 * 7. You should see a welcome message. Start typing and you will receive a copy of what you type in.
*/

static uint32_t Cppp_DefaultBaudRate = 115200u;
static char szUartTxBuf[] = "Welcome to the C/C++ lab!\r\n"; 
volatile stc_mfsn_uart_t* pstcUart0;
stc_mfs_uart_config_t stcUartConfig; 
uint8_t u8Count; 

void UART_USB_Init();
int UART_USB(void);
void UART_USB_Print(const char* text); 

#endif