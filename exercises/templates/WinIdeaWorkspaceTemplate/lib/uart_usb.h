#ifndef UART_USB_H
#define UART_USB_H
#include "mcu.h"
#include "pdl_header.h"

/**
 * @file uart_usb.h
 * @brief <strong>The following code is a minimal working example.
 * 1. Create main.c with the following content </strong>
 <pre>
#include "uart_usb.h"
int main(){
  initBoard();
  cppp_uartUsbInit();
  cppp_uartUsb();
  return 0;
}
</pre>
  <strong>
 * 2. Install Cypress Serial Port Viewer from http://www.cypress.com/documentation/software-and-drivers/serial-port-viewer-and-terminal
 * 3. Run the Serial Port Viewer
 * 4. Adjust the baud rate to the value of Cppp_DefaultBaudRate
 * 5. Press the Disconnected button to connect
 * 6. Reset the evaluation board.
 * 7. You should see a welcome message. Start typing and you will receive a copy of what you type in. </strong>
*/

/**
 * @brief The baudrate of the uart data transfer.
 */
static uint32_t Cppp_DefaultBaudRate = 115200u;

/**
 * @brief Welcome text when uart is started.
 */
static char szUartTxBuf[] = "Welcome to the C/C++ lab!\r\n"; 

/**
 * @brief Pointer to the uart 0 interface of the FM4.
 */
volatile stc_mfsn_uart_t* pstcUart0;

/**
 * @brief Configuration struct of uart 0.
 */
stc_mfs_uart_config_t stcUartConfig; 

/**
 * @brief 8 bit counter.
 */
uint8_t u8Count; 

/**
 * @brief Initializes the UART for the USB connection to your PC.
 * @return void
 */
void cppp_uartUsbInit(void);

/**
  * @brief This sends the text you write on your PC to the FM4 and the FM4 echos it back to your PCs. 
  *        You can display the result on a serial terminal with the baudrate Cppp_DefaultBaudRate.
  *        Also the characters will be display on the LCD of the lab board.
  * @return void
  */
void cppp_uartUsb(void);

/**
 * @brief This sends the text you write on your PC to the FM4 and the FM4 echos it back to your PCs. 
 *        You can display the result on a serial terminal with the baudrate Cppp_DefaultBaudRate.  
 * @param text
 * @return 
 */
void cppp_uartUsbPrint(const char* text); 


#endif