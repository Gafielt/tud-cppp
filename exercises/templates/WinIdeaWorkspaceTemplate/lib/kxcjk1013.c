/*******************************************************************************
* \file             kxcjk1013.c
* 
* \version          1.00
*
* \brief            This file provides source code to the API for the KXCJK1013 
*                   accelerometer driver.
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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "kxcjk1013.h"

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
#if !defined(SetPinFunc_SOT8_1) || !defined(SetPinFunc_SCK8_1)
#error SOT8_1 or SCK8_1 is not available on this product, please use other \
pins or channels and detele "me".
#endif

#define I2C_RET_OK                      KXCJK1013_RET_OK
#define I2C_RET_ERROR                   KXCJK1013_RET_ERROR

#define KXCJK1013_DEV_ADDR              (0x0Eu)
#define KXCJK1013_DEV_ADDR_W            ((KXCJK1013_DEV_ADDR << 1u) | 0u)
#define KXCJK1013_DEV_ADDR_R            ((KXCJK1013_DEV_ADDR << 1u) | 1u)

#define KXCJK1013_WHO_AM_I_CODE         0x11

#define KXCJK1013_DCST_RESP_CODE_55     0x55
#define KXCJK1013_DCST_RESP_CODE_AA     0xAA

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/
volatile stc_mfsn_i2c_t* I2cCh = &I2C8;
fnc_kxcjk1013_callback_t CallBack = NULL;

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/

/*******************************************************************************
* Function Name: I2c_Start
********************************************************************************
* Config the start condition
*
* \param Addr   The Slave address
*
* \return I2C_RET_ERROR  The start condition not generated or Slave address wasn't
*                        appended by ACK                            
* \return I2C_RET_OK     The start condition generated, and the Slave address 
*                        match and ACK generated
*******************************************************************************/
static uint8_t I2c_Start(uint8_t Addr)
{
    /* Prepare I2C device address */
    Mfs_I2c_SendData(I2cCh, Addr);
    
    /* Generate I2C start signal */
    if(Ok != Mfs_I2c_GenerateStart(I2cCh))
    {
        return I2C_RET_ERROR; /* Timeout or other error */
    }

    while(1)
    {
        if(TRUE != Mfs_I2c_GetStatus(I2cCh, I2cRxTxIrq))
        {
            break;
        }
    }
   
    if(I2cNAck == Mfs_I2c_GetAck(I2cCh))
    {
        return I2C_RET_ERROR;   /* NACK */
    }
    
    if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cBusErr))
    {
        return I2C_RET_ERROR; /* Bus error occurs? */
    }
    
    if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cOverrunError))
    {
        return I2C_RET_ERROR; /* Overrun error occurs? */
    }
   
    return I2C_RET_OK;
}

/*******************************************************************************
* Function Name: I2c_ReStart
********************************************************************************
* Config the repeated start condition
*
* \param Addr   The Slave address
*
* \return I2C_RET_ERROR  The repeated start condition not generated or Slave address
*                        wasn't appended by ACK                            
* \return I2C_RET_OK     The repeated start condition generated, and the Slave address 
*                        match and ACK generated
*******************************************************************************/
static uint8_t I2c_ReStart(uint8_t Addr)
{
    /* Prepare I2C device address */
    Mfs_I2c_SendData(I2cCh, Addr);
    
    /* Generate I2C start signal */
    if(Ok != Mfs_I2c_GenerateRestart(I2cCh))
    {
        return I2C_RET_ERROR; /* Timeout or other error */
    }

    while(1)
    {
        if(TRUE != Mfs_I2c_GetStatus(I2cCh, I2cRxTxIrq))
        {
            break;
        }
    }
   
    if(I2cNAck == Mfs_I2c_GetAck(I2cCh))
    {
        return I2C_RET_ERROR;   /* NACK */
    }
    
    if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cBusErr))
    {
        return I2C_RET_ERROR; /* Bus error occurs? */
    }
    
    if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cOverrunError))
    {
        return I2C_RET_ERROR; /* Overrun error occurs? */
    }
   
    return I2C_RET_OK;
}

