/*******************************************************************************
* File Name: Cm0Start.c
* Version 3.40
*
*  Description:
*  Startup code for the ARM CM0.
*
********************************************************************************
* Copyright 2010-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cydevice_trm.h"
#include "cytypes.h"
#include "cyfitter_cfg.h"
#include "CyLib.h"
#include "cyfitter.h"

#define NUM_VECTORS                 (CY_INT_IRQ_BASE + CY_NUM_INTERRUPTS)
#define CPUSS_CONFIG                ((reg32 *) CYREG_CPUSS_CONFIG)
#define NUM_ROM_VECTORS             4u

#if defined(__ARMCC_VERSION)
    #define INITIAL_STACK_POINTER (cyisraddress)(uint32)&Image$$ARM_LIB_STACK$$ZI$$Limit
#elif defined (__GNUC__)
    #define INITIAL_STACK_POINTER __cs3_stack
#endif  /* (__ARMCC_VERSION) */

/* Extern functions */
extern void CyBtldr_CheckLaunch(void);

/* Function prototypes */
void initialize_psoc(void);

/* Global variables */
CY_NOINIT static uint32 cySysNoInitDataValid;

#if (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_STANDARD)

    /*******************************************************************************
    This variable is used by Bootloader/Bootloadable components to schedule
    what application will be started after software reset.
    *******************************************************************************/
    #if (__ARMCC_VERSION)
        volatile uint32 __attribute__ ((section(".bootloaderruntype"), zero_init))  cyBtldrRunType;
    #else   /* (__GNUC__) */
        volatile uint32 __attribute__ ((section(".bootloaderruntype")))             cyBtldrRunType;
    #endif  /* (__ARMCC_VERSION) */

#endif  /* (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_STANDARD) */

/*******************************************************************************
* Function Name: IntDefaultHandler
********************************************************************************
*
* Summary:
*  This function is called for all interrupts, other than reset, that get called
*  before the system is setup.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*   Any value other than zero is acceptable.
*
*******************************************************************************/
__attribute__ ((noreturn))
CY_ISR(IntDefaultHandler)
{
    /***************************************************************************
    * We should never get here. If we do, a serious problem occured, so go into
    * an infinite loop.
    ***************************************************************************/
    while(1)
    {

    }
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
* Function Name: Reset
********************************************************************************
*
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
    EXTERN |Image$$ARM_LIB_STACK$$ZI$$Limit|
    EXTERN __main
    EXTERN CyBtldr_CheckLaunch
    LDR R3, =|Image$$ARM_LIB_STACK$$ZI$$Limit|
    MOV SP, R3
#if (CYDEV_BOOTLOADER_ENABLE)
    BL  CyBtldr_CheckLaunch
#endif /* CYDEV_BOOTLOADER_ENABLE */
    LDR R0, =__main
    BX R0

    ALIGN
}


/*******************************************************************************
* Function Name: $Sub$$main
********************************************************************************
*
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
__attribute__ ((noreturn))
void $Sub$$main(void)
{
    initialize_psoc();

    /* Call original main */
    $Super$$main();

    /* If main returns it is undefined what we should do. */
    while (1);
}

#elif defined(__GNUC__)

extern void __cs3_stack(void);
extern void __cs3_start_c(void);


/*******************************************************************************
* Function Name: Reset
********************************************************************************
*
* Summary:
*  This function handles the reset interrupt for the GCC toolchain.  This is
*  the first bit of code that is executed at startup.
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
          "    MOV sp, %0\n"
#if (CYDEV_BOOTLOADER_ENABLE)
          "    BL  CyBtldr_CheckLaunch\n"
#endif /* CYDEV_BOOTLOADER_ENABLE */
          : : "r" (__cs3_stack));
    __asm volatile(
          "    BX   %0\n"
          : : "r" (__cs3_start_c));
}

#endif /* __GNUC__ */


/*******************************************************************************
* Ram Interrupt Vector table storage area. Must be placed at 0x20000000.
*******************************************************************************/

__attribute__ ((section(".ramvectors")))
cyisraddress CyRamVectors[NUM_VECTORS];


/*******************************************************************************
* Rom Interrupt Vector table storage area. Must be 256-byte aligned.
*******************************************************************************/

#if defined(__ARMCC_VERSION)
    #pragma diag_suppress 1296
#endif  /* defined(__ARMCC_VERSION) */
__attribute__ ((section(".romvectors")))
const cyisraddress RomVectors[NUM_ROM_VECTORS] =
{
    #if defined(__ARMCC_VERSION)
        INITIAL_STACK_POINTER,           /* The initial stack pointer  0 */
    #elif defined (__GNUC__)
        &INITIAL_STACK_POINTER,          /* The initial stack pointer  0 */
    #endif  /* (__ARMCC_VERSION) */
    (cyisraddress)&Reset,            /* The reset handler          1 */
    &IntDefaultHandler,              /* The NMI handler            2 */
    &IntDefaultHandler,              /* The hard fault handler     3 */
};


/*******************************************************************************
* Function Name: initialize_psoc
********************************************************************************
*
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
#if(defined(__GNUC__) && !defined(__ARMCC_VERSION))
__attribute__ ((constructor(101)))
#endif  /* (defined(__GNUC__) && !defined(__ARMCC_VERSION)) */
void initialize_psoc(void)
{
    uint32 indexInit;

    /* Set Ram interrupt vectors to default functions. */
    for(indexInit = 0u; indexInit < NUM_VECTORS; indexInit++)
    {
        CyRamVectors[indexInit] = (indexInit < NUM_ROM_VECTORS) ? RomVectors[indexInit] : &IntDefaultHandler;
    }

    /* Initialize the configuration registers. */
    cyfitter_cfg();

    /* Actually, no need to clean this variable, just to make compiler happy. */
    cySysNoInitDataValid = 0u;

    #if (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_STANDARD)

        /* Need to make sure that this variable will not be optimized out */
        if (0u == cyBtldrRunType)
        {
            cyBtldrRunType = 0u;
        }

    #endif  /* (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_STANDARD) */

    /* Point Vector Table at the RAM vector table. */
    #if(CYDEV_CONFIG_READ_ACCELERATOR)
        *CPUSS_CONFIG = 1u;
    #else
        *CPUSS_CONFIG = 3u;
    #endif  /* (CYDEV_CONFIG_READ_ACCELERATOR) */
}


/* [] END OF FILE */
