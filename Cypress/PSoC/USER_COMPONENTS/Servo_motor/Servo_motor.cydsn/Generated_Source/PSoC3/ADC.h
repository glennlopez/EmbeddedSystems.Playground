/*******************************************************************************
* File Name: ADC.h  
* Version 2.30
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Delta-Sigma ADC user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_ADC_DELSIG_ADC_H) 
#define CY_ADC_DELSIG_ADC_H 

#include "cytypes.h"
#include "cylib.h"
#include "cyfitter.h"
#include "cydevice_trm.h" 

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component ADC_DelSig_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct ADC_backupStruct 
{
    uint8 enableState;
    uint8 deccr;
}   ADC_BACKUP_STRUCT;


/***************************************
*       Type defines
***************************************/

/* only valid for PSoCA */
#if (CY_PSOC5A)
    /* Power Mode register backup Support */
    typedef struct ADC_powerModeBackupStruct 
    {
        uint8 DSM_CR_14;
        uint8 DSM_CR_15;
        uint8 DSM_CR_16;
        uint8 DSM_CR_17;
        uint8 DSM_REF0;
        uint8 DSM_BUF0;
        uint8 DSM_BUF1;
        uint8 DSM_CLK;
        /* field to decide whether or not to save the registers 
           in the stop API*/
        uint8 bypassRestore;
    }   ADC_POWERMODE_BACKUP_STRUCT;
#endif /* CY_PSOC5A */


/***************************************
*        Function Prototypes 
***************************************/

void ADC_Start(void) ;
void ADC_Stop(void) ;
void ADC_Sleep(void) ;
void ADC_Wakeup(void) ;
void ADC_Init(void) ;   
void ADC_Enable(void) ;
void ADC_SaveConfig(void) ;
void ADC_RestoreConfig(void) ;
void ADC_SetBufferGain(uint8 gain) ;
void ADC_StartConvert(void) ;
void ADC_SetCoherency(uint8 coherency) ;
uint8 ADC_SetGCOR(float gainAdjust) ;
uint16 ADC_ReadGCOR(void) ;
void ADC_StopConvert(void) ;
void ADC_SetOffset(int32 offset) ; 
void ADC_SetGain(int32 adcGain) ; 
int8 ADC_GetResult8(void) ;
int16 ADC_GetResult16(void) ;
int32 ADC_GetResult32(void) ;
uint8 ADC_IsEndConversion(uint8 retMode) ;
int16 ADC_CountsTo_mVolts( int32 adcCounts) ; 
float ADC_CountsTo_Volts( int32 adcCounts) ; 
int32 ADC_CountsTo_uVolts( int32 adcCounts) ;
CY_ISR_PROTO(ADC_ISR1);
CY_ISR_PROTO(ADC_ISR2);
CY_ISR_PROTO(ADC_ISR3);
CY_ISR_PROTO(ADC_ISR4);
void ADC_SelectConfiguration(uint8 config, uint8 restart) \
                                           ;
void ADC_InitConfig(uint8 config) ;
void ADC_GainCompensation(uint8 inputRange, uint16 IdealDecGain, uint16 IdealOddDecGain, uint8 resolution)\
                                              ;
#if (CY_PSOC5A)
    void ADC_SavePowerRegisters(void) ;
    void ADC_RestorePowerRegisters(void) ;
    void ADC_SetLowPower(void) ;
#endif /* CY_PSOC5A */
uint16 ADC_RoundValue(uint32 busClockFreq, uint32 clockFreq) \
                                              ;
void ADC_SetDSMRef0Reg(uint8 value) ;

/* These functions may not be supported in the released version */
void    ADC_SetBufferChop(uint8 chopen, uint8 chopFreq) \
                                                  ;
#define ADC_IRQ_Enable() CyIntEnable(ADC_IRQ__INTC_NUMBER ); 
#define ADC_IRQ_Disable() CyIntDisable(ADC_IRQ__INTC_NUMBER );


/*******************************************************************************
* The following API?s are to support legacy code.  The IRQ_Start
* And IRQ_Stop routine have been replaced by the library source code
* for interrupts. IRQ_Start() and IRQ_Stop() should not be used in new
* designs
*******************************************************************************/
void ADC_IRQ_Start(void) ;
#define ADC_IRQ_Stop() CyIntDisable(ADC_IRQ__INTC_NUMBER )


/**************************************
*           Parameter Defaults        
**************************************/

/* Default config values from user parameters */

#define ADC_CFG1_RESOLUTION         (8u )
#define ADC_CFG1_RANGE              (2u)    
#define ADC_CFG1_SRATE              (10000u)         
#define ADC_CFG1_REFERENCE          (5u)       
#define ADC_CFG1_BUF_GAIN           (1u)   
#define ADC_CFG1_CONV_MODE          (0u)     
#define ADC_CFG1_RANGE_VALUE        (5)
#define ADC_DEFAULT_STROBE                     (0u) 
#define ADC_DEFAULT_INTERNAL_CLK               (1u)           
#define ADC_DEFAULT_NUM_CONFIGS                (1u)    
#define ADC_DEFAULT_CHARGE_PUMP_CLOCK          (1u)    
#define ADC_DEFAULT_INPUT_MODE                 (1u)

/* Config Constants which can be used as the "config" parameter of
   ADC_SelectConfiguration() API. */
#define ADC_CFG1        1
#define ADC_CFG2        2
#define ADC_CFG3        3
#define ADC_CFG4        4


/**************************************
*           API Constants        
**************************************/

/* Component's enable/disable state */
#define ADC_ENABLED                    (0x01u)
#define ADC_DISABLED                   (0x00u)

/* Defines for deciding whether or not to restore the 
   power registers in Enable API. Valid only for PSoC5A*/
#if (CY_PSOC5A)
    #define ADC_BYPASS_ENABLED                    (0x01u)
    #define ADC_BYPASS_DISABLED                   (0x00u)
#endif /* CY_PSOC5A */

/* Ideal Gain Constant */
#define ADC_IDEAL_GAIN_CONST           (0x8000u)

/* Gvalue constant */
#define ADC_MAX_GVAL                   (0x0Fu)

/* Gvalue constants based on resolution */
#define ADC_GVAL_RESOLUTIN_8           (0x09u)
#define ADC_GVAL_RESOLUTIN_9           (0x0Au)
#define ADC_GVAL_RESOLUTIN_10          (0x0Bu)
#define ADC_GVAL_RESOLUTIN_11          (0x0Cu)
#define ADC_GVAL_RESOLUTIN_12          (0x0Du)
#define ADC_GVAL_RESOLUTIN_13          (0x0Eu)

/* Constants for SetPower(), "power" paramter */
#define ADC_LOWPOWER                   (0x00u) 
#define ADC_MEDPOWER                   (0x01u) 
#define ADC_HIGHPOWER                  (0x02u) 
#define ADC_HIGHPOWER_1_5              (0x03u)  /* Reserved */
#define ADC_HIGHPOWER_2_0              (0x04u)  /* Reserved */
#define ADC_HIGHPOWER_2_5              (0x07u)  /* Reserved */
#define ADC_POWER_MASK                 (0x07u) 

/* Constants for SetBufferGain() "gain" paramter */
#define ADC_BUF_GAIN_1X                (0x00u) 
#define ADC_BUF_GAIN_2X                (0x01u) 
#define ADC_BUF_GAIN_4X                (0x02u) 
#define ADC_BUF_GAIN_8X                (0x03u) 
#define ADC_BUF_GAIN_MASK              (0x03u)

/* Constants for IsEndConversion() "retMode" parameter */
#define ADC_RETURN_STATUS              (0x01u) 
#define ADC_WAIT_FOR_RESULT            (0x00u)

/* Constants for input range parameter */

#define ADC_IR_VSSA_TO_VREF            (0x00u)
#define ADC_IR_VSSA_TO_2VREF           (0x01u)
#define ADC_IR_VSSA_TO_VDDA            (0x02u)
#define ADC_IR_VSSA_TO_6VREF           (0x03u)
#define ADC_IR_VNEG_VREF_DIFF          (0x04u)
#define ADC_IR_VNEG_2VREF_DIFF         (0x05u)
#define ADC_IR_VNEG_6VREF_DIFF         (0x06u)
#define ADC_IR_VNEG_VREF_2_DIFF        (0x07u)
#define ADC_IR_VNEG_VREF_4_DIFF        (0x08u)
#define ADC_IR_VNEG_VREF_8_DIFF        (0x09u)
#define ADC_IR_VNEG_VREF_16_DIFF       (0x0Au)

/* Constants for ADC reference parameter */

#define ADC_INT_REF_NOT_BYPASSED       (0x00u)
#define ADC_INT_REF_BYPASSED_ON_P03    (0x01u)
#define ADC_INT_REF_BYPASSED_ON_P32    (0x02u)
#define ADC_EXT_REF_ON_P03             (0x03u)
#define ADC_EXT_REF_ON_P32             (0x04u)
#define ADC_INT_REF_VDDA_4             (0x05u)
#define ADC_INT_REF_VDDA_3             (0x06u)

/* Priority of the ADC_IRQ interrupt. */
#define ADC_IRQ_INTC_PRIOR_NUMBER      ADC_IRQ__INTC_PRIOR_NUM

/* Constants for ADC coherency parameter */

#define ADC_COHER_LOW                  (0x01u) 
#define ADC_COHER_MID                  (0x02u) 
#define ADC_COHER_HIGH                 (0x03u)

/* Trim value defines */

#if (CY_PSOC3 || CY_PSOC5LP)
    #define ADC_DEC_TRIM_VREF_DIFF_8_15        (CY_GET_XTND_REG8(ADC_DEC__TRIM__M5))
    #define ADC_DEC_TRIM_VREF_DIFF_16_20       (CY_GET_XTND_REG8(ADC_DEC__TRIM__M1))
    #define ADC_DEC_TRIM_VREF_2_DIFF_8_15      (CY_GET_XTND_REG8(ADC_DEC__TRIM__M6))
    #define ADC_DEC_TRIM_VREF_2_DIFF_16_20     (CY_GET_XTND_REG8(ADC_DEC__TRIM__M2))
    #define ADC_DEC_TRIM_VREF_4_DIFF_8_15      (CY_GET_XTND_REG8(ADC_DEC__TRIM__M7))
    #define ADC_DEC_TRIM_VREF_4_DIFF_16_20     (CY_GET_XTND_REG8(ADC_DEC__TRIM__M3))
    #define ADC_DEC_TRIM_VREF_16_DIFF_8_15     (CY_GET_XTND_REG8(ADC_DEC__TRIM__M8))
    #define ADC_DEC_TRIM_VREF_16_DIFF_16_20    (CY_GET_XTND_REG8(ADC_DEC__TRIM__M4))
#elif (CY_PSOC5A)
    #define ADC_DEC_TRIM_VREF_DIFF_8_15        (CY_GET_XTND_REG8(ADC_DEC__TRIM__16L))
    #define ADC_DEC_TRIM_VREF_DIFF_16_20       (CY_GET_XTND_REG8(ADC_DEC__TRIM__1L))
    #define ADC_DEC_TRIM_VREF_2_DIFF_8_15      (CY_GET_XTND_REG8(ADC_DEC__TRIM__16H))
    #define ADC_DEC_TRIM_VREF_2_DIFF_16_20     (CY_GET_XTND_REG8(ADC_DEC__TRIM__1H))
    #define ADC_DEC_TRIM_VREF_4_DIFF_8_15      (CY_GET_XTND_REG8(ADC_DEC__TRIM__P25L))
    #define ADC_DEC_TRIM_VREF_4_DIFF_16_20     (CY_GET_XTND_REG8(ADC_DEC__TRIM__4L))
    #define ADC_DEC_TRIM_VREF_16_DIFF_8_15     (CY_GET_XTND_REG8(ADC_DEC__TRIM__P25H))
    #define ADC_DEC_TRIM_VREF_16_DIFF_16_20    (CY_GET_XTND_REG8(ADC_DEC__TRIM__4H))

