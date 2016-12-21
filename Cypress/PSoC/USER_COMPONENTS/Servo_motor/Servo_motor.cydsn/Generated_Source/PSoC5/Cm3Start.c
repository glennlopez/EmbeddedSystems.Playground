/*******************************************************************************
* File Name: Cm3Start.c
* Version 3.20
*
*  Description:
*  Startup code for the ARM CM3.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cydevice_trm.h"
#include "cytypes.h"
#include "cyfitter_cfg.h"
#include "CyLib.h"
#include "CyDmac.h"
#include "cyfitter.h"


#define NUM_INTERRUPTS              32
#define NUM_VECTORS                 (CYINT_IRQ_BASE+NUM_INTERRUPTS)
#define NVIC_APINT                  ((reg32 *) CYREG_NVIC_APPLN_INTR)
#define NVIC_CFG_CTRL               ((reg32 *) CYREG_NVIC_CFG_CONTROL)
#define NVIC_APINT_PRIGROUP_3_5     0x00000400  /* Priority group 3.5 split */
#define NVIC_APINT_VECTKEY          0x05FA0000  /* This key is required in order to write the NVIC_APINT register */
#define NVIC_CFG_STACKALIGN         0x00000200  /* This specifies that the exception stack must be 8 byte aligned */

/* Extern functions */
extern void CyBtldr_CheckLaunch(void);

/* Function prototypes */
void initialize_psoc(void);


/*******************************************************************************
* Default Ram Interrupt Vector table storage area. Must be 256-byte aligned.
*******************************************************************************/
__attribute__ ((section(".ramvectors")))
#if defined(__ARMCC_VERSION)
__align(256)
#elif defined (__GNUC__)
__attribute__ ((aligned(256)))
#endif
cyisraddress CyRamVectors[NUM_VECTORS];


/*******************************************************************************
* Function Name: IntDefaultHandler
********************************************************************************
* Summary:
*  This function is called for all interrupts, other than reset, that get
*  called before the system is setup.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  Any value other than zero is acceptable.
*
*******************************************************************************/
CY_ISR(IntDefaultHandler)
{
    /***************************************************************************
    * We should never get here. If we do, a serious problem occured, so go into
    * an infinite loop.
    ***************************************************************************/
    while(1);
}

#if defined(__ARMCC_VERSION)

/* Local function for the device reset. */
extern void Reset(void);

/* Application entry point. */
extern void $Super$$main(void);

/* Linker-generated Stack Base addresses, Two Region and One Region */
extern unsigned long Image$$ARM_LIB_STACK$$ZI$$Limit;

/* RealView C Library initialization. */
extern int __main(void);

/*******************************************************************************
*
* Default Rom Interrupt Vector table.
*
*******************************************************************************/
#pragma diag_suppress 1296
__attribute__ ((section(".romvectors")))
const cyisraddress RomVectors[NUM_VECTORS] =
{
    (cyisraddress)(uint32)&Image$$ARM_LIB_STACK$$ZI$$Limit,             /* The initial stack pointer  0 */
    (cyisraddress)Reset,                                                /* The reset handler          1 */
    IntDefaultHandler,                                                  /* The NMI handler            2 */
    IntDefaultHandler,                                                  /* The hard fault handler     3 */
    IntDefaultHandler,                                                  /* The MPU fault handler      4 */
    IntDefaultHandler,                                                  /* The bus fault handler      5 */
    IntDefaultHandler,                                                  /* The usage fault handler    6 */
    IntDefaultHandler,                                                  /* Reserved                   7 */
    IntDefaultHandler,                                                  /* Reserved                   8 */
    IntDefaultHandler,                                                  /* Reserved                   9 */
    IntDefaultHandler,                                                  /* Reserved                  10 */
    IntDefaultHandler,                                                  /* SVCall handler            11 */
    IntDefaultHandler,                                                  /* Debug monitor handler     12 */
    IntDefaultHandler,                                                  /* Reserved                  13 */
    IntDefaultHandler,                                                  /* The PendSV handler        14 */
    IntDefaultHandler,                                                  /* The SysTick handler       15 */
    IntDefaultHandler,                                                  /* External Interrupt(0)     16 */
    IntDefaultHandler,                                                  /* External Interrupt(1)     17 */
    IntDefaultHandler,                                                  /* External Interrupt(2)     18 */
    IntDefaultHandler,                                                  /* External Interrupt(3)     19 */
    IntDefaultHandler,                                                  /* External Interrupt(4)     20 */
    IntDefaultHandler,                                                  /* External Interrupt(5)     21 */
    IntDefaultHandler,                                                  /* External Interrupt(6)     22 */
    IntDefaultHandler,                                                  /* External Interrupt(7)     23 */
    IntDefaultHandler,                                                  /* External Interrupt(8)     24 */
    IntDefaultHandler,                                                  /* External Interrupt(9)     25 */
    IntDefaultHandler,                                                  /* External Interrupt(A)     26 */
    IntDefaultHandler,                                                  /* External Interrupt(B)     27 */
    IntDefaultHandler,                                                  /* External Interrupt(C)     28 */
    IntDefaultHandler,                                                  /* External Interrupt(D)     29 */
    IntDefaultHandler,                                                  /* External Interrupt(E)     30 */
    IntDefaultHandler,                                                  /* External Interrupt(F)     31 */
    IntDefaultHandler,                                                  /* External Interrupt(10)    32 */
    IntDefaultHandler,                                                  /* External Interrupt(11)    33 */
    IntDefaultHandler,                                                  /* External Interrupt(12)    34 */
    IntDefaultHandler,                                                  /* External Interrupt(13)    35 */
    IntDefaultHandler,                                                  /* External Interrupt(14)    36 */
    IntDefaultHandler,                                                  /* External Interrupt(15)    37 */
    IntDefaultHandler,                                                  /* External Interrupt(16)    38 */
    IntDefaultHandler,                                                  /* External Interrupt(17)    39 */
    IntDefaultHandler,                                                  /* External Interrupt(18)    40 */
    IntDefaultHandler,                                                  /* External Interrupt(19)    41 */
    IntDefaultHandler,                                                  /* External Interrupt(1A)    42 */
    IntDefaultHandler,                                                  /* External Interrupt(1B)    43 */
    IntDefaultHandler,                                                  /* External Interrupt(1C)    44 */
    IntDefaultHandler,                                                  /* External Interrupt(1D)    45 */
    IntDefaultHandler,                                                  /* External Interrupt(1E)    46 */
    IntDefaultHandler                                                   /* External Interrupt(1F)    47 */
};


