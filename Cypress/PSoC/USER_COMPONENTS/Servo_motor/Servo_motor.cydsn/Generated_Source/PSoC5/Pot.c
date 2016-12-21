/*******************************************************************************
* File Name: Pot.c  
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
#include "Pot.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pot__PORT == 15 && (Pot__MASK & 0xC0))

/*******************************************************************************
* Function Name: Pot_Write
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
void Pot_Write(uint8 value) 
{
    uint8 staticBits = Pot_DR & ~Pot_MASK;
    Pot_DR = staticBits | ((value << Pot_SHIFT) & Pot_MASK);
}


/*******************************************************************************
* Function Name: Pot_SetDriveMode
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
void Pot_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pot_0, mode);
}


/*******************************************************************************
* Function Name: Pot_Read
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
*  Macro Pot_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pot_Read(void) 
{
    return (Pot_PS & Pot_MASK) >> Pot_SHIFT;
}


/*******************************************************************************
* Function Name: Pot_ReadDataReg
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
uint8 Pot_ReadDataReg(void) 
{
    return (Pot_DR & Pot_MASK) >> Pot_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pot_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pot_ClearInterrupt
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
    uint8 Pot_ClearInterrupt(void) 
    {
        return (Pot_INTSTAT & Pot_MASK) >> Pot_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
