#include "delay.h"
#include "s6e2ccxj.h"

/**
* @brief  Initialise the BT RLT mode, One-Shot mode, No IRQ
* @param  u32us Delay time in microseconds
* @return void
*/
static void InitBtRLT_Reg(uint32_t u32us);

/**
* @brief  Wait the number of microseconds what has previously setup by function InitBtRLT_Reg()
* @param  void
* @return void
*/
static void BtRLT_Delay(void);

void cppp_microDelay(uint32_t timeInMicroseconds) {
      InitBtRLT_Reg(timeInMicroseconds);
      BtRLT_Delay();
}

static void InitBtRLT_Reg(uint32_t timeInMicroseconds) {
  FM_BT0_RT->TMCR  = 0x0000; // Stop BT0
  FM_BT0_RT->TMCR  = 0x10b4; // PCLK/4, 32bit reload timer mode, one-shot
  FM_BT0_RT->TMCR2 = 0x0000; // CKS3 = 0;
  FM_BT0_RT->STC   = 0x0000; // No Interrupts used
 
  const uint32_t u32ticks = timeInMicroseconds * 50;   // Timer Clock = 200MHz / 4 = 50MHz --> Ticks = Time[us] * 50
 
  FM_BT1_RT->PCSR = (u32ticks & 0xffff0000) >> 16; // Set duration (Upper) 
  FM_BT0_RT->PCSR = u32ticks & 0x0000ffff;         // Set duration (Lower) 
}

static void BtRLT_Delay()   {
  // Wait for the number of µs
  FM_BT0_RT->TMCR |= 0x0003;    // Start Base Timer
 
  while (!bFM_BT0_RT_STC_UDIR); // Busy waiting for Base Timer underflow
  bFM_BT0_RT_STC_UDIR = 0;      // Clear Underflow-Flag
}