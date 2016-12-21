/*******************************************************************************
* File Name: PWM_G.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the PWM_G
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_PWM_G_H)
#define CY_TCPWM_PWM_G_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWM_G_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWM_G_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define PWM_G_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWM_G_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define PWM_G_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWM_G_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWM_G_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWM_G_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWM_G_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWM_G_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWM_G_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWM_G_TC_RUN_MODE                    (0lu)
#define PWM_G_TC_COUNTER_MODE                (0lu)
#define PWM_G_TC_COMP_CAP_MODE               (2lu)
#define PWM_G_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWM_G_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWM_G_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWM_G_TC_START_SIGNAL_MODE           (0lu)
#define PWM_G_TC_STOP_SIGNAL_MODE            (0lu)
#define PWM_G_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_G_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWM_G_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWM_G_TC_START_SIGNAL_PRESENT        (0lu)
#define PWM_G_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWM_G_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_G_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWM_G_PWM_KILL_EVENT                 (0lu)
#define PWM_G_PWM_STOP_EVENT                 (0lu)
#define PWM_G_PWM_MODE                       (4lu)
#define PWM_G_PWM_OUT_N_INVERT               (0lu)
#define PWM_G_PWM_OUT_INVERT                 (1lu)
#define PWM_G_PWM_ALIGN                      (0lu)
#define PWM_G_PWM_RUN_MODE                   (0lu)
#define PWM_G_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWM_G_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWM_G_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWM_G_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWM_G_PWM_START_SIGNAL_MODE          (0lu)
#define PWM_G_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWM_G_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_G_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWM_G_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWM_G_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWM_G_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWM_G_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_G_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWM_G_TC_PERIOD_VALUE                (65535lu)
#define PWM_G_TC_COMPARE_VALUE               (65535lu)
#define PWM_G_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWM_G_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWM_G_PWM_PERIOD_VALUE               (65535lu)
#define PWM_G_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWM_G_PWM_PERIOD_SWAP                (0lu)
#define PWM_G_PWM_COMPARE_VALUE              (65535lu)
#define PWM_G_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWM_G_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWM_G__LEFT 0
#define PWM_G__RIGHT 1
#define PWM_G__CENTER 2
#define PWM_G__ASYMMETRIC 3

#define PWM_G__X1 0
#define PWM_G__X2 1
#define PWM_G__X4 2

#define PWM_G__PWM 4
#define PWM_G__PWM_DT 5
#define PWM_G__PWM_PR 6

#define PWM_G__INVERSE 1
#define PWM_G__DIRECT 0

#define PWM_G__CAPTURE 2
#define PWM_G__COMPARE 0

#define PWM_G__TRIG_LEVEL 3
#define PWM_G__TRIG_RISING 0
#define PWM_G__TRIG_FALLING 1
#define PWM_G__TRIG_BOTH 2

#define PWM_G__INTR_MASK_TC 1
#define PWM_G__INTR_MASK_CC_MATCH 2
#define PWM_G__INTR_MASK_NONE 0
#define PWM_G__INTR_MASK_TC_CC 3

#define PWM_G__UNCONFIG 8
#define PWM_G__TIMER 1
#define PWM_G__QUAD 3
#define PWM_G__PWM_SEL 7

#define PWM_G__COUNT_UP 0
#define PWM_G__COUNT_DOWN 1
#define PWM_G__COUNT_UPDOWN0 2
#define PWM_G__COUNT_UPDOWN1 3


/* Prescaler */
#define PWM_G_PRESCALE_DIVBY1                ((uint32)(0u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY2                ((uint32)(1u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY4                ((uint32)(2u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY8                ((uint32)(3u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY16               ((uint32)(4u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY32               ((uint32)(5u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY64               ((uint32)(6u << PWM_G_PRESCALER_SHIFT))
#define PWM_G_PRESCALE_DIVBY128              ((uint32)(7u << PWM_G_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWM_G_MODE_TIMER_COMPARE             ((uint32)(PWM_G__COMPARE         <<  \
                                                                  PWM_G_MODE_SHIFT))
#define PWM_G_MODE_TIMER_CAPTURE             ((uint32)(PWM_G__CAPTURE         <<  \
                                                                  PWM_G_MODE_SHIFT))
