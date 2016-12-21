/*******************************************************************************
* File Name: Common_0.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Common_0_H) /* Pins Common_0_H */
#define CY_PINS_Common_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Common_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Common_0_Write(uint8 value) ;
void    Common_0_SetDriveMode(uint8 mode) ;
uint8   Common_0_ReadDataReg(void) ;
uint8   Common_0_Read(void) ;
uint8   Common_0_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Common_0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Common_0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Common_0_DM_RES_UP          PIN_DM_RES_UP
#define Common_0_DM_RES_DWN         PIN_DM_RES_DWN
#define Common_0_DM_OD_LO           PIN_DM_OD_LO
#define Common_0_DM_OD_HI           PIN_DM_OD_HI
#define Common_0_DM_STRONG          PIN_DM_STRONG
#define Common_0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Common_0_MASK               Common_0__MASK
#define Common_0_SHIFT              Common_0__SHIFT
#define Common_0_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Common_0_PS                     (* (reg8 *) Common_0__PS)
/* Data Register */
#define Common_0_DR                     (* (reg8 *) Common_0__DR)
/* Port Number */
#define Common_0_PRT_NUM                (* (reg8 *) Common_0__PRT) 
/* Connect to Analog Globals */                                                  
#define Common_0_AG                     (* (reg8 *) Common_0__AG)                       
/* Analog MUX bux enable */
#define Common_0_AMUX                   (* (reg8 *) Common_0__AMUX) 
/* Bidirectional Enable */                                                        
#define Common_0_BIE                    (* (reg8 *) Common_0__BIE)
/* Bit-mask for Aliased Register Access */
#define Common_0_BIT_MASK               (* (reg8 *) Common_0__BIT_MASK)
/* Bypass Enable */
#define Common_0_BYP                    (* (reg8 *) Common_0__BYP)
/* Port wide control signals */                                                   
#define Common_0_CTL                    (* (reg8 *) Common_0__CTL)
/* Drive Modes */
#define Common_0_DM0                    (* (reg8 *) Common_0__DM0) 
#define Common_0_DM1                    (* (reg8 *) Common_0__DM1)
#define Common_0_DM2                    (* (reg8 *) Common_0__DM2) 
/* Input Buffer Disable Override */
#define Common_0_INP_DIS                (* (reg8 *) Common_0__INP_DIS)
/* LCD Common or Segment Drive */
#define Common_0_LCD_COM_SEG            (* (reg8 *) Common_0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Common_0_LCD_EN                 (* (reg8 *) Common_0__LCD_EN)
/* Slew Rate Control */
#define Common_0_SLW                    (* (reg8 *) Common_0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Common_0_PRTDSI__CAPS_SEL       (* (reg8 *) Common_0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Common_0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Common_0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Common_0_PRTDSI__OE_SEL0        (* (reg8 *) Common_0__PRTDSI__OE_SEL0) 
#define Common_0_PRTDSI__OE_SEL1        (* (reg8 *) Common_0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Common_0_PRTDSI__OUT_SEL0       (* (reg8 *) Common_0__PRTDSI__OUT_SEL0) 
#define Common_0_PRTDSI__OUT_SEL1       (* (reg8 *) Common_0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Common_0_PRTDSI__SYNC_OUT       (* (reg8 *) Common_0__PRTDSI__SYNC_OUT) 


#if defined(Common_0__INTSTAT)  /* Interrupt Registers */

    #define Common_0_INTSTAT                (* (reg8 *) Common_0__INTSTAT)
    #define Common_0_SNAP                   (* (reg8 *) Common_0__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Common_0_H */


/* [] END OF FILE */
