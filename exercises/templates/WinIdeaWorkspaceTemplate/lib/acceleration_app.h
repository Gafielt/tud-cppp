#ifndef ACCELERATION_APP_H
#define ACCELERATION_APP_H

/**
* @file acceleration_app.h
* @brief <strong> Initializes communication via I2C to the KXCJK1013 accelerometer chip and prints data on the lc display.
* UART is used to print data on the serial port terminal and NMI is used for the user button.
* For more informations about the accelerometer chip read here: http://kionixfs.kionix.com/en/datasheet/KXCJK-1013%20Specifications%20Rev%202.pdf
* If you want to the the accelerometer just use the following code example. </strong>  
* <pre>
#include "init.h"
#include "acceleration_app.h"
int main(){
 initBoard();
 cppp_testAccelerationSensor();
 return 0;
}
* </pre>
*/
#include "mcu.h"
#include "acceleration_core.h"

#define NORMAL_OPERATION_MODE                   0x00
#define CALIBRATION_READ_POSITIVE_X_MODE        0x01
#define CALIBRATION_READ_NEGATIVE_X_MODE        0x02
#define CALIBRATION_READ_POSITIVE_Y_MODE        0x03
#define CALIBRATION_READ_NEGATIVE_Y_MODE        0x04
#define CALIBRATION_READ_POSITIVE_Z_MODE        0x05
#define CALIBRATION_READ_NEGATIVE_Z_MODE        0x06

#define NUM_OF_AXIS                             3
#define ACCELERATION_AXIS_X                     0x00
#define ACCELERATION_AXIS_Y                     0x01
#define ACCELERATION_AXIS_Z                     0x02

#define GET_RAW_DATA                            0x00
#define GET_MOVING_AVERAGE_256                  0x01

/**
* @brief If defined in cppp_testAccelerationSensor x,y,z orientation values will be printed on the LC display. 
*/
#define PRINT_ACCELERATION_SENSOR_ON_LCD        0x01


unsigned long cppp_delayAccelerationSensor;
unsigned int cppp_counter;

int16_t cppp_accelerationData[NUM_OF_AXIS];
int16_t cppp_sensitivity[NUM_OF_AXIS];
uint8_t cppp_resolutionShifter;

uint8_t cppp_accelerationDataAvailable;
uint8_t cppp_operationMode;
uint8_t cppp_displayAccelerations;

/**
* @brief Initializes the accelerometer.
* @param void
* @return return 1 if initialization was succesfull else 0
*/
int cppp_initAccelerometer(void);


/**
* @brief Reads the x,y,z acceleration values from the accelerometer.
* @param data adress to the array, where the x,y,z acceleration values will be written to
* @return void
*/
int cppp_getAcceleration( int16_t *data );

/**
* @brief Callback function for KXCJK1013 interrupt routines.
* @param src interrupt configuration struct
* @return void
*/
void cppp_AccelerationInterruptCallback(en_kxcjk1013_interrupt_source_t src);

/**
* @brief NMI callback function.
* @param void
* @return void
*/
void cppp_accelerationNMICallback(void);

/**
* @brief Initializes NMI for the push button which is used for calibration process.
* @param void
* @return 0
*/
int cppp_accelerationInitNmi(void);

/**
* @brief Displays x,y,z acceleration values on the serial interface.
* @param x_out x axis acceleration
* @param y_out y axis acceleration
* @param z_out z axis acceleration
* @return 0
*/
int cppp_displayAccelerationsSerialInterface(float x_out, float y_out, float z_out);

/**
* @brief Displays x,y,z degrees on the serial interface.
* @param x_deg x acceleration degree
* @param y_deg y acceleration degree
* @param z_deg z acceleration degree
* @return 0
*/
int cppp_displayPositionMap(float x_deg, float y_deg, float z_deg);


/**
* @brief Initializes UART, I2C and NMI activate accelerometer and serial interface. 
  The serial interface UART is used to print informations on the terminal.
* @param void
* @return void
*/
void cppp_initAccelerometerPrequisites(void);


/**
* @brief Prints the x,y,z orientation on the LC display. 
* @param x_out x axis acceleration
* @param y_out y axis acceleration
* @param z_out z axis acceleration
* @return void
*/
void cppp_printAccelerationsLcd(float x_out, float y_out, float z_out);
                                                               
/**
* @brief  Prints X,Y,Z values of the acceleration sensor and calibrate the sensor through a serialport terminal.
* @param void
* @return void
*/
int cppp_testAccelerationSensor(void);


#endif