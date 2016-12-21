/*******************************************************************************
* File Name: PWM2_PM.c
* Version 3.10
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM2.h"

static PWM2_backupStruct PWM2_backup;


/*******************************************************************************
* Function Name: PWM2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM2_SaveConfig(void) 
{

    #if(!PWM2_UsingFixedFunction)
        #if(!PWM2_PWMModeIsCenterAligned)
            PWM2_backup.PWMPeriod = PWM2_ReadPeriod();
        #endif /* (!PWM2_PWMModeIsCenterAligned) */
        PWM2_backup.PWMUdb = PWM2_ReadCounter();
        #if (PWM2_UseStatus)
            PWM2_backup.InterruptMaskValue = PWM2_STATUS_MASK;
        #endif /* (PWM2_UseStatus) */

        #if(PWM2_DeadBandMode == PWM2__B_PWM__DBM_256_CLOCKS || \
            PWM2_DeadBandMode == PWM2__B_PWM__DBM_2_4_CLOCKS)
            PWM2_backup.PWMdeadBandValue = PWM2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM2_KillModeMinTime)
             PWM2_backup.PWMKillCounterPeriod = PWM2_ReadKillTime();
        #endif /* (PWM2_KillModeMinTime) */

        #if(PWM2_UseControl)
            PWM2_backup.PWMControlRegister = PWM2_ReadControlRegister();
        #endif /* (PWM2_UseControl) */
    #endif  /* (!PWM2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM2_RestoreConfig(void) 
{
        #if(!PWM2_UsingFixedFunction)
            #if(!PWM2_PWMModeIsCenterAligned)
                PWM2_WritePeriod(PWM2_backup.PWMPeriod);
            #endif /* (!PWM2_PWMModeIsCenterAligned) */

            PWM2_WriteCounter(PWM2_backup.PWMUdb);

            #if (PWM2_UseStatus)
                PWM2_STATUS_MASK = PWM2_backup.InterruptMaskValue;
            #endif /* (PWM2_UseStatus) */

            #if(PWM2_DeadBandMode == PWM2__B_PWM__DBM_256_CLOCKS || \
                PWM2_DeadBandMode == PWM2__B_PWM__DBM_2_4_CLOCKS)
                PWM2_WriteDeadTime(PWM2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM2_KillModeMinTime)
                PWM2_WriteKillTime(PWM2_backup.PWMKillCounterPeriod);
            #endif /* (PWM2_KillModeMinTime) */

            #if(PWM2_UseControl)
                PWM2_WriteControlRegister(PWM2_backup.PWMControlRegister);
            #endif /* (PWM2_UseControl) */
        #endif  /* (!PWM2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM2_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM2_Sleep(void) 
{
    #if(PWM2_UseControl)
        if(PWM2_CTRL_ENABLE == (PWM2_CONTROL & PWM2_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM2_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM2_UseControl) */

    /* Stop component */
    PWM2_Stop();

    /* Save registers configuration */
    PWM2_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM2_Wakeup(void) 
{
     /* Restore registers values */
    PWM2_RestoreConfig();

    if(PWM2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
