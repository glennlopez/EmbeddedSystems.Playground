/*******************************************************************************
* File Name: Segment_0.h  
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

#if !defined(CY_PINS_Segment_0_H) /* Pins Segment_0_H */
#define CY_PINS_Segment_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Segment_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Segment_0_Write(uint8 value) ;
void    Segment_0_SetDriveMode(uint8 mode) ;
uint8   Segment_0_ReadDataReg(void) ;
uint8   Segment_0_Read(void) ;
uint8   Segment_0_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Segment_0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Segment_0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Segment_0_DM_RES_UP          PIN_DM_RES_UP
#define Segment_0_DM_RES_DWN         PIN_DM_RES_DWN
#define Segment_0_DM_OD_LO           PIN_DM_OD_LO
#define Segment_0_DM_OD_HI           PIN_DM_OD_HI
#define Segment_0_DM_STRONG          PIN_DM_STRONG
#define Segment_0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Segment_0_MASK               Segment_0__MASK
#define Segment_0_SHIFT              Segment_0__SHIFT
#define Segment_0_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Segment_0_PS                     (* (reg8 *) Segment_0__PS)
/* Data Register */
#define Segment_0_DR                     (* (reg8 *) Segment_0__DR)
/* Port Number */
#define Segment_0_PRT_NUM                (* (reg8 *) Segment_0__PRT) 
/* Connect to Analog Globals */                                                  
#define Segment_0_AG                     (* (reg8 *) Segment_0__AG)                       
/* Analog MUX bux enable */
#define Segment_0_AMUX                   (* (reg8 *) Segment_0__AMUX) 
/* Bidirectional Enable */                                                        
#define Segment_0_BIE                    (* (reg8 *) Segment_0__BIE)
/* Bit-mask for Aliased Register Access */
#define Segment_0_BIT_MASK               (* (reg8 *) Segment_0__BIT_MASK)
/* Bypass Enable */
#define Segment_0_BYP                    (* (reg8 *) Segment_0__BYP)
/* Port wide control signals */                                                   
#define Segment_0_CTL                    (* (reg8 *) Segment_0__CTL)
/* Drive Modes */
#define Segment_0_DM0                    (* (reg8 *) Segment_0__DM0) 
#define Segment_0_DM1                    (* (reg8 *) Segment_0__DM1)
#define Segment_0_DM2                    (* (reg8 *) Segment_0__DM2) 
/* Input Buffer Disable Override */
#define Segment_0_INP_DIS                (* (reg8 *) Segment_0__INP_DIS)
/* LCD Common or Segment Drive */
#define Segment_0_LCD_COM_SEG            (* (reg8 *) Segment_0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Segment_0_LCD_EN                 (* (reg8 *) Segment_0__LCD_EN)
/* Slew Rate Control */
#define Segment_0_SLW                    (* (reg8 *) Segment_0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Segment_0_PRTDSI__CAPS_SEL       (* (reg8 *) Segment_0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Segment_0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Segment_0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Segment_0_PRTDSI__OE_SEL0        (* (reg8 *) Segment_0__PRTDSI__OE_SEL0) 
#define Segment_0_PRTDSI__OE_SEL1        (* (reg8 *) Segment_0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Segment_0_PRTDSI__OUT_SEL0       (* (reg8 *) Segment_0__PRTDSI__OUT_SEL0) 
#define Segment_0_PRTDSI__OUT_SEL1       (* (reg8 *) Segment_0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Segment_0_PRTDSI__SYNC_OUT       (* (reg8 *) Segment_0__PRTDSI__SYNC_OUT) 


#if defined(Segment_0__INTSTAT)  /* Interrupt Registers */

    #define Segment_0_INTSTAT                (* (reg8 *) Segment_0__INTSTAT)
    #define Segment_0_SNAP                   (* (reg8 *) Segment_0__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Segment_0_H */


/* [] END OF FILE */
