/**
 * @file pins.h
 * @brief <strong>Makros for the MCU pins</strong>
 */
#ifndef pins_h
#define pins_h


/**
 *            LCD pins
 */

/**
 * @brief LCD data register 
 */
#define LCD_DATA FM4_GPIO->PDOR1LL 

/**
 * @brief LCD data IO register
 */
#define LCD_DATA_IO FM4_GPIO->DDR1 
                       
/**
 * @brief LCD read register and is connected to P44 of the MCU.
 */
#define LCD_RD   FM4_GPIO->PDOR4_f.P4  

/**
 * @brief LCD reset register and is connected to P45 of the MCU.
 */
#define LCD_RS   FM4_GPIO->PDOR4_f.P5  

/**
 * @brief LCD write register and is connected to PF0 of the MCU.
 */
#define LCD_WR   FM4_GPIO->PDORF_f.P0  

/**
 * @brief LCD cd register and is connected to PF1 of the MCU.
 */
#define LCD_CD   FM4_GPIO->PDORF_f.P1  

/**
 * @brief LCD chip select register and is connected to P7D of the MCU.
 */
#define LCD_CS   FM4_GPIO->PDOR7_f.PD 

/**
 * @brief LCD read IO register and is connected to P44 of the MCU.
 */
#define LCD_RD_IO   FM4_GPIO->DDR4_f.P4  

/**
 * @brief LCD reset IO register and is connected to P45 of the MCU.
 */
#define LCD_RS_IO   FM4_GPIO->DDR4_f.P5  

/**
 * @brief LCD write IO register and is connected to PF0 of the MCU.
 */
#define LCD_WR_IO   FM4_GPIO->DDRF_f.P0 

/**
 * @brief LCD cd IO register and is connected to PF1 of the MCU.
 */
#define LCD_CD_IO   FM4_GPIO->DDRF_f.P1 

/**
 * @brief LCD chip select IO register and is connected to P7D of the MCU.
 */
#define LCD_CS_IO   FM4_GPIO->DDR7_f.PD 


/**
 *            LCD touch pins
 */

/**
 * @brief LCD touch X minus register, which is connected to P1B of the MCU.
 *        P1B has also an analog function A11. 
 */
#define TOUCH_XM    FM4_GPIO->PDOR1_f.PB 

/**
 * @brief LCD touch X plus register, which is connected to P7B of the MCU.
 */
#define TOUCH_XP    FM4_GPIO->PDOR7_f.PB

/**
 * @brief LCD touch Y minus register, which is connected to PF6 of the MCU.
 */
#define TOUCH_YM    FM4_GPIO->PDORF_f.P6 

/**
 * @brief LCD touch Y plus register, which is connected to P1C of the MCU.
 *        P1C has also an analog function A12.
 */
#define TOUCH_YP    FM4_GPIO->PDOR1_f.PC

/**
 * @brief LCD touch X minus IO register, which is connected to P1B of the MCU.
 *        P1B has also an analog function A11.
 */
#define TOUCH_XM_IO FM4_GPIO->DDR1_f.PB  

/**
 * @brief LCD touch X plus IO register, which is connected to P7B of the MCU.
 */
#define TOUCH_XP_IO FM4_GPIO->DDR7_f.PB  

/**
 * @brief LCD touch Y minus IO register, which is connected to PF6 of the MCU.
 */
#define TOUCH_YM_IO FM4_GPIO->DDRF_f.P6

/**
 * @brief LCD touch Y plus IO register, which is connected to P1C of the MCU.
 *        P1C has also an analog function A12.
 */
#define TOUCH_YP_IO FM4_GPIO->DDR1_f.PC  // TOUCH_YP => P1C / A12


/**
 *            LCD touch pins
 */

/**
 * @brief Joystick 1 (left) X axis pin register, which is connected to PB0 of the MCU.
 *        PB0 has also an analog function A16.
 */
#define JS1_X    FM4_GPIO->PDORB_f.P0

/**
 * @brief Joystick 1 (left) Y axis pin register, which is connected to PB3 of the MCU.
 *        PB3 has also an analog function A19.
 */
#define JS1_Y    FM4_GPIO->PDORB_f.P3 

/**
 * @brief Joystick 2 (right) X axis pin register, which is connected to P1D of the MCU.
 *        P1D has also an analog function A13.
 */
#define JS2_X    FM4_GPIO->PDOR1_f.PD 

/**
 * @brief Joystick 2 (right) Y axis pin register, which is connected to PB7 of the MCU.
 *        PB7 has also an analog function A23.
 */
#define JS2_Y    FM4_GPIO->PDORB_f.P7

/**
 * @brief Joystick 1 (left) X axis IO pin register, which is connected to PB0 of the MCU.
 *        PB0 has also an analog function A16.
 */
#define JS1_X_IO    FM4_GPIO->DDRB_f.P0 

/**
 * @brief Joystick 1 (left) Y axis IO pin register, which is connected to PB3 of the MCU.
 *        PB3 has also an analog function A19.
 */
#define JS1_Y_IO    FM4_GPIO->DDRB_f.P3

/**
 * @brief Joystick 2 (right) X axis pin register, which is connected to P1D of the MCU.
 *        P1D has also an analog function A13.
 */
#define JS2_X_IO    FM4_GPIO->DDR1_f.PD

