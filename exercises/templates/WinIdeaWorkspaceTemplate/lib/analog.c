#include "pdl_header.h"
#include "pins.h"
#include "analog.h"


void cppp_initAdc(void){
  // declare configuration structures
  stc_adc_config_t stcConfig;   // ADC configuration
  stc_adc_scan_t   stcScanCfg;  // Scan configuration
  
  // Clear the structures
  PDL_ZERO_STRUCT(stcConfig);
  PDL_ZERO_STRUCT(stcScanCfg);
     
  stcScanCfg.u32ScanCannelSelect.AD_CH_17 = 1u;  // Analog Input -> Light Sensor
  stcConfig.u32SamplingTimeSelect.AD_CH_17 = 1u; // Channel 17 uses sample time 1
    
  
  stcScanCfg.u32ScanCannelSelect.AD_CH_11 = 1u;  // Analog Input -> TOUCH X-
  stcConfig.u32SamplingTimeSelect.AD_CH_11 = 1u; // 
     
  stcScanCfg.u32ScanCannelSelect.AD_CH_12 = 1u;  // Analog Input -> TOUCH Y+
  stcConfig.u32SamplingTimeSelect.AD_CH_12 = 1u; // 
    
  stcScanCfg.u32ScanCannelSelect.AD_CH_13 = 1u;  // Analog Input -> J2 X
  stcConfig.u32SamplingTimeSelect.AD_CH_13 = 1u; // 

  stcScanCfg.u32ScanCannelSelect.AD_CH_16 = 1u;  // Analog Input -> Joystick1 X
  stcConfig.u32SamplingTimeSelect.AD_CH_16 = 1u; // JS1 X uses sample time 1
    
  stcScanCfg.u32ScanCannelSelect.AD_CH_19 = 1u;  // Analog Input -> J1 Y
  stcConfig.u32SamplingTimeSelect.AD_CH_19 = 1u; // 
    
  stcScanCfg.u32ScanCannelSelect.AD_CH_23 = 1u;  // Analog Input -> J2Y
  stcConfig.u32SamplingTimeSelect.AD_CH_23 = 1u; // 
   
  
  stcScanCfg.enScanMode = ScanSingleConversion;
  stcScanCfg.enScanTimerTrigger = AdcNoTimer;
  stcScanCfg.bScanTimerStartEnable = FALSE;
  stcScanCfg.u8ScanFifoDepth = 6u;  // CHANGED 

  // ADC Configuration
  stcConfig.bLsbAlignment = TRUE;                // least significant bit alignment

  stcConfig.enSamplingTimeN0 = Value4;           // sample time 0 multiplier
  stcConfig.u8SamplingTime0 = 3u;                // sample time 0 base
  stcConfig.enSamplingTimeN1 = Value8;           // sample time 1 multiplier
  stcConfig.u8SamplingTime1 = 10u;               // sample time 1 base
  stcConfig.u8ComparingClockDiv = 10u;           // clock divisor is 12
  stcConfig.pstcScanInit = &stcScanCfg;          // address of scan config structure
  stcConfig.pstcPrioInit = NULL;                 // no priority scans
  stcConfig.pstcComparisonInit = NULL;           // no comparison
  stcConfig.pstcRangeComparisonInit = NULL;      // no range
  stcConfig.pstcIrqEn = NULL;                    // no interrupts
  stcConfig.pstcIrqCb = NULL;                    // no interrupts
  stcConfig.bTouchNvic = FALSE;                  // not using NVIC

  // Initialize and Start ADC
  if(Ok != Adc_Init(&ADC0, &stcConfig))
  {
    while(1)                    // catch an error
    {}
  }  
  
  Adc_EnableWaitReady(&ADC0);  // Enable ADC0 and wait until ready
  
  return;
}

void cppp_adcPollData(uint32_t *u32Data){
  // Wait for ADC data to receive.
  do
  {
    // Read ADC Value
    *u32Data = Adc_ReadScanFifo(&ADC0);
  
    // check if data is valid
  } while(AdcFifoDataValid != Adc_GetScanDataValid(&ADC0, *u32Data)); 
}


