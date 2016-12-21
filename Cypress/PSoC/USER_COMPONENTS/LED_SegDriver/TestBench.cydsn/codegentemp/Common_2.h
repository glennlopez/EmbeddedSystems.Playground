/*******************************************************************************
* File Name: Common_2.h  
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

#if !defined(CY_PINS_Common_2_H) /* Pins Common_2_H */
#define CY_PINS_Common_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Common_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Common_2_Write(uint8 value) ;
void    Common_2_SetDriveMode(uint8 mode) ;
uint8   Common_2_ReadDataReg(void) ;
uint8   Common_2_Read(void) ;
uint8   Common_2_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Common_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Common_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Common_2_DM_RES_UP          PIN_DM_RES_UP
#define Common_2_DM_RES_DWN         PIN_DM_RES_DWN
#define Common_2_DM_OD_LO           PIN_DM_OD_LO
#define Common_2_DM_OD_HI           PIN_DM_OD_HI
#define Common_2_DM_STRONG          PIN_DM_STRONG
#define Common_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Common_2_MASK               Common_2__MASK
#define Common_2_SHIFT              Common_2__SHIFT
#define Common_2_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Common_2_PS                     (* (reg8 *) Common_2__PS)
/* Data Register */
#define Common_2_DR                     (* (reg8 *) Common_2__DR)
/* Port Number */
#define Common_2_PRT_NUM                (* (reg8 *) Common_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Common_2_AG                     (* (reg8 *) Common_2__AG)                       
/* Analog MUX bux enable */
#define Common_2_AMUX                   (* (reg8 *) Common_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Common_2_BIE                    (* (reg8 *) Common_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Common_2_BIT_MASK               (* (reg8 *) Common_2__BIT_MASK)
/* Bypass Enable */
#define Common_2_BYP                    (* (reg8 *) Common_2__BYP)
/* Port wide control signals */                                                   
#define Common_2_CTL                    (* (reg8 *) Common_2__CTL)
/* Drive Modes */
#define Common_2_DM0                    (* (reg8 *) Common_2__DM0) 
#define Common_2_DM1                    (* (reg8 *) Common_2__DM1)
#define Common_2_DM2                    (* (reg8 *) Common_2__DM2) 
/* Input Buffer Disable Override */
#define Common_2_INP_DIS                (* (reg8 *) Common_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Common_2_LCD_COM_SEG            (* (reg8 *) Common_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Common_2_LCD_EN                 (* (reg8 *) Common_2__LCD_EN)
/* Slew Rate Control */
#define Common_2_SLW                    (* (reg8 *) Common_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Common_2_PRTDSI__CAPS_SEL       (* (reg8 *) Common_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Common_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Common_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Common_2_PRTDSI__OE_SEL0        (* (reg8 *) Common_2__PRTDSI__OE_SEL0) 
#define Common_2_PRTDSI__OE_SEL1        (* (reg8 *) Common_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Common_2_PRTDSI__OUT_SEL0       (* (reg8 *) Common_2__PRTDSI__OUT_SEL0) 
#define Common_2_PRTDSI__OUT_SEL1       (* (reg8 *) Common_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Common_2_PRTDSI__SYNC_OUT       (* (reg8 *) Common_2__PRTDSI__SYNC_OUT) 


#if defined(Common_2__INTSTAT)  /* Interrupt Registers */

    #define Common_2_INTSTAT                (* (reg8 *) Common_2__INTSTAT)
    #define Common_2_SNAP                   (* (reg8 *) Common_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Common_2_H */


/* [] END OF FILE */
