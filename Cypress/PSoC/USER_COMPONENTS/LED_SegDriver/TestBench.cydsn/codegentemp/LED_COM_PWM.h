/*******************************************************************************
* File Name: LED_COM_PWM.h  
* Version 2.10
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

#if !defined(CY_PWM_LED_COM_PWM_H)
#define CY_PWM_LED_COM_PWM_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define LED_COM_PWM_Resolution 8u
#define LED_COM_PWM_UsingFixedFunction 0u
#define LED_COM_PWM_DeadBandMode 0u
#define LED_COM_PWM_KillModeMinTime 0u
#define LED_COM_PWM_KillMode 0u
#define LED_COM_PWM_PWMMode 0u
#define LED_COM_PWM_PWMModeIsCenterAligned 0u
#define LED_COM_PWM_DeadBandUsed 0u
#define LED_COM_PWM_DeadBand2_4 0u
#if !defined(LED_COM_PWM_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define LED_COM_PWM_UseStatus 1u
#else
    #define LED_COM_PWM_UseStatus 0u
#endif
#if !defined(LED_COM_PWM_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define LED_COM_PWM_UseControl 1u
#else
    #define LED_COM_PWM_UseControl 0u
#endif
#define LED_COM_PWM_UseOneCompareMode 1u
#define LED_COM_PWM_MinimumKillTime 1u
#define LED_COM_PWM_EnableMode 0u

#define LED_COM_PWM_CompareMode1SW 0u
#define LED_COM_PWM_CompareMode2SW 0u

/* PSoC3 ES2 or early */
#define LED_COM_PWM_PSOC3_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES1 or early */
#define LED_COM_PWM_PSOC5_ES1   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* PSoC3 ES3 or later */
#define LED_COM_PWM_PSOC3_ES3   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                     (CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* PSoC5 ES2 or later */
#define LED_COM_PWM_PSOC5_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

/* Use Kill Mode Enumerated Types */
#define LED_COM_PWM__B_PWM__DISABLED 0
#define LED_COM_PWM__B_PWM__ASYNCHRONOUS 1
#define LED_COM_PWM__B_PWM__SINGLECYCLE 2
#define LED_COM_PWM__B_PWM__LATCHED 3
#define LED_COM_PWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define LED_COM_PWM__B_PWM__DBMDISABLED 0
#define LED_COM_PWM__B_PWM__DBM_2_4_CLOCKS 1
#define LED_COM_PWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define LED_COM_PWM__B_PWM__ONE_OUTPUT 0
#define LED_COM_PWM__B_PWM__TWO_OUTPUTS 1
#define LED_COM_PWM__B_PWM__DUAL_EDGE 2
#define LED_COM_PWM__B_PWM__CENTER_ALIGN 3
#define LED_COM_PWM__B_PWM__DITHER 5
#define LED_COM_PWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define LED_COM_PWM__B_PWM__LESS_THAN 1
#define LED_COM_PWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define LED_COM_PWM__B_PWM__GREATER_THAN 3
#define LED_COM_PWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define LED_COM_PWM__B_PWM__EQUAL 0
#define LED_COM_PWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/

/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct LED_COM_PWM_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!LED_COM_PWM_UsingFixedFunction)
        #if (LED_COM_PWM_PSOC3_ES2 || LED_COM_PWM_PSOC5_ES1)
            uint8 PWMUdb;               /* PWM Current Counter value  */
            uint8 PWMPeriod;            /* PWM Current Period value   */
            #if (LED_COM_PWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            #if(LED_COM_PWM_UseOneCompareMode)
                uint8 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint8 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint8 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif
            
            /* Backup for Deadband parameters */
            #if(LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_256_CLOCKS || LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(LED_COM_PWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
            
        #endif
        
        #if (LED_COM_PWM_PSOC3_ES3 || LED_COM_PWM_PSOC5_ES2)
            uint8 PWMUdb;               /* PWM Current Counter value  */
            #if(!LED_COM_PWM_PWMModeIsCenterAligned)
                uint8 PWMPeriod;
            #endif
            #if (LED_COM_PWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif
            
            /* Backup for Deadband parameters */
            #if(LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_256_CLOCKS || LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(LED_COM_PWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
        #endif
        
        
        /* Backup control register */
        #if(LED_COM_PWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif
        
    #endif 
   
}LED_COM_PWM_backupStruct;

