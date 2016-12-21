/*******************************************************************************
* File Name: LED_6.h  
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

#if !defined(CY_PINS_LED_6_H) /* Pins LED_6_H */
#define CY_PINS_LED_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_6_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_6_Write(uint8 value) ;
void    LED_6_SetDriveMode(uint8 mode) ;
uint8   LED_6_ReadDataReg(void) ;
uint8   LED_6_Read(void) ;
uint8   LED_6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_6_DRIVE_MODE_BITS        (3)
#define LED_6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_6_DRIVE_MODE_BITS))
#define LED_6_DRIVE_MODE_SHIFT       (0x00u)
#define LED_6_DRIVE_MODE_MASK        (0x07u << LED_6_DRIVE_MODE_SHIFT)

#define LED_6_DM_ALG_HIZ         (0x00u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_DIG_HIZ         (0x01u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_RES_UP          (0x02u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_RES_DWN         (0x03u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_OD_LO           (0x04u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_OD_HI           (0x05u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_STRONG          (0x06u << LED_6_DRIVE_MODE_SHIFT)
#define LED_6_DM_RES_UPDWN       (0x07u << LED_6_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_6_MASK               LED_6__MASK
#define LED_6_SHIFT              LED_6__SHIFT
#define LED_6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_6_PS                     (* (reg32 *) LED_6__PS)
/* Port Configuration */
#define LED_6_PC                     (* (reg32 *) LED_6__PC)
/* Data Register */
#define LED_6_DR                     (* (reg32 *) LED_6__DR)
/* Input Buffer Disable Override */
#define LED_6_INP_DIS                (* (reg32 *) LED_6__PC2)


#if defined(LED_6__INTSTAT)  /* Interrupt Registers */

    #define LED_6_INTSTAT                (* (reg32 *) LED_6__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_6_H */


/* [] END OF FILE */