/*******************************************************************************
* Function Name: I2c_Write
********************************************************************************
* Transmit the dedicated size data to device
*
* \param  pTxData Transmit data pointer
*
* \param  u8Size the number of transmitted data
*
* \return I2C_RET_ERROR  The error uccured during transmission
* \return I2C_RET_OK     The transmission is succesfully ended
*******************************************************************************/
static uint8_t I2c_Write(uint8_t *pTxData, uint8_t u8Size)
{
    uint8_t i;
    
    for(i=0; i<u8Size; i++)
    {
        /* Transmit the data */
        Mfs_I2c_SendData(I2cCh, pTxData[i]);
        Mfs_I2c_ClrStatus(I2cCh, I2cRxTxIrq);
        
        /* Wait for end of transmission */
        while(1)
        {
            if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cRxTxIrq))
            {
                break;
            }
        }
        
        while(1)
        {
            if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cTxEmpty))
            {
                break;
            }
        }
       
        if(I2cNAck == Mfs_I2c_GetAck(I2cCh))
        {
            return I2C_RET_ERROR;   /* NACK */
        }
        
        if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cBusErr))
        {
            return I2C_RET_ERROR; /* Bus error occurs? */
        }
        
        if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cOverrunError))
        {
            return I2C_RET_ERROR; /* Overrun error occurs? */
        }
    }
    
    return I2C_RET_OK;
}

/*******************************************************************************
* Function Name: I2c_Read
********************************************************************************
* Receive the dedicated size data to device
*
* \param  pRxData The receive buffer pointer
*
* \param  u8Size The number of receiving data
*
* \return I2C_RET_ERROR  The error uccured during reception
* \return I2C_RET_OK     The reception is succesfully ended
*******************************************************************************/
static uint8_t I2c_Read(uint8_t *pRxData, uint8_t u8Size)
{
    uint8_t i = 0;
    
    /* Clear interrupt flag generated by device address send */
    Mfs_I2c_ClrStatus(I2cCh, I2cRxTxIrq);
    
    if(I2cNAck == Mfs_I2c_GetAck(I2cCh))
    {
        return I2C_RET_ERROR;   /* NACK */
    }
    
    while(i < u8Size)
    {   
        /* Wait for the receive data */
        while(1)
        {
            if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cRxTxIrq))
            {
                break;
            }
        }
        
        if(i == u8Size-1)
        {
            Mfs_I2c_ConfigAck(I2cCh, I2cNAck); /* Last byte send a NACK */
        }
        else
        {
            Mfs_I2c_ConfigAck(I2cCh, I2cAck);
        }
        
        /* Clear interrupt flag and receive data to RX buffer */
        Mfs_I2c_ClrStatus(I2cCh, I2cRxTxIrq);
        
        /* Wait for the receive data */
        while(1)
        {
            if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cRxFull))
            {
                break;
            }
        }
         
        if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cBusErr))
        {
            return I2C_RET_ERROR;   /* Bus error occurs? */
        }
        
        if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cOverrunError))
        {
            return I2C_RET_ERROR;  /* Overrun error occurs? */
        }
        
        pRxData[i++] = Mfs_I2c_ReceiveData(I2cCh);
    }
    return I2C_RET_OK;
}

/*******************************************************************************
* Function Name: I2c_Stop
********************************************************************************
* Config the stop condition
*
* \return I2C_RET_ERROR Stop condition is unsuccesfully generated
* \return I2C_RET_OK    Stop condition is succesfully generated
*******************************************************************************/
static uint8_t I2c_Stop(void)
{
    /* Generate I2C start signal */
    if(Ok != Mfs_I2c_GenerateStop(I2cCh))
    {
        return I2C_RET_ERROR; /* Timeout or other error */
    }
    /* Clear Stop condition flag */
    while(1)
    {
        if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cStopDetect))
        {
            break;
        }
    }
   
    if(TRUE == Mfs_I2c_GetStatus(I2cCh, I2cBusErr))
    {
        return I2C_RET_ERROR;
    }
   
    Mfs_I2c_ClrStatus(I2cCh, I2cStopDetect);
    Mfs_I2c_ClrStatus(I2cCh, I2cRxTxIrq);
    
    return I2C_RET_OK;
}