/***************************************
*        Function Prototypes
 **************************************/
 
void    LED_COM_PWM_Start(void);
void    LED_COM_PWM_Stop(void) ;
#if (LED_COM_PWM_UseStatus || LED_COM_PWM_UsingFixedFunction)
    #define LED_COM_PWM_SetInterruptMode(interruptMode) CY_SET_REG8(LED_COM_PWM_STATUS_MASK_PTR, interruptMode)
    #define LED_COM_PWM_ReadStatusRegister() CY_GET_REG8(LED_COM_PWM_STATUS_PTR)
#endif
#define LED_COM_PWM_GetInterruptSource() LED_COM_PWM_ReadStatusRegister()
#if (LED_COM_PWM_UseControl)
    #define LED_COM_PWM_ReadControlRegister() CY_GET_REG8(LED_COM_PWM_CONTROL_PTR) 
    #define LED_COM_PWM_WriteControlRegister(control) CY_SET_REG8(LED_COM_PWM_CONTROL_PTR, control)
#endif
#if (LED_COM_PWM_UseOneCompareMode)
   #if (LED_COM_PWM_CompareMode1SW)
       void    LED_COM_PWM_SetCompareMode(uint8 comparemode) ;
   #endif
#else
    #if (LED_COM_PWM_CompareMode1SW)
        void    LED_COM_PWM_SetCompareMode1(uint8 comparemode) ;
    #endif
    #if (LED_COM_PWM_CompareMode2SW)
        void    LED_COM_PWM_SetCompareMode2(uint8 comparemode) ;
    #endif
#endif

#if (!LED_COM_PWM_UsingFixedFunction)
    uint8   LED_COM_PWM_ReadCounter(void) ;
    #define LED_COM_PWM_ReadCapture() CY_GET_REG8(LED_COM_PWM_CAPTURE_LSB_PTR)
    #if (LED_COM_PWM_UseStatus)
        void LED_COM_PWM_ClearFIFO(void) ;
    #endif
#endif

void    LED_COM_PWM_WriteCounter(uint8 counter) ;
void    LED_COM_PWM_WritePeriod(uint8 period) ;
#define LED_COM_PWM_ReadPeriod() CY_GET_REG8(LED_COM_PWM_PERIOD_LSB_PTR) 
#if (LED_COM_PWM_UseOneCompareMode)
    void    LED_COM_PWM_WriteCompare(uint8 compare) ;
    #define LED_COM_PWM_ReadCompare() CY_GET_REG8(LED_COM_PWM_COMPARE1_LSB_PTR) 
#else
    void    LED_COM_PWM_WriteCompare1(uint8 compare) ;
    #define LED_COM_PWM_ReadCompare1() CY_GET_REG8(LED_COM_PWM_COMPARE1_LSB_PTR) 
    void    LED_COM_PWM_WriteCompare2(uint8 compare) ;
    #define LED_COM_PWM_ReadCompare2() CY_GET_REG8(LED_COM_PWM_COMPARE2_LSB_PTR) 
#endif


#if (LED_COM_PWM_DeadBandUsed)
    void    LED_COM_PWM_WriteDeadTime(uint8 deadtime) ;
    uint8   LED_COM_PWM_ReadDeadTime(void) ;
#endif

#if ( LED_COM_PWM_KillModeMinTime)
    #define LED_COM_PWM_WriteKillTime(killtime) CY_SET_REG8(LED_COM_PWM_KILLMODEMINTIME_PTR, killtime) 
    #define LED_COM_PWM_ReadKillTime() CY_GET_REG8(LED_COM_PWM_KILLMODEMINTIME_PTR) 
#endif

