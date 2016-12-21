/*******************************************************************************
* File Name: LED_5.h  
* Version 2.5
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

#if !defined(CY_PINS_LED_5_H) /* Pins LED_5_H */
#define CY_PINS_LED_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_5_Write(uint8 value) ;
void    LED_5_SetDriveMode(uint8 mode) ;
uint8   LED_5_ReadDataReg(void) ;
uint8   LED_5_Read(void) ;
uint8   LED_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_5_DRIVE_MODE_BITS        (3)
#define LED_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_5_DRIVE_MODE_BITS))
#define LED_5_DRIVE_MODE_SHIFT       (0x00u)
#define LED_5_DRIVE_MODE_MASK        (0x07u << LED_5_DRIVE_MODE_SHIFT)

#define LED_5_DM_ALG_HIZ         (0x00u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_DIG_HIZ         (0x01u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_RES_UP          (0x02u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_RES_DWN         (0x03u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_OD_LO           (0x04u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_OD_HI           (0x05u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_STRONG          (0x06u << LED_5_DRIVE_MODE_SHIFT)
#define LED_5_DM_RES_UPDWN       (0x07u << LED_5_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_5_MASK               LED_5__MASK
#define LED_5_SHIFT              LED_5__SHIFT
#define LED_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_5_PS                     (* (reg32 *) LED_5__PS)
/* Port Configuration */
#define LED_5_PC                     (* (reg32 *) LED_5__PC)
/* Data Register */
#define LED_5_DR                     (* (reg32 *) LED_5__DR)
/* Input Buffer Disable Override */
#define LED_5_INP_DIS                (* (reg32 *) LED_5__PC2)


#if defined(LED_5__INTSTAT)  /* Interrupt Registers */

    #define LED_5_INTSTAT                (* (reg32 *) LED_5__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_5_H */


/* [] END OF FILE */
