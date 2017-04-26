
// Systick & NVIC Registers (pg 132)
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

void EnableInterrupts(void);
void DisableInterrupts(void);

void Sound_Init(void);
void Sound_Tone(unsigned long period);
void Sound_Off(void);
void SysTick_Handler(void);