#endif /* CY_PSOC5A */


/**************************************
*      Unsupported API Constants        
**************************************/

/* Constants for SetBuffer() "bufMode" parameter */   
#define ADC_BUF_DIFF_MODE              (0x00u)  /* Differential mode */
#define ADC_BUF_BYPASS_POS             (0x04u)  /* Bypass and power down positive channel */
#define ADC_BUF_BYPASS_NEG             (0x08u)  /* Bypass and power down negative channel */
#define ADC_BUF_RAIL_TO_RAIL           (0x10u)  /* Enables Rail-to-rail mode */
#define ADC_BUF_FILTER_EN              (0x20u)  /* Output filter enable */
#define ADC_BUF_LOW_PWR                (0x40u)  /* Enable  Low power mode */

/* Constants for SetInputRange() "inputMode" parameter */
#define ADC_INMODE_VSSA_TO_VREF        (0x00u) 
#define ADC_INMODE_VSSA_TO_2VREF       (0x01u) 
#define ADC_INMODE_VSSA_TO_VDDA        (0x02u) 
#define ADC_INMODE_VNEG_PM_VREF_DIFF   (0x03u) 
#define ADC_INMODE_VNEG_PM_2VREF_DIFF  (0x04u)

/* Constants for SetBufferChop() "chopen" parameter */
#define ADC_BUF_CHOP_ENABLE            (0x01u)
#define ADC_BUF_CHOP_DISABLE           (0x00u)

/* Constants for SetBufferChop() "chopFreq" parameter */
#define ADC_BUF_CHOP_FREQ_FS2          (0x00u) 
#define ADC_BUF_CHOP_FREQ_FS4          (0x01u) 
#define ADC_BUF_CHOP_FREQ_FS8          (0x02u) 
#define ADC_BUF_CHOP_FREQ_FS16         (0x03u) 
#define ADC_BUF_CHOP_FREQ_FS32         (0x04u) 
#define ADC_BUF_CHOP_FREQ_FS64         (0x05u) 
#define ADC_BUF_CHOP_FREQ_FS128        (0x06u) 
#define ADC_BUF_CHOP_FREQ_FS256        (0x07u) 

/* Constants for custom reference mode settings */
#define ADC_REF_INTREF                 (0x80u) 
#define ADC_REF_REFMODE_MASK           (0x07u) 
#define ADC_INTREF_MASK                (0x07u)

#define ADC_MIN_RES                    (8u)
#define ADC_MAX_RES                    (20u) 


/**************************************
*       Register Constants        
**************************************/


/******************************************/
/* DSM.CR0 Control Register 0 definitions */
/******************************************/

/* Bit Field  DSM_NONOV */
#define ADC_DSM_NONOV_MASK             (0x0Cu)
#define ADC_DSM_NONOV_LOW              (0x00u)
#define ADC_DSM_NONOV_MED              (0x04u)
#define ADC_DSM_NONOV_HIGH             (0x08u)
#define ADC_DSM_NONOV_VHIGH            (0x0Cu)

/* Bit Field  DSM_QLEV */
#define ADC_DSM_QLEV_MASK              (0x03u)
#define ADC_DSM_QLEV_2                 (0x00u)
#define ADC_DSM_QLEV_3                 (0x01u)
#define ADC_DSM_QLEV_9                 (0x02u)
#define ADC_DSM_QLEV_9x                (0x03u)


/******************************************/
/* DSM.CR1 Control Register 1 definitions */
/******************************************/
#define ADC_DSM_ODET_TH_MASK           (0x1Fu)
#define ADC_DSM_ODEN                   (0x20u)
#define ADC_DSM_DPMODE                 (0x40u)


/******************************************/
/* DSM.CR2 Control Register 2 definitions */
/******************************************/

/* Bit Field  DSM_FCHOP */
#define ADC_DSM_FCHOP_MASK             (0x07u)
#define ADC_DSM_FCHOP_DIV2             (0x00u)
#define ADC_DSM_FCHOP_DIV4             (0x01u)
#define ADC_DSM_FCHOP_DIV8             (0x02u)
#define ADC_DSM_FCHOP_DIV16            (0x03u)
#define ADC_DSM_FCHOP_DIV32            (0x04u)
#define ADC_DSM_FCHOP_DIV64            (0x05u)
#define ADC_DSM_FCHOP_DIV128           (0x06u)
#define ADC_DSM_FCHOP_DIV256           (0x07u)

/* Bit Field  DSM_MOD_CHOP_EN */
#define ADC_DSM_MOD_CHOP_EN            (0x08u)

/* Bit Field  DSM_MX_RESET */
#define ADC_DSM_MX_RESET               (0x80u)

/* Bit Field  DSM_RESET1_EN */
#define ADC_DSM_RESET1_EN              (0x10u)

/* Bit Field  DSM_RESET2_EN */
#define ADC_DSM_RESET2_EN              (0x20u)

/* Bit Field  DSM_RESET3_EN */
#define ADC_DSM_RESET3_EN              (0x40u)


/******************************************/
/* DSM.CR3 Control Register 3 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_MOD_BIT */
#define ADC_DSM_MODBITIN_MASK          (0x0Fu)
#define ADC_DSM_MODBITIN_LUT0          (0x00u)
#define ADC_DSM_MODBITIN_LUT1          (0x01u)
#define ADC_DSM_MODBITIN_LUT2          (0x02u)
#define ADC_DSM_MODBITIN_LUT3          (0x03u)
#define ADC_DSM_MODBITIN_LUT4          (0x04u)
#define ADC_DSM_MODBITIN_LUT5          (0x05u)
#define ADC_DSM_MODBITIN_LUT6          (0x06u)
#define ADC_DSM_MODBITIN_LUT7          (0x07u)
#define ADC_DSM_MODBITIN_UDB           (0x08u)

/* Bit Field  DSM_MODBIT_EN */
#define ADC_DSM_MODBIT_EN              (0x10u)

/* Bit Field  DSM_MX_DOUT */
#define ADC_DSM_MX_DOUT_8BIT           (0x00u)
#define ADC_DSM_MX_DOUT_2SCOMP         (0x20u)

/* Bit Field  DSM_MODBIT  TBD */
#define ADC_DSM_MODBIT                 (0x40u)

/* Bit Field  DSM_SIGN */
#define ADC_DSM_SIGN_NINV              (0x00u)
#define ADC_DSM_SIGN_INV               (0x80u)


/******************************************/
/* DSM.CR4 Control Register 4 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_FCAP_EN */
#define ADC_DSM_FCAP1_EN               (0x80u)
#define ADC_DSM_FCAP1_DIS              (0x00u)

/* Bit Field  DSM_SELECT_FCAP1 */
#define ADC_DSM_FCAP1_MASK             (0x7Fu)
#define ADC_DSM_FCAP1_MIN              (0x00u)
#define ADC_DSM_FCAP1_MAX              (0x7Fu)
#define ADC_DSM_FCAP1_100FF            (0x01u)
#define ADC_DSM_FCAP1_200FF            (0x02u)
#define ADC_DSM_FCAP1_400FF            (0x04u)
#define ADC_DSM_FCAP1_800FF            (0x08u)
#define ADC_DSM_FCAP1_1600FF           (0x10u)
#define ADC_DSM_FCAP1_3200FF           (0x20u)
#define ADC_DSM_FCAP1_6400FF           (0x40u)


/******************************************/
/* DSM.CR5 Control Register 5 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_IPCAP_EN */
#define ADC_DSM_IPCAP1_EN              (0x80u)
#define ADC_DSM_IPCAP1_DIS             (0x00u)

/* Bit Field  DSM_SELECT_IPCAP1 */
#define ADC_DSM_IPCAP1_MASK            (0x7Fu)
#define ADC_DSM_IPCAP1_MIN             (0x00u)
#define ADC_DSM_IPCAP1_MAX             (0x7Fu)
#define ADC_DSM_IPCAP1_96FF            (0x01u)
#define ADC_DSM_IPCAP1_192FF           (0x02u)
#define ADC_DSM_IPCAP1_400FF           (0x04u)
#define ADC_DSM_IPCAP1_800FF           (0x08u)
#define ADC_DSM_IPCAP1_1600FF          (0x10u)
#define ADC_DSM_IPCAP1_3200FF          (0x20u)
#define ADC_DSM_IPCAP1_6400FF          (0x40u)


/******************************************/
/* DSM.CR6 Control Register 6 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_DACCAP_EN */
#define ADC_DSM_DACCAP_EN              (0x40u)
#define ADC_DSM_DACCAP_DIS             (0x00u)

/* Bit Field  DSM_SELECT_DACCAP */
#define ADC_DSM_DACCAP_MASK            (0x3Fu)
#define ADC_DSM_DACCAP_MIN             (0x00u)
#define ADC_DSM_DACCAP_MAX             (0x3Fu)
#define ADC_DSM_DACCAP_96FF            (0x01u)
#define ADC_DSM_DACCAP_192FF           (0x02u)
#define ADC_DSM_DACCAP_400FF           (0x04u)
#define ADC_DSM_DACCAP_800FF           (0x08u)
#define ADC_DSM_DACCAP_1600FF          (0x10u)
#define ADC_DSM_DACCAP_3200FF          (0x20u)


/******************************************/
/* DSM.CR7 Control Register 7 definitions */
/******************************************/

/* Bit Field  DSM_SELECT_RESCAP_EN */
#define ADC_DSM_RESCAP_EN              (0x08u)
#define ADC_DSM_RESCAP_DIS             (0x00u)

/* Bit Field  DSM_SELECT_RESCAP */
#define ADC_DSM_RESCAP_MASK            (0x07u)
#define ADC_DSM_RESCAP_MIN             (0x00u)
#define ADC_DSM_RESCAP_MAX             (0x07u)
#define ADC_DSM_RESCAP_12FF            (0x00u)
#define ADC_DSM_RESCAP_24FF            (0x01u)
#define ADC_DSM_RESCAP_36FF            (0x02u)
#define ADC_DSM_RESCAP_48FF            (0x03u)
#define ADC_DSM_RESCAP_60FF            (0x04u)
#define ADC_DSM_RESCAP_72FF            (0x05u)
#define ADC_DSM_RESCAP_84FF            (0x06u)
#define ADC_DSM_RESCAP_96FF            (0x07u)

#define ADC_DSM_FCAP2_DIS              (0x00u)
#define ADC_DSM_FCAP2_EN               (0x80u)

#define ADC_DSM_FCAP3_DIS              (0x00u)
#define ADC_DSM_FCAP3_EN               (0x40u)

#define ADC_DSM_IPCAP1OFFSET           (0x20u)
#define ADC_DSM_FPCAP1OFFSET           (0x10u)


/******************************************/
/* DSM.CR8 Control Register 8 definitions */
/******************************************/

#define ADC_DSM_IPCAP2_EN              (0x80u)

#define ADC_DSM_IPCAP2_MASK            (0x70u)
#define ADC_DSM_IPCAP2_0_FF            (0x00u)
#define ADC_DSM_IPCAP2_50_FF           (0x10u)
#define ADC_DSM_IPCAP2_100_FF          (0x20u)
#define ADC_DSM_IPCAP2_150_FF          (0x30u)
#define ADC_DSM_IPCAP2_200_FF          (0x40u)
#define ADC_DSM_IPCAP2_250_FF          (0x50u)
#define ADC_DSM_IPCAP2_300_FF          (0x60u)
#define ADC_DSM_IPCAP2_350_FF          (0x70u)

