//
//  pins.h
//  Makros for the MCU pins
//
//  @author Puria Izady
//
//

#ifndef pins_h
#define pins_h

#define OLD_DESIGN 0x00
#define NEW_DESIGN 0x01

#define LCD_DESIGN NEW_DESIGN

#define LCD_DATA FM4_GPIO->PDOR1LL  // LCD_DATA


#define LCD_DATA_IO FM4_GPIO->DDR1 // LCD_DATA_IO
                       
#if (LCD_DESIGN == OLD_DESIGN)
  #define LCD_RD   FM4_GPIO->PDOR4_f.P1  // LCD_RD => P41
  #define LCD_RS   FM4_GPIO->PDOR4_f.P0  // LCD_RS => P40
#elif (LCD_DESIGN == NEW_DESIGN)
  #define LCD_RD   FM4_GPIO->PDOR4_f.P4  // LCD_RD => P44
  #define LCD_RS   FM4_GPIO->PDOR4_f.P5  // LCD_RS => P45
#endif

#define LCD_WR   FM4_GPIO->PDORF_f.P0  // LCD_WR => PF0
#define LCD_CD   FM4_GPIO->PDORF_f.P1  // LCD_CD => PF1    
#define LCD_CS   FM4_GPIO->PDOR7_f.PD  // LCD_CS => P7D

#if (LCD_DESIGN == OLD_DESIGN)
  #define LCD_RD_IO   FM4_GPIO->DDR4_f.P1  // LCD_RD => P41
  #define LCD_RS_IO   FM4_GPIO->DDR4_f.P0  // LCD_RS => P40
#elif (LCD_DESIGN == NEW_DESIGN)
  #define LCD_RD_IO   FM4_GPIO->DDR4_f.P4  // LCD_RD => P44
  #define LCD_RS_IO   FM4_GPIO->DDR4_f.P5  // LCD_RS => P45
#endif

#define LCD_WR_IO   FM4_GPIO->DDRF_f.P0  // LCD_WR => PF0    
#define LCD_CD_IO   FM4_GPIO->DDRF_f.P1  // LCD_CD => PF1
#define LCD_CS_IO   FM4_GPIO->DDR7_f.PD  // LCD_CS => P7D


// TOUCH SIGNALE LCD
#define TOUCH_XM    FM4_GPIO->PDOR1_f.PB // TOUCH_XM => P1B / A11
#define TOUCH_XP    FM4_GPIO->PDOR7_f.PB // TOUCH_XP => P7B
#define TOUCH_YM    FM4_GPIO->PDORF_f.P6 // TOUCH_YM => PF6
#define TOUCH_YP    FM4_GPIO->PDOR1_f.PC // TOUCH_YP => P1C / A12

#define TOUCH_XM_IO FM4_GPIO->DDR1_f.PB  // TOUCH_XM => P1B / A11
#define TOUCH_XP_IO FM4_GPIO->DDR7_f.PB  // TOUCH_XP => P7B 
#define TOUCH_YM_IO FM4_GPIO->DDRF_f.P6  // TOUCH_YM => PF6
#define TOUCH_YP_IO FM4_GPIO->DDR1_f.PC  // TOUCH_YP => P1C / A12

// JOYSTICK ANALOG PINS
#define JS1_X_IO    FM4_GPIO->DDRB_f.P0 // A16
#define JS1_Y_IO    FM4_GPIO->DDRB_f.P3 // A19
#define JS1_D_IO    FM4_GPIO->DDRF_f.P5 // JS1_D => PF5
#define JS2_X_IO    FM4_GPIO->DDR1_f.PD // A13 
#define JS2_Y_IO    FM4_GPIO->DDRB_f.P7 // A23

#define JS1_X    FM4_GPIO->PDORB_f.P0 // JS1_X => PB0
#define JS1_Y    FM4_GPIO->PDORB_f.P3 // JS1_Y => PB3
#define JS1_D    FM4_GPIO->PDORF_f.P5 // JS1_D => PF5
#define JS2_X    FM4_GPIO->PDOR1_f.PD // JS2_X => P1D
#define JS2_Y    FM4_GPIO->PDORB_f.P7 // JS2_Y => PB7


// DHT11 Pin
#define DHT11_SIGNAL_OUT     FM4_GPIO->PDORF_f.P7   // PF7 PIN 75
#define DHT11_SIGNAL_IO      FM4_GPIO->DDRF_f.P7        // PF7 PIN 75
#define DHT11_SIGNAL_IN      FM4_GPIO->PDIRF_f.P7       // PF7 PIN 75

// RGB LED pins
#define LED_RED_DDR FM4_GPIO->DDR1   // Data direction register.
#define LED_RED_DOR FM4_GPIO->PDOR1  // Data output register.
#define LED_RED_PIN 0x0A             // Pin number.

#define LED_GREEN_DDR FM4_GPIO->DDRB
#define LED_GREEN_DOR FM4_GPIO->PDORB
#define LED_GREEN_PIN 0x02

#define LED_BLUE_DDR FM4_GPIO->DDR1
#define LED_BLUE_DOR FM4_GPIO->PDOR1
#define LED_BLUE_PIN 0x08

// Joystick button pins
#define BUTTON_LEFT_DDR FM4_GPIO->DDRF  // Data direction register.
#define BUTTON_LEFT_PCR FM4_GPIO->PCRF  // Pullup configuration register.
#define BUTTON_LEFT_DIR FM4_GPIO->PDIRF // Data input register.
#define BUTTON_LEFT_PIN 0x05            // Pin number.

#define BUTTON_RIGHT_DDR FM4_GPIO->DDRF
#define BUTTON_RIGHT_PCR FM4_GPIO->PCRF
#define BUTTON_RIGHT_DIR FM4_GPIO->PDIRF
#define BUTTON_RIGHT_PIN 0x03

#define TEST_PIN_MULTICON_DDR FM4_GPIO->DDR3
#define TEST_PIN_MULTICON_PCR FM4_GPIO->PCR3
#define TEST_PIN_MULTICON_DIR FM4_GPIO->PDIR3
#define TEST_PIN_MULTICON_PIN 0x02

#endif /* pins_h */
