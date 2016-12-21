/*******************************************************************************
* File Name: LED_RAM_1.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CONTROL_REG_LED_RAM_1_H) /* CY_CONTROL_REG_LED_RAM_1_H */
#define CY_CONTROL_REG_LED_RAM_1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*         Function Prototypes 
***************************************/    

void    LED_RAM_1_Write(uint8 control) ;
uint8   LED_RAM_1_Read(void) ;

/***************************************
*            Registers        
***************************************/

/* Control Register */
#define LED_RAM_1_Control         (* (reg8 *) LED_RAM_1_ctrl_reg__CONTROL_REG )
#endif /* End CY_CONTROL_REG_LED_RAM_1_H */

/* [] END OF FILE */
