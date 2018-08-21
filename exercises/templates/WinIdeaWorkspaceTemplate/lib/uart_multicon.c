#include "uart_multicon.h"

void initUART3(){
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


void testMulticonConnection(){
  // Initialize test pin as input and activate pullup resistor
  TEST_PIN_MULTICON_DDR &= ~(1 << TEST_PIN_MULTICON_PIN);
  TEST_PIN_MULTICON_PCR |= (1 << TEST_PIN_MULTICON_PIN); 

  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
  
  while(1u){
    uint8_t pinStatus = !(TEST_PIN_MULTICON_DIR & (1 << TEST_PIN_MULTICON_PIN));
    setCursor_s(480,320); 
    char freeSpace[] = " ";
    char headlineText[] = "  BLE Multicon Test";
    writeTextln_s(headlineText);
    writeTextln_s(freeSpace);
    if(pinStatus == 1){
       LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
       writeText_s("  test pin is high ");
       writeTextln_s(freeSpace);
    }
    else {
      LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
      writeText_s("  test pin is low ");
      writeTextln_s(freeSpace);
    }
  }
}
int uartMulticon(void){
  /*
  volatile stc_mfsn_uart_t* pstcUart3 = &UART3; 
  stc_mfs_uart_config_t stcUartConfig; 
  uint8_t u8Count; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN3_1();
  SetPinFunc_SOT3_1();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = 115200u;
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;

  Mfs_Uart_Init(pstcUart3, &stcUartConfig); // Initialize UART 
  Mfs_Uart_EnableFunc(pstcUart3, UartTx); 
  Mfs_Uart_EnableFunc(pstcUart3, UartRx);
  for (u8Count = 0u; u8Count < strlen((char*)&txBuf); u8Count++) {
    // wait until TX buffer empty
    while (TRUE != Mfs_Uart_GetStatus(pstcUart3, UartTxEmpty)) {}
    Mfs_Uart_SendData(pstcUart3, txBuf[u8Count]);
  } 
  while(1u) {
    // wait until RX buffer full
    while(TRUE != Mfs_Uart_GetStatus(pstcUart3, UartRxFull)) {}
    // Echo data
    Mfs_Uart_SendData(pstcUart3, Mfs_Uart_ReceiveData(pstcUart3));
  }
  */
}

void uartMulticonListen(){
  /*
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
    
  volatile stc_mfsn_uart_t* pstcUart3 = &UART3; 
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
  if(Ok != Mfs_Uart_Init(pstcUart3, &stcUartConfig)){
    while(1){}
  }
  Mfs_Uart_EnableFunc(pstcUart3, UartTx); 
  Mfs_Uart_EnableFunc(pstcUart3, UartRx);
  setCursor_s(480,320); 
  char headlineText[] = "  BLE Multicon UART Test";
  writeTextln_s(headlineText);
  writeTextln_s("");
  writeText_s("  UART received: ");
  while(1u) {
    // wait until RX buffer full

    if (TRUE == Mfs_Uart_GetStatus(pstcUart3, UartRxFull)) {
      // received data from the BLE module
      uint8_t tmp = Mfs_Uart_ReceiveData(pstcUart3);
      write8BitValueOnLCD(&tmp);
      //char tmpChar = (char) tmp;
      //writeAuto_s(tmpChar);
    }
  }
 */
}  

void initRGBLED(){
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
  
  LED_RED_DDR |= (1 << LED_RED_PIN); // Configure red LED pin as output.
  LED_RED_DOR |= (1 << LED_RED_PIN); // Turn LED off.
  
  LED_GREEN_DDR |= (1 << LED_GREEN_PIN); // Configure green LED pin as output.
  LED_GREEN_DOR |= (1 << LED_GREEN_PIN); // Turn LED off.
}

void setRGBLED(uint8_t color){
  switch(color){
    case 0:
      LED_RED_DOR   |= (1 << LED_RED_PIN);
      LED_GREEN_DOR |= (1 << LED_GREEN_PIN); 
      LED_BLUE_DOR  |= (1 << LED_BLUE_PIN);
    case 1: 
      LED_RED_DOR   &= ~(1 << LED_RED_PIN);
      LED_GREEN_DOR |= (1 << LED_GREEN_PIN); 
      LED_BLUE_DOR  |= (1 << LED_BLUE_PIN); 
      break;
    case 2: 
      LED_RED_DOR   |= (1 << LED_RED_PIN);
      LED_GREEN_DOR &= ~(1 << LED_GREEN_PIN); 
      LED_BLUE_DOR  |= (1 << LED_BLUE_PIN); 
      break;
    case 3: 
      LED_RED_DOR   |= (1 << LED_RED_PIN);
      LED_GREEN_DOR |= (1 << LED_GREEN_PIN); 
      LED_BLUE_DOR  &= ~(1 << LED_BLUE_PIN); 
      break;
  
  }
}


void uartListenRainbowLED(){
  initRGBLED();
  initUART3();
  setCursor_s(480,320); 
  char headlineText[] = "  BLE Multicon UART Test";
  writeTextln_s(headlineText);
  writeTextln_s("");
  writeText_s("  UART received: ");
  while(1u) {
    if (TRUE == Mfs_Uart_GetStatus(&UART3, UartRxFull)) {
      uint8_t tmp = Mfs_Uart_ReceiveData(&UART3);
      write8BitValueOnLCD(&tmp);
      switch(tmp){
        case 0:
          writeTextln_s("Rainbow RGB started ...");
          setRGBLED(0);
          break;
        case 1:
          setRGBLED(1);
          break;
        case 2:
          setRGBLED(2);
          break;
        case 3:
          setRGBLED(3);
          break;
      }
    }
  } 
}  

void uartMulticonWriteTest(){
  initUART3();
  char data = 'a';
  while (TRUE != Mfs_Uart_GetStatus(&UART3, UartTxEmpty)){}
  Mfs_Uart_SendData(&UART3, data);
}

void uartMulticonWrite(uint8_t data){
  while (TRUE != Mfs_Uart_GetStatus(&UART3, UartTxEmpty)){}
  Mfs_Uart_SendData(&UART3, data);
} 

void uartSendJoystick1XValue(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  setCursor_s(0, 319); // set to top-left corner
  char freeSpace[] = " ";
  char headlineText[] = "  UART DEBUG";
  writeTextln_s(freeSpace);
  writeTextln_s(headlineText);
  writeTextln_s(freeSpace);
  
  writeText_s("  Joystick 1 X-Achse: ");
  writeNumberOnDisplayRight_s(&analog16);
  uartMulticonWrite(analog16);
  
  writeTextln_s("");
  writeText_s("  Joystick 1 Y-Achse: ");
  writeNumberOnDisplayRight_s(&analog19);
  writeTextln_s("");
  
  writeText_s("  Joystick 2 X-Achse: ");
  writeNumberOnDisplayRight_s(&analog13);
  writeTextln_s("");
  writeText_s("  Joystick 2 Y-Achse: ");
  writeNumberOnDisplayRight_s(&analog23);
  writeTextln_s("");
}
