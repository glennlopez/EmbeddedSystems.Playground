/*******************************************************************************
* FILENAME: cytypes.h
* Version 2.40
*
*  Description:
*  CyTypes provides register access macros and approved types for use in 
*  firmware.
* 
*  Note:
*  Due to endiannesses of the hardware and some compilers, the register
*  access macros for big endian compilers use some library calls to arrange 
*  data the correct way.
*   
*  Register Access macros and functions perform their operations on an 
*  input of type pointer to void.  The arguments passed to it should be 
*  pointers to the type associated with the register size. 
*  (i.e. a "uint8 *" shouldn't be passed to obtain a 16-bit register value)
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CYTYPES_H)
#define CYTYPES_H

#if defined(__C51__)
#include <intrins.h>
#endif

#if defined(__GNUC__) || defined(__ARMCC_VERSION) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
/* Include for the ARM compilers (GCC and RealView) */
#include <stdint.h>
#endif

#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* ARCHITECTURES */
/* Device is PSoC 3 */
#define CY_PSOC3 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)

/* Device is PSoC 4 */
#define CY_PSOC4 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4)

/* Device is PSoC 5 */
#define CY_PSOC5 (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5)

/* SILICON REVISIONS */
/* Device is PSoC 3 and the revision is ES2 or earlier */
#define CY_PSOC3_ES2 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* Device is PSoC 5 and the revision is ES1 or earlier */
#define CY_PSOC5_ES1 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && \
(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* Device is PSoC 4 and the revision is ES0 or later */
#define CY_PSOC4_ES0 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_4A) && \
(CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_4A_ES0))

