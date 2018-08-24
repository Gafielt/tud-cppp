#include "uart_usb.h"
#include "src\display.h"

void UART_USB_Init(){
  pstcUart0 = &UART0; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN0_0();
  SetPinFunc_SOT0_0();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = Cppp_DefaultBaudRate; 
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;

  Mfs_Uart_Init(pstcUart0, &stcUartConfig); // Initialize 
  Mfs_Uart_EnableFunc(pstcUart0, UartTx); 
  Mfs_Uart_EnableFunc(pstcUart0, UartRx);
}
int UART_USB(void){
  for (u8Count = 0u; u8Count < strlen((char*)&szUartTxBuf); u8Count++) {
    // wait until TX buffer empty
    while (TRUE != Mfs_Uart_GetStatus(pstcUart0, UartTxEmpty)) {}
    Mfs_Uart_SendData(pstcUart0, szUartTxBuf[u8Count]);
  } 
  while(1u) {
    // wait until RX buffer full
    while(TRUE != Mfs_Uart_GetStatus(pstcUart0, UartRxFull)) {}
    // Echo data
    uint16_t tmp = Mfs_Uart_ReceiveData(pstcUart0);
    //write16BitDigit(&tmp,2);
    char tmpChar = (char) tmp;
    writeAuto_s(tmpChar);
    Mfs_Uart_SendData(pstcUart0, tmp);
  }
}

void UART_USB_Print(const char* text){
  for (u8Count = 0u; u8Count < strlen((char*)&text); u8Count++) {
    // wait until TX buffer empty
    while (TRUE != Mfs_Uart_GetStatus(pstcUart0, UartTxEmpty)) {}
    Mfs_Uart_SendData(pstcUart0, text[u8Count]);
  }
}