#define PWM_G_MODE_QUAD                      ((uint32)(PWM_G__QUAD            <<  \
                                                                  PWM_G_MODE_SHIFT))
#define PWM_G_MODE_PWM                       ((uint32)(PWM_G__PWM             <<  \
                                                                  PWM_G_MODE_SHIFT))
#define PWM_G_MODE_PWM_DT                    ((uint32)(PWM_G__PWM_DT          <<  \
                                                                  PWM_G_MODE_SHIFT))
#define PWM_G_MODE_PWM_PR                    ((uint32)(PWM_G__PWM_PR          <<  \
                                                                  PWM_G_MODE_SHIFT))

/* Quad Modes */
#define PWM_G_MODE_X1                        ((uint32)(PWM_G__X1              <<  \
                                                                  PWM_G_QUAD_MODE_SHIFT))
#define PWM_G_MODE_X2                        ((uint32)(PWM_G__X2              <<  \
                                                                  PWM_G_QUAD_MODE_SHIFT))
#define PWM_G_MODE_X4                        ((uint32)(PWM_G__X4              <<  \
                                                                  PWM_G_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWM_G_COUNT_UP                       ((uint32)(PWM_G__COUNT_UP        <<  \
                                                                  PWM_G_UPDOWN_SHIFT))
#define PWM_G_COUNT_DOWN                     ((uint32)(PWM_G__COUNT_DOWN      <<  \
                                                                  PWM_G_UPDOWN_SHIFT))
#define PWM_G_COUNT_UPDOWN0                  ((uint32)(PWM_G__COUNT_UPDOWN0   <<  \
                                                                  PWM_G_UPDOWN_SHIFT))
#define PWM_G_COUNT_UPDOWN1                  ((uint32)(PWM_G__COUNT_UPDOWN1   <<  \
                                                                  PWM_G_UPDOWN_SHIFT))

/* PWM output invert */
#define PWM_G_INVERT_LINE                    ((uint32)(PWM_G__INVERSE         <<  \
                                                                  PWM_G_INV_OUT_SHIFT))
#define PWM_G_INVERT_LINE_N                  ((uint32)(PWM_G__INVERSE         <<  \
                                                                  PWM_G_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWM_G_TRIG_RISING                    (PWM_G__TRIG_RISING)
#define PWM_G_TRIG_FALLING                   (PWM_G__TRIG_FALLING)
#define PWM_G_TRIG_BOTH                      (PWM_G__TRIG_BOTH)
#define PWM_G_TRIG_LEVEL                     (PWM_G__TRIG_LEVEL)

/* Interrupt mask */
#define PWM_G_INTR_MASK_TC                   (PWM_G__INTR_MASK_TC)
#define PWM_G_INTR_MASK_CC_MATCH             (PWM_G__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWM_G_CC_MATCH_SET                   (0x00u)
#define PWM_G_CC_MATCH_CLEAR                 (0x01u)
#define PWM_G_CC_MATCH_INVERT                (0x02u)
#define PWM_G_CC_MATCH_NO_CHANGE             (0x03u)
#define PWM_G_OVERLOW_SET                    (0x00u)
#define PWM_G_OVERLOW_CLEAR                  (0x04u)
#define PWM_G_OVERLOW_INVERT                 (0x08u)
#define PWM_G_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWM_G_UNDERFLOW_SET                  (0x00u)
#define PWM_G_UNDERFLOW_CLEAR                (0x10u)
#define PWM_G_UNDERFLOW_INVERT               (0x20u)
#define PWM_G_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWM_G_PWM_MODE_LEFT                  (PWM_G_CC_MATCH_CLEAR        |   \
                                                         PWM_G_OVERLOW_SET           |   \
                                                         PWM_G_UNDERFLOW_NO_CHANGE)
#define PWM_G_PWM_MODE_RIGHT                 (PWM_G_CC_MATCH_SET          |   \
                                                         PWM_G_OVERLOW_NO_CHANGE     |   \
                                                         PWM_G_UNDERFLOW_CLEAR)
#define PWM_G_PWM_MODE_CENTER                (PWM_G_CC_MATCH_INVERT       |   \
                                                         PWM_G_OVERLOW_NO_CHANGE     |   \
                                                         PWM_G_UNDERFLOW_CLEAR)
