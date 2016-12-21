/*******************************************************************************
* File Name: PWM.h  
* Version 2.20
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

#if !defined(CY_PWM_PWM_H)
#define CY_PWM_PWM_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWM_Resolution 16u
#define PWM_UsingFixedFunction 0u
#define PWM_DeadBandMode 0u
#define PWM_KillModeMinTime 0u
#define PWM_KillMode 0u
#define PWM_PWMMode 0u
#define PWM_PWMModeIsCenterAligned 0u
#define PWM_DeadBandUsed 0u
#define PWM_DeadBand2_4 0u
#if !defined(PWM_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define PWM_UseStatus 1u
#else
    #define PWM_UseStatus 0u
#endif /* !defined(PWM_PWMUDB_sSTSReg_stsreg__REMOVED) */
#if !defined(PWM_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define PWM_UseControl 1u
#else
    #define PWM_UseControl 0u
#endif /* !defined(PWM_PWMUDB_sCTRLReg_ctrlreg__REMOVED) */
#define PWM_UseOneCompareMode 1u
#define PWM_MinimumKillTime 1u
#define PWM_EnableMode 0u

#define PWM_CompareMode1SW 0u
#define PWM_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWM__B_PWM__DISABLED 0
#define PWM__B_PWM__ASYNCHRONOUS 1
#define PWM__B_PWM__SINGLECYCLE 2
#define PWM__B_PWM__LATCHED 3
#define PWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWM__B_PWM__DBMDISABLED 0
#define PWM__B_PWM__DBM_2_4_CLOCKS 1
#define PWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWM__B_PWM__ONE_OUTPUT 0
#define PWM__B_PWM__TWO_OUTPUTS 1
#define PWM__B_PWM__DUAL_EDGE 2
#define PWM__B_PWM__CENTER_ALIGN 3
#define PWM__B_PWM__DITHER 5
#define PWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWM__B_PWM__LESS_THAN 1
#define PWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWM__B_PWM__GREATER_THAN 3
#define PWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWM__B_PWM__EQUAL 0
#define PWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct PWM_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!PWM_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (PWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (PWM_UseStatus) */
            #if(PWM_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif /* (PWM_UseOneCompareMode) */
            
            /* Backup for Deadband parameters */
            #if(PWM_DeadBandMode == PWM__B_PWM__DBM_256_CLOCKS || \
                PWM_DeadBandMode == PWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(PWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (PWM_KillModeMinTime) */
            
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!PWM_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif /* (!PWM_PWMModeIsCenterAligned) */
            #if (PWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (PWM_UseStatus) */
            
            /* Backup for Deadband parameters */
            #if(PWM_DeadBandMode == PWM__B_PWM__DBM_256_CLOCKS || \
                PWM_DeadBandMode == PWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(PWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (PWM_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        
        /* Backup control register */
        #if(PWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWM_UseControl) */
        
    #endif /* (!PWM_UsingFixedFunction) */
   
}PWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    PWM_Start(void) ;
void    PWM_Stop(void) ;
#if (PWM_UseStatus || PWM_UsingFixedFunction)
    #define PWM_SetInterruptMode(interruptMode) CY_SET_REG8(PWM_STATUS_MASK_PTR, interruptMode)
    #define PWM_ReadStatusRegister() CY_GET_REG8(PWM_STATUS_PTR)
#endif /* (PWM_UseStatus || PWM_UsingFixedFunction) */
#define PWM_GetInterruptSource() PWM_ReadStatusRegister()
#if (PWM_UseControl)
    #define PWM_ReadControlRegister() CY_GET_REG8(PWM_CONTROL_PTR) 
    #define PWM_WriteControlRegister(control) CY_SET_REG8(PWM_CONTROL_PTR, control)
#endif /* (PWM_UseControl) */
#if (PWM_UseOneCompareMode)
   #if (PWM_CompareMode1SW)
       void    PWM_SetCompareMode(uint8 comparemode) ;
   #endif /* (PWM_CompareMode1SW) */
#else
    #if (PWM_CompareMode1SW)
        void    PWM_SetCompareMode1(uint8 comparemode) \
                                                ;
    #endif /* (PWM_CompareMode1SW) */
    #if (PWM_CompareMode2SW)
        void    PWM_SetCompareMode2(uint8 comparemode) \
                                                ;
    #endif /* (PWM_CompareMode2SW) */
#endif /* (PWM_UseOneCompareMode) */

#if (!PWM_UsingFixedFunction)
    uint16   PWM_ReadCounter(void) ;
    #define PWM_ReadCapture() CY_GET_REG16(PWM_CAPTURE_LSB_PTR)
    #if (PWM_UseStatus)
        void PWM_ClearFIFO(void) ;
    #endif /* (PWM_UseStatus) */

    void    PWM_WriteCounter(uint16 counter) \
                                       ;
#endif /* (!PWM_UsingFixedFunction) */

void    PWM_WritePeriod(uint16 period) \
                                     ;
#define PWM_ReadPeriod() CY_GET_REG16(PWM_PERIOD_LSB_PTR) 
#if (PWM_UseOneCompareMode)
    void    PWM_WriteCompare(uint16 compare) \
                                          ;
    #define PWM_ReadCompare() CY_GET_REG16(PWM_COMPARE1_LSB_PTR) 
#else
    void    PWM_WriteCompare1(uint16 compare) \
                                           ;
    #define PWM_ReadCompare1() CY_GET_REG16(PWM_COMPARE1_LSB_PTR) 
    void    PWM_WriteCompare2(uint16 compare) \
                                           ;
    #define PWM_ReadCompare2() CY_GET_REG16(PWM_COMPARE2_LSB_PTR) 
#endif /* (PWM_UseOneCompareMode) */


#if (PWM_DeadBandUsed)
    void    PWM_WriteDeadTime(uint8 deadtime) ;
    uint8   PWM_ReadDeadTime(void) ;
#endif /* (PWM_DeadBandUsed) */

#if ( PWM_KillModeMinTime)
    #define PWM_WriteKillTime(killtime) CY_SET_REG8(PWM_KILLMODEMINTIME_PTR, killtime) 
    #define PWM_ReadKillTime() CY_GET_REG8(PWM_KILLMODEMINTIME_PTR) 
#endif /* ( PWM_KillModeMinTime) */

void PWM_Init(void) ;
void PWM_Enable(void) ;
void PWM_Sleep(void) ;
void PWM_Wakeup(void) ;
void PWM_SaveConfig(void) ;
void PWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWM_INIT_PERIOD_VALUE        39999u
#define PWM_INIT_COMPARE_VALUE1      1000u
#define PWM_INIT_COMPARE_VALUE2      63u
#define PWM_INIT_INTERRUPTS_MODE     ((0u << PWM_STATUS_TC_INT_EN_MASK_SHIFT) | \
                                                  (0 << PWM_STATUS_CMP2_INT_EN_MASK_SHIFT) | \
                                                  (0 << PWM_STATUS_CMP1_INT_EN_MASK_SHIFT ) | \
                                                  (0 << PWM_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define PWM_DEFAULT_COMPARE2_MODE    (1u << PWM_CTRL_CMPMODE2_SHIFT)
#define PWM_DEFAULT_COMPARE1_MODE    (1u << PWM_CTRL_CMPMODE1_SHIFT)
#define PWM_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (PWM_UsingFixedFunction)
   #define PWM_PERIOD_LSB          (*(reg16 *) PWM_PWMHW__PER0)
   #define PWM_PERIOD_LSB_PTR      ( (reg16 *) PWM_PWMHW__PER0)
   #define PWM_COMPARE1_LSB        (*(reg16 *) PWM_PWMHW__CNT_CMP0)
   #define PWM_COMPARE1_LSB_PTR    ( (reg16 *) PWM_PWMHW__CNT_CMP0)
   #define PWM_COMPARE2_LSB        0x00u
   #define PWM_COMPARE2_LSB_PTR    0x00u
   #define PWM_COUNTER_LSB         (*(reg16 *) PWM_PWMHW__CNT_CMP0)
   #define PWM_COUNTER_LSB_PTR     ( (reg16 *) PWM_PWMHW__CNT_CMP0)
   #define PWM_CAPTURE_LSB         (*(reg16 *) PWM_PWMHW__CAP0)
   #define PWM_CAPTURE_LSB_PTR     ( (reg16 *) PWM_PWMHW__CAP0)
   #define PWM_RT1                 (*(reg8 *)  PWM_PWMHW__RT1)
   #define PWM_RT1_PTR             ( (reg8 *)  PWM_PWMHW__RT1)
      
#else
   #if(PWM_PWMModeIsCenterAligned)
       #define PWM_PERIOD_LSB      (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define PWM_PERIOD_LSB_PTR   ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #else
       #define PWM_PERIOD_LSB      (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #define PWM_PERIOD_LSB_PTR   ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
   #endif /* (PWM_PWMModeIsCenterAligned) */
   #define PWM_COMPARE1_LSB    (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PWM_COMPARE1_LSB_PTR ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define PWM_COMPARE2_LSB    (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PWM_COMPARE2_LSB_PTR ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define PWM_COUNTERCAP_LSB   *(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWM_COUNTERCAP_LSB_PTR ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define PWM_COUNTER_LSB     (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PWM_COUNTER_LSB_PTR  ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define PWM_CAPTURE_LSB     (*(reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PWM_CAPTURE_LSB_PTR  ((reg16 *) PWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define PWM_AUX_CONTROLDP0      (*(reg8 *) PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWM_AUX_CONTROLDP0_PTR  ((reg8 *) PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #if (PWM_Resolution == 16)
       #define PWM_AUX_CONTROLDP1    (*(reg8 *) PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWM_AUX_CONTROLDP1_PTR  ((reg8 *) PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
   #endif /* (PWM_Resolution == 16) */
#endif /* (PWM_UsingFixedFunction) */
   
#if(PWM_KillModeMinTime )
    #define PWM_KILLMODEMINTIME      (*(reg8 *) PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWM_KILLMODEMINTIME_PTR   ((reg8 *) PWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWM_KillModeMinTime ) */

#if(PWM_DeadBandMode == PWM__B_PWM__DBM_256_CLOCKS)
    #define PWM_DEADBAND_COUNT      (*(reg8 *) PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_DEADBAND_COUNT_PTR  ((reg8 *) PWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_DEADBAND_LSB_PTR    ((reg8 *) PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWM_DEADBAND_LSB        (*(reg8 *) PWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWM_DeadBandMode == PWM__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWM_UsingFixedFunction)
        #define PWM_DEADBAND_COUNT        (*(reg8 *) PWM_PWMHW__CFG0) 
        #define PWM_DEADBAND_COUNT_PTR     ((reg8 *) PWM_PWMHW__CFG0)
        #define PWM_DEADBAND_COUNT_MASK    (0x03u << PWM_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWM_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWM_DEADBAND_COUNT        (*(reg8 *) PWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define PWM_DEADBAND_COUNT_PTR     ((reg8 *) PWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define PWM_DEADBAND_COUNT_MASK    (0x03u << PWM_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define PWM_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (PWM_UsingFixedFunction) */
#endif /* (PWM_DeadBandMode == PWM__B_PWM__DBM_256_CLOCKS) */



#if (PWM_UsingFixedFunction)
    #define PWM_STATUS                (*(reg8 *) PWM_PWMHW__SR0)
    #define PWM_STATUS_PTR            ((reg8 *) PWM_PWMHW__SR0)
    #define PWM_STATUS_MASK           (*(reg8 *) PWM_PWMHW__SR0)
    #define PWM_STATUS_MASK_PTR       ((reg8 *) PWM_PWMHW__SR0)
    #define PWM_CONTROL               (*(reg8 *) PWM_PWMHW__CFG0)
    #define PWM_CONTROL_PTR           ((reg8 *) PWM_PWMHW__CFG0)    
    #define PWM_CONTROL2              (*(reg8 *) PWM_PWMHW__CFG1)    
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_CONTROL3              (*(reg8 *) PWM_PWMHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define PWM_GLOBAL_ENABLE         (*(reg8 *) PWM_PWMHW__PM_ACT_CFG)
    #define PWM_GLOBAL_ENABLE_PTR       ( (reg8 *) PWM_PWMHW__PM_ACT_CFG)
    #define PWM_GLOBAL_STBY_ENABLE      (*(reg8 *) PWM_PWMHW__PM_STBY_CFG)
    #define PWM_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PWM_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWM_BLOCK_EN_MASK          PWM_PWMHW__PM_ACT_MSK
    #define PWM_BLOCK_STBY_EN_MASK     PWM_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PWM_CTRL_ENABLE_SHIFT      0x00u
    
    #if(CY_PSOC5A)
        #define PWM_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    #define PWM_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define PWM_CFG0_MODE              0x02u   /*  Set to compare mode */
    /* #define PWM_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define PWM_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PWM_CTRL_ENABLE            (0x01u << PWM_CTRL_ENABLE_SHIFT)
    #define PWM_CTRL_RESET             (0x01u << PWM_CTRL_RESET_SHIFT)
    #define PWM_CTRL_CMPMODE2_MASK     (0x07u << PWM_CTRL_CMPMODE2_SHIFT)
    #if(CY_PSOC5A)
        #define PWM_CTRL_CMPMODE1_MASK     (0x07u << PWM_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_CTRL_CMPMODE1_MASK     (0x07u << PWM_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWM_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define PWM_CTRL2_IRQ_SEL          (0x01u << PWM_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PWM_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PWM_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PWM_STATUS_TC_INT_EN_MASK_SHIFT            (PWM_STATUS_TC_SHIFT - 4)
    #define PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWM_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define PWM_STATUS_TC              (0x01u << PWM_STATUS_TC_SHIFT)
    #define PWM_STATUS_CMP1            (0x01u << PWM_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define PWM_STATUS_TC_INT_EN_MASK              (PWM_STATUS_TC >> 4)
    #define PWM_STATUS_CMP1_INT_EN_MASK            (PWM_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP*/
    #define PWM_RT1_SHIFT             0x04u
    #define PWM_RT1_MASK              (0x03u << PWM_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define PWM_SYNC                  (0x03u << PWM_RT1_SHIFT)
    #define PWM_SYNCDSI_SHIFT         0x00u
    #define PWM_SYNCDSI_MASK          (0x0Fu << PWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PWM_SYNCDSI_EN            (0x0Fu << PWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PWM_STATUS                (*(reg8 *) PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define PWM_STATUS_PTR            ((reg8 *) PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define PWM_STATUS_MASK           (*(reg8 *) PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define PWM_STATUS_MASK_PTR       ((reg8 *) PWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define PWM_STATUS_AUX_CTRL       (*(reg8 *) PWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PWM_CONTROL               (*(reg8 *) PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define PWM_CONTROL_PTR           ((reg8 *) PWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define PWM_CTRL_ENABLE_SHIFT      0x07u
    #define PWM_CTRL_RESET_SHIFT       0x06u
    #define PWM_CTRL_CMPMODE2_SHIFT    0x03u
    #define PWM_CTRL_CMPMODE1_SHIFT    0x00u
    #define PWM_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PWM_CTRL_ENABLE            (0x01u << PWM_CTRL_ENABLE_SHIFT)
    #define PWM_CTRL_RESET             (0x01u << PWM_CTRL_RESET_SHIFT)
    #define PWM_CTRL_CMPMODE2_MASK     (0x07u << PWM_CTRL_CMPMODE2_SHIFT)
    #define PWM_CTRL_CMPMODE1_MASK     (0x07u << PWM_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PWM_STATUS_KILL_SHIFT          0x05u
    #define PWM_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PWM_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PWM_STATUS_TC_SHIFT            0x02u
    #define PWM_STATUS_CMP2_SHIFT          0x01u
    #define PWM_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWM_STATUS_KILL_INT_EN_MASK_SHIFT          PWM_STATUS_KILL_SHIFT          
    #define PWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PWM_STATUS_FIFONEMPTY_SHIFT    
    #define PWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PWM_STATUS_FIFOFULL_SHIFT        
    #define PWM_STATUS_TC_INT_EN_MASK_SHIFT            PWM_STATUS_TC_SHIFT            
    #define PWM_STATUS_CMP2_INT_EN_MASK_SHIFT          PWM_STATUS_CMP2_SHIFT          
    #define PWM_STATUS_CMP1_INT_EN_MASK_SHIFT          PWM_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PWM_STATUS_KILL            (0x00u << PWM_STATUS_KILL_SHIFT )
    #define PWM_STATUS_FIFOFULL        (0x01u << PWM_STATUS_FIFOFULL_SHIFT)
    #define PWM_STATUS_FIFONEMPTY      (0x01u << PWM_STATUS_FIFONEMPTY_SHIFT)
    #define PWM_STATUS_TC              (0x01u << PWM_STATUS_TC_SHIFT)
    #define PWM_STATUS_CMP2            (0x01u << PWM_STATUS_CMP2_SHIFT) 
    #define PWM_STATUS_CMP1            (0x01u << PWM_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWM_STATUS_KILL_INT_EN_MASK            PWM_STATUS_KILL
    #define PWM_STATUS_FIFOFULL_INT_EN_MASK        PWM_STATUS_FIFOFULL
    #define PWM_STATUS_FIFONEMPTY_INT_EN_MASK      PWM_STATUS_FIFONEMPTY
    #define PWM_STATUS_TC_INT_EN_MASK              PWM_STATUS_TC
    #define PWM_STATUS_CMP2_INT_EN_MASK            PWM_STATUS_CMP2
    #define PWM_STATUS_CMP1_INT_EN_MASK            PWM_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PWM_AUX_CTRL_FIFO0_CLR     0x01u
    #define PWM_AUX_CTRL_FIFO1_CLR     0x02u
    #define PWM_AUX_CTRL_FIFO0_LVL     0x04u
    #define PWM_AUX_CTRL_FIFO1_LVL     0x08u
    #define PWM_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PWM_UsingFixedFunction */

#endif  /* CY_PWM_PWM_H */


/* [] END OF FILE */
