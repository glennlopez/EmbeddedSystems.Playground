/*******************************************************************************
* File Name: LED_SegDriver_1_COM_PWM.c  
* Version 2.10
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks. 
*  The compare value output may be configured to be active when the present 
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "LED_SegDriver_1_COM_PWM.h"

uint8 LED_SegDriver_1_COM_PWM_initVar = 0u;

/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  LED_SegDriver_1_COM_PWM_initVar: Is modified when this function is called for the first 
*   time. Is used to ensure that initialization happens only once.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LED_SegDriver_1_COM_PWM_initVar == 0u)
    {
        LED_SegDriver_1_COM_PWM_Init();
        LED_SegDriver_1_COM_PWM_initVar = 1u;
    }
    LED_SegDriver_1_COM_PWM_Enable();

}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  LED_SegDriver_1_COM_PWM_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Init(void) 
{
    #if (LED_SegDriver_1_COM_PWM_UsingFixedFunction || LED_SegDriver_1_COM_PWM_UseControl)
        uint8 ctrl;
    #endif
    
    #if(!LED_SegDriver_1_COM_PWM_UsingFixedFunction) 
        #if(LED_SegDriver_1_COM_PWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 LED_SegDriver_1_COM_PWM_interruptState;
        #endif
    #endif
    
   #if (LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        LED_SegDriver_1_COM_PWM_CONTROL |= LED_SegDriver_1_COM_PWM_CFG0_MODE;
        #if (LED_SegDriver_1_COM_PWM_DeadBand2_4)
            LED_SegDriver_1_COM_PWM_CONTROL |= LED_SegDriver_1_COM_PWM_CFG0_DB;
        #endif
                
        /* Set the default Compare Mode */
        #if(LED_SegDriver_1_COM_PWM_PSOC3_ES2 || LED_SegDriver_1_COM_PWM_PSOC5_ES1)
                ctrl = LED_SegDriver_1_COM_PWM_CONTROL2 & ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK;
                LED_SegDriver_1_COM_PWM_CONTROL2 = ctrl | LED_SegDriver_1_COM_PWM_DEFAULT_COMPARE1_MODE;
        #endif
        #if(LED_SegDriver_1_COM_PWM_PSOC3_ES3 || LED_SegDriver_1_COM_PWM_PSOC5_ES2)
                ctrl = LED_SegDriver_1_COM_PWM_CONTROL3 & ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK;
                LED_SegDriver_1_COM_PWM_CONTROL3 = ctrl | LED_SegDriver_1_COM_PWM_DEFAULT_COMPARE1_MODE;
        #endif
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        LED_SegDriver_1_COM_PWM_RT1 &= ~LED_SegDriver_1_COM_PWM_RT1_MASK;
        LED_SegDriver_1_COM_PWM_RT1 |= LED_SegDriver_1_COM_PWM_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        LED_SegDriver_1_COM_PWM_RT1 &= ~(LED_SegDriver_1_COM_PWM_SYNCDSI_MASK);
        LED_SegDriver_1_COM_PWM_RT1 |= LED_SegDriver_1_COM_PWM_SYNCDSI_EN;
       
    #elif (LED_SegDriver_1_COM_PWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = LED_SegDriver_1_COM_PWM_CONTROL & ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_MASK & ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK;
        LED_SegDriver_1_COM_PWM_CONTROL = ctrl | LED_SegDriver_1_COM_PWM_DEFAULT_COMPARE2_MODE | LED_SegDriver_1_COM_PWM_DEFAULT_COMPARE1_MODE;
    #endif 
        
    #if (!LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        #if (LED_SegDriver_1_COM_PWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            LED_SegDriver_1_COM_PWM_AUX_CONTROLDP0 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
        #else /* (LED_SegDriver_1_COM_PWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            LED_SegDriver_1_COM_PWM_AUX_CONTROLDP0 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
            LED_SegDriver_1_COM_PWM_AUX_CONTROLDP1 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
        #endif
    #endif
        
    LED_SegDriver_1_COM_PWM_WritePeriod(LED_SegDriver_1_COM_PWM_INIT_PERIOD_VALUE);
    LED_SegDriver_1_COM_PWM_WriteCounter(LED_SegDriver_1_COM_PWM_INIT_PERIOD_VALUE);
        
        #if (LED_SegDriver_1_COM_PWM_UseOneCompareMode)
            LED_SegDriver_1_COM_PWM_WriteCompare(LED_SegDriver_1_COM_PWM_INIT_COMPARE_VALUE1);
        #else
            LED_SegDriver_1_COM_PWM_WriteCompare1(LED_SegDriver_1_COM_PWM_INIT_COMPARE_VALUE1);
            LED_SegDriver_1_COM_PWM_WriteCompare2(LED_SegDriver_1_COM_PWM_INIT_COMPARE_VALUE2);
        #endif
        
        #if (LED_SegDriver_1_COM_PWM_KillModeMinTime)
            LED_SegDriver_1_COM_PWM_WriteKillTime(LED_SegDriver_1_COM_PWM_MinimumKillTime);
        #endif
        
        #if (LED_SegDriver_1_COM_PWM_DeadBandUsed)
            LED_SegDriver_1_COM_PWM_WriteDeadTime(LED_SegDriver_1_COM_PWM_INIT_DEAD_TIME);
        #endif

    #if (LED_SegDriver_1_COM_PWM_UseStatus || LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        LED_SegDriver_1_COM_PWM_SetInterruptMode(LED_SegDriver_1_COM_PWM_INIT_INTERRUPTS_MODE);
    #endif
        
    #if (LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        LED_SegDriver_1_COM_PWM_GLOBAL_ENABLE |= LED_SegDriver_1_COM_PWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        LED_SegDriver_1_COM_PWM_CONTROL2 |= LED_SegDriver_1_COM_PWM_CTRL2_IRQ_SEL;
    #else
        #if(LED_SegDriver_1_COM_PWM_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LED_SegDriver_1_COM_PWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            LED_SegDriver_1_COM_PWM_STATUS_AUX_CTRL |= LED_SegDriver_1_COM_PWM_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(LED_SegDriver_1_COM_PWM_interruptState);
            
            /* Clear the FIFO to enable the LED_SegDriver_1_COM_PWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            LED_SegDriver_1_COM_PWM_ClearFIFO();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        LED_SegDriver_1_COM_PWM_GLOBAL_ENABLE |= LED_SegDriver_1_COM_PWM_BLOCK_EN_MASK;
        LED_SegDriver_1_COM_PWM_GLOBAL_STBY_ENABLE |= LED_SegDriver_1_COM_PWM_BLOCK_STBY_EN_MASK;
    #endif 
    
    /* Enable the PWM from the control register  */
    #if (LED_SegDriver_1_COM_PWM_UseControl || LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        LED_SegDriver_1_COM_PWM_CONTROL |= LED_SegDriver_1_COM_PWM_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Stop(void) 
{
    #if (LED_SegDriver_1_COM_PWM_UseControl || LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        LED_SegDriver_1_COM_PWM_CONTROL &= ~LED_SegDriver_1_COM_PWM_CTRL_ENABLE;
    #endif
    
    /* Globally disable the Fixed Function Block chosen */
    #if (LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        LED_SegDriver_1_COM_PWM_GLOBAL_ENABLE &= ~LED_SegDriver_1_COM_PWM_BLOCK_EN_MASK;
        LED_SegDriver_1_COM_PWM_GLOBAL_STBY_ENABLE &= ~LED_SegDriver_1_COM_PWM_BLOCK_STBY_EN_MASK;
    #endif
}


