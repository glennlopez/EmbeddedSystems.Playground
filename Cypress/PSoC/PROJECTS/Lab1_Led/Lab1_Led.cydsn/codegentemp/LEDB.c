/*******************************************************************************
* File Name: LEDB.c  
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
#include "LEDB.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        LEDB_PC =   (LEDB_PC & \
                                (uint32)(~(uint32)(LEDB_DRIVE_MODE_IND_MASK << (LEDB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (LEDB_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: LEDB_Write
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
void LEDB_Write(uint8 value) 
{
    uint8 drVal = (uint8)(LEDB_DR & (uint8)(~LEDB_MASK));
    drVal = (drVal | ((uint8)(value << LEDB_SHIFT) & LEDB_MASK));
    LEDB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: LEDB_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LEDB_DM_STRONG     Strong Drive 
*  LEDB_DM_OD_HI      Open Drain, Drives High 
*  LEDB_DM_OD_LO      Open Drain, Drives Low 
*  LEDB_DM_RES_UP     Resistive Pull Up 
*  LEDB_DM_RES_DWN    Resistive Pull Down 
*  LEDB_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LEDB_DM_DIG_HIZ    High Impedance Digital 
*  LEDB_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LEDB_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(LEDB__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: LEDB_Read
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
*  Macro LEDB_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LEDB_Read(void) 
{
    return (uint8)((LEDB_PS & LEDB_MASK) >> LEDB_SHIFT);
}


/*******************************************************************************
* Function Name: LEDB_ReadDataReg
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
uint8 LEDB_ReadDataReg(void) 
{
    return (uint8)((LEDB_DR & LEDB_MASK) >> LEDB_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LEDB_INTSTAT) 

    /*******************************************************************************
    * Function Name: LEDB_ClearInterrupt
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
    uint8 LEDB_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(LEDB_INTSTAT & LEDB_MASK);
		LEDB_INTSTAT = maskedStatus;
        return maskedStatus >> LEDB_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
