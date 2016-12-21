/*******************************************************************************
* File Name: Pin_RedLED.h  
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

#if !defined(CY_PINS_Pin_RedLED_H) /* Pins Pin_RedLED_H */
#define CY_PINS_Pin_RedLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_RedLED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_RedLED_Write(uint8 value) ;
void    Pin_RedLED_SetDriveMode(uint8 mode) ;
uint8   Pin_RedLED_ReadDataReg(void) ;
uint8   Pin_RedLED_Read(void) ;
uint8   Pin_RedLED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_RedLED_DRIVE_MODE_BITS        (3)
#define Pin_RedLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_RedLED_DRIVE_MODE_BITS))
#define Pin_RedLED_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_RedLED_DRIVE_MODE_MASK        (0x07u << Pin_RedLED_DRIVE_MODE_SHIFT)

#define Pin_RedLED_DM_ALG_HIZ         (0x00u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_DIG_HIZ         (0x01u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_RES_UP          (0x02u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_RES_DWN         (0x03u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_OD_LO           (0x04u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_OD_HI           (0x05u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_STRONG          (0x06u << Pin_RedLED_DRIVE_MODE_SHIFT)
#define Pin_RedLED_DM_RES_UPDWN       (0x07u << Pin_RedLED_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Pin_RedLED_MASK               Pin_RedLED__MASK
#define Pin_RedLED_SHIFT              Pin_RedLED__SHIFT
#define Pin_RedLED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_RedLED_PS                     (* (reg32 *) Pin_RedLED__PS)
/* Port Configuration */
#define Pin_RedLED_PC                     (* (reg32 *) Pin_RedLED__PC)
/* Data Register */
#define Pin_RedLED_DR                     (* (reg32 *) Pin_RedLED__DR)
/* Input Buffer Disable Override */
#define Pin_RedLED_INP_DIS                (* (reg32 *) Pin_RedLED__PC2)


#if defined(Pin_RedLED__INTSTAT)  /* Interrupt Registers */

    #define Pin_RedLED_INTSTAT                (* (reg32 *) Pin_RedLED__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_RedLED_H */


/* [] END OF FILE */