#if (LED_SegDriver_1_COM_PWM_UseOneCompareMode)
#if (LED_SegDriver_1_COM_PWM_CompareMode1SW)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_SetCompareMode
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm output when in Dither mode,
*  Center Align Mode or One Output Mode.
*
* Parameters:
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return:
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_SetCompareMode(uint8 comparemode) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
            #if(LED_SegDriver_1_COM_PWM_PSOC3_ES2 || LED_SegDriver_1_COM_PWM_PSOC5_ES1)
                        uint8 comparemodemasked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_SHIFT);
                        LED_SegDriver_1_COM_PWM_CONTROL2 &= ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
                        LED_SegDriver_1_COM_PWM_CONTROL2 |= comparemodemasked;  
                #endif
                
            #if(LED_SegDriver_1_COM_PWM_PSOC3_ES3 || LED_SegDriver_1_COM_PWM_PSOC5_ES2)
                    uint8 comparemodemasked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_SHIFT);
            LED_SegDriver_1_COM_PWM_CONTROL3 &= ~LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            LED_SegDriver_1_COM_PWM_CONTROL3 |= comparemodemasked;     
                #endif
                
    #elif (LED_SegDriver_1_COM_PWM_UseControl)
        uint8 comparemode1masked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_SHIFT) & LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_SHIFT) & LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_MASK;
        LED_SegDriver_1_COM_PWM_CONTROL &= ~(LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK | LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_MASK); /*Clear existing mode */
        LED_SegDriver_1_COM_PWM_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif
}
#endif /* LED_SegDriver_1_COM_PWM_CompareMode1SW */

