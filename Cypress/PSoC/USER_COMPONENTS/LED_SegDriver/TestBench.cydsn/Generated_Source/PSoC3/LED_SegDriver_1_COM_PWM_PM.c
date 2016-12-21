/*******************************************************************************
* File Name: LED_SegDriver_1_COM_PWM_PM.c
* Version 2.10
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "LED_SegDriver_1_COM_PWM.h"

static LED_SegDriver_1_COM_PWM_backupStruct LED_SegDriver_1_COM_PWM_backup;


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LED_SegDriver_1_COM_PWM_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_SaveConfig(void)
{
    
    #if(!LED_SegDriver_1_COM_PWM_UsingFixedFunction)
        #if (LED_SegDriver_1_COM_PWM_PSOC3_ES2 || LED_SegDriver_1_COM_PWM_PSOC5_ES1)
            LED_SegDriver_1_COM_PWM_backup.PWMUdb = LED_SegDriver_1_COM_PWM_ReadCounter();
            LED_SegDriver_1_COM_PWM_backup.PWMPeriod = LED_SegDriver_1_COM_PWM_ReadPeriod();
            #if (LED_SegDriver_1_COM_PWM_UseStatus)
                LED_SegDriver_1_COM_PWM_backup.InterruptMaskValue = LED_SegDriver_1_COM_PWM_STATUS_MASK;
            #endif
            
            #if(LED_SegDriver_1_COM_PWM_UseOneCompareMode)
                LED_SegDriver_1_COM_PWM_backup.PWMCompareValue = LED_SegDriver_1_COM_PWM_ReadCompare();
            #else
                LED_SegDriver_1_COM_PWM_backup.PWMCompareValue1 = LED_SegDriver_1_COM_PWM_ReadCompare1();
                LED_SegDriver_1_COM_PWM_backup.PWMCompareValue2 = LED_SegDriver_1_COM_PWM_ReadCompare2();
            #endif
            
           #if(LED_SegDriver_1_COM_PWM_DeadBandUsed)
                LED_SegDriver_1_COM_PWM_backup.PWMdeadBandValue = LED_SegDriver_1_COM_PWM_ReadDeadTime();
            #endif
          
            #if ( LED_SegDriver_1_COM_PWM_KillModeMinTime)
                LED_SegDriver_1_COM_PWM_backup.PWMKillCounterPeriod = LED_SegDriver_1_COM_PWM_ReadKillTime();
            #endif
        #endif
        
        #if (LED_SegDriver_1_COM_PWM_PSOC3_ES3 || LED_SegDriver_1_COM_PWM_PSOC5_ES2)
            #if(!LED_SegDriver_1_COM_PWM_PWMModeIsCenterAligned)
                LED_SegDriver_1_COM_PWM_backup.PWMPeriod = LED_SegDriver_1_COM_PWM_ReadPeriod();
            #endif
            LED_SegDriver_1_COM_PWM_backup.PWMUdb = LED_SegDriver_1_COM_PWM_ReadCounter();
            #if (LED_SegDriver_1_COM_PWM_UseStatus)
                LED_SegDriver_1_COM_PWM_backup.InterruptMaskValue = LED_SegDriver_1_COM_PWM_STATUS_MASK;
            #endif
            
            #if(LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_256_CLOCKS || LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
                LED_SegDriver_1_COM_PWM_backup.PWMdeadBandValue = LED_SegDriver_1_COM_PWM_ReadDeadTime();
            #endif
            
            #if(LED_SegDriver_1_COM_PWM_KillModeMinTime)
                 LED_SegDriver_1_COM_PWM_backup.PWMKillCounterPeriod = LED_SegDriver_1_COM_PWM_ReadKillTime();
            #endif
        #endif
        
        #if(LED_SegDriver_1_COM_PWM_UseControl)
            LED_SegDriver_1_COM_PWM_backup.PWMControlRegister = LED_SegDriver_1_COM_PWM_ReadControlRegister();
        #endif
    #endif  
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LED_SegDriver_1_COM_PWM_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_RestoreConfig(void) 
{
        #if(!LED_SegDriver_1_COM_PWM_UsingFixedFunction)
            #if (LED_SegDriver_1_COM_PWM_PSOC3_ES2 || LED_SegDriver_1_COM_PWM_PSOC5_ES1)
                /* Interrupt State Backup for Critical Region*/
                uint8 LED_SegDriver_1_COM_PWM_interruptState;
                /* Enter Critical Region*/
                LED_SegDriver_1_COM_PWM_interruptState = CyEnterCriticalSection();
                #if (LED_SegDriver_1_COM_PWM_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    LED_SegDriver_1_COM_PWM_STATUS_AUX_CTRL |= LED_SegDriver_1_COM_PWM_STATUS_ACTL_INT_EN_MASK;
                    
                    LED_SegDriver_1_COM_PWM_STATUS_MASK = LED_SegDriver_1_COM_PWM_backup.InterruptMaskValue;
                #endif
                
                #if (LED_SegDriver_1_COM_PWM_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    LED_SegDriver_1_COM_PWM_AUX_CONTROLDP0 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
                #else /* (LED_SegDriver_1_COM_PWM_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    LED_SegDriver_1_COM_PWM_AUX_CONTROLDP0 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
                    LED_SegDriver_1_COM_PWM_AUX_CONTROLDP1 |= (LED_SegDriver_1_COM_PWM_AUX_CTRL_FIFO0_CLR);
                #endif
                /* Exit Critical Region*/
                CyExitCriticalSection(LED_SegDriver_1_COM_PWM_interruptState);
                
                LED_SegDriver_1_COM_PWM_WriteCounter(LED_SegDriver_1_COM_PWM_backup.PWMUdb);
                LED_SegDriver_1_COM_PWM_WritePeriod(LED_SegDriver_1_COM_PWM_backup.PWMPeriod);
                
                #if(LED_SegDriver_1_COM_PWM_UseOneCompareMode)
                    LED_SegDriver_1_COM_PWM_WriteCompare(LED_SegDriver_1_COM_PWM_backup.PWMCompareValue);
                #else
                    LED_SegDriver_1_COM_PWM_WriteCompare1(LED_SegDriver_1_COM_PWM_backup.PWMCompareValue1);
                    LED_SegDriver_1_COM_PWM_WriteCompare2(LED_SegDriver_1_COM_PWM_backup.PWMCompareValue2);
                #endif
                
               #if(LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_256_CLOCKS || LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
                    LED_SegDriver_1_COM_PWM_WriteDeadTime(LED_SegDriver_1_COM_PWM_backup.PWMdeadBandValue);
                #endif
            
                #if ( LED_SegDriver_1_COM_PWM_KillModeMinTime)
                    LED_SegDriver_1_COM_PWM_WriteKillTime(LED_SegDriver_1_COM_PWM_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if (LED_SegDriver_1_COM_PWM_PSOC3_ES3 || LED_SegDriver_1_COM_PWM_PSOC5_ES2)
                #if(!LED_SegDriver_1_COM_PWM_PWMModeIsCenterAligned)
                    LED_SegDriver_1_COM_PWM_WritePeriod(LED_SegDriver_1_COM_PWM_backup.PWMPeriod);
                #endif
                LED_SegDriver_1_COM_PWM_WriteCounter(LED_SegDriver_1_COM_PWM_backup.PWMUdb);
                #if (LED_SegDriver_1_COM_PWM_UseStatus)
                    LED_SegDriver_1_COM_PWM_STATUS_MASK = LED_SegDriver_1_COM_PWM_backup.InterruptMaskValue;
                #endif
                
                #if(LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_256_CLOCKS || LED_SegDriver_1_COM_PWM_DeadBandMode == LED_SegDriver_1_COM_PWM__B_PWM__DBM_2_4_CLOCKS)
                    LED_SegDriver_1_COM_PWM_WriteDeadTime(LED_SegDriver_1_COM_PWM_backup.PWMdeadBandValue);
                #endif
                
                #if(LED_SegDriver_1_COM_PWM_KillModeMinTime)
                    LED_SegDriver_1_COM_PWM_WriteKillTime(LED_SegDriver_1_COM_PWM_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if(LED_SegDriver_1_COM_PWM_UseControl)
                LED_SegDriver_1_COM_PWM_WriteControlRegister(LED_SegDriver_1_COM_PWM_backup.PWMControlRegister); 
            #endif
        #endif  
    }


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LED_SegDriver_1_COM_PWM_backup.PWMEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Sleep(void)
{
    #if(LED_SegDriver_1_COM_PWM_UseControl)
        if(LED_SegDriver_1_COM_PWM_CTRL_ENABLE == (LED_SegDriver_1_COM_PWM_CONTROL & LED_SegDriver_1_COM_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            LED_SegDriver_1_COM_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LED_SegDriver_1_COM_PWM_backup.PWMEnableState = 0u;
        }
    #endif
    /* Stop component */
    LED_SegDriver_1_COM_PWM_Stop();
    
    /* Save registers configuration */
    LED_SegDriver_1_COM_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_SegDriver_1_COM_PWM_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LED_SegDriver_1_COM_PWM_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void LED_SegDriver_1_COM_PWM_Wakeup(void) 
{
     /* Restore registers values */
    LED_SegDriver_1_COM_PWM_RestoreConfig();
    
    if(LED_SegDriver_1_COM_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LED_SegDriver_1_COM_PWM_Enable();
    } /* Do nothing if component's block was disabled before */
    
}

/* [] END OF FILE */
