#include "uart_multicon.h"
#include "mcu.h"
#include "pdl_header.h"

/*
   Prints the char to the UART3
*/
void writeCharUart3(char c);

/*
   Prints a null-terminated c-String to UART3
*/
uint8_t sendCommand(char* cmd);


void writeCharUart3(char c){
	while (TRUE != Mfs_Uart_GetStatus(&UART3, UartTxEmpty)); /* wait until TX buffer empty */
    Mfs_Uart_SendData(&UART3, c); 
}

uint8_t sendCommand(char* cmd){
  while(*cmd != '\0'){
        writeCharUart3(*cmd);
        cmd++;
	}
	return 0;
}