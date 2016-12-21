/*******************************************************************************
* File Name: AnalogIn.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AnalogIn_H) /* Pins AnalogIn_H */
#define CY_PINS_AnalogIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AnalogIn_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    AnalogIn_Write(uint8 value) ;
void    AnalogIn_SetDriveMode(uint8 mode) ;
uint8   AnalogIn_ReadDataReg(void) ;
uint8   AnalogIn_Read(void) ;
uint8   AnalogIn_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define AnalogIn_DRIVE_MODE_BITS        (3)
#define AnalogIn_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AnalogIn_DRIVE_MODE_BITS))

#define AnalogIn_DM_ALG_HIZ         (0x00u)
#define AnalogIn_DM_DIG_HIZ         (0x01u)
#define AnalogIn_DM_RES_UP          (0x02u)
#define AnalogIn_DM_RES_DWN         (0x03u)
#define AnalogIn_DM_OD_LO           (0x04u)
#define AnalogIn_DM_OD_HI           (0x05u)
#define AnalogIn_DM_STRONG          (0x06u)
#define AnalogIn_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define AnalogIn_MASK               AnalogIn__MASK
#define AnalogIn_SHIFT              AnalogIn__SHIFT
#define AnalogIn_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AnalogIn_PS                     (* (reg32 *) AnalogIn__PS)
/* Port Configuration */
#define AnalogIn_PC                     (* (reg32 *) AnalogIn__PC)
/* Data Register */
#define AnalogIn_DR                     (* (reg32 *) AnalogIn__DR)
/* Input Buffer Disable Override */
#define AnalogIn_INP_DIS                (* (reg32 *) AnalogIn__PC2)


#if defined(AnalogIn__INTSTAT)  /* Interrupt Registers */

    #define AnalogIn_INTSTAT                (* (reg32 *) AnalogIn__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define AnalogIn_DRIVE_MODE_SHIFT       (0x00u)
#define AnalogIn_DRIVE_MODE_MASK        (0x07u << AnalogIn_DRIVE_MODE_SHIFT)


#endif /* End Pins AnalogIn_H */


/* [] END OF FILE */
