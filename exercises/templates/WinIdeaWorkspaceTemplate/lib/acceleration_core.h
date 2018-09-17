#ifndef ACCELERATION_CORE_H
#define ACCELERATION_CORE_H

/**
* @file acceleration_core.h
* @brief <strong>Core function for KXCJK1013 accelerometer chip. These functions are used by acceleration_app.h and
* acceleration.c to implement the accelerometer. If you want to test the accelerometer you should use the function
* cppp_testAccelerationSensor from acceleration_app.h. </strong>
*/
#include "pdl_header.h"

#define KXCJK1013_RET_OK                  0
#define KXCJK1013_RET_ERROR               1

/**
* @brief KXCJK1013 registers I2C addresses based on table 10 on the KXCJK1013 datasheet
*/
typedef enum en_kxcjk1013_reg
{
  /// X axis lowest Bits
  Kxcjk1013Reg_XOUT_L			= 0x06,
  /// X axis highest Bits
  Kxcjk1013Reg_XOUT_H			= 0x07,
  /// Y axis lowest Bits
  Kxcjk1013Reg_YOUT_L			= 0x08,
  /// X axis highest Bits
  Kxcjk1013Reg_YOUT_H			= 0x09,
  /// Z axis lowest Bits
  Kxcjk1013Reg_ZOUT_L			= 0x0A,
  /// X axis highest Bits
  Kxcjk1013Reg_ZOUT_H			= 0x0B,
  Kxcjk1013Reg_DCST_RESP		= 0x0C,

  Kxcjk1013Reg_WHO_AM_I		= 0x0F,

  Kxcjk1013Reg_INT_SOURCE1		= 0x16,
  Kxcjk1013Reg_INT_SOURCE2		= 0x17,
  Kxcjk1013Reg_STATUS_REG		= 0x18,
  
  Kxcjk1013Reg_INT_REL		= 0x1A,
  Kxcjk1013Reg_CTRL_REG1		= 0x1B,

  Kxcjk1013Reg_CTRL_REG2		= 0x1D,
  Kxcjk1013Reg_INT_CTRL_REG1		= 0x1E,
  Kxcjk1013Reg_INT_CTRL_REG2		= 0x1F,

  Kxcjk1013Reg_DATA_CTRL_REG		= 0x21,

  Kxcjk1013Reg_WAKEUP_TIMER		= 0x29,

  Kxcjk1013Reg_SELF_TEST		= 0x3A,

  Kxcjk1013Reg_WAKUP_THRESHOLD	= 0x6A,
} en_kxcjk1013_reg_t;

/**
* @brief Operating mode of the KXCJK1013
*/
typedef enum en_kxcjk1013_operating_mode
{
  Kxcjk1013StandbyMode		= 0x00,
  Kxcjk1013NormalMode			= 0x80,
} en_kxcjk1013_operating_mode_t;

/**
* @brief Resolution mode I2C addresses of the KXCJK1013
*/
typedef enum en_kxcjk1013_resolution_mode
{
  Kxcjk1013Resolution8Bit		= 0x00,
  Kxcjk1013Resolution12Bit		= 0x40,
} en_kxcjk1013_resolution_mode_t;

/**
* @brief Accleration range of the KXCJK1013
*/
typedef enum en_kxcjk1013_acceleration_range
{
  Kxcjk1013Acceleration2g		= 0x00,
  Kxcjk1013Acceleration4g		= 0x08,
  Kxcjk1013Acceleration8g		= 0x10,
} en_kxcjk1013_acceleration_range_t;

typedef enum en_kxcjk1013_odr_for_wakeup
{
	Kxcjk1013Owuf_781mHz		= 0x00,
	Kxcjk1013Owuf_1563mHz		= 0x01,
	Kxcjk1013Owuf_3125mHz		= 0x02,
	Kxcjk1013Owuf_6250mHz		= 0x03,
	Kxcjk1013Owuf_12500mHz		= 0x04,
	Kxcjk1013Owuf_25Hz		= 0x05,
	Kxcjk1013Owuf_50Hz		= 0x06,
	Kxcjk1013Owuf_100Hz		= 0x07,
} en_kxcjk1013_odr_for_wakeup_t;

typedef enum en_kxcjk1013_output_data_rate
{
	Kxcjk1013Osa_781mHz		= 0x08,
	Kxcjk1013Osa_1563mHz		= 0x09,
	Kxcjk1013Osa_3125mHz		= 0x0A,
	Kxcjk1013Osa_6250mHz		= 0x0B,
	Kxcjk1013Osa_12500mHz		= 0x00,
	Kxcjk1013Osa_25Hz		= 0x01,
	Kxcjk1013Osa_50Hz		= 0x02,
	Kxcjk1013Osa_100Hz		= 0x03,
	Kxcjk1013Osa_200Hz		= 0x04,
	Kxcjk1013Osa_400Hz		= 0x05,
	Kxcjk1013Osa_800Hz		= 0x06,
	Kxcjk1013Osa_1600Hz		= 0x07,
} en_kxcjk1013_output_data_rate_t;