#define PWM_G_PWM_MODE_ASYM                  (PWM_G_CC_MATCH_NO_CHANGE    |   \
                                                         PWM_G_OVERLOW_SET           |   \
                                                         PWM_G_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define PWM_G_CMD_CAPTURE                    (0u)
#define PWM_G_CMD_RELOAD                     (8u)
#define PWM_G_CMD_STOP                       (16u)
#define PWM_G_CMD_START                      (24u)

/* Status */
#define PWM_G_STATUS_DOWN                    (1u)
#define PWM_G_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWM_G_Init(void);
void   PWM_G_Enable(void);
void   PWM_G_Start(void);
void   PWM_G_Stop(void);

void   PWM_G_SetMode(uint32 mode);
void   PWM_G_SetCounterMode(uint32 counterMode);
void   PWM_G_SetPWMMode(uint32 modeMask);
void   PWM_G_SetQDMode(uint32 qdMode);

void   PWM_G_SetPrescaler(uint32 prescaler);
void   PWM_G_TriggerCommand(uint32 mask, uint32 command);
void   PWM_G_SetOneShot(uint32 oneShotEnable);
uint32 PWM_G_ReadStatus(void);

void   PWM_G_SetPWMSyncKill(uint32 syncKillEnable);
void   PWM_G_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWM_G_SetPWMDeadTime(uint32 deadTime);
void   PWM_G_SetPWMInvert(uint32 mask);

void   PWM_G_SetInterruptMode(uint32 interruptMask);
uint32 PWM_G_GetInterruptSourceMasked(void);
uint32 PWM_G_GetInterruptSource(void);
void   PWM_G_ClearInterrupt(uint32 interruptMask);
void   PWM_G_SetInterrupt(uint32 interruptMask);

void   PWM_G_WriteCounter(uint32 count);
uint32 PWM_G_ReadCounter(void);

uint32 PWM_G_ReadCapture(void);
uint32 PWM_G_ReadCaptureBuf(void);

void   PWM_G_WritePeriod(uint32 period);
uint32 PWM_G_ReadPeriod(void);
void   PWM_G_WritePeriodBuf(uint32 periodBuf);
uint32 PWM_G_ReadPeriodBuf(void);

void   PWM_G_WriteCompare(uint32 compare);
uint32 PWM_G_ReadCompare(void);
void   PWM_G_WriteCompareBuf(uint32 compareBuf);
uint32 PWM_G_ReadCompareBuf(void);

void   PWM_G_SetPeriodSwap(uint32 swapEnable);
void   PWM_G_SetCompareSwap(uint32 swapEnable);

void   PWM_G_SetCaptureMode(uint32 triggerMode);
void   PWM_G_SetReloadMode(uint32 triggerMode);
void   PWM_G_SetStartMode(uint32 triggerMode);
void   PWM_G_SetStopMode(uint32 triggerMode);
void   PWM_G_SetCountMode(uint32 triggerMode);