#define ADC_DSM_FCAP2_MASK             (0x0Fu)
#define ADC_DSM_FCAP2_0_FF             (0x00u)
#define ADC_DSM_FCAP2_50_FF            (0x01u)
#define ADC_DSM_FCAP2_100_FF           (0x02u)
#define ADC_DSM_FCAP2_150_FF           (0x03u)
#define ADC_DSM_FCAP2_200_FF           (0x04u)
#define ADC_DSM_FCAP2_250_FF           (0x05u)
#define ADC_DSM_FCAP2_300_FF           (0x06u)
#define ADC_DSM_FCAP2_350_FF           (0x07u)
#define ADC_DSM_FCAP2_400_FF           (0x08u)
#define ADC_DSM_FCAP2_450_FF           (0x09u)
#define ADC_DSM_FCAP2_500_FF           (0x0Au)
#define ADC_DSM_FCAP2_550_FF           (0x0Bu)
#define ADC_DSM_FCAP2_600_FF           (0x0Cu)
#define ADC_DSM_FCAP2_650_FF           (0x0Du)
#define ADC_DSM_FCAP2_700_FF           (0x0Eu)
#define ADC_DSM_FCAP2_750_FF           (0x0Fu)


/******************************************/
/* DSM.CR9 Control Register 9 definitions */
/******************************************/

#define ADC_DSM_IPCAP3_EN              (0x80u)

#define ADC_DSM_IPCAP3_MASK            (0x70u)
#define ADC_DSM_IPCAP3_0_FF            (0x00u)
#define ADC_DSM_IPCAP3_50_FF           (0x10u)
#define ADC_DSM_IPCAP3_100_FF          (0x20u)
#define ADC_DSM_IPCAP3_150_FF          (0x30u)
#define ADC_DSM_IPCAP3_200_FF          (0x40u)
#define ADC_DSM_IPCAP3_250_FF          (0x50u)
#define ADC_DSM_IPCAP3_300_FF          (0x60u)
#define ADC_DSM_IPCAP3_350_FF          (0x70u)

#define ADC_DSM_FCAP3_MASK             (0x0Fu)
#define ADC_DSM_FCAP3_0_FF             (0x00u)
#define ADC_DSM_FCAP3_50_FF            (0x01u)
#define ADC_DSM_FCAP3_100_FF           (0x02u)
#define ADC_DSM_FCAP3_150_FF           (0x03u)
#define ADC_DSM_FCAP3_200_FF           (0x04u)
#define ADC_DSM_FCAP3_250_FF           (0x05u)
#define ADC_DSM_FCAP3_300_FF           (0x06u)
#define ADC_DSM_FCAP3_350_FF           (0x07u)
#define ADC_DSM_FCAP3_400_FF           (0x08u)
#define ADC_DSM_FCAP3_450_FF           (0x09u)
#define ADC_DSM_FCAP3_500_FF           (0x0Au)
#define ADC_DSM_FCAP3_550_FF           (0x0Bu)
#define ADC_DSM_FCAP3_600_FF           (0x0Cu)
#define ADC_DSM_FCAP3_650_FF           (0x0Du)
#define ADC_DSM_FCAP3_700_FF           (0x0Eu)
#define ADC_DSM_FCAP3_750_FF           (0x0Fu)


/********************************************/
/* DSM.CR10 Control Register 10 definitions */
/********************************************/

#define ADC_DSM_SUMCAP1_EN             (0x80u)
#define ADC_DSM_SUMCAP2_EN             (0x08u)

#define ADC_DSM_SUMCAP1_MASK           (0x70u)
#define ADC_DSM_SUMCAP1_0_FF           (0x00u)
#define ADC_DSM_SUMCAP1_50_FF          (0x10u)
#define ADC_DSM_SUMCAP1_100_FF         (0x20u)
#define ADC_DSM_SUMCAP1_150_FF         (0x30u)
#define ADC_DSM_SUMCAP1_200_FF         (0x40u)
#define ADC_DSM_SUMCAP1_250_FF         (0x50u)
#define ADC_DSM_SUMCAP1_300_FF         (0x60u)
#define ADC_DSM_SUMCAP1_350_FF         (0x70u)

#define ADC_DSM_SUMCAP2_MASK           (0x07u)
#define ADC_DSM_SUMCAP2_0_FF           (0x00u)
#define ADC_DSM_SUMCAP2_50_FF          (0x01u)
#define ADC_DSM_SUMCAP2_100_FF         (0x02u)
#define ADC_DSM_SUMCAP2_150_FF         (0x03u)
#define ADC_DSM_SUMCAP2_200_FF         (0x04u)
#define ADC_DSM_SUMCAP2_250_FF         (0x05u)
#define ADC_DSM_SUMCAP2_300_FF         (0x06u)
#define ADC_DSM_SUMCAP2_350_FF         (0x07u)


/********************************************/
/* DSM.CR11 Control Register 11 definitions */
/********************************************/

#define ADC_DSM_SUMCAP3_EN             (0x08u)

#define ADC_DSM_SUMCAP3_MASK           (0x70u)
#define ADC_DSM_SUMCAP3_0_FF           (0x00u)
#define ADC_DSM_SUMCAP3_50_FF          (0x10u)
#define ADC_DSM_SUMCAP3_100_FF         (0x20u)
#define ADC_DSM_SUMCAP3_150_FF         (0x30u)
#define ADC_DSM_SUMCAP3_200_FF         (0x40u)
#define ADC_DSM_SUMCAP3_250_FF         (0x50u)
#define ADC_DSM_SUMCAP3_300_FF         (0x60u)
#define ADC_DSM_SUMCAP3_350_FF         (0x70u)

#define ADC_DSM_SUMCAPFB_MASK          (0x07u)
#define ADC_DSM_SUMCAPFB_0_FF          (0x00u)
#define ADC_DSM_SUMCAPFB_50_FF         (0x01u)
#define ADC_DSM_SUMCAPFB_100_FF        (0x02u)
#define ADC_DSM_SUMCAPFB_150_FF        (0x03u)
#define ADC_DSM_SUMCAPFB_200_FF        (0x04u)
#define ADC_DSM_SUMCAPFB_250_FF        (0x05u)
#define ADC_DSM_SUMCAPFB_300_FF        (0x06u)
#define ADC_DSM_SUMCAPFB_350_FF        (0x07u)
#define ADC_DSM_SUMCAPFB_400_FF        (0x08u)
#define ADC_DSM_SUMCAPFB_450_FF        (0x09u)
#define ADC_DSM_SUMCAPFB_500_FF        (0x0Au)
#define ADC_DSM_SUMCAPFB_550_FF        (0x0Bu)
#define ADC_DSM_SUMCAPFB_600_FF        (0x0Cu)
#define ADC_DSM_SUMCAPFB_650_FF        (0x0Du)
#define ADC_DSM_SUMCAPFB_700_FF        (0x0Eu)
#define ADC_DSM_SUMCAPFB_750_FF        (0x0Fu)


/********************************************/
/* DSM.CR12 Control Register 12 definitions */
/********************************************/

#define ADC_DSM_SUMCAPFB_EN            (0x40u)
#define ADC_DSM_SUMCAPIN_EN            (0x20u)

#define ADC_DSM_SUMCAPIN_MASK          (0x1Fu)
#define ADC_DSM_SUMCAPIN_0_FF          (0x00u)
#define ADC_DSM_SUMCAPIN_50_FF         (0x01u)
#define ADC_DSM_SUMCAPIN_100_FF        (0x02u)
#define ADC_DSM_SUMCAPIN_150_FF        (0x03u)
#define ADC_DSM_SUMCAPIN_200_FF        (0x04u)
#define ADC_DSM_SUMCAPIN_250_FF        (0x05u)
#define ADC_DSM_SUMCAPIN_300_FF        (0x06u)
#define ADC_DSM_SUMCAPIN_350_FF        (0x07u)
#define ADC_DSM_SUMCAPIN_400_FF        (0x08u)
#define ADC_DSM_SUMCAPIN_450_FF        (0x09u)
#define ADC_DSM_SUMCAPIN_500_FF        (0x0Au)
#define ADC_DSM_SUMCAPIN_550_FF        (0x0Bu)
#define ADC_DSM_SUMCAPIN_600_FF        (0x0Cu)
#define ADC_DSM_SUMCAPIN_650_FF        (0x0Du)
#define ADC_DSM_SUMCAPIN_700_FF        (0x0Eu)
#define ADC_DSM_SUMCAPIN_750_FF        (0x0Fu)
#define ADC_DSM_SUMCAPIN_800_FF        (0x10u)
#define ADC_DSM_SUMCAPIN_850_FF        (0x11u)
#define ADC_DSM_SUMCAPIN_900_FF        (0x12u)
#define ADC_DSM_SUMCAPIN_950_FF        (0x13u)
#define ADC_DSM_SUMCAPIN_1000_FF       (0x14u)
#define ADC_DSM_SUMCAPIN_1050_FF       (0x15u)
#define ADC_DSM_SUMCAPIN_1100_FF       (0x16u)
#define ADC_DSM_SUMCAPIN_1150_FF       (0x17u)
#define ADC_DSM_SUMCAPIN_1200_FF       (0x18u)
#define ADC_DSM_SUMCAPIN_1250_FF       (0x19u)
#define ADC_DSM_SUMCAPIN_1300_FF       (0x1Au)
#define ADC_DSM_SUMCAPIN_1350_FF       (0x1Bu)
#define ADC_DSM_SUMCAPIN_1400_FF       (0x1Cu)
#define ADC_DSM_SUMCAPIN_1450_FF       (0x1Du)
#define ADC_DSM_SUMCAPIN_1500_FF       (0x1Eu)
#define ADC_DSM_SUMCAPIN_1550_FF       (0x15u)


/********************************************/
/* DSM.CR13 Control Register 13 definitions */
/********************************************/

#define ADC_DSM_CR13_RSVD              (0xFFu)


/********************************************/
/* DSM.CR14 Control Register 14 definitions */
/********************************************/

/* Bit Field  DSM_POWER1 */
#define ADC_DSM_POWER1_MASK            (0x07u)

#define ADC_DSM_POWER1_0               (0x00u)
#define ADC_DSM_POWER1_1               (0x01u)
#define ADC_DSM_POWER1_2               (0x02u)
#define ADC_DSM_POWER1_3               (0x03u)
#define ADC_DSM_POWER1_4               (0x04u)
#define ADC_DSM_POWER1_5               (0x05u)
#define ADC_DSM_POWER1_6               (0x06u)
#define ADC_DSM_POWER1_7               (0x07u)
  
#define ADC_DSM_POWER1_44UA            (0x00u)
#define ADC_DSM_POWER1_123UA           (0x01u)
#define ADC_DSM_POWER1_492UA           (0x02u)
#define ADC_DSM_POWER1_750UA           (0x03u)
#define ADC_DSM_POWER1_1MA             (0x04u)

/* Bit Field  DSM_OPAMP1_BW */
#define ADC_DSM_OPAMP1_BW_MASK         (0xF0u)
#define ADC_DSM_OPAMP1_BW_0            (0x00u)
#define ADC_DSM_OPAMP1_BW_1            (0x10u)
#define ADC_DSM_OPAMP1_BW_2            (0x20u)
#define ADC_DSM_OPAMP1_BW_3            (0x30u)
#define ADC_DSM_OPAMP1_BW_4            (0x40u)
#define ADC_DSM_OPAMP1_BW_5            (0x50u)
#define ADC_DSM_OPAMP1_BW_6            (0x60u)
#define ADC_DSM_OPAMP1_BW_7            (0x70u)
#define ADC_DSM_OPAMP1_BW_8            (0x80u)
#define ADC_DSM_OPAMP1_BW_9            (0x90u)
#define ADC_DSM_OPAMP1_BW_A            (0xA0u)
#define ADC_DSM_OPAMP1_BW_B            (0xB0u)
#define ADC_DSM_OPAMP1_BW_C            (0xC0u)
#define ADC_DSM_OPAMP1_BW_D            (0xD0u)
#define ADC_DSM_OPAMP1_BW_E            (0xE0u)
#define ADC_DSM_OPAMP1_BW_F            (0xF0u)


/********************************************/
/* DSM.CR15 Control Register 15 definitions */
/********************************************/

