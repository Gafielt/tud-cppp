#include "analog.h"
#include "rgb_led.h"
#include "pins.h"
#include "gfx.h"
#include "src/display.h"
#include "lib/uart_usb.h"
#include "uart_multicon.h"

void cppp_initUart3(void){
  stc_mfs_uart_config_t stcUartConfig; 
  uint8_t u8Count; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN3_1();
  SetPinFunc_SOT3_1();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = 9600u;
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;
  if(Ok != Mfs_Uart_Init(&UART3, &stcUartConfig)){
    while(1){}
  }
  Mfs_Uart_EnableFunc(&UART3, UartTx); 
  Mfs_Uart_EnableFunc(&UART3, UartRx);
}

void cppp_initUart3Baud(uint32_t baudrate){
  stc_mfs_uart_config_t stcUartConfig; 
  uint8_t u8Count; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN3_1();
  SetPinFunc_SOT3_1();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = baudrate;
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;
  if(Ok != Mfs_Uart_Init(&UART3, &stcUartConfig)){
    while(1){}
  }
  Mfs_Uart_EnableFunc(&UART3, UartTx); 
  Mfs_Uart_EnableFunc(&UART3, UartRx);
}

void cppp_writeUart3(uint8_t data){
  while (TRUE != Mfs_Uart_GetStatus(&UART3, UartTxEmpty)){}
  Mfs_Uart_SendData(&UART3, data);
} 
 
void cppp_uart3DuplexTest(){
  cppp_initUart3();
  cppp_initLEDs();
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  
  while(1u){
    cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
    
    setCursor_s(0,319); 
    char freeSpace[] = " ";
    char headlineText[] = "  *** UART 3 DUPLEX TEST ***";
    setTextColor_s(YELLOW);
    writeTextln_s(freeSpace);
    writeTextln_s(headlineText);
    setTextColor_s(WHITE);
    writeTextln_s(freeSpace);
         
    writeText_s("Sending Brightness [Value:");
    writeNumberOnDisplayRight_s(&analog17);
    writeTextln_s("] ...");
    cppp_writeUart3(analog17);
    
    while(FALSE == Mfs_Uart_GetStatus(&UART3, UartRxFull)){}
    
    if(TRUE == Mfs_Uart_GetStatus(&UART3, UartRxFull)){
      uint8_t tmp = Mfs_Uart_ReceiveData(&UART3);
      writeText_s("Red LED [Value:");
      writeNumberOnDisplayRight_s(&tmp);
      writeTextln_s("] ...");
      if(tmp==1)
        cppp_redLEDOn();
      else
        cppp_redLEDOff();
    }
  }
}