void LED_COM_PWM_Init(void) ;
void LED_COM_PWM_Enable(void) ;
void LED_COM_PWM_Sleep(void);
void LED_COM_PWM_Wakeup(void) ;
void LED_COM_PWM_SaveConfig(void);
void LED_COM_PWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define LED_COM_PWM_INIT_PERIOD_VALUE        255u
#define LED_COM_PWM_INIT_COMPARE_VALUE1      127u
#define LED_COM_PWM_INIT_COMPARE_VALUE2      63u
#define LED_COM_PWM_INIT_INTERRUPTS_MODE     ((0u << LED_COM_PWM_STATUS_TC_INT_EN_MASK_SHIFT) | (0 << LED_COM_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT) | (0 << LED_COM_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT ) | (0 << LED_COM_PWM_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define LED_COM_PWM_DEFAULT_COMPARE2_MODE    (1u << LED_COM_PWM_CTRL_CMPMODE2_SHIFT)
#define LED_COM_PWM_DEFAULT_COMPARE1_MODE    (1u << LED_COM_PWM_CTRL_CMPMODE1_SHIFT)
#define LED_COM_PWM_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (LED_COM_PWM_UsingFixedFunction)
   #define LED_COM_PWM_PERIOD_LSB          (*(reg16 *) LED_COM_PWM_PWMHW__PER0)
   #define LED_COM_PWM_PERIOD_LSB_PTR      ( (reg16 *) LED_COM_PWM_PWMHW__PER0)
   #define LED_COM_PWM_COMPARE1_LSB        (*(reg16 *) LED_COM_PWM_PWMHW__CNT_CMP0)
   #define LED_COM_PWM_COMPARE1_LSB_PTR    ( (reg16 *) LED_COM_PWM_PWMHW__CNT_CMP0)
   #define LED_COM_PWM_COMPARE2_LSB        0x00u
   #define LED_COM_PWM_COMPARE2_LSB_PTR    0x00u
   #define LED_COM_PWM_COUNTER_LSB         (*(reg16 *) LED_COM_PWM_PWMHW__CNT_CMP0)
   #define LED_COM_PWM_COUNTER_LSB_PTR     ( (reg16 *) LED_COM_PWM_PWMHW__CNT_CMP0)
   #define LED_COM_PWM_CAPTURE_LSB         (*(reg16 *) LED_COM_PWM_PWMHW__CAP0)
   #define LED_COM_PWM_CAPTURE_LSB_PTR     ( (reg16 *) LED_COM_PWM_PWMHW__CAP0)
   #define LED_COM_PWM_RT1                 (*(reg8 *)  LED_COM_PWM_PWMHW__RT1)
   #define LED_COM_PWM_RT1_PTR             ( (reg8 *)  LED_COM_PWM_PWMHW__RT1)
      
#else
   #if(LED_COM_PWM_PWMModeIsCenterAligned)
       #define LED_COM_PWM_PERIOD_LSB      (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define LED_COM_PWM_PERIOD_LSB_PTR   ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
   #else
       #define LED_COM_PWM_PERIOD_LSB      (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #define LED_COM_PWM_PERIOD_LSB_PTR   ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
   #endif
   #define LED_COM_PWM_COMPARE1_LSB    (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
   #define LED_COM_PWM_COMPARE1_LSB_PTR ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
   #define LED_COM_PWM_COMPARE2_LSB    (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
   #define LED_COM_PWM_COMPARE2_LSB_PTR ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
   #define LED_COM_PWM_COUNTERCAP_LSB   *(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define LED_COM_PWM_COUNTERCAP_LSB_PTR ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define LED_COM_PWM_COUNTER_LSB     (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
   #define LED_COM_PWM_COUNTER_LSB_PTR  ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
   #define LED_COM_PWM_CAPTURE_LSB     (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
   #define LED_COM_PWM_CAPTURE_LSB_PTR  ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
   #define LED_COM_PWM_AUX_CONTROLDP0      (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define LED_COM_PWM_AUX_CONTROLDP0_PTR  ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #if (LED_COM_PWM_Resolution == 16)
       #define LED_COM_PWM_AUX_CONTROLDP1    (*(reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define LED_COM_PWM_AUX_CONTROLDP1_PTR  ((reg8 *) LED_COM_PWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
   #endif