/* Bit Field  DSM_POWER2_3 */
#define ADC_DSM_POWER2_3_MASK          (0x07u)

#define ADC_DSM_POWER2_3_LOW           (0x00u)
#define ADC_DSM_POWER2_3_MED           (0x01u)
#define ADC_DSM_POWER2_3_HIGH          (0x02u)
#define ADC_DSM_POWER2_3_IP5X          (0x03u)
#define ADC_DSM_POWER2_3_2X            (0x04u)
#define ADC_DSM_POWER2_3_HIGH_5        (0x05u)
#define ADC_DSM_POWER2_3_HIGH_6        (0x06u)
#define ADC_DSM_POWER2_3_HIGH_7        (0x07u)

/* Bit Field  DSM_POWER_COMP */
#define ADC_DSM_POWER_COMP_MASK        (0x30u)

#define ADC_DSM_POWER_VERYLOW          (0x00u)
#define ADC_DSM_POWER_NORMAL           (0x10u)
#define ADC_DSM_POWER_6MHZ             (0x20u)
#define ADC_DSM_POWER_12MHZ            (0x30u)


/********************************************/
/* DSM.CR16 Control Register 16 definitions */
/********************************************/

/* Bit Field  DSM_POWER_SUM */
#define ADC_DSM_POWER_SUM_MASK         (0x70u)

#define ADC_DSM_POWER_SUM_LOW          (0x00u)
#define ADC_DSM_POWER_SUM_MED          (0x10u)
#define ADC_DSM_POWER_SUM_HIGH         (0x20u)
#define ADC_DSM_POWER_SUM_IP5X         (0x30u)
#define ADC_DSM_POWER_SUM_2X           (0x40u)
#define ADC_DSM_POWER_SUM_HIGH_5       (0x50u)
#define ADC_DSM_POWER_SUM_HIGH_6       (0x60u)
#define ADC_DSM_POWER_SUM_HIGH_7       (0x70u)

#define ADC_DSM_CP_ENABLE              (0x08u)
#define ADC_DSM_CP_PWRCTL_MASK         (0x07u)
#define ADC_DSM_CP_PWRCTL_DEFAULT      (0x0Au)
#define ADC_DSM_CP_PWRCTL_2X           (0x09u)
#define ADC_DSM_CP_PWRCTL_LOW          (0x04u)


/********************************************/
/* DSM.CR17 Control Register 17 definitions */
/********************************************/

/* Bit Field  DSM_EN_BUF */
#define ADC_DSM_EN_BUF_VREF            (0x01u)
#define ADC_DSM_EN_BUF_VCM             (0x02u)

#define ADC_DSM_PWR_CTRL_VREF_MASK     (0x0Cu)
#define ADC_DSM_PWR_CTRL_VREF_0        (0x00u)
#define ADC_DSM_PWR_CTRL_VREF_1        (0x04u)
#define ADC_DSM_PWR_CTRL_VREF_2        (0x08u)
#define ADC_DSM_PWR_CTRL_VREF_3        (0x0Cu)

#define ADC_DSM_PWR_CTRL_VCM_MASK      (0x30u)
#define ADC_DSM_PWR_CTRL_VCM_0         (0x00u)
#define ADC_DSM_PWR_CTRL_VCM_1         (0x10u)
#define ADC_DSM_PWR_CTRL_VCM_2         (0x20u)
#define ADC_DSM_PWR_CTRL_VCM_3         (0x30u)

#define ADC_DSM_PWR_CTRL_VREF_INN_MASK (0xC0u)
#define ADC_DSM_PWR_CTRL_VREF_INN_0    (0x00u)
#define ADC_DSM_PWR_CTRL_VREF_INN_1    (0x40u)
#define ADC_DSM_PWR_CTRL_VREF_INN_2    (0x80u)
#define ADC_DSM_PWR_CTRL_VREF_INN_3    (0xC0u)


/*********************************************/
/* DSM.REF0 Reference Register 0 definitions */
/*********************************************/

#define ADC_DSM_REFMUX_MASK            (0x07u)
#define ADC_DSM_REFMUX_NONE            (0x00u)
#define ADC_DSM_REFMUX_UVCM            (0x01u)
#define ADC_DSM_REFMUX_VDA_4           (0x02u)
#define ADC_DSM_REFMUX_VDAC0           (0x03u)
#define ADC_DSM_REFMUX_1_024V          (0x04u)
#define ADC_DSM_REFMUX_1_20V           (0x05u)

#define ADC_DSM_EN_BUF_VREF_INN        (0x08u)
#define ADC_DSM_VREF_RES_DIV_EN        (0x10u)
#define ADC_DSM_VCM_RES_DIV_EN         (0x20u)
#define ADC_DSM_VCMSEL_MASK            (0xC0u)
#define ADC_DSM_VCMSEL_NOSEL           (0x00u)
#define ADC_DSM_VCMSEL_0_8V            (0x40u)
#define ADC_DSM_VCMSEL_0_7V            (0x80u)
#define ADC_DSM_VCMSEL_VPWRA_2         (0xC0u)


/*********************************************/
/* DSM.REF1 Reference Register 1 definitions */
/*********************************************/

#define ADC_DSM_REF1_MASK              (0xFFu)


/*********************************************/
/* DSM.REF2 Reference Register 2 definitions */
/*********************************************/

#define ADC_DSM_REF2_MASK              (0xFFu)
#define ADC_DSM_REF2_S0_EN             (0x01u)
#define ADC_DSM_REF2_S1_EN             (0x02u)
#define ADC_DSM_REF2_S2_EN             (0x04u)
#define ADC_DSM_REF2_S3_EN             (0x08u)
#define ADC_DSM_REF2_S4_EN             (0x10u)
#define ADC_DSM_REF2_S5_EN             (0x20u)
#define ADC_DSM_REF2_S6_EN             (0x40u)
#define ADC_DSM_REF2_S7_EN             (0x80u)


/*********************************************/
/* DSM.REF3 Reference Register 3 definitions */
/*********************************************/

#define ADC_DSM_REF3_MASK              (0xFFu)
#define ADC_DSM_REF2_S8_EN             (0x01u)
#define ADC_DSM_REF2_S9_EN             (0x02u)
#define ADC_DSM_REF2_S10_EN            (0x04u)
#define ADC_DSM_REF2_S11_EN            (0x08u)
#define ADC_DSM_REF2_S12_EN            (0x10u)
#define ADC_DSM_REF2_S13_EN            (0x20u)


/************************************************/
/* DSM.DEM0 Dynamic Element Matching Register 0 */
/************************************************/

#define ADC_DSM_EN_SCRAMBLER0          (0x01u)
#define ADC_DSM_EN_SCRAMBLER1          (0x02u)
#define ADC_DSM_EN_DEM                 (0x04u)
#define ADC_DSM_ADC_TEST_EN            (0x08u)
#define ADC_DSM_DEMTEST_SRC            (0x10u)


/************************************************/
/* DSM.DEM1 Dynamic Element Matching Register 1 */
/************************************************/

#define ADC_DSM_DEM1_MASK              (0xFF)


/***********************************************/
/* DSM.BUF0 Buffer Register 0                  */
/***********************************************/

#define ADC_DSM_ENABLE_P               (0x01u)
#define ADC_DSM_BYPASS_P               (0x02u)
#define ADC_DSM_RAIL_RAIL_EN           (0x04u)

#define ADC_DSM_BUFSEL                 (0x08u)
#define ADC_DSM_BUFSEL_A               (0x00u)
#define ADC_DSM_BUFSEL_B               (0x08u)


/***********************************************/
/* DSM.BUF1 Buffer Register 1                  */
/***********************************************/

#define ADC_DSM_ENABLE_N               (0x01u)
#define ADC_DSM_BYPASS_N               (0x02u)
#define ADC_DSM_GAIN_MASK              (0x0Cu)


/***********************************************/
/* DSM.BUF2 Buffer Register 2                  */
/***********************************************/

#define ADC_DSM_LOWPOWER_EN            (0x01u)
#define ADC_DSM_ADD_EXTRA_RC           (0x02u)


/***********************************************/
/* DSM.BUF3 Buffer Register 3                  */
/***********************************************/

#define ADC_DSM_BUF_CHOP_EN            (0x08u)

#define ADC_DSM_BUF_FCHOP_MASK         (0x07u)
#define ADC_DSM_BUF_FCHOP_FS2          (0x00u)
#define ADC_DSM_BUF_FCHOP_FS4          (0x01u)
#define ADC_DSM_BUF_FCHOP_FS8          (0x02u)
#define ADC_DSM_BUF_FCHOP_FS16         (0x03u)
#define ADC_DSM_BUF_FCHOP_FS32         (0x04u)
#define ADC_DSM_BUF_FCHOP_FS64         (0x05u)
#define ADC_DSM_BUF_FCHOP_FS128        (0x06u)
#define ADC_DSM_BUF_FCHOP_FS256        (0x07u)


/***********************************************/
/* DSM.MISC Delta Sigma Misc Register          */
/***********************************************/

#define ADC_DSM_SEL_ICLK_CP            (0x01u)


/************************************************/
/* DSM.CLK Delta Sigma Clock selection Register */
/************************************************/

#define ADC_DSM_CLK_MX_CLK_MSK         (0x07u)
#define ADC_DSM_CLK_CLK_EN             (0x08u)
#define ADC_DSM_CLK_BYPASS_SYNC        (0x10u)


/***********************************************/
/* DSM.OUT0 Output Register 0                  */
/***********************************************/
#define ADC_DSM_DOUT0                  (0xFFu)


/***********************************************/
/* DSM.OUT1 Output Register 1                  */
/***********************************************/
#define ADC_DSM_DOUT2SCOMP_MASK        (0x0Fu)
#define ADC_DSM_OVDFLAG                (0x10u)
#define ADC_DSM_OVDCAUSE               (0x20u)


/***********************************************/
/*          Decimator                          */
/***********************************************/


/***********************************************/
/* DEC.CR Control Register 0                   */
/***********************************************/

#define ADC_DEC_SAT_EN                 (0x80u) /* Enable post process offset correction */
#define ADC_DEC_FIR_EN                 (0x40u) /* Post process FIR enable  */
#define ADC_DEC_OCOR_EN                (0x20u) /* Offest correction enable */
#define ADC_DEC_GCOR_EN                (0x10u) /* Enable gain correction feature */

#define ADC_MODE_MASK                  (0x0Cu) /* Conversion Mode */
#define ADC_MODE_SINGLE_SAMPLE         (0x00u)
#define ADC_MODE_FAST_FILTER           (0x04u)
#define ADC_MODE_CONTINUOUS            (0x08u)
#define ADC_MODE_FAST_FIR              (0x0Cu)

#define ADC_DEC_XSTART_EN              (0x02u) /* Enables external start signal */
#define ADC_DEC_START_CONV             (0x01u) /* A write to this bit starts a conversion */


/***********************************************/
/* DEC.SR Status and Control Register 0        */
/***********************************************/

#define ADC_DEC_CORECLK_DISABLE        (0x20u) /* Controls gating of the Core clock */
#define ADC_DEC_INTR_PULSE             (0x10u) /* Controls interrupt mode */ 
#define ADC_DEC_OUT_ALIGN              (0x08u) /* Controls 8-bit shift of SAMP registers */
#define ADC_DEC_INTR_CLEAR             (0x04u) /* A write to this bit clears bit0 */
#define ADC_DEC_INTR_MASK              (0x02u) /* Controls the generation of the conversion comp. INTR */
#define ADC_DEC_CONV_DONE              (0x01u) /* Bit set if conversion has completed  */


/***********************************************/
/* DEC.SHIFT1 Decimator Input Shift Register 1 */
/***********************************************/

#define ADC_DEC_SHIFT1_MASK            (0x1Fu) /* Input shift1 control */


/***********************************************/
/* DEC.SHIFT2 Decimator Input Shift Register 2 */
/***********************************************/

