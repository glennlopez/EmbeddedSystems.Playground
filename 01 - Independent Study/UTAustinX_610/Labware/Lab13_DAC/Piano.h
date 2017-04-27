
// Bit-specific Address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define BTN_INPUT                   (*((volatile unsigned long *)0x4002403C))
#define SYSCTL_RCGC2_R          		(*((volatile unsigned long *)0x400FE108))

// Tones: 80Mhz for SineWave[48] as per Sound.c
// You can add more frequency tones below using the following formula:
//([(1/f)/(1/system clock)]/total pulse) = Wave Reload value
// Frq Table - http://www.phy.mtu.edu/~suits/notefreqs.html

#define CUT_OFF     0				//NO SOUND
#define C_NOTE      3186   	//523.251 *
#define D_NOTE      2839   	//587.330 *
#define E_NOTE      2529   	//659.255 *
#define F_NOTE			2388		//698.460
#define G_NOTE      2126   	//783.991 *
#define A_NOTE			1894		//880.000
#define B_NOTE			1687		//987.770

// Configures PortE as input for Piano Keys
void Piano_Init(void);

// Returns Reload value for Periodic interrupt based on key pressed
// Used in conjuction with: Sound_Tone(Piano_In()); to produce sound
unsigned long Piano_In(void);	
