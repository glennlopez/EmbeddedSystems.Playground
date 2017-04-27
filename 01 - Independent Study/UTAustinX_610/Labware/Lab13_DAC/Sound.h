// Systick & NVIC Registers (pg 132)
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// Systick Initialization
void Sound_Init(void);

// Sends the tone frq to NVIC RELOAD
void Sound_Tone(unsigned long period);

// Stops the sound when no buttons are pressed
void Sound_Off(void);

// Generates a periodic interupt required the dac
void SysTick_Handler(void);
