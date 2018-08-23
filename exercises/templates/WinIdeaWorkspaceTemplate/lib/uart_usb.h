#ifndef UART_USB_H
#define UART_USB_H

#include "mcu.h"
#include "pdl_header.h"
#include <string.h>

static char szUartTxBuf[] = "Welcome to Cypress\n\r"; 
volatile stc_mfsn_uart_t* pstcUart0;
stc_mfs_uart_config_t stcUartConfig; 
uint8_t u8Count; 

void UART_USB_Init();
int UART_USB(void);
void UART_USB_Print(const char* text); 

#endif