typedef enum en_kxcjk1013_interrupt_source
{
  Kxcjk1013IntSource_WakeUp           = 0x0002,
  Kxcjk1013IntSource_DataReady        = 0x0010,
  Kxcjk1013IntSource_ZPositiveReport  = 0x0100,
  Kxcjk1013IntSource_ZNegativeReport  = 0x0200,
  Kxcjk1013IntSource_YPositiveReport  = 0x0400,
  Kxcjk1013IntSource_YNegativeReport  = 0x0800,
  Kxcjk1013IntSource_XPositiveReport  = 0x1000,
  Kxcjk1013IntSource_XNegativeReport  = 0x2000,
} en_kxcjk1013_interrupt_source_t;

typedef void (*fnc_kxcjk1013_callback_t)(en_kxcjk1013_interrupt_source_t src);

typedef struct stc_kxcjk1013_interrupt_config
{
  en_kxcjk1013_interrupt_source_t             src;
  uint8_t                                     wakeup_timer;
  uint8_t                                     wakeup_threshold;
  en_kxcjk1013_odr_for_wakeup_t               wakeup_odr;
  fnc_kxcjk1013_callback_t                    callback;
} stc_kxcjk1013_interrupt_config_t;

typedef struct stc_kxcjk1013_output_performance_config
{
  en_kxcjk1013_resolution_mode_t		    res;
  en_kxcjk1013_acceleration_range_t	    range;
  en_kxcjk1013_output_data_rate_t		    odr;
  stc_kxcjk1013_interrupt_config_t      *int_config;
} stc_kxcjk1013_output_performance_config_t;
                                                                                
/**
* @brief I2C communication initialization of the accelerometer
* @param a Used for important stuff.
* @return KXCJK1013_RET_ERROR KXCJK1013 is unsuccesfully initialized
* @return KXCJK1013_RET_OK    KXCJK1013 is succesfully initialized
*/
uint8_t Kxcjk1013_Init(stc_kxcjk1013_output_performance_config_t *config);

/**
* @brief KXCJK1013_ExtInt11Callback callback function
* @param void
* @return void
*/
void KXCJK1013_ExtInt11Callback(void);

/**
* @brief Reset the KXCJK1013
* @param void
* @return KXCJK1013_RET_ERROR  The error uccured
* @return KXCJK1013_RET_OK     The software is succesfully completed
*/
uint8_t Kxcjk1013_Reset(void);

/**
* @brief Write the dedicated size data to KXCJK1013 registers
* @param  addr the first address of the registers to be written
* @param  pTxData Transmit data pointer
* @param  u8Size the number of transmitted data
* @return KXCJK1013_RET_ERROR  The error uccured during transmission
* @return KXCJK1013_RET_OK     The transmission is succesfully ended
*/
uint8_t Kxcjk1013_WriteRegisters(en_kxcjk1013_reg_t addr, uint8_t *pTxData, uint8_t u8Size);

/**
* @brief Read the dedicated size data from KXCJK1013 registers
* @param  addr the first address of the registers to be read
* @param  pRxData The receive buffer pointer
* @param  u8Size The number of receiving data
* @return KXCJK1013_RET_ERROR  The error uccured during reception
* @return KXCJK1013_RET_OK     The reception is succesfully ended
*/
uint8_t Kxcjk1013_ReadRegisters(en_kxcjk1013_reg_t addr, uint8_t *pRxData, uint8_t u8Size);

/**
* @brief Set or Clear PC1 bit of CTRL_REG1 of KXCJK1013 device
* @param  mode 0 = stand-by mode, 1 = operating mode
* @return KXCJK1013_RET_ERROR  The error uccured
* @return KXCJK1013_RET_OK     The device is succesfully configured
*/
uint8_t Kxcjk1013_SetOperationMode(en_kxcjk1013_operating_mode_t mode);

/**
* @brief Read PC1 bit of CTRL_REG1 of KXCJK1013 device and return operation mode
* @return KXCJK1013_STANDBY_MODE    stand-by mode
* @return KXCJK1013_OPERATING_MODE  operating mode
*/
en_kxcjk1013_operating_mode_t Kxcjk1013_GetOperationMode(void);

/**
* @brief Run Digital Communication Self Test of KXCJK1013 device
* @return KXCJK1013_RET_ERROR  The error uccured
* @return KXCJK1013_RET_OK     The self test is succesfully completed
*/
uint8_t Kxcjk1013_DigitalCommunicationSelfTest(void);

/**
* @brief Read accleration registers
* @param  x_out pointer to buffer for acceleration data of X axis
* @param  y_out pointer to buffer for acceleration data of Y axis
* @param  z_out pointer to buffer for acceleration data of Z axis
* @return KXCJK1013_RET_ERROR  The error uccured
* @return KXCJK1013_RET_OK     Accelerations are successfully aquired.
*/
uint8_t Kxcjk1013_GetAccelerations(int16_t *x_out, int16_t *y_out, int16_t *z_out);

#endif                     