#define ADC_DEC_SHIFT2_MASK            (0x0Fu) /* Input shift2 control */


/****************************************************************/
/* DEC.DR2 Decimator Decimation Rate of FIR Filter Low Register */
/****************************************************************/

#define ADC_DEC_DR2_MASK               (0xFFu)


/******************************************************************/
/* DEC.DR2H Decimator Decimation Rate of FIR Filter High Register */
/******************************************************************/

#define ADC_DEC_DR2H_MASK              (0x03u)


/***********************************************/
/* DEC.COHR Decimator Coherency Register       */
/***********************************************/

#define ADC_DEC_GCOR_KEY_MASK          (0x30u) 
#define ADC_DEC_GCOR_KEY_OFF           (0x00u) 
#define ADC_DEC_GCOR_KEY_LOW           (0x10u) 
#define ADC_DEC_GCOR_KEY_MID           (0x20u) 
#define ADC_DEC_GCOR_KEY_HIGH          (0x30u) 

#define ADC_DEC_OCOR_KEY_MASK          (0x0Cu)
#define ADC_DEC_OCOR_KEY_OFF           (0x00u) 
#define ADC_DEC_OCOR_KEY_LOW           (0x04u) 
#define ADC_DEC_OCOR_KEY_MID           (0x08u) 
#define ADC_DEC_OCOR_KEY_HIGH          (0x0Cu) 

#define ADC_DEC_SAMP_KEY_MASK          (0x03u) 
#define ADC_DEC_SAMP_KEY_OFF           (0x00u) 
#define ADC_DEC_SAMP_KEY_LOW           (0x01u) 
#define ADC_DEC_SAMP_KEY_MID           (0x02u) 
#define ADC_DEC_SAMP_KEY_HIGH          (0x03u)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define ADC_ACT_PWR_DEC_EN             ADC_DEC__PM_ACT_MSK /* Power enable mask */
#define ADC_STBY_PWR_DEC_EN            ADC_DEC__PM_STBY_MSK /* Power enable mask */

/* Active and Alternative active power masks for DSM */

#if (CY_PSOC3 || CY_PSOC5LP)
    #define ADC_ACT_PWR_DSM_EN         (0x10u) /* Active Power enable mask */
    #define ADC_STBY_PWR_DSM_EN        (0x10u) /* Alternate active Power enable mask */
#elif (CY_PSOC5A)
    #define ADC_ACT_PWR_DSM_EN         (0x01u) /* Power enable mask */
#endif /* CY_PSOC5A */


/* Internal and charge pump clock power enable masks */
#if(ADC_DEFAULT_INTERNAL_CLK)
    #define ADC_ACT_PWR_CLK_EN              ADC_theACLK__PM_ACT_MSK 
    #define ADC_STBY_PWR_CLK_EN             ADC_theACLK__PM_STBY_MSK 
#endif /* ADC_DEFAULT_INTERNAL_CLK */

#define ADC_ACT_PWR_CHARGE_PUMP_CLK_EN  ADC_Ext_CP_Clk__PM_ACT_MSK 
#define ADC_STBY_PWR_CHARGE_PUMP_CLK_EN ADC_Ext_CP_Clk__PM_STBY_MSK 


/***********************************************/
/* DSM.SW3 DSM Analog Routing Register 3       */
/***********************************************/
#define ADC_DSM_VP_VSSA                (0x04u) 

/* To connect negative input to analog mux Bus. This is valid only
   for PSoC5A */
#if(CY_PSOC5A)
    #define ADC_DSM_VN_AMX             (0x10u) 
#endif /* CY_PSOC5A */

/* To connect positive input to analog mux Bus. This is valid only
   for PSoC3 or PSoC5LP silicon */
#if(CY_PSOC3 || CY_PSOC5LP)
    #define ADC_DSM_VP_AMX             (0x01u) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define ADC_DSM_VN_VREF                (0x20u) 
#define ADC_DSM_VN_VSSA                (0x40u) 
#define ADC_DSM_VN_REF_MASK            (0x60u) 


/***********************************************/
/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
/***********************************************/

#define ADC_PUMP_CR1_CLKSEL            (0x04u)
#define ADC_PUMP_CR1_FORCE             (0x02u)
#define ADC_PUMP_CR1_AUTO              (0x01u)

/***********************************************/
/* RESET_CR4 Reset Ignore Control Register     */
/***********************************************/ 

#define ADC_IGNORE_PRESD1              (0x01u) 
#define ADC_IGNORE_PRESA1              (0x02u)
#define ADC_IGNORE_LPCOMPD1            (0x04u)
#define ADC_IGNORE_LPCOMPA1            (0x08u)
#define ADC_IGNORE_HBR1                (0x10u)


/***********************************************/
/* RESET_CR5 Reset Ignore Control Register     */
/***********************************************/ 

#define ADC_IGNORE_PRESD2              (0x01u) 
#define ADC_IGNORE_PRESA2              (0x02u)
#define ADC_IGNORE_LPCOMPD2            (0x04u)
#define ADC_IGNORE_LPCOMPA2            (0x08u)
#define ADC_IGNORE_HBR2                (0x10u)


/***********************************************/
/* RESET_CR1 Reset Ignore Control Register     */
/***********************************************/ 

#define ADC_DIS_HBR1                   (0x20u) 
#define ADC_DIS_PRES1                  (0x10u)
#define ADC_VMON_HVI_SEL               (0x08u)
#define ADC_EN_HVI_A                   (0x04u)
#define ADC_EN_LVI_A                   (0x02u)
#define ADC_EN_LVI_D                   (0x01u)


/***********************************************/
/* RESET_CR3 Reset Ignore Control Register     */
/***********************************************/ 

#define ADC_DIS_PRES2                  (0x08u) 
#define ADC_DIS_HBR2                   (0x10u)


/***************************************
*              Registers        
***************************************/

/* Decimator (DEC) Registers */
#define ADC_DEC_CR_REG               (* (reg8 *) ADC_DEC__CR )
#define ADC_DEC_CR_PTR               (  (reg8 *) ADC_DEC__CR )

#define ADC_DEC_SR_REG               (* (reg8 *) ADC_DEC__SR )
#define ADC_DEC_SR_PTR               (  (reg8 *) ADC_DEC__SR )

#define ADC_DEC_SHIFT1_REG           (* (reg8 *) ADC_DEC__SHIFT1 )
#define ADC_DEC_SHIFT1_PTR           (  (reg8 *) ADC_DEC__SHIFT1 )

#define ADC_DEC_SHIFT2_REG           (* (reg8 *) ADC_DEC__SHIFT2 )
#define ADC_DEC_SHIFT2_PTR           ( (reg8 *) ADC_DEC__SHIFT2 )

#define ADC_DEC_DR2_REG              (* (reg8 *) ADC_DEC__DR2 )
#define ADC_DEC_DR2_PTR              (  (reg8 *) ADC_DEC__DR2 )

#define ADC_DEC_DR2H_REG             (* (reg8 *) ADC_DEC__DR2H )
#define ADC_DEC_DR2H_PTR             (  (reg8 *) ADC_DEC__DR2H )

#define ADC_DEC_DR1_REG              (* (reg8 *) ADC_DEC__DR1 )
#define ADC_DEC_DR1_PTR              (  (reg8 *) ADC_DEC__DR1 )

#define ADC_DEC_OCOR_REG             (* (reg8 *) ADC_DEC__OCOR )
#define ADC_DEC_OCOR_PTR             (  (reg8 *) ADC_DEC__OCOR )

#define ADC_DEC_OCORM_REG            (* (reg8 *) ADC_DEC__OCORM )
#define ADC_DEC_OCORM_PTR            (  (reg8 *) ADC_DEC__OCORM )

#define ADC_DEC_OCORH_REG            (* (reg8 *) ADC_DEC__OCORH )
#define ADC_DEC_OCORH_PTR            (  (reg8 *) ADC_DEC__OCORH )

#define ADC_DEC_GVAL_REG             (* (reg8 *) ADC_DEC__GVAL )
#define ADC_DEC_GVAL_PTR             (  (reg8 *) ADC_DEC__GVAL )

#define ADC_DEC_GCOR_REG             (* (reg8 *) ADC_DEC__GCOR )
#define ADC_DEC_GCOR_PTR             (  (reg8 *) ADC_DEC__GCOR )

#define ADC_DEC_GCORH_REG            (* (reg8 *) ADC_DEC__GCORH )
#define ADC_DEC_GCORH_PTR            (  (reg8 *) ADC_DEC__GCORH )

#define ADC_DEC_SAMP_REG             (* (reg8 *) ADC_DEC__OUTSAMP )
#define ADC_DEC_SAMP_PTR             (  (reg8 *) ADC_DEC__OUTSAMP )

#define ADC_DEC_SAMPM_REG            (* (reg8 *) ADC_DEC__OUTSAMPM )
#define ADC_DEC_SAMPM_PTR            (  (reg8 *) ADC_DEC__OUTSAMPM )

#define ADC_DEC_SAMPH_REG            (* (reg8 *) ADC_DEC__OUTSAMPH )
#define ADC_DEC_SAMPH_PTR            (  (reg8 *) ADC_DEC__OUTSAMPH )

#define ADC_DEC_COHER_REG            (* (reg8 *) ADC_DEC__COHER )
#define ADC_DEC_COHER_PTR            (  (reg8 *) ADC_DEC__COHER )

#define ADC_PWRMGR_DEC_REG           (* (reg8 *) ADC_DEC__PM_ACT_CFG )    
#define ADC_PWRMGR_DEC_PTR           (  (reg8 *) ADC_DEC__PM_ACT_CFG )

#define ADC_STBY_PWRMGR_DEC_REG      (* (reg8 *) ADC_DEC__PM_STBY_CFG )     
#define ADC_STBY_PWRMGR_DEC_PTR      (  (reg8 *) ADC_DEC__PM_STBY_CFG )

/* Delta Sigma Modulator (DSM) Registers */  
#define ADC_DSM_CR0_REG              (* (reg8 *) ADC_DSM4__CR0 )
#define ADC_DSM_CR0_PTR              (  (reg8 *) ADC_DSM4__CR0 )

#define ADC_DSM_CR1_REG              (* (reg8 *) ADC_DSM4__CR1 )
#define ADC_DSM_CR1_PTR              (  (reg8 *) ADC_DSM4__CR1 )

#define ADC_DSM_CR2_REG              (* (reg8 *) ADC_DSM4__CR2 )
#define ADC_DSM_CR2_PTR              (  (reg8 *) ADC_DSM4__CR2 )

#define ADC_DSM_CR3_REG              (* (reg8 *) ADC_DSM4__CR3 )
#define ADC_DSM_CR3_PTR              (  (reg8 *) ADC_DSM4__CR3 )

#define ADC_DSM_CR4_REG              (* (reg8 *) ADC_DSM4__CR4 )
#define ADC_DSM_CR4_PTR              (  (reg8 *) ADC_DSM4__CR4 )

#define ADC_DSM_CR5_REG              (* (reg8 *) ADC_DSM4__CR5 )
#define ADC_DSM_CR5_PTR              (  (reg8 *) ADC_DSM4__CR5 )

#define ADC_DSM_CR6_REG              (* (reg8 *) ADC_DSM4__CR6 )
#define ADC_DSM_CR6_PTR              (  (reg8 *) ADC_DSM4__CR6 )

#define ADC_DSM_CR7_REG              (* (reg8 *) ADC_DSM4__CR7 )
#define ADC_DSM_CR7_PTR              (  (reg8 *) ADC_DSM4__CR7 )

#define ADC_DSM_CR8_REG              (* (reg8 *) ADC_DSM4__CR8 )
#define ADC_DSM_CR8_PTR              (  (reg8 *) ADC_DSM4__CR8 )

#define ADC_DSM_CR9_REG              (* (reg8 *) ADC_DSM4__CR9 )
#define ADC_DSM_CR9_PTR              (  (reg8 *) ADC_DSM4__CR9 )