/**
 * @brief Joystick 2 (right) Y axis IO pin register, which is connected to PB7 of the MCU.
 *        PB7 has also an analog function A23.
 */
#define JS2_Y_IO    FM4_GPIO->DDRB_f.P7

/**
 *            Joystick button pins
 */

/**
 * @brief Joystick 1 (left) button IO port, this pin is connected to port F pin 5 (PF5).
 */
#define BUTTON_LEFT_DDR FM4_GPIO->DDRF  

/**
 * @brief Joystick 1 (left) button pullup configuration port, this pin is connected to port F pin 5 (PF5).
 */
#define BUTTON_LEFT_PCR FM4_GPIO->PCRF 

/**
 * @brief Joystick 1 (left) button input data port, this pin is connected to port F pin 5 (PF5).
 */
#define BUTTON_LEFT_DIR FM4_GPIO->PDIRF 

/**
 * @brief Joystick 1 (left) pin number, this pin is connected to port F pin 5 (PF5).
 */
#define BUTTON_LEFT_PIN 0x05 

/**
 * @brief Joystick 2 (right) button IO port, this pin is connected to port F pin 3 (PF3).
 */
#define BUTTON_RIGHT_DDR FM4_GPIO->DDRF

/**
 * @brief Joystick 2 (right) button pullup configuration port, this pin is connected to port F pin 3 (PF3).
 */
#define BUTTON_RIGHT_PCR FM4_GPIO->PCRF

/**
 * @brief Joystick 2 (right) button input data port, this pin is connected to port F pin 3 (PF3).
 */
#define BUTTON_RIGHT_DIR FM4_GPIO->PDIRF

/**
 * @brief Joystick 2 (right) pin number, this pin is connected to port F pin 3 (PF3).
 */
#define BUTTON_RIGHT_PIN 0x03

/**
 *            RGB LED pins
 */

/**
 * @brief RED LED IO register port. 
 * This pin is connected to port 1 pin A.
 */
#define LED_RED_DDR FM4_GPIO->DDR1   

/**
 * @brief RED LED data output register port. 
 * This pin is connected to port 1 pin A.
 */
#define LED_RED_DOR FM4_GPIO->PDOR1  

/**
 * @brief RED LED IO pin number. 
 * This pin is connected to port 1 pin A.
 */
#define LED_RED_PIN 0x0A     

/**
 * @brief GREEN LED IO register port. 
 * This pin is connected to port B pin 2.
 */
#define LED_GREEN_DDR FM4_GPIO->DDRB

/**
 * @brief GREEN LED data output register port. 
 * This pin is connected to port B pin 2.
 */
#define LED_GREEN_DOR FM4_GPIO->PDORB

/**
 * @brief GREEN LED IO pin number. 
 * This pin is connected to port B pin 2.
 */
#define LED_GREEN_PIN 0x02

/**
 * @brief RED led IO register port. 
 * This pin is connected to port 1 pin 8.
 */
#define LED_BLUE_DDR FM4_GPIO->DDR1

/**
 * @brief BLUE LED data output register port. 
 * This pin is connected to port 1 pin 8.
 */
#define LED_BLUE_DOR FM4_GPIO->PDOR1

/**
 * @brief BLUE LED IO pin number. 
 * This pin is connected to port 1 pin 8.
 */
#define LED_BLUE_PIN 0x08

/**
 *            DHT11 pin connected to pin 75 (PF7) of FM4
 */

/**
 * @brief DHT11 data out pin, which is connected to PF7 of FM4.
 */
#define DHT11_SIGNAL_OUT     FM4_GPIO->PDORF_f.P7  

/**
 * @brief DHT11 IO configuration pin, which is connected to PF7 of FM4.
 */
#define DHT11_SIGNAL_IO      FM4_GPIO->DDRF_f.P7 

/**
 * @brief DHT11 data in pin, which is connected to PF7 of FM4.
 */
#define DHT11_SIGNAL_IN      FM4_GPIO->PDIRF_f.P7      


/**
 *             User button (SW2 User, connected to pin 128 of FM4)
 */

/**
 * @brief The port that is connected to the user button
 */
#define USER_BUTTON_PORT 2

/**
 * @brief The pin within USER_BUTTON_PORT that is connected to the user button
 */
#define USER_BUTTON_PIN 0

/**
 * @brief Data-direction register of user button.
 * Set to 0 at program start to configure as input pin.
 */
#define USER_BUTTON_IO FM4_GPIO->DDR2_f.P0

/**
 * @brief Data input register of user button
 * Contains 0 if button is pressed and 1 if button is not pressed.
 */
#define USER_BUTTON_DATA FM4_GPIO->PDIR2_f.P0

/**
 *             Multicon interface test pin connceted to P32 of FM4
 */

/**
 * @brief Mutlicon interface test pin IO configuration port.
 */
#define TEST_PIN_MULTICON_DDR FM4_GPIO->DDR3
/**
 * @brief Mutlicon interface test pin pullup configuration port.
 */
#define TEST_PIN_MULTICON_PCR FM4_GPIO->PCR3

/**
 * @brief Mutlicon interface test pin input data port.
 */
#define TEST_PIN_MULTICON_DIR FM4_GPIO->PDIR3

/**
 * @brief Mutlicon interface test pin number.
 */
#define TEST_PIN_MULTICON_PIN 0x02

#endif
