/******************************************************************************/
/** \file interrupts.c
 **
 ** PDL Interrupt Handler Inclusion for PDL
 **
 ** A detailed description is available at 
 ** @link PdlInterrupts PDL Interrupt handling description @endlink
 **
 ** History:
 **   - 2015-06-17  1.0  MWi   First version for universal PDL        
 **   - 2015-11-12  1.1  ACEH  Update build process, added Cypress Disclaimer 
 **
 ******************************************************************************/
 
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "pdl.h"

#if (PDL_MCU_CORE == PDL_FM0P_CORE)

  #if (PDL_MCU_INT_TYPE == PDL_FM0P_INT_TYPE_1_A)
    #define   __INTERRUPTS_FM0P_TYPE_1_A_C__
    #include  "interrupts_fm0p_type_1-a.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM0P_INT_TYPE_1_B)
    #define   __INTERRUPTS_FM0P_TYPE_1_B_C__
    #include  "interrupts_fm0p_type_1-b.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM0P_INT_TYPE_2_A)
    #define   __INTERRUPTS_FM0P_TYPE_2_A_C__
    #include  "interrupts_fm0p_type_2-a.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM0P_INT_TYPE_2_B)
    #define   __INTERRUPTS_FM0P_TYPE_2_B_C__
    #include  "interrupts_fm0p_type_2-b.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM0P_INT_TYPE_3)
    #define   __INTERRUPTS_FM0P_TYPE_3_C__
    #include  "interrupts_fm0p_type_3.c"

  #else
    #error Interrupt Type for FM0P not defined!
  #endif

#elif (PDL_MCU_CORE == PDL_FM3_CORE)

  #if (PDL_MCU_INT_TYPE == PDL_FM3_INT_TYPE_A)
    #define   __INTERRUPTS_FM3_TYPE_A_C__
    #include  "interrupts_fm3_type_a.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM3_INT_TYPE_B)
    #define   __INTERRUPTS_FM3_TYPE_B_C__
    #include  "interrupts_fm3_type_b.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM3_INT_TYPE_C)
    #define   __INTERRUPTS_FM3_TYPE_C_C__
    #include  "interrupts_fm3_type_c.c"

  #else
    #error Interrupt Type for FM3 not defined!
  #endif

#elif (PDL_MCU_CORE == PDL_FM4_CORE)

  #if (PDL_MCU_INT_TYPE == PDL_FM4_INT_TYPE_A)
    #define   __INTERRUPTS_FM4_TYPE_A_C__
    #include  "interrupts_fm4_type_a.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM4_INT_TYPE_B)
    #define   __INTERRUPTS_FM4_TYPE_B_C__
    #include  "interrupts_fm4_type_b.c"

  #elif (PDL_MCU_INT_TYPE == PDL_FM4_INT_TYPE_C)
    #define   __INTERRUPTS_FM4_TYPE_C_C__
    #include  "interrupts_fm4_type_c.c"

  #else
    #error Interrupt Type for FM4 not defined!
  #endif


#else
    #error FM core not defined!
#endif

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