#define ADC_DSM_CR10_REG             (* (reg8 *) ADC_DSM4__CR10 )
#define ADC_DSM_CR10_PTR             (  (reg8 *) ADC_DSM4__CR10 )

#define ADC_DSM_CR11_REG             (* (reg8 *) ADC_DSM4__CR11 )
#define ADC_DSM_CR11_PTR             (  (reg8 *) ADC_DSM4__CR11 )

#define ADC_DSM_CR12_REG             (* (reg8 *) ADC_DSM4__CR12 )
#define ADC_DSM_CR12_PTR             (  (reg8 *) ADC_DSM4__CR12 )

#define ADC_DSM_CR13_REG             (* (reg8 *) ADC_DSM4__CR13 )
#define ADC_DSM_CR13_PTR             (  (reg8 *) ADC_DSM4__CR13 )

#define ADC_DSM_CR14_REG             (* (reg8 *) ADC_DSM4__CR14 )
#define ADC_DSM_CR14_PTR             (  (reg8 *) ADC_DSM4__CR14 )

#define ADC_DSM_CR15_REG             (* (reg8 *) ADC_DSM4__CR15 )
#define ADC_DSM_CR15_PTR             (  (reg8 *) ADC_DSM4__CR15 )

#define ADC_DSM_CR16_REG             (* (reg8 *) ADC_DSM4__CR16 )
#define ADC_DSM_CR16_PTR             (  (reg8 *) ADC_DSM4__CR16 )

#define ADC_DSM_CR17_REG             (* (reg8 *) ADC_DSM4__CR17 )
#define ADC_DSM_CR17_PTR             (  (reg8 *) ADC_DSM4__CR17 )

#define ADC_DSM_REF0_REG             (* (reg8 *) ADC_DSM4__REF0 )
#define ADC_DSM_REF0_PTR             (  (reg8 *) ADC_DSM4__REF0 )

#define ADC_DSM_REF1_REG             (* (reg8 *) ADC_DSM4__REF1 )
#define ADC_DSM_REF1_PTR             (  (reg8 *) ADC_DSM4__REF1 )

#define ADC_DSM_REF2_REG             (* (reg8 *) ADC_DSM4__REF2 )
#define ADC_DSM_REF2_PTR             (  (reg8 *) ADC_DSM4__REF2 )

#define ADC_DSM_REF3_REG             (* (reg8 *) ADC_DSM4__REF3 )
#define ADC_DSM_REF3_PTR             (  (reg8 *) ADC_DSM4__REF3 )

#define ADC_DSM_DEM0_REG             (* (reg8 *) ADC_DSM4__DEM0 )
#define ADC_DSM_DEM0_PTR             (  (reg8 *) ADC_DSM4__DEM0 )

#define ADC_DSM_DEM1_REG             (* (reg8 *) ADC_DSM4__DEM1 )
#define ADC_DSM_DEM1_PTR             (  (reg8 *) ADC_DSM4__DEM1 )

#define ADC_DSM_MISC_REG             (* (reg8 *) ADC_DSM4__MISC )
#define ADC_DSM_MISC_PTR             (  (reg8 *) ADC_DSM4__MISC )

#define ADC_DSM_CLK_REG              (* (reg8 *) ADC_DSM4__CLK )
#define ADC_DSM_CLK_PTR              (  (reg8 *) ADC_DSM4__CLK )

#define ADC_DSM_TST0_REG             (* (reg8 *) ADC_DSM4__TST0 )
#define ADC_DSM_TST0_PTR             (  (reg8 *) ADC_DSM4__TST0 )

#define ADC_DSM_TST1_REG             (* (reg8 *) ADC_DSM4__TST1 )
#define ADC_DSM_TST1_PTR             (  (reg8 *) ADC_DSM4__TST1 )

#define ADC_DSM_BUF0_REG             (* (reg8 *) ADC_DSM4__BUF0 )
#define ADC_DSM_BUF0_PTR             (  (reg8 *) ADC_DSM4__BUF0 )

#define ADC_DSM_BUF1_REG             (* (reg8 *) ADC_DSM4__BUF1 )
#define ADC_DSM_BUF1_PTR             (  (reg8 *) ADC_DSM4__BUF1 )

#define ADC_DSM_BUF2_REG             (* (reg8 *) ADC_DSM4__BUF2 )
#define ADC_DSM_BUF2_PTR             (  (reg8 *) ADC_DSM4__BUF2 )

#define ADC_DSM_BUF3_REG             (* (reg8 *) ADC_DSM4__BUF3 )
#define ADC_DSM_BUF3_PTR             (  (reg8 *) ADC_DSM4__BUF3 )

#define ADC_DSM_OUT0_REG             (* (reg8 *) ADC_DSM4__OUT0 )
#define ADC_DSM_OUT0_PTR             (  (reg8 *) ADC_DSM4__OUT0 )

#define ADC_DSM_OUT1_REG             (* (reg8 *) ADC_DSM4__OUT1 )
#define ADC_DSM_OUT1_PTR             (  (reg8 *) ADC_DSM4__OUT1 )

#define ADC_DSM_SW0_REG              (* (reg8 *) ADC_DSM4__SW0 )
#define ADC_DSM_SW0_PTR              (  (reg8 *) ADC_DSM4__SW0 )

#define ADC_DSM_SW2_REG              (* (reg8 *) ADC_DSM4__SW2 )
#define ADC_DSM_SW2_PTR              (  (reg8 *) ADC_DSM4__SW2 )

#define ADC_DSM_SW3_REG              (* (reg8 *) ADC_DSM4__SW3 )
#define ADC_DSM_SW3_PTR              (  (reg8 *) ADC_DSM4__SW3 )

#define ADC_DSM_SW4_REG              (* (reg8 *) ADC_DSM4__SW4 )
#define ADC_DSM_SW4_PTR              (  (reg8 *) ADC_DSM4__SW4 )

#define ADC_DSM_SW6_REG              (* (reg8 *) ADC_DSM4__SW6 )
#define ADC_DSM_SW6_PTR              (  (reg8 *) ADC_DSM4__SW6 )

/* Charge pump configuration register */
#define ADC_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define ADC_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* DSM Active Power manager register */

#if(CY_PSOC3 || CY_PSOC5LP)
    #define ADC_PWRMGR_DSM_REG       (* (reg8 *) CYDEV_PM_ACT_CFG10 )  /* Modulator Power manager */
    #define ADC_PWRMGR_DSM_PTR       (  (reg8 *) CYDEV_PM_ACT_CFG10 )  /* Modulator Power manager */
#elif (CY_PSOC5A)
    #define ADC_PWRMGR_DSM_REG       (* (reg8 *) CYDEV_PM_AVAIL_CR5 )  /* Modulator Power manager */
    #define ADC_PWRMGR_DSM_PTR       (  (reg8 *) CYDEV_PM_AVAIL_CR5 )  /* Modulator Power manager */
#endif /* CY_PSOC5A */

/* DSM Alternative Active Power manager register */

#if(CY_PSOC3 || CY_PSOC5LP)
    #define ADC_STBY_PWRMGR_DSM_REG  (* (reg8 *) CYDEV_PM_STBY_CFG10 )  
    #define ADC_STBY_PWRMGR_DSM_PTR  (  (reg8 *) CYDEV_PM_STBY_CFG10 )  
#endif /* CY_PSOC3 || CY_PSOC5LP */

/* This is only valid if there is an internal clock */
#if(ADC_DEFAULT_INTERNAL_CLK)
    #define ADC_PWRMGR_CLK_REG       (* (reg8 *) ADC_theACLK__PM_ACT_CFG ) 
    #define ADC_PWRMGR_CLK_PTR       (  (reg8 *) ADC_theACLK__PM_ACT_CFG ) 

    #define ADC_STBY_PWRMGR_CLK_REG  (* (reg8 *) ADC_theACLK__PM_STBY_CFG )
    #define ADC_STBY_PWRMGR_CLK_PTR  (  (reg8 *) ADC_theACLK__PM_STBY_CFG )
#endif /* ADC_DEFAULT_INTERNAL_CLK */

/* This is only valid if there is an external charge clock */

/* Clock power manager register */
#define ADC_PWRMGR_CHARGE_PUMP_CLK_REG       (* (reg8 *) ADC_Ext_CP_Clk__PM_ACT_CFG )
#define ADC_PWRMGR_CHARGE_PUMP_CLK_PTR       (  (reg8 *) ADC_Ext_CP_Clk__PM_ACT_CFG )

#define ADC_STBY_PWRMGR_CHARGE_PUMP_CLK_REG  (* (reg8 *) ADC_Ext_CP_Clk__PM_STBY_CFG ) 
#define ADC_STBY_PWRMGR_CHARGE_PUMP_CLK_PTR  (  (reg8 *) ADC_Ext_CP_Clk__PM_STBY_CFG ) 

/* PRES-A related registers */
#if (CY_PSOC3 || CY_PSOC5LP)

    #define ADC_RESET_CR4_REG                    (* (reg8 *) CYDEV_RESET_CR4)
    #define ADC_RESET_CR4_PTR                    (  (reg8 *) CYDEV_RESET_CR4)

    #define ADC_RESET_CR5_REG                    (* (reg8 *) CYDEV_RESET_CR5)
    #define ADC_RESET_CR5_PTR                    (  (reg8 *) CYDEV_RESET_CR5)
    
#elif (CY_PSOC5A)
    #define ADC_RESET_CR1_REG                    (* (reg8 *) CYDEV_RESET_CR1)
    #define ADC_RESET_CR1_PTR                    (  (reg8 *) CYDEV_RESET_CR1)

    #define ADC_RESET_CR3_REG                    (* (reg8 *) CYDEV_RESET_CR3)
    #define ADC_RESET_CR3_PTR                    (  (reg8 *) CYDEV_RESET_CR3)
    
#endif /* CY_PSOC5A */
    

/* Default register settings for the Config 1 */
/* Default Config */
/* ADC_CFG1 Sample Rate: 10000 Samples per Second */
/* ADC_CFG1 Conversion Mode: 0 */
/* ADC_CFG1 Input Buffer Gain: 1   */
/* ADC_CFG1 Reference: 5 */
/* ADC_CFG1 Input Range: 2  */
/* ADC_CFG1 Resolution: 8 bits */
/* ADC_CFG1 Clock: 670000 Hz */

