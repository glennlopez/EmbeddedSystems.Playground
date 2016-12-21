/*******************************************************************************
* File Name: LED_1.h  
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

#if !defined(CY_PINS_LED_1_H) /* Pins LED_1_H */
#define CY_PINS_LED_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_1_Write(uint8 value) ;
void    LED_1_SetDriveMode(uint8 mode) ;
uint8   LED_1_ReadDataReg(void) ;
uint8   LED_1_Read(void) ;
uint8   LED_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_1_DRIVE_MODE_BITS        (3)
#define LED_1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_1_DRIVE_MODE_BITS))
#define LED_1_DRIVE_MODE_SHIFT       (0x00u)
#define LED_1_DRIVE_MODE_MASK        (0x07u << LED_1_DRIVE_MODE_SHIFT)

#define LED_1_DM_ALG_HIZ         (0x00u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_DIG_HIZ         (0x01u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_RES_UP          (0x02u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_RES_DWN         (0x03u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_OD_LO           (0x04u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_OD_HI           (0x05u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_STRONG          (0x06u << LED_1_DRIVE_MODE_SHIFT)
#define LED_1_DM_RES_UPDWN       (0x07u << LED_1_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_1_MASK               LED_1__MASK
#define LED_1_SHIFT              LED_1__SHIFT
#define LED_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_1_PS                     (* (reg32 *) LED_1__PS)
/* Port Configuration */
#define LED_1_PC                     (* (reg32 *) LED_1__PC)
/* Data Register */
#define LED_1_DR                     (* (reg32 *) LED_1__DR)
/* Input Buffer Disable Override */
#define LED_1_INP_DIS                (* (reg32 *) LED_1__PC2)


#if defined(LED_1__INTSTAT)  /* Interrupt Registers */

    #define LED_1_INTSTAT                (* (reg32 *) LED_1__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_1_H */


/* [] END OF FILE */