#else /* UseOneCompareMode */


#if (LED_SegDriver_1_COM_PWM_CompareMode1SW)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_SetCompareMode1
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm1 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_SHIFT) & LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK;
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
            #if(LED_SegDriver_1_COM_PWM_PSOC3_ES2 || LED_SegDriver_1_COM_PWM_PSOC5_ES1)
                        LED_SegDriver_1_COM_PWM_CONTROL2 &= LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        LED_SegDriver_1_COM_PWM_CONTROL2 |= comparemodemasked; 
            #endif
                
                #if(LED_SegDriver_1_COM_PWM_PSOC3_ES3 || LED_SegDriver_1_COM_PWM_PSOC5_ES2)
                    LED_SegDriver_1_COM_PWM_CONTROL3 &= LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        LED_SegDriver_1_COM_PWM_CONTROL3 |= comparemodemasked; 
            #endif
                
    #elif (LED_SegDriver_1_COM_PWM_UseControl)
        LED_SegDriver_1_COM_PWM_CONTROL &= LED_SegDriver_1_COM_PWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        LED_SegDriver_1_COM_PWM_CONTROL |= comparemodemasked;
    #endif    
}
#endif /* LED_SegDriver_1_COM_PWM_CompareMode1SW */


#if (LED_SegDriver_1_COM_PWM_CompareMode2SW)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_SetCompareMode2
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm2 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_SetCompareMode2(uint8 comparemode) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block*/ 
    #elif (LED_SegDriver_1_COM_PWM_UseControl)
    uint8 comparemodemasked = (comparemode << LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_SHIFT) & LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_MASK;
    LED_SegDriver_1_COM_PWM_CONTROL &= LED_SegDriver_1_COM_PWM_CTRL_CMPMODE2_MASK; /*Clear existing mode */
    LED_SegDriver_1_COM_PWM_CONTROL |= comparemodemasked;
    #endif    
}
#endif /*LED_SegDriver_1_COM_PWM_CompareMode2SW */
#endif /* UseOneCompareMode */


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WriteCounter
********************************************************************************
* 
* Summary:
*  This function is used to change the counter value.
*
* Parameters:  
*  counter:  This value may be between 1 and (2^Resolution)-1.   
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WriteCounter(uint8 counter) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        CY_SET_REG16(LED_SegDriver_1_COM_PWM_COUNTER_LSB_PTR, (uint16)counter);
    #else
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_COUNTER_LSB_PTR, counter);
    #endif
}


