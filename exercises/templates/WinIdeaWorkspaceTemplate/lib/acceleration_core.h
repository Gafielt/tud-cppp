/*******************************************************************************
* \file              kxcjk1013.h
* 
* \version           1.00
*
* \brief             Headerfile for KXCJK1013 functions.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
* CYPRESS PROVIDES THIS SOFTWARE "AS IS" AND MAKES NO WARRANTY
* OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE,
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
* PURPOSE.
*******************************************************************************/

#ifndef ACCELERATION_CORE_H
#define ACCELERATION_CORE_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "pdl_header.h"

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
#define KXCJK1013_RET_OK                  0
#define KXCJK1013_RET_ERROR               1

/* KXCJK1013 Registers */
typedef enum en_kxcjk1013_reg
{
    Kxcjk1013Reg_XOUT_L			= 0x06,
    Kxcjk1013Reg_XOUT_H			= 0x07,
    Kxcjk1013Reg_YOUT_L			= 0x08,
    Kxcjk1013Reg_YOUT_H			= 0x09,
    Kxcjk1013Reg_ZOUT_L			= 0x0A,
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

/* Operating mode of the KXCJK1013 */
typedef enum en_kxcjk1013_operating_mode
{
    Kxcjk1013StandbyMode		= 0x00,
    Kxcjk1013NormalMode			= 0x80,
} en_kxcjk1013_operating_mode_t;

typedef enum en_kxcjk1013_resolution_mode
{
    Kxcjk1013Resolution8Bit		= 0x00,
    Kxcjk1013Resolution12Bit		= 0x40,
} en_kxcjk1013_resolution_mode_t;

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
	en_kxcjk1013_resolution_mode_t		res;
	en_kxcjk1013_acceleration_range_t	range;
	en_kxcjk1013_output_data_rate_t		odr;
        stc_kxcjk1013_interrupt_config_t        *int_config;
} stc_kxcjk1013_output_performance_config_t;

/******************************************************************************/
/* Local type definitions ('typedef')                                         */
/******************************************************************************/

/******************************************************************************/
/* Global variable definitions ('extern')                                     */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes (definition in C source)                        */
/******************************************************************************/
uint8_t Kxcjk1013_Init(stc_kxcjk1013_output_performance_config_t *config);
uint8_t Kxcjk1013_Reset(void);
uint8_t Kxcjk1013_WriteRegisters(en_kxcjk1013_reg_t addr, uint8_t *pTxData, uint8_t u8Size);
uint8_t Kxcjk1013_ReadRegisters(en_kxcjk1013_reg_t addr, uint8_t *pRxData, uint8_t u8Size);
uint8_t Kxcjk1013_SetOperationMode(en_kxcjk1013_operating_mode_t mode);
en_kxcjk1013_operating_mode_t Kxcjk1013_GetOperationMode(void);
uint8_t Kxcjk1013_DigitalCommunicationSelfTest(void);
uint8_t Kxcjk1013_GetAccelerations(int16_t *x_out, int16_t *y_out, int16_t *z_out);

#ifdef __cplusplus
}
#endif

#endif                     