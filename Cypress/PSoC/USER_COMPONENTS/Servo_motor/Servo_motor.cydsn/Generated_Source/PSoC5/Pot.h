/*******************************************************************************
* File Name: Pot.h  
* Version 1.70
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

#if !defined(CY_PINS_Pot_H) /* Pins Pot_H */
#define CY_PINS_Pot_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pot_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pot__PORT == 15 && (Pot__MASK & 0xC0))

/***************************************
*        Function Prototypes             
***************************************/    

void    Pot_Write(uint8 value) ;
void    Pot_SetDriveMode(uint8 mode) ;
uint8   Pot_ReadDataReg(void) ;
uint8   Pot_Read(void) ;
uint8   Pot_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pot_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pot_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pot_DM_RES_UP          PIN_DM_RES_UP
#define Pot_DM_RES_DWN         PIN_DM_RES_DWN
#define Pot_DM_OD_LO           PIN_DM_OD_LO
#define Pot_DM_OD_HI           PIN_DM_OD_HI
#define Pot_DM_STRONG          PIN_DM_STRONG
#define Pot_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pot_MASK               Pot__MASK
#define Pot_SHIFT              Pot__SHIFT
#define Pot_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pot_PS                     (* (reg8 *) Pot__PS)
/* Data Register */
#define Pot_DR                     (* (reg8 *) Pot__DR)
/* Port Number */
#define Pot_PRT_NUM                (* (reg8 *) Pot__PRT) 
/* Connect to Analog Globals */                                                  
#define Pot_AG                     (* (reg8 *) Pot__AG)                       
/* Analog MUX bux enable */
#define Pot_AMUX                   (* (reg8 *) Pot__AMUX) 
/* Bidirectional Enable */                                                        
#define Pot_BIE                    (* (reg8 *) Pot__BIE)
/* Bit-mask for Aliased Register Access */
#define Pot_BIT_MASK               (* (reg8 *) Pot__BIT_MASK)
/* Bypass Enable */
#define Pot_BYP                    (* (reg8 *) Pot__BYP)
/* Port wide control signals */                                                   
#define Pot_CTL                    (* (reg8 *) Pot__CTL)
/* Drive Modes */
#define Pot_DM0                    (* (reg8 *) Pot__DM0) 
#define Pot_DM1                    (* (reg8 *) Pot__DM1)
#define Pot_DM2                    (* (reg8 *) Pot__DM2) 
/* Input Buffer Disable Override */
#define Pot_INP_DIS                (* (reg8 *) Pot__INP_DIS)
/* LCD Common or Segment Drive */
#define Pot_LCD_COM_SEG            (* (reg8 *) Pot__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pot_LCD_EN                 (* (reg8 *) Pot__LCD_EN)
/* Slew Rate Control */
#define Pot_SLW                    (* (reg8 *) Pot__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pot_PRTDSI__CAPS_SEL       (* (reg8 *) Pot__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pot_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pot__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pot_PRTDSI__OE_SEL0        (* (reg8 *) Pot__PRTDSI__OE_SEL0) 
#define Pot_PRTDSI__OE_SEL1        (* (reg8 *) Pot__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pot_PRTDSI__OUT_SEL0       (* (reg8 *) Pot__PRTDSI__OUT_SEL0) 
#define Pot_PRTDSI__OUT_SEL1       (* (reg8 *) Pot__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pot_PRTDSI__SYNC_OUT       (* (reg8 *) Pot__PRTDSI__SYNC_OUT) 


#if defined(Pot__INTSTAT)  /* Interrupt Registers */

    #define Pot_INTSTAT                (* (reg8 *) Pot__INTSTAT)
    #define Pot_SNAP                   (* (reg8 *) Pot__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pot_H */

#endif
/* [] END OF FILE */
