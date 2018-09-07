#include "mcu.h"
#include "kxcjk1013.h"

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
static int16_t AccelerationData[NUM_OF_AXIS];
static int16_t Sensitivity[NUM_OF_AXIS];
static uint8_t ResolutionShifter;

static uint8_t data_available = 0;
static uint8_t operation_mode = NORMAL_OPERATION_MODE;
static uint8_t display_accelerations = 0;

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/
void interrupt_callback(en_kxcjk1013_interrupt_source_t src);

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

/*******************************************************************************
* Function Name: SampleRtcHalfSecondCb
*******************************************************************************/
static void SampleRtcHalfSecondCb(void);

/**
 ******************************************************************************
 ** InitSubClock
 ******************************************************************************/
int InitSubClock(void);

/**
 ******************************************************************************
 ** InitRTC function
 ******************************************************************************/
int InitRTC(void);

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
 ** DisplayAccelerations on CPPP Board LCD
 ******************************************************************************/
void cppp_printAccelerationSensorOnLCD(float x_out, float y_out, float z_out);

/**
 ******************************************************************************
 ** Debug X,Y,Z values of the acceleration sensor and calibrate the sensor through a serialport terminal
 ******************************************************************************/
int cppp_debugAccelerationSensor(void);