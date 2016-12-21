/*******************************************************************************
* File Name: PWM_out.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "PWM_out.h"


/*******************************************************************************
* Function Name: PWM_out_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void PWM_out_Write(uint8 value) 
{
    uint8 staticBits = PWM_out_DR & ~PWM_out_MASK;
    PWM_out_DR = staticBits | ((value << PWM_out_SHIFT) & PWM_out_MASK);
}


/*******************************************************************************
* Function Name: PWM_out_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void PWM_out_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PWM_out_0, mode);
}


/*******************************************************************************
* Function Name: PWM_out_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PWM_out_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWM_out_Read(void) 
{
    return (PWM_out_PS & PWM_out_MASK) >> PWM_out_SHIFT;
}


/*******************************************************************************
* Function Name: PWM_out_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PWM_out_ReadDataReg(void) 
{
    return (PWM_out_DR & PWM_out_MASK) >> PWM_out_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWM_out_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWM_out_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PWM_out_ClearInterrupt(void) 
    {
        return (PWM_out_INTSTAT & PWM_out_MASK) >> PWM_out_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
