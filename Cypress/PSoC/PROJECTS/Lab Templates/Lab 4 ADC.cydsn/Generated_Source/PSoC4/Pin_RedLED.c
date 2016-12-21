/*******************************************************************************
* File Name: Pin_RedLED.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Pin_RedLED.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Pin_RedLED_PC =   (Pin_RedLED_PC & \
                                (uint32)(~(uint32)(Pin_RedLED_DRIVE_MODE_IND_MASK << (Pin_RedLED_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Pin_RedLED_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Pin_RedLED_Write
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
void Pin_RedLED_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Pin_RedLED_DR & (uint8)(~Pin_RedLED_MASK));
    drVal = (drVal | ((uint8)(value << Pin_RedLED_SHIFT) & Pin_RedLED_MASK));
    Pin_RedLED_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Pin_RedLED_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void Pin_RedLED_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Pin_RedLED__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Pin_RedLED_Read
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
*  Macro Pin_RedLED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin_RedLED_Read(void) 
{
    return (uint8)((Pin_RedLED_PS & Pin_RedLED_MASK) >> Pin_RedLED_SHIFT);
}


/*******************************************************************************
* Function Name: Pin_RedLED_ReadDataReg
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
uint8 Pin_RedLED_ReadDataReg(void) 
{
    return (uint8)((Pin_RedLED_DR & Pin_RedLED_MASK) >> Pin_RedLED_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin_RedLED_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin_RedLED_ClearInterrupt
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
    uint8 Pin_RedLED_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Pin_RedLED_INTSTAT & Pin_RedLED_MASK);
		Pin_RedLED_INTSTAT = maskedStatus;
        return maskedStatus >> Pin_RedLED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
