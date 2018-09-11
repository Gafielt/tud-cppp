#include "acceleration_app.h"
#include "pdl_header.h"
#include <stdio.h> 
#include <string.h> 
#include <math.h>
#include "src\display.h"
#include "gfx.h"

#include "rgb_led.h"



int InitAccelerometer(void)
{
    stc_kxcjk1013_interrupt_config_t            int_config;
    stc_kxcjk1013_output_performance_config_t   config;

    /* Init the Accelerometer KXCJK-1013 */
    int_config.src      = Kxcjk1013IntSource_DataReady;
    int_config.callback = interrupt_callback;
    
    config.res		= Kxcjk1013Resolution12Bit;
    config.range	= Kxcjk1013Acceleration2g;
    config.odr		= Kxcjk1013Osa_200Hz;
    config.int_config   = &int_config;
    
    // Set Default Sensitivity (counts per g)
    if(config.res == Kxcjk1013Resolution12Bit){
        cppp_resolutionShifter = 4;
        switch(config.range){
            case Kxcjk1013Acceleration2g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>1;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>1;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>1;
                break;
            case Kxcjk1013Acceleration4g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>2;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>2;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>2;
                break;
            case Kxcjk1013Acceleration8g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>3;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>3;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>3;
                break;
        }
    } else{
        cppp_resolutionShifter = 8;
        switch(config.range){
            case Kxcjk1013Acceleration2g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7F>>1;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>1;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>1;
                break;
            case Kxcjk1013Acceleration4g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7F>>2;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>2;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>2;
                break;
            case Kxcjk1013Acceleration8g:
                cppp_sensitivity[ACCELERATION_AXIS_X] = 0x7F>>3;
                cppp_sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>3;
                cppp_sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>3;
                break;
        }
    }
    
    if( KXCJK1013_RET_OK != Kxcjk1013_Init(&config) ){
        // Initialization Error
        // Original code was: while(1)
        Kxcjk1013_Reset();
    }
    
    // Set the device to the operating mode
    if( KXCJK1013_RET_OK != Kxcjk1013_SetOperationMode( Kxcjk1013NormalMode ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    return 0;

}


int GetAcceleration( int16_t *data )
{   
    int16_t xout, yout, zout;
    
    if(data == NULL )return (-1);
    
    if( KXCJK1013_RET_OK != Kxcjk1013_GetAccelerations( &xout, &yout, &zout ) ){
        // Register read error
        while(1);
    }

    // Raw data
    data[ACCELERATION_AXIS_X] = xout >> cppp_resolutionShifter;
    data[ACCELERATION_AXIS_Y] = yout >> cppp_resolutionShifter;
    data[ACCELERATION_AXIS_Z] = zout >> cppp_resolutionShifter;
            
    return 0;
}


void interrupt_callback(en_kxcjk1013_interrupt_source_t src){
    cppp_accelerationDataAvailable = 1;
    if( 0 != GetAcceleration( cppp_accelerationData ) ){
        // Register read error
        while(1);
    }
}


void Main_NmiCallback(void)
{
    static int16_t temp;
    
    switch(cppp_operationMode){
        case NORMAL_OPERATION_MODE:
            cppp_operationMode = CALIBRATION_READ_POSITIVE_X_MODE;
            break;
        case CALIBRATION_READ_POSITIVE_X_MODE:
            cppp_operationMode = CALIBRATION_READ_NEGATIVE_X_MODE;
            temp = cppp_accelerationData[ACCELERATION_AXIS_X];
            break;
        case CALIBRATION_READ_NEGATIVE_X_MODE:
            cppp_operationMode = CALIBRATION_READ_POSITIVE_Y_MODE;
            cppp_sensitivity[ACCELERATION_AXIS_X] = (temp - cppp_accelerationData[ACCELERATION_AXIS_X])>>1;
            break;
        case CALIBRATION_READ_POSITIVE_Y_MODE:
            cppp_operationMode = CALIBRATION_READ_NEGATIVE_Y_MODE;
            temp = cppp_accelerationData[ACCELERATION_AXIS_Y];
            break;
        case CALIBRATION_READ_NEGATIVE_Y_MODE:
            cppp_operationMode = CALIBRATION_READ_POSITIVE_Z_MODE;
            cppp_sensitivity[ACCELERATION_AXIS_Y] = (temp - cppp_accelerationData[ACCELERATION_AXIS_Y])>>1;
            break;
        case CALIBRATION_READ_POSITIVE_Z_MODE:
            cppp_operationMode = CALIBRATION_READ_NEGATIVE_Z_MODE;
            temp = cppp_accelerationData[ACCELERATION_AXIS_Z];
            break;
        case CALIBRATION_READ_NEGATIVE_Z_MODE:
            cppp_operationMode = NORMAL_OPERATION_MODE;
            cppp_sensitivity[ACCELERATION_AXIS_Z] = (temp - cppp_accelerationData[ACCELERATION_AXIS_Z])>>1;
            break;      
    }
}

int InitNMI(void)
{
    stc_exint_nmi_config_t                      stcNmiConfig;

    /* Congfigure NMI for "User" Button */
    PDL_ZERO_STRUCT(stcNmiConfig);
    stcNmiConfig.pfnNmiCallback = Main_NmiCallback;
    Exint_Nmi_Init(&stcNmiConfig);
    SetPinFunc_NMIX(0u);                      /* Pin Function: NMIX */
    
    return 0;
}                                                              

int DisplayAccelerations(float x_out, float y_out, float z_out)
{
    printf("\x1b[1;1H");
    switch(cppp_operationMode){
        case NORMAL_OPERATION_MODE:
            printf("\x1b[2K");
            printf("Push User Button to calibrate accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_X_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep X axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_X_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep X axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_Y_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Y axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_Y_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Y axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_Z_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Z axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_Z_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Z axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;      
    }
    printf("\x1b[2K"); printf( "XOUT = % 2.3f [g]\n", x_out );
    printf("\x1b[2K"); printf( "YOUT = % 2.3f [g]\n", y_out );
    printf("\x1b[2K"); printf( "ZOUT = % 2.3f [g]\n", z_out );
    
    return 0;
    
}

int DisplayPositionMap(float x_deg, float y_deg, float z_deg)
{
    static int prev_x, prev_y;
    
    printf("\x1b[%d;%dH ", prev_y, prev_x);
    printf("\x1b[30;64H+");
    printf("\x1b[%d;%dH*", 30 + (int)(y_deg * 16.0f), 64 + (int)(x_deg * 32.0f));
    prev_x = 64 + (int)(x_deg * 32.0f);
    prev_y = 30 + (int)(y_deg * 16.0f);
    
    return 0;
}

void cppp_initAcceleration(){
  
    cppp_accelerationDataAvailable = 0;
    cppp_operationMode = NORMAL_OPERATION_MODE;
    cppp_displayAccelerations = 0;

    /* Initializatio of the UART unit and GPIO used in the communication */
    Uart_Io_Init();
    printf("\r\n Acceleration Sensor Debug ... \r\n");
    
    // Init Accelerometer
    InitAccelerometer();

    // Init NMI for Push Button
    InitNMI();
    
    __enable_irq();
    
    printf("\x1b[?25l\n");
}

void cppp_printAccelerationSensorOnLCD(float x_out, float y_out, float z_out){ 
    setCursor_s(0, 319);
    char freeSpace[] = " ";
    char headlineText[] = "   *** ACCELERATION SENSOR DEBUG ***";
    
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    setTextColor_s(YELLOW);
    writeTextln_s(headlineText);
    setTextColor_s(WHITE);
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeText_s("      X_OUT = ");
    writeFloat(x_out, 4, 10);
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeText_s("      y_OUT = ");
    writeFloat(y_out, 4, 10);
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeText_s("      Z_OUT = ");
    writeFloat(z_out, 4, 10);
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeText_s("      Loop #");
    uint16_t loopNumber = (uint16_t) counter;
    write16BitDigit(&loopNumber, 2);
}

int cppp_testAccelerationSensor(void)
{   
    float x_out, y_out, z_out;
    float x_deg, y_deg, z_deg;
    
    while(1)
    {
      if( cppp_accelerationDataAvailable == 1 ){
  	    x_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_X]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_X];
  	    y_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Y]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Y];
  	    z_out = ((float)((cppp_accelerationData[ACCELERATION_AXIS_Z]))) / (float)cppp_sensitivity[ACCELERATION_AXIS_Z];
  	    
  	    x_deg = (x_out>1.0f?1.0f:(x_out<-1.0f?-1.0f:x_out));
  	    y_deg = (y_out>1.0f?1.0f:(y_out<-1.0f?-1.0f:y_out));
  	    z_deg = (z_out>1.0f?1.0f:(z_out<-1.0f?-1.0f:z_out));
  	    x_deg = asin(x_deg)/(3.141592f/2.0f);
  	    y_deg = asin(y_deg)/(3.141592f/2.0f);
  	    z_deg = asin(z_deg)/(3.141592f/2.0f);
  	    DisplayPositionMap(x_deg, y_deg, z_deg);
        cppp_accelerationDataAvailable = 0;
      }
      delayAccelerationSensor = delayAccelerationSensor + 1;
      if (delayAccelerationSensor > 1000000L)
      {
  			DisplayAccelerations(x_out, y_out, z_out);
        printf("Loop#%05d",counter++);
        delayAccelerationSensor = 0;
        #ifdef PRINT_ACCELERATION_SENSOR_ON_LCD
          cppp_printAccelerationSensorOnLCD(x_out, y_out, z_out);
        #endif
      }        
    } 
}