#if (!LED_SegDriver_1_COM_PWM_UsingFixedFunction)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_ReadCounter
********************************************************************************
* 
* Summary:
*  This function returns the current value of the counter.  It doesn't matter
*  if the counter is enabled or running.
*
* Parameters:  
*  void  
*
* Return: 
*  The current value of the counter.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint8 LED_SegDriver_1_COM_PWM_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(LED_SegDriver_1_COM_PWM_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG8(LED_SegDriver_1_COM_PWM_CAPTURE_LSB_PTR));
}


#if (LED_SegDriver_1_COM_PWM_UseStatus)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_ClearFIFO
********************************************************************************
* 
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_ClearFIFO(void) 
{
    while(LED_SegDriver_1_COM_PWM_ReadStatusRegister() & LED_SegDriver_1_COM_PWM_STATUS_FIFONEMPTY)
        LED_SegDriver_1_COM_PWM_ReadCapture();
}
#endif /* LED_SegDriver_1_COM_PWM_UseStatus */
#endif /* !LED_SegDriver_1_COM_PWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0 
*           will result in the counter remaining at zero.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WritePeriod(uint8 period) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        CY_SET_REG16(LED_SegDriver_1_COM_PWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_PERIOD_LSB_PTR, period);
    #endif
}


#if (LED_SegDriver_1_COM_PWM_UseOneCompareMode)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WriteCompare
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value when the PWM is in Dither
*  mode. The compare output will reflect the new value on the next UDB clock. 
*  The compare output will be driven high when the present counter value is 
*  compared to the compare value based on the compare mode defined in 
*  Dither Mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Side Effects:
*  This function is only available if the PWM mode parameter is set to
*  Dither Mode, Center Aligned Mode or One Output Mode
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WriteCompare(uint8 compare) 
{
   CY_SET_REG8(LED_SegDriver_1_COM_PWM_COMPARE1_LSB_PTR, compare);
   #if (LED_SegDriver_1_COM_PWM_PWMMode == LED_SegDriver_1_COM_PWM__B_PWM__DITHER)
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_COMPARE2_LSB_PTR, compare+1);
   #endif
}


#else


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WriteCompare1
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value.  The compare output will 
*  reflect the new value on the next UDB clock.  The compare output will be 
*  driven high when the present counter value is less than or less than or 
*  equal to the compare register, depending on the mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WriteCompare1(uint8 compare) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        CY_SET_REG16(LED_SegDriver_1_COM_PWM_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_COMPARE1_LSB_PTR, compare);
    #endif
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WriteCompare2
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare value, for compare1 output.  
*  The compare output will reflect the new value on the next UDB clock.  
*  The compare output will be driven high when the present counter value is 
*  less than or less than or equal to the compare register, depending on the 
*  mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WriteCompare2(uint8 compare) 
{
    #if(LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        CY_SET_REG16(LED_SegDriver_1_COM_PWM_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_COMPARE2_LSB_PTR, compare);
    #endif
}
#endif /* UseOneCompareMode */


#if (LED_SegDriver_1_COM_PWM_DeadBandUsed)
/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_WriteDeadTime
********************************************************************************
* 
* Summary:
*  This function writes the dead-band counts to the corresponding register
*
* Parameters:  
*  deadtime:  Number of counts for dead time 
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!LED_SegDriver_1_COM_PWM_DeadBand2_4)
        CY_SET_REG8(LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        LED_SegDriver_1_COM_PWM_DEADBAND_COUNT &= ~LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        LED_SegDriver_1_COM_PWM_DEADBAND_COUNT |= (deadtime << LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_SHIFT) & LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_MASK; 
    #endif
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_ReadDeadTime
********************************************************************************
* 
* Summary:
*  This function reads the dead-band counts from the corresponding register
*
* Parameters:  
*  void
*
* Return: 
*  Dead Band Counts
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint8 LED_SegDriver_1_COM_PWM_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!LED_SegDriver_1_COM_PWM_DeadBand2_4)
        return (CY_GET_REG8(LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((LED_SegDriver_1_COM_PWM_DEADBAND_COUNT & LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_MASK) >> LED_SegDriver_1_COM_PWM_DEADBAND_COUNT_SHIFT);
    #endif
}
#endif /* DeadBandUsed */

