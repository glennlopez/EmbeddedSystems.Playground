/*******************************************************************************
* File Name: LEDG.c  
* Version 2.5
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
#include "LEDG.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        LEDG_PC =   (LEDG_PC & \
                                (uint32)(~(uint32)(LEDG_DRIVE_MODE_IND_MASK << (LEDG_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (LEDG_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: LEDG_Write
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
void LEDG_Write(uint8 value) 
{
    uint8 drVal = (uint8)(LEDG_DR & (uint8)(~LEDG_MASK));
    drVal = (drVal | ((uint8)(value << LEDG_SHIFT) & LEDG_MASK));
    LEDG_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: LEDG_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDG_DM_STRONG     Strong Drive 
*  LEDG_DM_OD_HI      Open Drain, Drives High 
*  LEDG_DM_OD_LO      Open Drain, Drives Low 
*  LEDG_DM_RES_UP     Resistive Pull Up 
*  LEDG_DM_RES_DWN    Resistive Pull Down 
*  LEDG_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDG_DM_DIG_HIZ    High Impedance Digital 
*  LEDG_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDG_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(LEDG__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: LEDG_Read
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
*  Macro LEDG_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDG_Read(void) 
{
    return (uint8)((LEDG_PS & LEDG_MASK) >> LEDG_SHIFT);
}


/*******************************************************************************
* Function Name: LEDG_ReadDataReg
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
uint8 LEDG_ReadDataReg(void) 
{
    return (uint8)((LEDG_DR & LEDG_MASK) >> LEDG_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDG_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDG_ClearInterrupt
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
    uint8 LEDG_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(LEDG_INTSTAT & LEDG_MASK);
		LEDG_INTSTAT = maskedStatus;
        return maskedStatus >> LEDG_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
