#ifndef UART_MULTICON_H
#define UART_MULTICON_H

/**
 * @file uart_multicon.h
 * @brief <strong>UART multicon interface of the FM4, which can be used to connect the BLE module to the FM4.
 *        You can test the BLE module duplex connection with this code:</strong>
 * <pre>
#include "init.h"
#include "uart_multicon.h"
int main(){
 initBoard();
 cppp_initUart3();
 cppp_uart3DuplexTest();
 return 0;
}
 * </pre> 
 */
#include "mcu.h"
 
/**
 * @brief Initialization of the UART3 interface of the multicon.
 * @return void
 */
void cppp_initUart3(void);
/**
 * @brief Initialization of the UART3 interface of the multicon.
 * @param baudrate that the interface should work at.
 * @return void
 */
void cppp_initUart3Baud(uint32_t baudrate);
    
/**
 * @brief Write 8 Bit data through UART 3.
 * @param data 8 bit data
 */
void cppp_writeUart3(uint8_t data);

/**
 * @brief Test the duplex UART 3 connection to the BLE module.
 *        If everything on the BLE module side is configured correctly, you should be able to toggle the
 *        red LED of the FM4 via BLE and send the value of the brightness sensor from the FM4 to the BLE module.
 */
void cppp_uart3DuplexTest(void);

#endif