/*******************************************************************************
* File Name: PWM_G.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the PWM_G
*  component
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

#include "PWM_G.h"
#include "cyLib.h"

uint8 PWM_G_initVar = 0u;


/*******************************************************************************
* Function Name: PWM_G_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWM_G configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWM_G__QUAD == PWM_G_CONFIG)
        PWM_G_CONTROL_REG =
        (((uint32)(PWM_G_QUAD_ENCODING_MODES     << PWM_G_QUAD_MODE_SHIFT))       |
         ((uint32)(PWM_G_CONFIG                  << PWM_G_MODE_SHIFT)));
    #endif  /* (PWM_G__QUAD == PWM_G_CONFIG) */

    #if (PWM_G__PWM_SEL == PWM_G_CONFIG)
        PWM_G_CONTROL_REG =
        (((uint32)(PWM_G_PWM_STOP_EVENT          << PWM_G_PWM_STOP_KILL_SHIFT))    |
         ((uint32)(PWM_G_PWM_OUT_INVERT          << PWM_G_INV_OUT_SHIFT))         |
         ((uint32)(PWM_G_PWM_OUT_N_INVERT        << PWM_G_INV_COMPL_OUT_SHIFT))     |
         ((uint32)(PWM_G_PWM_MODE                << PWM_G_MODE_SHIFT)));

        #if (PWM_G__PWM_PR == PWM_G_PWM_MODE)
            PWM_G_CONTROL_REG |=
            ((uint32)(PWM_G_PWM_RUN_MODE         << PWM_G_ONESHOT_SHIFT));

            PWM_G_WriteCounter(PWM_G_PWM_PR_INIT_VALUE);
        #else
            PWM_G_CONTROL_REG |=
            (((uint32)(PWM_G_PWM_ALIGN           << PWM_G_UPDOWN_SHIFT))          |
             ((uint32)(PWM_G_PWM_KILL_EVENT      << PWM_G_PWM_SYNC_KILL_SHIFT)));
        #endif  /* (PWM_G__PWM_PR == PWM_G_PWM_MODE) */

        #if (PWM_G__PWM_DT == PWM_G_PWM_MODE)
            PWM_G_CONTROL_REG |=
            ((uint32)(PWM_G_PWM_DEAD_TIME_CYCLE  << PWM_G_PRESCALER_SHIFT));
        #endif  /* (PWM_G__PWM_DT == PWM_G_PWM_MODE) */

        #if (PWM_G__PWM == PWM_G_PWM_MODE)
            PWM_G_CONTROL_REG |=
            ((uint32)PWM_G_PWM_PRESCALER         << PWM_G_PRESCALER_SHIFT);
        #endif  /* (PWM_G__PWM == PWM_G_PWM_MODE) */
    #endif  /* (PWM_G__PWM_SEL == PWM_G_CONFIG) */

    #if (PWM_G__TIMER == PWM_G_CONFIG)
        PWM_G_CONTROL_REG =
        (((uint32)(PWM_G_TC_PRESCALER            << PWM_G_PRESCALER_SHIFT))   |
         ((uint32)(PWM_G_TC_COUNTER_MODE         << PWM_G_UPDOWN_SHIFT))      |
         ((uint32)(PWM_G_TC_RUN_MODE             << PWM_G_ONESHOT_SHIFT))     |
         ((uint32)(PWM_G_TC_COMP_CAP_MODE        << PWM_G_MODE_SHIFT)));
    #endif  /* (PWM_G__TIMER == PWM_G_CONFIG) */

    /* Set values from customizer to CTRL1 */
    #if (PWM_G__QUAD == PWM_G_CONFIG)
        PWM_G_TRIG_CONTROL1_REG  =
        (((uint32)(PWM_G_QUAD_PHIA_SIGNAL_MODE   << PWM_G_COUNT_SHIFT))       |
         ((uint32)(PWM_G_QUAD_INDEX_SIGNAL_MODE  << PWM_G_RELOAD_SHIFT))      |
         ((uint32)(PWM_G_QUAD_STOP_SIGNAL_MODE   << PWM_G_STOP_SHIFT))        |
         ((uint32)(PWM_G_QUAD_PHIB_SIGNAL_MODE   << PWM_G_START_SHIFT)));
    #endif  /* (PWM_G__QUAD == PWM_G_CONFIG) */

    #if (PWM_G__PWM_SEL == PWM_G_CONFIG)
        PWM_G_TRIG_CONTROL1_REG  =
        (((uint32)(PWM_G_PWM_SWITCH_SIGNAL_MODE  << PWM_G_CAPTURE_SHIFT))     |
         ((uint32)(PWM_G_PWM_COUNT_SIGNAL_MODE   << PWM_G_COUNT_SHIFT))       |
         ((uint32)(PWM_G_PWM_RELOAD_SIGNAL_MODE  << PWM_G_RELOAD_SHIFT))      |
         ((uint32)(PWM_G_PWM_STOP_SIGNAL_MODE    << PWM_G_STOP_SHIFT))        |
         ((uint32)(PWM_G_PWM_START_SIGNAL_MODE   << PWM_G_START_SHIFT)));
    #endif  /* (PWM_G__PWM_SEL == PWM_G_CONFIG) */

    #if (PWM_G__TIMER == PWM_G_CONFIG)
        PWM_G_TRIG_CONTROL1_REG  =
        (((uint32)(PWM_G_TC_CAPTURE_SIGNAL_MODE  << PWM_G_CAPTURE_SHIFT))     |
         ((uint32)(PWM_G_TC_COUNT_SIGNAL_MODE    << PWM_G_COUNT_SHIFT))       |
         ((uint32)(PWM_G_TC_RELOAD_SIGNAL_MODE   << PWM_G_RELOAD_SHIFT))      |
         ((uint32)(PWM_G_TC_STOP_SIGNAL_MODE     << PWM_G_STOP_SHIFT))        |
         ((uint32)(PWM_G_TC_START_SIGNAL_MODE    << PWM_G_START_SHIFT)));
    #endif  /* (PWM_G__TIMER == PWM_G_CONFIG) */

    /* Set values from customizer to INTR */
    #if (PWM_G__QUAD == PWM_G_CONFIG)
        PWM_G_SetInterruptMode(PWM_G_QUAD_INTERRUPT_MASK);
    #endif  /* (PWM_G__QUAD == PWM_G_CONFIG) */

    #if (PWM_G__PWM_SEL == PWM_G_CONFIG)
        PWM_G_SetInterruptMode(PWM_G_PWM_INTERRUPT_MASK);
    #endif  /* (PWM_G__PWM_SEL == PWM_G_CONFIG) */

    #if (PWM_G__TIMER == PWM_G_CONFIG)
        PWM_G_SetInterruptMode(PWM_G_TC_INTERRUPT_MASK);
    #endif  /* (PWM_G__TIMER == PWM_G_CONFIG) */

    /* Set other values from customizer */
    #if (PWM_G__TIMER == PWM_G_CONFIG)
        PWM_G_WritePeriod(PWM_G_TC_PERIOD_VALUE );
        #if (PWM_G__COMPARE == PWM_G_TC_COMP_CAP_MODE)
            PWM_G_WriteCompare(PWM_G_TC_COMPARE_VALUE);

            #if (1u == PWM_G_TC_COMPARE_SWAP)
                PWM_G_SetCompareSwap(1u);
                PWM_G_WriteCompareBuf(PWM_G_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWM_G_TC_COMPARE_SWAP) */
        #endif  /* (PWM_G__COMPARE == PWM_G_TC_COMP_CAP_MODE) */
    #endif  /* (PWM_G__TIMER == PWM_G_CONFIG) */

    #if (PWM_G__PWM_SEL == PWM_G_CONFIG)
        PWM_G_WritePeriod(PWM_G_PWM_PERIOD_VALUE );
        PWM_G_WriteCompare(PWM_G_PWM_COMPARE_VALUE);

        #if (1u == PWM_G_PWM_COMPARE_SWAP)
            PWM_G_SetCompareSwap(1u);
            PWM_G_WriteCompareBuf(PWM_G_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWM_G_PWM_COMPARE_SWAP) */

        #if (1u == PWM_G_PWM_PERIOD_SWAP)
            PWM_G_SetPeriodSwap(1u);
            PWM_G_WritePeriodBuf(PWM_G_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWM_G_PWM_PERIOD_SWAP) */

        /* Set values from customizer to CTRL2 */
        #if (PWM_G__PWM_PR == PWM_G_PWM_MODE)
            PWM_G_TRIG_CONTROL2_REG =
                    (PWM_G_CC_MATCH_NO_CHANGE    |
                    PWM_G_OVERLOW_NO_CHANGE      |
                    PWM_G_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWM_G__LEFT == PWM_G_PWM_ALIGN)
                PWM_G_TRIG_CONTROL2_REG = PWM_G_PWM_MODE_LEFT;
            #endif  /* ( PWM_G_PWM_LEFT == PWM_G_PWM_ALIGN) */

            #if (PWM_G__RIGHT == PWM_G_PWM_ALIGN)
                PWM_G_TRIG_CONTROL2_REG = PWM_G_PWM_MODE_RIGHT;
            #endif  /* ( PWM_G_PWM_RIGHT == PWM_G_PWM_ALIGN) */

            #if (PWM_G__CENTER == PWM_G_PWM_ALIGN)
                PWM_G_TRIG_CONTROL2_REG = PWM_G_PWM_MODE_CENTER;
            #endif  /* ( PWM_G_PWM_CENTER == PWM_G_PWM_ALIGN) */

            #if (PWM_G__ASYMMETRIC == PWM_G_PWM_ALIGN)
                PWM_G_TRIG_CONTROL2_REG = PWM_G_PWM_MODE_ASYM;
            #endif  /* (PWM_G__ASYMMETRIC == PWM_G_PWM_ALIGN) */
        #endif  /* (PWM_G__PWM_PR == PWM_G_PWM_MODE) */
    #endif  /* (PWM_G__PWM_SEL == PWM_G_CONFIG) */
}