#define ADC_CFG1_DEC_CR             (0X30u)
#define ADC_CFG1_DEC_SR             (0X14u)
#define ADC_CFG1_DEC_SHIFT1         (0X04u)
#define ADC_CFG1_DEC_SHIFT2         (0X06u)
#define ADC_CFG1_DEC_DR2            (0X00u)
#define ADC_CFG1_DEC_DR2H           (0X00u)
#define ADC_CFG1_DEC_DR1            (0X0Fu)
#define ADC_CFG1_DEC_OCOR           (0X00u)
#define ADC_CFG1_DEC_OCORM          (0X00u)
#define ADC_CFG1_DEC_OCORH          (0X00u)
#define ADC_CFG1_DEC_GVAL           (0X09u)
#define ADC_CFG1_DEC_GCOR           (0X00u)
#define ADC_CFG1_DEC_GCORH          (0X00u)
#define ADC_CFG1_DEC_COHER          (0X01u)
#define ADC_CFG1_DSM_CR0            (0X0Au)
#define ADC_CFG1_DSM_CR1            (0X00u)
#define ADC_CFG1_DSM_CR2            (0X7Au)
#define ADC_CFG1_DSM_CR3            (0X00u)
#define ADC_CFG1_DSM_CR4            (0X14u)
#define ADC_CFG1_DSM_CR5            (0X0Bu)
#define ADC_CFG1_DSM_CR6            (0X31u)
#define ADC_CFG1_DSM_CR7            (0X00u)
#define ADC_CFG1_DSM_CR8            (0X12u)
#define ADC_CFG1_DSM_CR9            (0X13u)
#define ADC_CFG1_DSM_CR10           (0X44u)
#define ADC_CFG1_DSM_CR11           (0X48u)
#define ADC_CFG1_DSM_CR12           (0X01u)
#define ADC_CFG1_DSM_CR13           (0X00u)
#define ADC_CFG1_DSM_CR14           (0X01u)
#define ADC_CFG1_DSM_CR15           (0X11u)
#define ADC_CFG1_DSM_CR16           (0X19u)
#define ADC_CFG1_DSM_CR17           (0X97u)
#define ADC_CFG1_DSM_REF0           (0X52u)
#define ADC_CFG1_DSM_REF1           (0X00u)
#define ADC_CFG1_DSM_REF2           (0X58u)
#define ADC_CFG1_DSM_REF3           (0X00u)
#define ADC_CFG1_DSM_DEM0           (0X07u)
#define ADC_CFG1_DSM_DEM1           (0X00u)
#define ADC_CFG1_DSM_MISC           (0X00u)
#define ADC_CFG1_DSM_CLK            (0X18u)
#define ADC_CFG1_DSM_BUF0           (0X05u)
#define ADC_CFG1_DSM_BUF1           (0X02u)
#define ADC_CFG1_DSM_BUF2           (0X01u)
#define ADC_CFG1_DSM_BUF3           (0X00u)
#define ADC_CFG1_DSM_OUT0           (0X00u)
#define ADC_CFG1_DSM_OUT1           (0X00u)
#define ADC_CFG1_DSM_SW3            (0X40u)
#define ADC_CFG1_CLOCKS_PER_SAMPLE  (0X0043u)
#define ADC_CFG1_CLOCK_FREQ         (670000u)
#define ADC_CFG1_CP_CLOCK_FREQ      (2680000u)
#define ADC_CFG1_REFERENCE_VOLTAGE  (1.2500)
#define ADC_CFG1_COUNTS_PER_VOLT    (51u)
#define ADC_CFG1_IDEAL_DEC_GAIN     (0X9000u)

#define ADC_CFG1_IDEAL_ODDDEC_GAIN  (0X8000u)

/* Input and DAC Cap values in pF */
#define ADC_CFG1_IPCAP1VALUE        (0X0440u)
#define ADC_CFG1_DACAPVALUE         (0X1320u)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define ADC_DEFAULT_SRATE                      ADC_CFG1_SRATE              
#define ADC_CLOCKS_PER_SAMPLE                  ADC_CFG1_CLOCKS_PER_SAMPLE  
#define ADC_DFLT_CLOCK_FREQ                    ADC_CFG1_CLOCK_FREQ         
#define ADC_REFERENCE_VOLTAGE                  ADC_CFG1_REFERENCE_VOLTAGE  
#define ADC_DFLT_COUNTS_PER_VOLT               ADC_CFG1_COUNTS_PER_VOLT    
#define ADC_DEFAULT_RESOLUTION                 ADC_CFG1_RESOLUTION         
#define ADC_DEFAULT_CONV_MODE                  ADC_CFG1_CONV_MODE           
#define ADC_DEFAULT_IDEAL_DEC_GAIN             ADC_CFG1_IDEAL_DEC_GAIN     
#define ADC_DEFAULT_RANGE                      ADC_CFG1_RANGE        
#define ADC_DEFAULT_RANGE_VALUE                ADC_CFG1_RANGE_VALUE  
#define ADC_DEFAULT_REFERENCE                  ADC_CFG1_REFERENCE         
#define ADC_DEFAULT_BUF_GAIN                   ADC_CFG1_BUF_GAIN       

/* Input and DAC Cap values in pF */
#define ADC_DEFAULT_IPCAP1VALUE                ADC_CFG1_IPCAP1VALUE       
#define ADC_DEFAULT_DACAPVALUE                 ADC_CFG1_DACAPVALUE        
#define ADC_DEFAULT_IDEAL_ODDDEC_GAIN          ADC_CFG1_IDEAL_ODDDEC_GAIN 


/* Default register settings for the Config 2 */
/* Second Config */
/* ADC_CFG2 Sample Rate: 10000 Samples per Second */
/* ADC_CFG2 Conversion Mode: 2 */
/* ADC_CFG2 Input Buffer Gain: 1   */
/* ADC_CFG2 Reference: 0 */
/* ADC_CFG2 Input Range: 0  */
/* ADC_CFG2 Resolution: 16 bits */
/* ADC_CFG2 Clock: 640000 Hz */

#define ADC_CFG2_DEC_CR             (0X38u)
#define ADC_CFG2_DEC_SR             (0X14u)
#define ADC_CFG2_DEC_SHIFT1         (0X04u)
#define ADC_CFG2_DEC_SHIFT2         (0X06u)
#define ADC_CFG2_DEC_DR2            (0X00u)
#define ADC_CFG2_DEC_DR2H           (0X00u)
#define ADC_CFG2_DEC_DR1            (0X3Fu)
#define ADC_CFG2_DEC_OCOR           (0X00u)
#define ADC_CFG2_DEC_OCORM          (0X00u)
#define ADC_CFG2_DEC_OCORH          (0X00u)
#define ADC_CFG2_DEC_GVAL           (0X0Fu)
#define ADC_CFG2_DEC_GCOR           (0X00u)
#define ADC_CFG2_DEC_GCORH          (0X00u)
#define ADC_CFG2_DEC_COHER          (0X01u)
#define ADC_CFG2_DSM_CR0            (0X0Au)
#define ADC_CFG2_DSM_CR1            (0X00u)
#define ADC_CFG2_DSM_CR2            (0X7Au)
#define ADC_CFG2_DSM_CR3            (0X00u)
#define ADC_CFG2_DSM_CR4            (0X50u)
#define ADC_CFG2_DSM_CR5            (0X27u)
#define ADC_CFG2_DSM_CR6            (0X2Cu)
#define ADC_CFG2_DSM_CR7            (0X00u)
#define ADC_CFG2_DSM_CR8            (0X12u)
#define ADC_CFG2_DSM_CR9            (0X13u)
#define ADC_CFG2_DSM_CR10           (0X55u)
#define ADC_CFG2_DSM_CR11           (0X5Au)
#define ADC_CFG2_DSM_CR12           (0X05u)
#define ADC_CFG2_DSM_CR13           (0X00u)
#define ADC_CFG2_DSM_CR14           (0X01u)
#define ADC_CFG2_DSM_CR15           (0X11u)
#define ADC_CFG2_DSM_CR16           (0X19u)
#define ADC_CFG2_DSM_CR17           (0X97u)
#define ADC_CFG2_DSM_REF0           (0X44u)
#define ADC_CFG2_DSM_REF2           (0X58u)
#define ADC_CFG2_DSM_REF3           (0X00u)
#define ADC_CFG2_DSM_DEM0           (0X07u)
#define ADC_CFG2_DSM_DEM1           (0X00u)
#define ADC_CFG2_DSM_BUF0           (0X05u)
#define ADC_CFG2_DSM_BUF1           (0X02u)
#define ADC_CFG2_DSM_BUF2           (0X01u)
#define ADC_CFG2_DSM_BUF3           (0X00u)
#define ADC_CFG2_DSM_OUT0           (0X00u)
#define ADC_CFG2_DSM_OUT1           (0X00u)
#define ADC_CFG2_DSM_SW3            (0X40u)
#define ADC_CFG2_SRATE              (10000u )
#define ADC_CFG2_CLOCKS_PER_SAMPLE  (0X0040u)
#define ADC_CFG2_CLOCK_FREQ         (640000u)
#define ADC_CFG2_CP_CLOCK_FREQ      (2560000u)
#define ADC_CFG2_REFERENCE_VOLTAGE  (1.0240)
#define ADC_CFG2_COUNTS_PER_VOLT    (64000u)
#define ADC_CFG2_RESOLUTION         (16u)
#define ADC_CFG2_CONVMODE           (2u)
#define ADC_CFG2_IDEAL_DEC_GAIN     (0X90DBu)
#define ADC_CFG2_INPUT_RANGE        (0u)
#define ADC_CFG2_INPUT_RANGE_VALUE  (1.024)

#define ADC_CFG2_INPUT_MODE         (1u)
#define ADC_CFG2_REFERENCE          (0u)
#define ADC_CFG2_BUFFER_GAIN        (1u)

/* Input and DAC Cap values in pF */
#define ADC_CFG2_IPCAP1VALUE        (0X0F30u)
#define ADC_CFG2_DACAPVALUE         (0X1130u)
#define ADC_CFG2_IDEAL_ODDDEC_GAIN  (0X8000u)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define ADC_DEFAULT_SRATE_CFG2                 ADC_CFG2_SRATE              
#define ADC_CLOCKS_PER_SAMPLE_CFG2             ADC_CFG2_CLOCKS_PER_SAMPLE  
#define ADC_DFLT_CLOCK_FREQ_CFG2               ADC_CFG2_CLOCK_FREQ         
#define ADC_REFERENCE_VOLTAGE_CFG2             ADC_CFG2_REFERENCE_VOLTAGE  
#define ADC_DFLT_COUNTS_PER_VOLT_CFG2          ADC_CFG2_COUNTS_PER_VOLT    
#define ADC_DEFAULT_RESOLUTION_CFG2            ADC_CFG2_RESOLUTION         
#define ADC_CONVMODE_CFG2                      ADC_CFG2_CONVMODE           
#define ADC_DEFAULT_IDEAL_DEC_GAIN_CFG2        ADC_CFG2_IDEAL_DEC_GAIN     
#define ADC_DEFAULT_INPUT_RANGE_CFG2           ADC_CFG2_INPUT_RANGE        
#define ADC_DEFAULT_INPUT_RANGE_VALUE_CFG2     ADC_CFG2_INPUT_RANGE_VALUE  
#define ADC_DEFAULT_INPUT_MODE_CFG2            ADC_CFG2_INPUT_MODE         
#define ADC_DEFAULT_REFERENCE_CFG2             ADC_CFG2_REFERENCE         
#define ADC_DEFAULT_BUFFER_GAIN_CONFIG2        ADC_CFG2_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define ADC_DEFAULT_IPCAP1VALUE_CFG2           ADC_CFG2_IPCAP1VALUE       
#define ADC_DEFAULT_DACAPVALUE_CFG2            ADC_CFG2_DACAPVALUE        
#define ADC_DEFAULT_IDEAL_ODDDEC_GAIN_CFG2     ADC_CFG2_IDEAL_ODDDEC_GAIN 


/* Default register settings for the following configuration */
/* Third Config */
/* ADC_CFG3 Sample Rate: 10000 Samples per Second */
/* ADC_CFG3 Conversion Mode: 2 */
/* ADC_CFG3 Input Buffer Gain: 1   */
/* ADC_CFG3 Reference: 0 */
/* ADC_CFG3 Input Range: 0  */
/* ADC_CFG3 Resolution: 16 bits */
/* ADC_CFG3 Clock: 640000 Hz */

