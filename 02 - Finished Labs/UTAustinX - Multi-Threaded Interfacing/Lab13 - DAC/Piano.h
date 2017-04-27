
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define PIANO_KEY                   (*((volatile unsigned long *)0x4002403C))
#define G_KEY /* E3: (783.991) */ (*((volatile unsigned long *)0x40024020))
#define E_KEY /* E2: (659.255) */ (*((volatile unsigned long *)0x40024010))
#define D_KEY /* E1: (587.330) */ (*((volatile unsigned long *)0x40024008))
#define C_KEY /* E0: (523.251) */ (*((volatile unsigned long *)0x40024004))

// Tones: 80Mhz
#define CUT_OFF     0
#define G_NOTE      2126     //783.991
#define E_NOTE      2529     //659.255
#define D_NOTE      2839     //587.330
#define C_NOTE      3186     //523.251

// Configure PortE as input for Piano Keys
void Piano_Init(void);

// Returns Reload value for Periodic interrupt based on key pressed
unsigned long Piano_In(void);