/*******************************************************************************
* Function Name: PWM_G_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM_G.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWM_G_BLOCK_CONTROL_REG |= PWM_G_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Statr Timer or PWM if start input is absent */
    #if (PWM_G__PWM_SEL == PWM_G_CONFIG)
        #if (0u == PWM_G_PWM_START_SIGNAL_PRESENT)
            PWM_G_TriggerCommand(PWM_G_MASK, PWM_G_CMD_START);
        #endif /* (0u == PWM_G_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWM_G__PWM_SEL == PWM_G_CONFIG) */

    #if (PWM_G__TIMER == PWM_G_CONFIG)
        #if (0u == PWM_G_TC_START_SIGNAL_PRESENT)
            PWM_G_TriggerCommand(PWM_G_MASK, PWM_G_CMD_START);
        #endif /* (0u == PWM_G_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWM_G__TIMER == PWM_G_CONFIG) */
}


/*******************************************************************************
* Function Name: PWM_G_Start
********************************************************************************
*
* Summary:
*  Initialize the PWM_G with default customizer
*  values when called the first time and enables the PWM_G.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_G_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWM_G_Start() is called. This allows
*  enable/disable component without re-initialization in all subsequent calls
*  to the PWM_G_Start() routine.
*
*******************************************************************************/
void PWM_G_Start(void)
{
    if (0u == PWM_G_initVar)
    {
        PWM_G_Init();
        PWM_G_initVar = 1u;
    }

    PWM_G_Enable();
}