void cppp_getAnalogValues(uint8_t *analog11, uint8_t *analog12, uint8_t *analog13, uint8_t *analog16, uint8_t *analog17,  uint8_t *analog19, uint8_t *analog23){
  uint32_t u32Data = 0u;     // 32 Bit Data buffer for measurements
  
  // Start single ADC Scan 
  Adc_SwTriggerScan(&ADC0);

  uint8_t i = 0;
  for(i = 0; i<7; i++){
    cppp_adcPollData(&u32Data);
    // extract the ADC value from the data
    switch(i){
      case 0: *analog11 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 1: *analog12 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 2: *analog23 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 3: *analog19 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 4: *analog17 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 5: *analog16 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
      case 6: *analog13 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
        break;
    }
  }
}

uint16_t cppp_mapValueRange(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max){
  uint32_t result =  (x - in_min); // * (out_max - out_min) / (in_max - in_min) + out_min;
  result *= (out_max - out_min);
  result /= (in_max - in_min); 
  result += out_min;
  return result; 
}

uint16_t cppp_readTouchX(void){
  TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
  TOUCH_XM_IO = 1u;   // pinMode(_xm, OUTPUT);
  bFM4_GPIO_ADE_AN11 = 0u; // ANALOG 11 OFF
  TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
  TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
  TOUCH_XP_IO = 0u;   // pinMode(_xp, INPUT);
  TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
  
  bFM4_GPIO_ADE_AN12 = 0u;   // ANALOG12 OFF
  TOUCH_YP_IO = 1u;   // pinMode(_yp, OUTPUT);
  TOUCH_YP = 1u;      // digitalWrite(_yp, HIGH);
  TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
  TOUCH_YM = 0u;      // digitalWrite(_ym, LOW);
  bFM4_GPIO_ADE_AN11 = 1u; // ANALOG 11 ON
  
  
  /**
   * DOUBLE SAMPLING
   */
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  uint16_t i = 0;
  uint16_t samples[2];
  for(i=0; i<2; i++){
    cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
    samples[i] = analog11;
  }
  if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
    return 500;
  } else {
    samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
  } 
  uint8_t xCorrected = TOUCHXMAX + TOUCHXMIN - samples[1];
  uint16_t result = cppp_mapValueRange(xCorrected, TOUCHXMIN, TOUCHXMAX, 0, 480);
  return result;
}


uint16_t cppp_readTouchY(void){
  TOUCH_YP_IO = 1u;   //    pinMode(_yp, OUTPUT);
  TOUCH_YM_IO = 1u;   //    pinMode(_ym, OUTPUT);
  bFM4_GPIO_ADE_AN12 = 0u;  // ANALOG 12 OFF
  TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
  TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);
  TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
  TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);
  
  TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
  TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
  TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
  bFM4_GPIO_ADE_AN11 = 0u; // Xm/P16 ANALOG OFF
  TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
  bFM4_GPIO_ADE_AN12 = 1u;   // ANALOG 12 ON 
  
  /**
   * DOUBLE SAMPLING
   */
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  uint16_t i = 0;
  uint16_t samples[2];
  for(i=0; i<2; i++){
    cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
    samples[i] = analog12;
  }
  if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
    return 500;
  } else {
    samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
  } 
  uint8_t yCorrected = TOUCHYMAX + TOUCHYMIN - samples[1];
  uint16_t result = cppp_mapValueRange(yCorrected, TOUCHYMIN, TOUCHYMAX, 0, 320);
  return result;
}

uint16_t cppp_readTouchZ(void){
  //uint16_t rXPlate = 248;  // Resistance between X+ and X-
  
  // Set X+ to ground
  TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
  TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
  
  // Set Y- to VCC
  TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
  TOUCH_YM = 1u;      // digitalWrite(_ym, HIGH);
  
  // Hi-Z X- and Y+
  bFM4_GPIO_ADE_AN11 = 0u; //Xm/Analog 6 OFF
  bFM4_GPIO_ADE_AN12 = 0u; //Yp/Analog 7 OFF
  TOUCH_XM_IO = 1u; // Xm OUTPUT
  TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
  TOUCH_YP = 1u;      // Yp OUTPUT
  TOUCH_YP = 0u;      // digitalWrite(_yp, LOW);
  
  TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
  TOUCH_YP_IO = 0u;   // pinMode(_yp, INPUT);
  bFM4_GPIO_ADE_AN11 = 1u; //Xm/Analog 6 ON
  bFM4_GPIO_ADE_AN12 = 1u; //Yp/Analog 7 ON
  
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  cppp_getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  uint8_t z1 = analog11; // z1 = Xm = analog6
  uint8_t z2 = analog12; // z2 = Ym = analog7 
  return (255-(z2-z1));
}