/**
 ******************************************************************************
 ** \brief KXCJK1013_ExtInt11Callback callback function
 ******************************************************************************/
void KXCJK1013_ExtInt11Callback(void)
{
    uint16_t buf;
    
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_INT_SOURCE1, (uint8_t*)&buf, 2 ) ){
    }
    
    if( CallBack != NULL ){
        CallBack((en_kxcjk1013_interrupt_source_t)buf);
    }
    
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_INT_REL, (uint8_t*)&buf, 1 ) ){
    }
    
    
}

/*******************************************************************************
* Function Name: Kxcjk1013_Init
********************************************************************************
* Initialize KXCJK1013
*
* \return KXCJK1013_RET_ERROR KXCJK1013 is unsuccesfully initialized
* \return KXCJK1013_RET_OK    KXCJK1013 is succesfully initialized
*******************************************************************************/
uint8_t Kxcjk1013_Init(stc_kxcjk1013_output_performance_config_t *config)
{
    stc_mfs_i2c_config_t stcI2cConfig;
    stc_exint_config_t stcExintConfig;
    uint8_t buf;
    
    if( config == NULL ) return KXCJK1013_RET_ERROR;

    /* Configure SCK and SDA pins for I2C communications */
    SetPinFunc_SOT8_1();
    SetPinFunc_SCK8_1();
    
    /* Configure I2C as a master */
    stcI2cConfig.enMsMode = I2cMaster;
    stcI2cConfig.u32BaudRate = 400000u;
    stcI2cConfig.bWaitSelection = FALSE;
    stcI2cConfig.bDmaEnable = FALSE;
    stcI2cConfig.pstcFifoConfig = NULL;
    
    if( Ok != Mfs_I2c_Init(I2cCh, &stcI2cConfig) ){
        return KXCJK1013_RET_ERROR;
    }

    // Digital Communication Self Test
    if( KXCJK1013_RET_OK != Kxcjk1013_DigitalCommunicationSelfTest() ){
        return KXCJK1013_RET_ERROR;
    }
    
    // Reset the device
    if( KXCJK1013_RET_OK != Kxcjk1013_Reset() ){
        return KXCJK1013_RET_ERROR;
    }

    // Configure the output performance of the device
    buf = config->odr;
    if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_DATA_CTRL_REG, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    buf = ((uint8_t)config->res) | ((uint8_t)config->range);
    if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_CTRL_REG1, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    if(config->int_config != NULL){
        // Configure Interrupt
        if((config->int_config->callback == NULL) || (config->int_config->src == 0x0000)){
            return KXCJK1013_RET_ERROR;
        }
        
        // Set Call Back Function
        CallBack = config->int_config->callback;
        
        // Enable Data Ready interrupt and/or Wakeup interrupt
        if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG1, &buf, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
        if(((config->int_config->src)&Kxcjk1013IntSource_WakeUp) == Kxcjk1013IntSource_WakeUp){
            buf |= 0x02;
        }        
        if(((config->int_config->src)&Kxcjk1013IntSource_DataReady) == Kxcjk1013IntSource_DataReady){
            buf |= 0x20;
        }
        if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_CTRL_REG1, &buf, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
        
        // Configure axis and direction of motion detections
        buf = (uint8_t)((((uint16_t)(config->int_config->src))>>8) & 0x00FF);
        if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_INT_CTRL_REG2, &buf, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
        
        // Configure phyisical interrupt pin - enable the pin, active high, cleared by reading INT_REL
        buf = 0x30;
        if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_INT_CTRL_REG1, &buf, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
        
        SetPinFunc_INT11_1(0u);
		
        /* Configure interrupt ch.11 */
        PDL_ZERO_STRUCT(stcExintConfig);
    
        /* Before initialize external interrupt ch.11, make sure 
        * PDL_PERIPHERAL_ENABLE_EXINT11 is set to PDL_ON in pdl_user.h
        * If external interrupt ch.11 is not used, set PDL_PERIPHERAL_ENABLE_EXINT11 
        * to PDL_OFF !! Otherwise, the external interrupt ch.11 may be mis-enabled. */
        stcExintConfig.abEnable[ExintInstanceIndexExint11] = 1u;
        stcExintConfig.aenLevel[ExintInstanceIndexExint11] = ExIntRisingEdge;
        stcExintConfig.apfnExintCallback[ExintInstanceIndexExint11] = KXCJK1013_ExtInt11Callback;
        stcExintConfig.bTouchNvic = TRUE;
        
        Exint_Init(&stcExintConfig);
    
    }
    
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_Reset
********************************************************************************
* Reset KXCJK1013 device
*
* \return KXCJK1013_RET_ERROR  The error uccured
* \return KXCJK1013_RET_OK     The software is succesfully completed
*******************************************************************************/
uint8_t Kxcjk1013_Reset(void)
{
    uint8_t buf;
    uint32_t i;
    
    // Read CTRL_REG2 register
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG2, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    // Set SRST bit in CTRL_REG2 register
    buf |= 0x80;
    if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_CTRL_REG2, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    for(i=0; i<50000; i++ );
    
    // Wait for clearing the SRST bit
    do{
      if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG2, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
      }
    }while( (buf&0x80)==0x80 );
            
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_WriteRegisters
********************************************************************************
* Write the dedicated size data to KXCJK1013 registers
*
* \param  addr the first address of the registers to be written
*
* \param  pTxData Transmit data pointer
*
* \param  u8Size the number of transmitted data
*
* \return KXCJK1013_RET_ERROR  The error uccured during transmission
* \return KXCJK1013_RET_OK     The transmission is succesfully ended
*******************************************************************************/
uint8_t Kxcjk1013_WriteRegisters(en_kxcjk1013_reg_t addr, uint8_t *pTxData, uint8_t u8Size)
{
    /* I2C Master Write data */
    if( Ok != I2c_Start(KXCJK1013_DEV_ADDR_W) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Write((uint8_t *)&addr, 1) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Write(pTxData, u8Size) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Stop() ){ return KXCJK1013_RET_ERROR; };
    
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_ReadRegisters
********************************************************************************
* Read the dedicated size data from KXCJK1013 registers
*
* \param  addr the first address of the registers to be read
*
* \param  pRxData The receive buffer pointer
*
* \param  u8Size The number of receiving data
*
* \return KXCJK1013_RET_ERROR  The error uccured during reception
* \return KXCJK1013_RET_OK     The reception is succesfully ended
*******************************************************************************/
uint8_t Kxcjk1013_ReadRegisters(en_kxcjk1013_reg_t addr, uint8_t *pRxData, uint8_t u8Size)
{
    /* I2C Master Write data */
    if( Ok != I2c_Start(KXCJK1013_DEV_ADDR_W) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Write((uint8_t *)&addr, 1) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_ReStart(KXCJK1013_DEV_ADDR_R) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Read(pRxData, u8Size) ){ return KXCJK1013_RET_ERROR; };
    if( Ok != I2c_Stop() ){ return KXCJK1013_RET_ERROR; };
        
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_SetOperationMode
********************************************************************************
* Set or Clear PC1 bit of CTRL_REG1 of KXCJK1013 device
*
* \param  mode 0 = stand-by mode, 1 = operating mode
*
* \return KXCJK1013_RET_ERROR  The error uccured
* \return KXCJK1013_RET_OK     The device is succesfully configured
*******************************************************************************/
uint8_t Kxcjk1013_SetOperationMode(en_kxcjk1013_operating_mode_t mode)
{
    uint8_t buf;
    
    // Read CTRL_REG1 register
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG1, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    if( mode == Kxcjk1013NormalMode ){
        // Set PC1 bit
        buf |= Kxcjk1013NormalMode;
    }else if( mode == Kxcjk1013StandbyMode ){
        // Clear PC1 bit
        buf &= ~Kxcjk1013NormalMode;
    }else{
      return KXCJK1013_RET_ERROR;
    }
        
    // Write CTRL_REG1 register
    if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_CTRL_REG1, &buf, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_GetOperationMode
********************************************************************************
* Read PC1 bit of CTRL_REG1 of KXCJK1013 device and return operation mode
*
* \return KXCJK1013_STANDBY_MODE    stand-by mode
* \return KXCJK1013_OPERATING_MODE  operating mode
*******************************************************************************/
en_kxcjk1013_operating_mode_t Kxcjk1013_GetOperationMode(void)
{
    en_kxcjk1013_operating_mode_t mode = Kxcjk1013StandbyMode;
    
    // Read CTRL_REG1 register
    if( KXCJK1013_RET_OK == Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG1, (uint8_t*)&mode, 1 ) ){
        if( (mode & Kxcjk1013NormalMode) == Kxcjk1013NormalMode ){
            mode = Kxcjk1013NormalMode;
        }else{
            mode = Kxcjk1013StandbyMode;
        }
    }

    return mode;
}

/*******************************************************************************
* Function Name: Kxcjk1013_DigitalCommunicationSelfTest
********************************************************************************
* Run Digital Communication Self Test of KXCJK1013 device
*
* \return KXCJK1013_RET_ERROR  The error uccured
* \return KXCJK1013_RET_OK     The self test is succesfully completed
*******************************************************************************/
uint8_t Kxcjk1013_DigitalCommunicationSelfTest(void)
{
    uint8_t buf;
    uint8_t ctrl_reg2;
    int i;
    
    // Confirm if the I2C communication is available or not.
    // Read WHO_AM_I register to test the I2C communication
    if( KXCJK1013_RET_OK == Kxcjk1013_ReadRegisters( Kxcjk1013Reg_WHO_AM_I, &buf, 1 ) ){
        if(buf != KXCJK1013_WHO_AM_I_CODE) return KXCJK1013_RET_ERROR;
    }else{
        return KXCJK1013_RET_ERROR;
    }

    // Set the operation mode to Stand-by mode
    if( Kxcjk1013NormalMode ==  Kxcjk1013_GetOperationMode() ){
      if( KXCJK1013_RET_OK != Kxcjk1013_SetOperationMode( Kxcjk1013StandbyMode ) ){
          return KXCJK1013_RET_ERROR;
      }
    }
        
    // Read CTRL_REG2 register to test the I2C communication
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_CTRL_REG2, &ctrl_reg2, 1 ) ){
        return KXCJK1013_RET_ERROR;
    }

    // Do the test twice.
    for(i=0; i<2; i++ ){
        // Read DCST_RESP register
        if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_DCST_RESP, &buf, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
        
        // Check DCST bit in the CTRL_REG2 register
        if( (ctrl_reg2&0x10)==0x10){
            if(buf != KXCJK1013_DCST_RESP_CODE_AA) return KXCJK1013_RET_ERROR;
            ctrl_reg2 &= ~(0x10);
        }else{
            if(buf != KXCJK1013_DCST_RESP_CODE_55) return KXCJK1013_RET_ERROR;
            ctrl_reg2 |= 0x10;
        }
        
        if( KXCJK1013_RET_OK != Kxcjk1013_WriteRegisters( Kxcjk1013Reg_CTRL_REG2, &ctrl_reg2, 1 ) ){
            return KXCJK1013_RET_ERROR;
        }
    }
    
    return KXCJK1013_RET_OK;
}

/*******************************************************************************
* Function Name: Kxcjk1013_GetAccelerations
********************************************************************************
* Read accleration registers
*
* \param  x_out pointer to buffer for acceleration data of X axis
* \param  y_out pointer to buffer for acceleration data of Y axis
* \param  z_out pointer to buffer for acceleration data of Z axis
*
* \return KXCJK1013_RET_ERROR  The error uccured
* \return KXCJK1013_RET_OK     Accelerations are successfully aquired.
*******************************************************************************/
uint8_t Kxcjk1013_GetAccelerations(int16_t *x_out, int16_t *y_out, int16_t *z_out)
{
    int16_t buf[3];
    
    // Read Acceleration registers
    if( KXCJK1013_RET_OK != Kxcjk1013_ReadRegisters( Kxcjk1013Reg_XOUT_L, (uint8_t*)buf, 6 ) ){
        return KXCJK1013_RET_ERROR;
    }

    *x_out = buf[0];
    *y_out = buf[1];
    *z_out = buf[2];
    
    return KXCJK1013_RET_OK;
}


/* [] END OF FILE */