void   PWM_G_SaveConfig(void);
void   PWM_G_RestoreConfig(void);
void   PWM_G_Sleep(void);
void   PWM_G_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWM_G_BLOCK_CONTROL_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_G_BLOCK_CONTROL_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_G_COMMAND_REG                    (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_G_COMMAND_PTR                    ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_G_INTRRUPT_CAUSE_REG             (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_G_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_G_CONTROL_REG                    (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__CTRL )
#define PWM_G_CONTROL_PTR                    ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__CTRL )
#define PWM_G_STATUS_REG                     (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__STATUS )
#define PWM_G_STATUS_PTR                     ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__STATUS )
#define PWM_G_COUNTER_REG                    (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_G_COUNTER_PTR                    ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_G_COMP_CAP_REG                   (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__CC )
#define PWM_G_COMP_CAP_PTR                   ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__CC )
#define PWM_G_COMP_CAP_BUF_REG               (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_G_COMP_CAP_BUF_PTR               ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_G_PERIOD_REG                     (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_G_PERIOD_PTR                     ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_G_PERIOD_BUF_REG                 (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_G_PERIOD_BUF_PTR                 ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_G_TRIG_CONTROL0_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_G_TRIG_CONTROL0_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_G_TRIG_CONTROL1_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_G_TRIG_CONTROL1_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_G_TRIG_CONTROL2_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_G_TRIG_CONTROL2_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_G_INTERRUPT_REQ_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR )
#define PWM_G_INTERRUPT_REQ_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR )
#define PWM_G_INTERRUPT_SET_REG              (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_G_INTERRUPT_SET_PTR              ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_G_INTERRUPT_MASK_REG             (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_G_INTERRUPT_MASK_PTR             ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_G_INTERRUPT_MASKED_REG           (*(reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWM_G_INTERRUPT_MASKED_PTR           ( (reg32 *) PWM_G_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWM_G_MASK                           ((uint32)PWM_G_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWM_G_RELOAD_CC_SHIFT                (0u)
#define PWM_G_RELOAD_PERIOD_SHIFT            (1u)
#define PWM_G_PWM_SYNC_KILL_SHIFT            (2u)
#define PWM_G_PWM_STOP_KILL_SHIFT            (3u)
#define PWM_G_PRESCALER_SHIFT                (8u)
#define PWM_G_UPDOWN_SHIFT                   (16u)
#define PWM_G_ONESHOT_SHIFT                  (18u)
#define PWM_G_QUAD_MODE_SHIFT                (20u)
#define PWM_G_INV_OUT_SHIFT                  (20u)
#define PWM_G_INV_COMPL_OUT_SHIFT            (21u)
#define PWM_G_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWM_G_RELOAD_CC_MASK                 ((uint32)(PWM_G_1BIT_MASK        <<  \
                                                                            PWM_G_RELOAD_CC_SHIFT))
#define PWM_G_RELOAD_PERIOD_MASK             ((uint32)(PWM_G_1BIT_MASK        <<  \
                                                                            PWM_G_RELOAD_PERIOD_SHIFT))
#define PWM_G_PWM_SYNC_KILL_MASK             ((uint32)(PWM_G_1BIT_MASK        <<  \
                                                                            PWM_G_PWM_SYNC_KILL_SHIFT))
#define PWM_G_PWM_STOP_KILL_MASK             ((uint32)(PWM_G_1BIT_MASK        <<  \
                                                                            PWM_G_PWM_STOP_KILL_SHIFT))
#define PWM_G_PRESCALER_MASK                 ((uint32)(PWM_G_8BIT_MASK        <<  \
                                                                            PWM_G_PRESCALER_SHIFT))
#define PWM_G_UPDOWN_MASK                    ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                            PWM_G_UPDOWN_SHIFT))
#define PWM_G_ONESHOT_MASK                   ((uint32)(PWM_G_1BIT_MASK        <<  \
                                                                            PWM_G_ONESHOT_SHIFT))
#define PWM_G_QUAD_MODE_MASK                 ((uint32)(PWM_G_3BIT_MASK        <<  \
                                                                            PWM_G_QUAD_MODE_SHIFT))
#define PWM_G_INV_OUT_MASK                   ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                            PWM_G_INV_OUT_SHIFT))
#define PWM_G_MODE_MASK                      ((uint32)(PWM_G_3BIT_MASK        <<  \
                                                                            PWM_G_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWM_G_CAPTURE_SHIFT                  (0u)
#define PWM_G_COUNT_SHIFT                    (2u)
#define PWM_G_RELOAD_SHIFT                   (4u)
#define PWM_G_STOP_SHIFT                     (6u)
#define PWM_G_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWM_G_CAPTURE_MASK                   ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                  PWM_G_CAPTURE_SHIFT))
#define PWM_G_COUNT_MASK                     ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                  PWM_G_COUNT_SHIFT))
#define PWM_G_RELOAD_MASK                    ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                  PWM_G_RELOAD_SHIFT))
#define PWM_G_STOP_MASK                      ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                  PWM_G_STOP_SHIFT))
#define PWM_G_START_MASK                     ((uint32)(PWM_G_2BIT_MASK        <<  \
                                                                  PWM_G_START_SHIFT))

/* MASK */
#define PWM_G_1BIT_MASK                      ((uint32)0x01u)
#define PWM_G_2BIT_MASK                      ((uint32)0x03u)
#define PWM_G_3BIT_MASK                      ((uint32)0x07u)
#define PWM_G_6BIT_MASK                      ((uint32)0x3Fu)
#define PWM_G_8BIT_MASK                      ((uint32)0xFFu)
#define PWM_G_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWM_G_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWM_G_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_PWM_G_H */

/* [] END OF FILE */