/*******************************************************************************
* Function Name: Reset
********************************************************************************
* Summary:
*  This function handles the reset interrupt for the RVDS/MDK toolchains.
*  This is the first bit of code that is executed at startup.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
__asm void Reset(void)
{
    PRESERVE8
    EXTERN __main
    EXTERN CyResetStatus

    #if(CYDEV_BOOTLOADER_ENABLE)
        EXTERN CyBtldr_CheckLaunch
    #endif  /* (CYDEV_BOOTLOADER_ENABLE) */


    #if(CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLE)
        #if(CYDEV_DEBUGGING_ENABLE)
    ldr  r3, =0x400046e8 /* CYDEV_DEBUG_ENABLE_REGISTER */
            ldrb r4, [r3, #0]
            orr  r4, r4, #01
            strb r4, [r3, #0]
debugEnabled
        #endif    /* (CYDEV_DEBUGGING_ENABLE) */

    ldr  r3, =0x400046f8 /* CYREG_RESET_SR0 */
        ldrb r2, [r3, #0]

    #endif  /* (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLE) */

    ldr  r3, =0x400076BC /* CYREG_PHUB_CFGMEM23_CFG1 */
    strb r2, [r3, #0]

    #if(CYDEV_BOOTLOADER_ENABLE)
        bl CyBtldr_CheckLaunch
    #endif /* (CYDEV_BOOTLOADER_ENABLE) */

    /* Let RealView setup the libraries. */
    bl __main

    ALIGN
}


/*******************************************************************************
* Function Name: $Sub$$main
********************************************************************************
* Summary:
*  This function is called imediatly before the users main
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void $Sub$$main(void)
{
    initialize_psoc();

    /* Call original main */
    $Super$$main();

    /* If main returns it is undefined what we should do. */
    while (1);
}

#elif defined(__GNUC__)

extern unsigned long __cs3_interrupt_vector;
extern void __cs3_start_c(void);

#define RomVectors (cyisraddress)(&__cs3_interrupt_vector)


/*******************************************************************************
* Function Name: Reset
********************************************************************************
* Summary:
*  This function handles the reset interrupt for the GCC toolchain.  This is the
*  first bit of code that is executed at startup.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
__attribute__ ((naked))
void Reset(void)
{
    __asm volatile(
#if(CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLE)

  #if(CYDEV_DEBUGGING_ENABLE)
    "    ldr  r3, =%0\n"
    "    ldrb r4, [r3, #0]\n"
    "    orr  r4, r4, #01\n"
    "    strb r4, [r3, #0]\n"
    "debugEnabled:\n"
  #endif    /* (CYDEV_DEBUGGING_ENABLE) */

    "    ldr  r3, =%1\n"
    "    ldrb r2, [r3, #0]\n"
    "    uxtb r2, r2\n"
#endif  /* (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLE) */

    "    ldr  r3, =%2\n"
    "    strb r2, [r3, #0]\n"

#if(CYDEV_BOOTLOADER_ENABLE)
    "    bl CyBtldr_CheckLaunch\n"
#endif /* (CYDEV_BOOTLOADER_ENABLE) */

    /*  Switch to C initialization phase */
    "    bl __cs3_start_c\n" : : "i" (CYDEV_DEBUG_ENABLE_REGISTER), "i" (CYREG_RESET_SR0), "i" (CYREG_PHUB_CFGMEM23_CFG1));
}

#endif /* __GNUC__ */

/*******************************************************************************
* Function Name: initialize_psoc
********************************************************************************
* Summary:
*  This function used to initialize the PSoC chip before calling main.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
#if (defined(__GNUC__) && !defined(__ARMCC_VERSION))
__attribute__ ((constructor(101)))
#endif

void initialize_psoc(void)
{
    unsigned long index;

    /* Set Priority group 5. */

    /* Writes to NVIC_APINT register require the VECTKEY in the upper half */
    *NVIC_APINT = NVIC_APINT_VECTKEY | NVIC_APINT_PRIGROUP_3_5;
    *NVIC_CFG_CTRL |= NVIC_CFG_STACKALIGN;

    /* Set Ram interrupt vectors to default functions. */
    for(index = 0; index < NUM_VECTORS; index++)
    {
        CyRamVectors[index] = RomVectors[index];
    }

    /* Was stored in CFGMEM to avoid being cleared while SRAM gets cleared */
    CyResetStatus = CY_GET_REG8(CYREG_PHUB_CFGMEM23_CFG1);

    /* Point NVIC at the RAM vector table. */
    *CYINT_VECT_TABLE = CyRamVectors;

    /* Initialize the configuration registers. */
    cyfitter_cfg();

    #if(0u != DMA_CHANNELS_USED__MASK0)

        /* Setup DMA - only necessary if the design contains a DMA component. */
        CyDmacConfigure();

    #endif  /* (0u != DMA_CHANNELS_USED__MASK0) */
}


/* [] END OF FILE */