/* Device is PSoC 3 and the revision is ES3 or later */
#define CY_PSOC3_ES3 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
(CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* Device is PSoC 5 and the revision is ES2 or later */
#define CY_PSOC5_ES2 ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A) && \
(CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


typedef char           char8;

/* Acceptable types from MISRA-C specifying signedness and size.*/
typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;

typedef signed char             int8;
typedef signed short            int16;
typedef signed long             int32;

/* Get 8 bits of a 16 bit value. */
#define LO8(x)                  ((uint8) (x))
#define HI8(x)                  ((uint8) ((x) >> 8))

/* Get 16 bits of a 32 bit value. */
#define LO16(x)                 ((uint16) (x))
#define HI16(x)                 ((uint16) ((uint32)(x) >> 16))

/* Swap the byte ordering of a 32 bit value */
#define CYSWAP_ENDIAN32(x) ((uint32)(((x) >> 24) | (((x) & 0x00FF0000u) >> 8) | (((x) & 0x0000FF00u) << 8) | ((x) << 24)))
/* Swap the byte ordering of a 16 bit value */
#define CYSWAP_ENDIAN16(x) ((uint16)(((x) << 8) | ((x) >> 8)))

/*
*   Defines the standard return values used PSoC content. A function is
*   not limited to these return values but can use them when returning standard
*   error values.
*
*   Return values can be overloaded if documented in the function header.
*
*   On the 8051 a function can use a larger return type but still use the defined
*   return codes.
*
*   0 is successful, all other values indicate some form of failure.
*
*   1 - 0x7F, Standard defined values.
*   0x80 - ... , User or content defined values.
*/

/* Completed successfully. */
#define CYRET_SUCCESS                   0x00u

/* Failed, the exact cause is unknown. */
#define CYRET_UNKNOWN                   ((cystatus) -1)

/* One or more parameters to the function were invalid. */
#define CYRET_BAD_PARAM                 0x01u

/* One or more parameters to the function were invalid. */
#define CYRET_INVALID_OBJECT            0x02u

/* There was a memory problem. */
#define CYRET_MEMORY                    0x03u

/* The object was locked, already in use. */
#define CYRET_LOCKED                    0x04u

/* No more objects are available. */
#define CYRET_EMPTY                     0x05u

/* The CRC, Checksum, FEC or packet format was bad. */
#define CYRET_BAD_DATA                  0x06u

/* The operation was started correctly, but may not be completed. */
#define CYRET_STARTED                   0x07u

/* The operation has finished. */
#define CYRET_FINISHED                  0x08u

/* The operation was canceled. */
#define CYRET_CANCELED                  0x09u

/* The operation timed out. */
#define CYRET_TIMEOUT                   0x10u

/* The operation was not setup or in a proper state. */
#define CYRET_INVALID_STATE             0x11u

/* Include for the KEIL C51 compiler
*  KEIL for the 8051 is a Big Endian compiler This causes problems as the
*  on chip registers are little endian.  Byte swapping for two and four byte
*  registers is implemented in the functions below.  This will require
*  conditional compilation of function prototypes in code.
*/
#if defined(__C51__)

/* To allow code to be 8051-ARM agnostic. */
#define CYBDATA bdata
#define CYBIT bit
#define CYCODE code
#define CYCOMPACT compact
#define CYDATA data
#define CYFAR far
#define CYIDATA idata
#define CYLARGE large
#define CYPDATA pdata
#define CYREENTRANT reentrant
#define CYSMALL small
#define CYXDATA xdata
#define XDATA xdata

/* Interrupt service routine declarations */
#define CY_ISR(FuncName)  void FuncName (void) interrupt 0
#define CY_ISR_PROTO(FuncName) void FuncName (void)
typedef void (CYCODE * cyisraddress)(void);

/* 8051 naturally returns an 8 bit value. */
typedef unsigned char cystatus;

/* Prototypes for absolute memory address functions (cymem.a51) with built-in endian conversion.
 * These functions should be called through the CY_GET_XTND_REGxx and CY_SET_XTND_REGxx macros.
 */
extern uint8 cyread8(const void far *addr);
extern void cywrite8(void far *addr, uint8 value);
extern uint16 cyread16(const void far *addr);
extern uint16 cyread16_nodpx(const void far *addr);
extern void cywrite16(void far *addr, uint16 value);
extern void cywrite16_nodpx(void far *addr, uint16 value);
extern uint32 cyread24(const void far *addr);
extern uint32 cyread24_nodpx(const void far *addr);
extern void cywrite24(void far *addr, uint32 value);
extern void cywrite24_nodpx(void far *addr, uint32 value);
extern uint32 cyread32(const void far *addr);
extern uint32 cyread32_nodpx(const void far *addr);
extern void cywrite32(void far *addr, uint32 value);
extern void cywrite32_nodpx(void far *addr, uint32 value);
/* Memory access routines from cymem.a51 for the generated device configuration
 * code. These functions may be subject to change in future revisions of the
 * cy_boot component and they are not available for all devices. Most code
 * should use memset or memcpy instead.
 */
void cymemzero(void far *addr, unsigned short size);
void cyconfigcpy(unsigned short size, const void far *src, void far *dest) large;
void cyconfigcpycode(unsigned short size, const void code *src, void far *dest);
#define CYCONFIGCPY_DECLARED 1

/*
 * KEIL for the 8051 is a big endian compiler This causes problems as the
 * on chip registers are little endian.  Byte swapping for two and four byte
 * registers is implemented in the functions below.  This will require
 * conditional compilation of function prototypes in code.
 */

/* Access macros for 8, 16, 24 and 32-bit registers, IN THE FIRST 64K OF XDATA */
#define CY_GET_REG8(addr)           (*((volatile uint8 xdata *)(addr)))
#define CY_SET_REG8(addr, value)    (*((volatile uint8 xdata *)(addr))  = (uint8)(value))

#define CY_GET_REG16(addr)          cyread16_nodpx((void far *)(uint8 xdata *)(addr))
#define CY_SET_REG16(addr, value)   cywrite16_nodpx((void far *)(uint8 xdata *)(addr), value)

#define CY_GET_REG24(addr)          cyread24_nodpx((void far *)(uint8 xdata *)(addr))
#define CY_SET_REG24(addr, value)   cywrite24_nodpx((void far *)(uint8 xdata *)(addr),value)

#define CY_GET_REG32(addr)          cyread32_nodpx((void far *)(uint8 xdata *)(addr))
#define CY_SET_REG32(addr, value)   cywrite32_nodpx((void far *)(uint8 xdata *)(addr), value)

/* Access macros for 8, 16, 24 and 32-bit registers, ABOVE THE FIRST 64K OF XDATA */
#define CY_GET_XTND_REG8(addr)           cyread8(addr)
#define CY_SET_XTND_REG8(addr, value)    cywrite8(addr,value)

#define CY_GET_XTND_REG16(addr)          cyread16(addr)
#define CY_SET_XTND_REG16(addr, value)   cywrite16(addr,value)

#define CY_GET_XTND_REG24(addr)          cyread24(addr)
#define CY_SET_XTND_REG24(addr, value)   cywrite24(addr,value)

#define CY_GET_XTND_REG32(addr)          cyread32(addr)
#define CY_SET_XTND_REG32(addr, value)   cywrite32(addr,value)

/* Generate a NOP assembly instruction. */
#define CY_NOP      _nop_()

/* End of Keil C51 section. */
#elif defined(__GNUC__) || defined(__ARMCC_VERSION)
/* Include for the ARM compilers (GCC and RealView) */

/* For compatibility with Keil C51. */
#define CYBDATA
#define CYBIT      uint8
#define CYCODE
#define CYCOMPACT
#define CYDATA
#define CYFAR
#define CYIDATA
#define CYLARGE
#define CYPDATA
#define CYREENTRANT
#define CYSMALL
#define CYXDATA
#define XDATA

/* Interrupt service routine declarations */
#define CY_ISR(FuncName) void FuncName (void)
#define CY_ISR_PROTO(FuncName) void FuncName (void)
typedef void (* cyisraddress)(void);

/* ARM naturally returns a 32 bit value. */
typedef unsigned long cystatus;

/* Prototype for function to set a 24-bit register */
extern void     CySetReg24(uint8 volatile *addr, uint32 value);

/* 8, 16, 24 and 32-bit register access macros */
#define CY_GET_REG8(addr)           	(*((volatile uint8 *)(addr)))
#define CY_SET_REG8(addr, value)    	(*((volatile uint8 *)(addr))  = (uint8)(value))

#define CY_GET_REG16(addr)          	(*((volatile uint16 *)(addr)))
#define CY_SET_REG16(addr, value)   	(*((volatile uint16 *)(addr)) = (uint16)(value))

#define CY_GET_REG24(addr)          	(*((volatile uint32 *)(addr)) & 0x00FFFFFFu)
#define CY_SET_REG24(addr, value)   	CySetReg24((uint8 volatile *)addr, value)

#define CY_GET_REG32(addr)          	(*((volatile uint32 *)(addr)))
#define CY_SET_REG32(addr, value)   	(*((volatile uint32 *)(addr)) = (uint32)(value))

/* To allow code to be 8051-ARM agnostic. */
#define CY_GET_XTND_REG8(addr)			CY_GET_REG8(addr)
#define CY_SET_XTND_REG8(addr, value)   CY_SET_REG8(addr, value)

#define CY_GET_XTND_REG16(addr)         CY_GET_REG16(addr)
#define CY_SET_XTND_REG16(addr, value)  CY_SET_REG16(addr, value)

#define CY_GET_XTND_REG24(addr)         CY_GET_REG24(addr)
#define CY_SET_XTND_REG24(addr, value)  CY_SET_REG24(addr, value)

#define CY_GET_XTND_REG32(addr)         CY_GET_REG32(addr)
#define CY_SET_XTND_REG32(addr, value)  CY_SET_REG32(addr, value)

/* Generate a NOP assembly instruction. */
#if defined(__ARMCC_VERSION)
/* RealView */
#define CY_NOP      __nop()
#else
/* GCC */
#define CY_NOP      __asm("NOP\n")
#endif

/* End of ARM Compiler section */
#endif

/* Types for PSoC hardware registers. */
typedef volatile uint8 CYXDATA reg8;
typedef volatile uint16 CYXDATA reg16;
typedef volatile uint32 CYXDATA reg32;

#endif