/*******************************************************************************
* Function Name: PWM_G_Stop
********************************************************************************
*
* Summary:
*  Disables the PWM_G.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_BLOCK_CONTROL_REG &= (uint32)~PWM_G_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWM_G. This function is used when
*  configured as a generic PWM_G and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWM_G to operate in
*   Values:
*   - PWM_G_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWM_G_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWM_G_MODE_QUAD - Quadrature decoder
*         - PWM_G_MODE_PWM - PWM
*         - PWM_G_MODE_PWM_DT - PWM with dead time
*         - PWM_G_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_MODE_MASK;
    PWM_G_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of 3 supported modes.
*  Is functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWM_G_MODE_X1 - Counts on phi 1 rising
*         - PWM_G_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWM_G_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_QUAD_MODE_MASK;
    PWM_G_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to PWM with dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWM_G_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWM_G_PRESCALE_DIVBY2    - Divide by 2
*         - PWM_G_PRESCALE_DIVBY4    - Divide by 4
*         - PWM_G_PRESCALE_DIVBY8    - Divide by 8
*         - PWM_G_PRESCALE_DIVBY16   - Divide by 16
*         - PWM_G_PRESCALE_DIVBY32   - Divide by 32
*         - PWM_G_PRESCALE_DIVBY64   - Divide by 64
*         - PWM_G_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_PRESCALER_MASK;
    PWM_G_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM_G runs
*  continuously or stops when terminal count is reached.  By default the
*  PWM_G operates in continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_ONESHOT_MASK;
    PWM_G_CONTROL_REG |= ((uint32)((oneShotEnable & PWM_G_1BIT_MASK) <<
                                                               PWM_G_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the 3 must be ORed together to form the
*  mode.
*
* Parameters:
*  modeMask: Combination of the 3 mode settings.  Mask must include a value for
*  each of the 3 or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be 
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPWMMode(uint32 modeMask)
{
    PWM_G_TRIG_CONTROL2_REG = (modeMask & PWM_G_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWM_G_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes an asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to PWM and
*  PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_PWM_SYNC_KILL_MASK;
    PWM_G_CONTROL_REG |= ((uint32)((syncKillEnable & PWM_G_1BIT_MASK)  <<
                                               PWM_G_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_PWM_STOP_KILL_MASK;
    PWM_G_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWM_G_1BIT_MASK)  <<
                                                         PWM_G_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_PRESCALER_MASK;
    PWM_G_CONTROL_REG |= ((uint32)((deadTime & PWM_G_8BIT_MASK) <<
                                                          PWM_G_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - PWM_G_INVERT_LINE   - Inverts the line output
*         - PWM_G_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_INV_OUT_MASK;
    PWM_G_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWM_G_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_WriteCounter(uint32 count)
{
    PWM_G_COUNTER_REG = (count & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 PWM_G_ReadCounter(void)
{
    return (PWM_G_COUNTER_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and PWM with pseudo random output.
*
* Parameters:
*  counterMode: Enumerated couner type values
*   Values:
*     - PWM_G_COUNT_UP       - Counts up
*     - PWM_G_COUNT_DOWN     - Counts down
*     - PWM_G_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWM_G_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_UPDOWN_MASK;
    PWM_G_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_WritePeriod(uint32 period)
{
    PWM_G_PERIOD_REG = (period & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWM_G_ReadPeriod(void)
{
    return (PWM_G_PERIOD_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in Timer/Counter mode(without capture) the swap occurs
*  at a TC event. In PWM mode the swap occurs at the next TC event following
*  a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_RELOAD_CC_MASK;
    PWM_G_CONTROL_REG |= (swapEnable & PWM_G_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_WritePeriodBuf(uint32 periodBuf)
{
    PWM_G_PERIOD_BUF_REG = (periodBuf & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWM_G_ReadPeriodBuf(void)
{
    return (PWM_G_PERIOD_BUF_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In PWM mode the swap occurs at the next TC event following a hardware switch
*  event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_CONTROL_REG &= (uint32)~PWM_G_RELOAD_PERIOD_MASK;
    PWM_G_CONTROL_REG |= ((uint32)((swapEnable & PWM_G_1BIT_MASK) <<
                                                            PWM_G_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_WriteCompare(uint32 compare)
{
    PWM_G_COMP_CAP_REG = (compare & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 PWM_G_ReadCompare(void)
{
    return (PWM_G_COMP_CAP_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_WriteCompareBuf(uint32 compareBuf)
{
   PWM_G_COMP_CAP_BUF_REG = (compareBuf & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 PWM_G_ReadCompareBuf(void)
{
    return (PWM_G_COMP_CAP_BUF_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 PWM_G_ReadCapture(void)
{
    return (PWM_G_COMP_CAP_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 PWM_G_ReadCaptureBuf(void)
{
    return (PWM_G_COMP_CAP_BUF_REG & PWM_G_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWM_G_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_G_TRIG_LEVEL     - Level
*     - PWM_G_TRIG_RISING    - Rising edge
*     - PWM_G_TRIG_FALLING   - Falling edge
*     - PWM_G_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_TRIG_CONTROL1_REG &= (uint32)~PWM_G_CAPTURE_MASK;
    PWM_G_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_G_TRIG_LEVEL     - Level
*     - PWM_G_TRIG_RISING    - Rising edge
*     - PWM_G_TRIG_FALLING   - Falling edge
*     - PWM_G_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_TRIG_CONTROL1_REG &= (uint32)~PWM_G_RELOAD_MASK;
    PWM_G_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_G_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_G_TRIG_LEVEL     - Level
*     - PWM_G_TRIG_RISING    - Rising edge
*     - PWM_G_TRIG_FALLING   - Falling edge
*     - PWM_G_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_TRIG_CONTROL1_REG &= (uint32)~PWM_G_START_MASK;
    PWM_G_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_G_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_G_TRIG_LEVEL     - Level
*     - PWM_G_TRIG_RISING    - Rising edge
*     - PWM_G_TRIG_FALLING   - Falling edge
*     - PWM_G_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_TRIG_CONTROL1_REG &= (uint32)~PWM_G_STOP_MASK;
    PWM_G_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_G_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWM_G_TRIG_LEVEL     - Level
*     - PWM_G_TRIG_RISING    - Rising edge
*     - PWM_G_TRIG_FALLING   - Falling edge
*     - PWM_G_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_TRIG_CONTROL1_REG &= (uint32)~PWM_G_COUNT_MASK;
    PWM_G_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWM_G_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: Combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - PWM_G_CMD_CAPTURE    - Trigger Capture command
*     - PWM_G_CMD_RELOAD     - Trigger Reload command
*     - PWM_G_CMD_STOP       - Trigger Stop command
*     - PWM_G_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWM_G_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWM_G_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWM_G.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWM_G_STATUS_DOWN    - Set if counting down
*     - PWM_G_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWM_G_ReadStatus(void)
{
    return ((PWM_G_STATUS_REG >> PWM_G_RUNNING_STATUS_SHIFT) |
            (PWM_G_STATUS_REG & PWM_G_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWM_G_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWM_G_INTR_MASK_TC       - Terminal count mask
*     - PWM_G_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetInterruptMode(uint32 interruptMask)
{
    PWM_G_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWM_G_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - PWM_G_INTR_MASK_TC       - Terminal count mask
*     - PWM_G_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWM_G_GetInterruptSourceMasked(void)
{
    return (PWM_G_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWM_G_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - PWM_G_INTR_MASK_TC       - Terminal count mask
*     - PWM_G_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWM_G_GetInterruptSource(void)
{
    return (PWM_G_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWM_G_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWM_G_INTR_MASK_TC       - Terminal count mask
*     - PWM_G_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_ClearInterrupt(uint32 interruptMask)
{
    PWM_G_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWM_G_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWM_G_INTR_MASK_TC       - Terminal count mask
*     - PWM_G_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWM_G_SetInterrupt(uint32 interruptMask)
{
    PWM_G_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