#endif
   
#if(LED_COM_PWM_KillModeMinTime )
    #define LED_COM_PWM_KILLMODEMINTIME      (*(reg8 *) LED_COM_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define LED_COM_PWM_KILLMODEMINTIME_PTR   ((reg8 *) LED_COM_PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif

#if(LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_256_CLOCKS)
    #define LED_COM_PWM_DEADBAND_COUNT        (*(reg8 *) LED_COM_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LED_COM_PWM_DEADBAND_COUNT_PTR     ((reg8 *) LED_COM_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LED_COM_PWM_DEADBAND_LSB_PTR       ((reg8 *) LED_COM_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define LED_COM_PWM_DEADBAND_LSB          (*(reg8 *) LED_COM_PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(LED_COM_PWM_DeadBandMode == LED_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (LED_COM_PWM_UsingFixedFunction)
        #define LED_COM_PWM_DEADBAND_COUNT        (*(reg8 *) LED_COM_PWM_PWMHW__CFG0) 
        #define LED_COM_PWM_DEADBAND_COUNT_PTR     ((reg8 *) LED_COM_PWM_PWMHW__CFG0)
        #define LED_COM_PWM_DEADBAND_COUNT_MASK    (0x03u << LED_COM_PWM_DEADBAND_COUNT_SHIFT) 
        #define LED_COM_PWM_DEADBAND_COUNT_SHIFT   0x06u /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */ 
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define LED_COM_PWM_DEADBAND_COUNT        (*(reg8 *) LED_COM_PWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define LED_COM_PWM_DEADBAND_COUNT_PTR     ((reg8 *) LED_COM_PWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define LED_COM_PWM_DEADBAND_COUNT_MASK    (0x03u << LED_COM_PWM_DEADBAND_COUNT_SHIFT) 
        #define LED_COM_PWM_DEADBAND_COUNT_SHIFT   0x00u /* As defined by the verilog implementation of the Control Register */
    #endif
#endif



#if (LED_COM_PWM_UsingFixedFunction)
    #define LED_COM_PWM_STATUS                (*(reg8 *) LED_COM_PWM_PWMHW__SR0)
    #define LED_COM_PWM_STATUS_PTR            ((reg8 *) LED_COM_PWM_PWMHW__SR0)
    #define LED_COM_PWM_STATUS_MASK           (*(reg8 *) LED_COM_PWM_PWMHW__SR0)
    #define LED_COM_PWM_STATUS_MASK_PTR       ((reg8 *) LED_COM_PWM_PWMHW__SR0)
    #define LED_COM_PWM_CONTROL               (*(reg8 *) LED_COM_PWM_PWMHW__CFG0)
    #define LED_COM_PWM_CONTROL_PTR           ((reg8 *) LED_COM_PWM_PWMHW__CFG0)    
    #define LED_COM_PWM_CONTROL2              (*(reg8 *) LED_COM_PWM_PWMHW__CFG1)    
    #if(LED_COM_PWM_PSOC3_ES3 || LED_COM_PWM_PSOC5_ES2)
        #define LED_COM_PWM_CONTROL3              (*(reg8 *) LED_COM_PWM_PWMHW__CFG2)
    #endif
    #define LED_COM_PWM_GLOBAL_ENABLE         (*(reg8 *) LED_COM_PWM_PWMHW__PM_ACT_CFG)
    #define LED_COM_PWM_GLOBAL_ENABLE_PTR       ( (reg8 *) LED_COM_PWM_PWMHW__PM_ACT_CFG)
    #define LED_COM_PWM_GLOBAL_STBY_ENABLE      (*(reg8 *) LED_COM_PWM_PWMHW__PM_STBY_CFG)
    #define LED_COM_PWM_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) LED_COM_PWM_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/
    /* Fixed Function Block Chosen */
    #define LED_COM_PWM_BLOCK_EN_MASK          LED_COM_PWM_PWMHW__PM_ACT_MSK
    #define LED_COM_PWM_BLOCK_STBY_EN_MASK     LED_COM_PWM_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define LED_COM_PWM_CTRL_ENABLE_SHIFT      0x00u
    
    #if(LED_COM_PWM_PSOC3_ES2 || LED_COM_PWM_PSOC5_ES1)
        #define LED_COM_PWM_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif
    #if(LED_COM_PWM_PSOC3_ES3 || LED_COM_PWM_PSOC5_ES2)
        #define LED_COM_PWM_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif
    
    #define LED_COM_PWM_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define LED_COM_PWM_CFG0_MODE              0x02u   /*  Set to compare mode */
    //#define LED_COM_PWM_CFG0_ENABLE            0x01u   /* Enable the block to run */
    #define LED_COM_PWM_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define LED_COM_PWM_CTRL_ENABLE            (0x01u << LED_COM_PWM_CTRL_ENABLE_SHIFT)
    #define LED_COM_PWM_CTRL_RESET             (0x01u << LED_COM_PWM_CTRL_RESET_SHIFT)
    #define LED_COM_PWM_CTRL_CMPMODE2_MASK     (0x07u << LED_COM_PWM_CTRL_CMPMODE2_SHIFT)
    #if(LED_COM_PWM_PSOC3_ES2 || LED_COM_PWM_PSOC5_ES1)
        #define LED_COM_PWM_CTRL_CMPMODE1_MASK     (0x07u << LED_COM_PWM_CTRL_CMPMODE1_SHIFT)
    #endif
    #if(LED_COM_PWM_PSOC3_ES3 || LED_COM_PWM_PSOC5_ES2)
        #define LED_COM_PWM_CTRL_CMPMODE1_MASK     (0x07u << LED_COM_PWM_CTRL_CMPMODE1_SHIFT)
    #endif
    
    /* Control2 Register Bit Masks */
    #define LED_COM_PWM_CTRL2_IRQ_SEL_SHIFT    0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LED_COM_PWM_CTRL2_IRQ_SEL          (0x01u << LED_COM_PWM_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define LED_COM_PWM_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define LED_COM_PWM_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define LED_COM_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define LED_COM_PWM_STATUS_TC_INT_EN_MASK_SHIFT            (LED_COM_PWM_STATUS_TC_SHIFT - 4)
    #define LED_COM_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define LED_COM_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (LED_COM_PWM_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define LED_COM_PWM_STATUS_TC              (0x01u << LED_COM_PWM_STATUS_TC_SHIFT)
    #define LED_COM_PWM_STATUS_CMP1            (0x01u << LED_COM_PWM_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define LED_COM_PWM_STATUS_TC_INT_EN_MASK              (LED_COM_PWM_STATUS_TC >> 4)
    #define LED_COM_PWM_STATUS_CMP1_INT_EN_MASK            (LED_COM_PWM_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define LED_COM_PWM_RT1_SHIFT              0x04u
    #define LED_COM_PWM_RT1_MASK               (0x03u << LED_COM_PWM_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define LED_COM_PWM_SYNC                   (0x03u << LED_COM_PWM_RT1_SHIFT)
    #define LED_COM_PWM_SYNCDSI_SHIFT          0x00u
    #define LED_COM_PWM_SYNCDSI_MASK           (0x0Fu << LED_COM_PWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define LED_COM_PWM_SYNCDSI_EN             (0x0Fu << LED_COM_PWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define LED_COM_PWM_STATUS                (*(reg8 *) LED_COM_PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define LED_COM_PWM_STATUS_PTR            ((reg8 *) LED_COM_PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define LED_COM_PWM_STATUS_MASK           (*(reg8 *) LED_COM_PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define LED_COM_PWM_STATUS_MASK_PTR       ((reg8 *) LED_COM_PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define LED_COM_PWM_STATUS_AUX_CTRL       (*(reg8 *) LED_COM_PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define LED_COM_PWM_CONTROL               (*(reg8 *) LED_COM_PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define LED_COM_PWM_CONTROL_PTR           ((reg8 *) LED_COM_PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/
    /* Control Register definitions */
    #define LED_COM_PWM_CTRL_ENABLE_SHIFT      0x07u
    #define LED_COM_PWM_CTRL_RESET_SHIFT       0x06u
    #define LED_COM_PWM_CTRL_CMPMODE2_SHIFT    0x03u
    #define LED_COM_PWM_CTRL_CMPMODE1_SHIFT    0x00u
    #define LED_COM_PWM_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define LED_COM_PWM_CTRL_ENABLE            (0x01u << LED_COM_PWM_CTRL_ENABLE_SHIFT)
    #define LED_COM_PWM_CTRL_RESET             (0x01u << LED_COM_PWM_CTRL_RESET_SHIFT)
    #define LED_COM_PWM_CTRL_CMPMODE2_MASK     (0x07u << LED_COM_PWM_CTRL_CMPMODE2_SHIFT)
    #define LED_COM_PWM_CTRL_CMPMODE1_MASK     (0x07u << LED_COM_PWM_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define LED_COM_PWM_STATUS_KILL_SHIFT          0x05u
    #define LED_COM_PWM_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define LED_COM_PWM_STATUS_FIFOFULL_SHIFT      0x03u  
    #define LED_COM_PWM_STATUS_TC_SHIFT            0x02u
    #define LED_COM_PWM_STATUS_CMP2_SHIFT          0x01u
    #define LED_COM_PWM_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LED_COM_PWM_STATUS_KILL_INT_EN_MASK_SHIFT          LED_COM_PWM_STATUS_KILL_SHIFT          
    #define LED_COM_PWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    LED_COM_PWM_STATUS_FIFONEMPTY_SHIFT    
    #define LED_COM_PWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      LED_COM_PWM_STATUS_FIFOFULL_SHIFT        
    #define LED_COM_PWM_STATUS_TC_INT_EN_MASK_SHIFT            LED_COM_PWM_STATUS_TC_SHIFT            
    #define LED_COM_PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          LED_COM_PWM_STATUS_CMP2_SHIFT          
    #define LED_COM_PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          LED_COM_PWM_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define LED_COM_PWM_STATUS_KILL            (0x00u << LED_COM_PWM_STATUS_KILL_SHIFT )
    #define LED_COM_PWM_STATUS_FIFOFULL        (0x01u << LED_COM_PWM_STATUS_FIFOFULL_SHIFT)
    #define LED_COM_PWM_STATUS_FIFONEMPTY      (0x01u << LED_COM_PWM_STATUS_FIFONEMPTY_SHIFT)
    #define LED_COM_PWM_STATUS_TC              (0x01u << LED_COM_PWM_STATUS_TC_SHIFT)
    #define LED_COM_PWM_STATUS_CMP2            (0x01u << LED_COM_PWM_STATUS_CMP2_SHIFT) 
    #define LED_COM_PWM_STATUS_CMP1            (0x01u << LED_COM_PWM_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LED_COM_PWM_STATUS_KILL_INT_EN_MASK            LED_COM_PWM_STATUS_KILL
    #define LED_COM_PWM_STATUS_FIFOFULL_INT_EN_MASK        LED_COM_PWM_STATUS_FIFOFULL
    #define LED_COM_PWM_STATUS_FIFONEMPTY_INT_EN_MASK      LED_COM_PWM_STATUS_FIFONEMPTY
    #define LED_COM_PWM_STATUS_TC_INT_EN_MASK              LED_COM_PWM_STATUS_TC
    #define LED_COM_PWM_STATUS_CMP2_INT_EN_MASK            LED_COM_PWM_STATUS_CMP2
    #define LED_COM_PWM_STATUS_CMP1_INT_EN_MASK            LED_COM_PWM_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define LED_COM_PWM_AUX_CTRL_FIFO0_CLR     0x01u
    #define LED_COM_PWM_AUX_CTRL_FIFO1_CLR     0x02u
    #define LED_COM_PWM_AUX_CTRL_FIFO0_LVL     0x04u
    #define LED_COM_PWM_AUX_CTRL_FIFO1_LVL     0x08u
    #define LED_COM_PWM_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* LED_COM_PWM_UsingFixedFunction */

#endif  /* CY_PWM_LED_COM_PWM_H */
