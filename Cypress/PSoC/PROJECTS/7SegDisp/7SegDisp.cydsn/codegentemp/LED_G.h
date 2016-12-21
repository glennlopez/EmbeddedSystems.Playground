/*******************************************************************************
* File Name: LED_G.h  
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

#if !defined(CY_PINS_LED_G_H) /* Pins LED_G_H */
#define CY_PINS_LED_G_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_G_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_G_Write(uint8 value) ;
void    LED_G_SetDriveMode(uint8 mode) ;
uint8   LED_G_ReadDataReg(void) ;
uint8   LED_G_Read(void) ;
uint8   LED_G_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_G_DRIVE_MODE_BITS        (3)
#define LED_G_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_G_DRIVE_MODE_BITS))

#define LED_G_DM_ALG_HIZ         (0x00u)
#define LED_G_DM_DIG_HIZ         (0x01u)
#define LED_G_DM_RES_UP          (0x02u)
#define LED_G_DM_RES_DWN         (0x03u)
#define LED_G_DM_OD_LO           (0x04u)
#define LED_G_DM_OD_HI           (0x05u)
#define LED_G_DM_STRONG          (0x06u)
#define LED_G_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_G_MASK               LED_G__MASK
#define LED_G_SHIFT              LED_G__SHIFT
#define LED_G_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_G_PS                     (* (reg32 *) LED_G__PS)
/* Port Configuration */
#define LED_G_PC                     (* (reg32 *) LED_G__PC)
/* Data Register */
#define LED_G_DR                     (* (reg32 *) LED_G__DR)
/* Input Buffer Disable Override */
#define LED_G_INP_DIS                (* (reg32 *) LED_G__PC2)


#if defined(LED_G__INTSTAT)  /* Interrupt Registers */

    #define LED_G_INTSTAT                (* (reg32 *) LED_G__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_G_DRIVE_MODE_SHIFT       (0x00u)
#define LED_G_DRIVE_MODE_MASK        (0x07u << LED_G_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_G_H */


/* [] END OF FILE */
