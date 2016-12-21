/*******************************************************************************
* File Name: AnalogIn.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "AnalogIn.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        AnalogIn_PC =   (AnalogIn_PC & \
                                (uint32)(~(uint32)(AnalogIn_DRIVE_MODE_IND_MASK << (AnalogIn_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (AnalogIn_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: AnalogIn_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void AnalogIn_Write(uint8 value) 
{
    uint8 drVal = (uint8)(AnalogIn_DR & (uint8)(~AnalogIn_MASK));
    drVal = (drVal | ((uint8)(value << AnalogIn_SHIFT) & AnalogIn_MASK));
    AnalogIn_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: AnalogIn_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  AnalogIn_DM_STRONG     Strong Drive 
*  AnalogIn_DM_OD_HI      Open Drain, Drives High 
*  AnalogIn_DM_OD_LO      Open Drain, Drives Low 
*  AnalogIn_DM_RES_UP     Resistive Pull Up 
*  AnalogIn_DM_RES_DWN    Resistive Pull Down 
*  AnalogIn_DM_RES_UPDWN  Resistive Pull Up/Down 
*  AnalogIn_DM_DIG_HIZ    High Impedance Digital 
*  AnalogIn_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void AnalogIn_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(AnalogIn__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: AnalogIn_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro AnalogIn_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 AnalogIn_Read(void) 
{
    return (uint8)((AnalogIn_PS & AnalogIn_MASK) >> AnalogIn_SHIFT);
}


/*******************************************************************************
* Function Name: AnalogIn_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 AnalogIn_ReadDataReg(void) 
{
    return (uint8)((AnalogIn_DR & AnalogIn_MASK) >> AnalogIn_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(AnalogIn_INTSTAT) 

    /*******************************************************************************
    * Function Name: AnalogIn_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 AnalogIn_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(AnalogIn_INTSTAT & AnalogIn_MASK);
		AnalogIn_INTSTAT = maskedStatus;
        return maskedStatus >> AnalogIn_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
