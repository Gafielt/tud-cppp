#ifndef ACCELERATION_APP_H
#define ACCELERATION_APP_H

#include "mcu.h"
#include "acceleration_core.h"

unsigned long delayAccelerationSensor;
unsigned int counter;

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
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

#define PRINT_ACCELERATION_SENSOR_ON_LCD        0x01

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/
int16_t cppp_accelerationData[NUM_OF_AXIS];
int16_t cppp_sensitivity[NUM_OF_AXIS];
uint8_t cppp_resolutionShifter;

uint8_t cppp_accelerationDataAvailable;
uint8_t cppp_operationMode;
uint8_t cppp_displayAccelerations;

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/

/**
 ******************************************************************************
 ** InitAccelerometer function
 ******************************************************************************/
int InitAccelerometer(void);
/**
 ******************************************************************************
 ** GetAcceleration function
 ******************************************************************************/
int GetAcceleration( int16_t *data );

/**
 ******************************************************************************
 ** callback function for get KXCJK1013 interrupt
 ******************************************************************************/
void interrupt_callback(en_kxcjk1013_interrupt_source_t src);

/**
 ******************************************************************************
 ** NMI callback function
 ******************************************************************************/
void Main_NmiCallback(void);

/**
 ******************************************************************************
 ** InitNMI function
 ******************************************************************************/
int InitNMI(void);

/**
 ******************************************************************************
 ** DisplayAccelerations function
 ******************************************************************************/
int DisplayAccelerations(float x_out, float y_out, float z_out);

/**
 ******************************************************************************
 ** DisplayAccelerations function
 ******************************************************************************/
int DisplayPositionMap(float x_deg, float y_deg, float z_deg);


/**
 ******************************************************************************
 ** DisplayAccelerations function
 ******************************************************************************/
void cppp_initAcceleration();


/**
 ******************************************************************************
 ** DisplayAccelerations on CPPP Board LCD
 ******************************************************************************/
void cppp_printAccelerationSensorOnLCD(float x_out, float y_out, float z_out);

/**
 ******************************************************************************
 ** Prints X,Y,Z values of the acceleration sensor and calibrate the sensor through a serialport terminal
 ******************************************************************************/
int cppp_testAccelerationSensor(void);


#endif