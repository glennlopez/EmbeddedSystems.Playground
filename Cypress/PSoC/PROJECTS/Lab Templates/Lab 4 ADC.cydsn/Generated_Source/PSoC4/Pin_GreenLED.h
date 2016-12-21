/*******************************************************************************
* File Name: Pin_GreenLED.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin_GreenLED_H) /* Pins Pin_GreenLED_H */
#define CY_PINS_Pin_GreenLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_GreenLED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_GreenLED_Write(uint8 value) ;
void    Pin_GreenLED_SetDriveMode(uint8 mode) ;
uint8   Pin_GreenLED_ReadDataReg(void) ;
uint8   Pin_GreenLED_Read(void) ;
uint8   Pin_GreenLED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_GreenLED_DRIVE_MODE_BITS        (3)
#define Pin_GreenLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_GreenLED_DRIVE_MODE_BITS))
#define Pin_GreenLED_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_GreenLED_DRIVE_MODE_MASK        (0x07u << Pin_GreenLED_DRIVE_MODE_SHIFT)

#define Pin_GreenLED_DM_ALG_HIZ         (0x00u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_DIG_HIZ         (0x01u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_RES_UP          (0x02u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_RES_DWN         (0x03u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_OD_LO           (0x04u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_OD_HI           (0x05u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_STRONG          (0x06u << Pin_GreenLED_DRIVE_MODE_SHIFT)
#define Pin_GreenLED_DM_RES_UPDWN       (0x07u << Pin_GreenLED_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin_GreenLED_MASK               Pin_GreenLED__MASK
#define Pin_GreenLED_SHIFT              Pin_GreenLED__SHIFT
#define Pin_GreenLED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_GreenLED_PS                     (* (reg32 *) Pin_GreenLED__PS)
/* Port Configuration */
#define Pin_GreenLED_PC                     (* (reg32 *) Pin_GreenLED__PC)
/* Data Register */
#define Pin_GreenLED_DR                     (* (reg32 *) Pin_GreenLED__DR)
/* Input Buffer Disable Override */
#define Pin_GreenLED_INP_DIS                (* (reg32 *) Pin_GreenLED__PC2)


#if defined(Pin_GreenLED__INTSTAT)  /* Interrupt Registers */

    #define Pin_GreenLED_INTSTAT                (* (reg32 *) Pin_GreenLED__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_GreenLED_H */


/* [] END OF FILE */
