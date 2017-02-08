// CortexM.h
// Cortex M registers used in these labs
// Daniel and Jonathan Valvano
// February 7, 2016

#define STCTRL          (*((volatile uint32_t *)0xE000E010))
#define STRELOAD        (*((volatile uint32_t *)0xE000E014))
#define STCURRENT       (*((volatile uint32_t *)0xE000E018))
#define INTCTRL         (*((volatile uint32_t *)0xE000ED04))
#define SYSPRI1         (*((volatile uint32_t *)0xE000ED18))
#define SYSPRI2         (*((volatile uint32_t *)0xE000ED1C))
#define SYSPRI3         (*((volatile uint32_t *)0xE000ED20))
#define SYSHNDCTRL      (*((volatile uint32_t *)0xE000ED24))
#define FAULTSTAT       (*((volatile uint32_t *)0xE000ED28))
#define HFAULTSTAT      (*((volatile uint32_t *)0xE000ED2C))
#define MMADDR          (*((volatile uint32_t *)0xE000ED34))
#define FAULTADDR       (*((volatile uint32_t *)0xE000ED38))

// these functions are defined in the startup file

//******DisableInterrupts************
// sets the I bit in the PRIMASK to disable interrupts
// Inputs: none
// Outputs: none
void DisableInterrupts(void); // Disable interrupts

//******EnableInterrupts************
// clears the I bit in the PRIMASK to enable interrupts
// Inputs: none
// Outputs: none
void EnableInterrupts(void);  // Enable interrupts

//******StartCritical************
// StartCritical saves a copy of PRIMASK and disables interrupts
// Code between StartCritical and EndCritical is run atomically
// Inputs: none
// Outputs: copy of the PRIMASK (I bit) before StartCritical called
long StartCritical(void);    

//******EndCritical************
// EndCritical sets PRIMASK with value passed in
// Code between StartCritical and EndCritical is run atomically
// Inputs: PRIMASK (I bit) before StartCritical called
// Outputs: none
void EndCritical(long sr);    // restore I bit to previous value

//******WaitForInterrupt************
// enters low power sleep mode waiting for interrupt (WFI instruction)
// processor sleeps until next hardware interrupt
// returns after ISR has been run
// Inputs: none
// Outputs: none
void WaitForInterrupt(void);  