#define ADC_CFG3_DEC_CR             (0X38u)
#define ADC_CFG3_DEC_SR             (0X14u)
#define ADC_CFG3_DEC_SHIFT1         (0X04u)
#define ADC_CFG3_DEC_SHIFT2         (0X06u)
#define ADC_CFG3_DEC_DR2            (0X00u)
#define ADC_CFG3_DEC_DR2H           (0X00u)
#define ADC_CFG3_DEC_DR1            (0X3Fu)
#define ADC_CFG3_DEC_OCOR           (0X00u)
#define ADC_CFG3_DEC_OCORM          (0X00u)
#define ADC_CFG3_DEC_OCORH          (0X00u)
#define ADC_CFG3_DEC_GVAL           (0X0Fu)
#define ADC_CFG3_DEC_GCOR           (0X00u)
#define ADC_CFG3_DEC_GCORH          (0X00u)
#define ADC_CFG3_DEC_COHER          (0X01u)
#define ADC_CFG3_DSM_CR0            (0X0Au)
#define ADC_CFG3_DSM_CR1            (0X00u)
#define ADC_CFG3_DSM_CR2            (0X7Au)
#define ADC_CFG3_DSM_CR3            (0X00u)
#define ADC_CFG3_DSM_CR4            (0X50u)
#define ADC_CFG3_DSM_CR5            (0X27u)
#define ADC_CFG3_DSM_CR6            (0X2Cu)
#define ADC_CFG3_DSM_CR7            (0X00u)
#define ADC_CFG3_DSM_CR8            (0X12u)
#define ADC_CFG3_DSM_CR9            (0X13u)
#define ADC_CFG3_DSM_CR10           (0X55u)
#define ADC_CFG3_DSM_CR11           (0X5Au)
#define ADC_CFG3_DSM_CR12           (0X05u)
#define ADC_CFG3_DSM_CR13           (0X00u)
#define ADC_CFG3_DSM_CR14           (0X01u)
#define ADC_CFG3_DSM_CR15           (0X11u)
#define ADC_CFG3_DSM_CR16           (0X19u)
#define ADC_CFG3_DSM_CR17           (0X97u)
#define ADC_CFG3_DSM_REF0           (0X44u)
#define ADC_CFG3_DSM_REF2           (0X58u)
#define ADC_CFG3_DSM_REF3           (0X00u)
#define ADC_CFG3_DSM_DEM0           (0X07u)
#define ADC_CFG3_DSM_DEM1           (0X00u)
#define ADC_CFG3_DSM_BUF0           (0X05u)
#define ADC_CFG3_DSM_BUF1           (0X02u)
#define ADC_CFG3_DSM_BUF2           (0X01u)
#define ADC_CFG3_DSM_BUF3           (0X00u)
#define ADC_CFG3_DSM_OUT0           (0X00u)
#define ADC_CFG3_DSM_OUT1           (0X00u)
#define ADC_CFG3_DSM_SW3            (0X40u)
#define ADC_CFG3_SRATE              (10000u)
#define ADC_CFG3_CLOCKS_PER_SAMPLE  (0X0040u)
#define ADC_CFG3_CLOCK_FREQ         (640000u)
#define ADC_CFG3_CP_CLOCK_FREQ      (2560000u)
#define ADC_CFG3_REFERENCE_VOLTAGE  (1.0240)
#define ADC_CFG3_COUNTS_PER_VOLT    (64000u)
#define ADC_CFG3_RESOLUTION         (16u)
#define ADC_CFG3_CONVMODE           (2u)
#define ADC_CFG3_IDEAL_DEC_GAIN     (0X90DBu)
#define ADC_CFG3_INPUT_RANGE        (0u)
#define ADC_CFG3_INPUT_MODE         (1u)
#define ADC_CFG3_REFERENCE          (0u)
#define ADC_CFG3_BUFFER_GAIN        (1u)
#define ADC_CFG3_INPUT_RANGE_VALUE  (1.024)

/* Input and DAC Cap values in pF */
#define ADC_CFG3_IPCAP1VALUE        (0X0F30u)
#define ADC_CFG3_DACAPVALUE         (0X1130u)
#define ADC_CFG3_IDEAL_ODDDEC_GAIN  (0X8000u)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define ADC_DEFAULT_SRATE_CFG3                 ADC_CFG3_SRATE              
#define ADC_CLOCKS_PER_SAMPLE_CFG3             ADC_CFG3_CLOCKS_PER_SAMPLE  
#define ADC_DFLT_CLOCK_FREQ_CFG3               ADC_CFG3_CLOCK_FREQ         
#define ADC_REFERENCE_VOLTAGE_CFG3             ADC_CFG3_REFERENCE_VOLTAGE  
#define ADC_DFLT_COUNTS_PER_VOLT_CFG3          ADC_CFG3_COUNTS_PER_VOLT    
#define ADC_DEFAULT_RESOLUTION_CFG3            ADC_CFG3_RESOLUTION         
#define ADC_CONVMODE_CFG3                      ADC_CFG3_CONVMODE           
#define ADC_DEFAULT_IDEAL_DEC_GAIN_CFG3        ADC_CFG3_IDEAL_DEC_GAIN     
#define ADC_DEFAULT_INPUT_RANGE_CFG3           ADC_CFG3_INPUT_RANGE        
#define ADC_DEFAULT_INPUT_RANGE_VALUE_CFG3     ADC_CFG3_INPUT_RANGE_VALUE  
#define ADC_DEFAULT_INPUT_MODE_CFG3            ADC_CFG3_INPUT_MODE         
#define ADC_DEFAULT_REFERENCE_CFG3             ADC_CFG3_REFERENCE         
#define ADC_DEFAULT_BUFFER_GAIN_CONFIG3        ADC_CFG3_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define ADC_DEFAULT_IPCAP1VALUE_CFG3           ADC_CFG3_IPCAP1VALUE       
#define ADC_DEFAULT_DACAPVALUE_CFG3            ADC_CFG3_DACAPVALUE        
#define ADC_DEFAULT_IDEAL_ODDDEC_GAIN_CFG3     ADC_CFG3_IDEAL_ODDDEC_GAIN 


/* Default register settings for the following configuration */
/* Fourth Config */
/* ADC_CFG4 Sample Rate: 10000 Samples per Second */
/* ADC_CFG4 Conversion Mode: 2 */
/* ADC_CFG4 Input Buffer Gain: 1   */
/* ADC_CFG4 Reference: 0 */
/* ADC_CFG4 Input Range: 0  */
/* ADC_CFG4 Resolution: 16 bits */
/* ADC_CFG4 Clock: 640000 Hz */

#define ADC_CFG4_DEC_CR             (0X38u)
#define ADC_CFG4_DEC_SR             (0X14u)
#define ADC_CFG4_DEC_SHIFT1         (0X04u)
#define ADC_CFG4_DEC_SHIFT2         (0X06u)
#define ADC_CFG4_DEC_DR2            (0X00u)
#define ADC_CFG4_DEC_DR2H           (0X00u)
#define ADC_CFG4_DEC_DR1            (0X3Fu)
#define ADC_CFG4_DEC_OCOR           (0X00u)
#define ADC_CFG4_DEC_OCORM          (0X00u)
#define ADC_CFG4_DEC_OCORH          (0X00u)
#define ADC_CFG4_DEC_GVAL           (0X0Fu)
#define ADC_CFG4_DEC_GCOR           (0X00u)
#define ADC_CFG4_DEC_GCORH          (0X00u)
#define ADC_CFG4_DEC_COHER          (0X01u)
#define ADC_CFG4_DSM_CR0            (0X0Au)
#define ADC_CFG4_DSM_CR1            (0X00u)
#define ADC_CFG4_DSM_CR2            (0X7Au)
#define ADC_CFG4_DSM_CR3            (0X00u)
#define ADC_CFG4_DSM_CR4            (0X50u)
#define ADC_CFG4_DSM_CR5            (0X27u)
#define ADC_CFG4_DSM_CR6            (0X2Cu)
#define ADC_CFG4_DSM_CR7            (0X00u)
#define ADC_CFG4_DSM_CR8            (0X12u)
#define ADC_CFG4_DSM_CR9            (0X13u)
#define ADC_CFG4_DSM_CR10           (0X55u)
#define ADC_CFG4_DSM_CR11           (0X5Au)
#define ADC_CFG4_DSM_CR12           (0X05u)
#define ADC_CFG4_DSM_CR13           (0X00u)
#define ADC_CFG4_DSM_CR14           (0X01u)
#define ADC_CFG4_DSM_CR15           (0X11u)
#define ADC_CFG4_DSM_CR16           (0X19u)
#define ADC_CFG4_DSM_CR17           (0X97u)
#define ADC_CFG4_DSM_REF0           (0X44u)
#define ADC_CFG4_DSM_REF2           (0X58u)
#define ADC_CFG4_DSM_REF3           (0X00u)
#define ADC_CFG4_DSM_DEM0           (0X07u)
#define ADC_CFG4_DSM_DEM1           (0X00u)
#define ADC_CFG4_DSM_BUF0           (0X05u)
#define ADC_CFG4_DSM_BUF1           (0X02u)
#define ADC_CFG4_DSM_BUF2           (0X01u)
#define ADC_CFG4_DSM_BUF3           (0X00u)
#define ADC_CFG4_DSM_OUT0           (0X00u)
#define ADC_CFG4_DSM_OUT1           (0X00u)
#define ADC_CFG4_DSM_SW3            (0X40u)
#define ADC_CFG4_SRATE              (10000u)         
#define ADC_CFG4_CLOCKS_PER_SAMPLE  (0X0040u)
#define ADC_CFG4_CLOCK_FREQ         (640000u)
#define ADC_CFG4_CP_CLOCK_FREQ      (2560000u)
#define ADC_CFG4_REFERENCE_VOLTAGE  (1.0240)
#define ADC_CFG4_COUNTS_PER_VOLT    (64000u)
#define ADC_CFG4_RESOLUTION         (16u)
#define ADC_CFG4_CONVMODE           (2u)
#define ADC_CFG4_IDEAL_DEC_GAIN     (0X90DBu)
#define ADC_CFG4_INPUT_RANGE        (0u)
#define ADC_CFG4_INPUT_MODE         (1u)
#define ADC_CFG4_REFERENCE          (0u)
#define ADC_CFG4_BUFFER_GAIN        (1u)
#define ADC_CFG4_INPUT_RANGE_VALUE  (1.024)

/* Input cap and DAC Cap values in pF */
#define ADC_CFG4_IPCAP1VALUE        (0X0F30u)
#define ADC_CFG4_DACAPVALUE         (0X1130u)
#define ADC_CFG4_IDEAL_ODDDEC_GAIN  (0X8000u)

/* Below defines are depricated and should not be used. These are provided 
   just to keep the component backward compatible */
#define ADC_DEFAULT_SRATE_CFG4                 ADC_CFG4_SRATE              
#define ADC_CLOCKS_PER_SAMPLE_CFG4             ADC_CFG4_CLOCKS_PER_SAMPLE  
#define ADC_DFLT_CLOCK_FREQ_CFG4               ADC_CFG4_CLOCK_FREQ         
#define ADC_REFERENCE_VOLTAGE_CFG4             ADC_CFG4_REFERENCE_VOLTAGE  
#define ADC_DFLT_COUNTS_PER_VOLT_CFG4          ADC_CFG4_COUNTS_PER_VOLT    
#define ADC_DEFAULT_RESOLUTION_CFG4            ADC_CFG4_RESOLUTION         
#define ADC_CONVMODE_CFG4                      ADC_CFG4_CONVMODE           
#define ADC_DEFAULT_IDEAL_DEC_GAIN_CFG4        ADC_CFG4_IDEAL_DEC_GAIN     
#define ADC_DEFAULT_INPUT_RANGE_CFG4           ADC_CFG4_INPUT_RANGE        
#define ADC_DEFAULT_INPUT_RANGE_VALUE_CFG4     ADC_CFG4_INPUT_RANGE_VALUE  
#define ADC_DEFAULT_INPUT_MODE_CFG4            ADC_CFG4_INPUT_MODE         
#define ADC_DEFAULT_REFERENCE_CFG4             ADC_CFG4_REFERENCE         
#define ADC_DEFAULT_BUFFER_GAIN_CONFIG4        ADC_CFG4_BUFFER_GAIN       

/* Input and DAC Cap values in pF */
#define ADC_DEFAULT_IPCAP1VALUE_CFG4           ADC_CFG4_IPCAP1VALUE       
#define ADC_DEFAULT_DACAPVALUE_CFG4            ADC_CFG4_DACAPVALUE        
#define ADC_DEFAULT_IDEAL_ODDDEC_GAIN_CFG4     ADC_CFG4_IDEAL_ODDDEC_GAIN 

#endif /* CY_ADC_DELSIG_ADC_H */


/* [] END OF FILE */
