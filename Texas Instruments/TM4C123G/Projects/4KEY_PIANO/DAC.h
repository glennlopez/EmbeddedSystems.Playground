#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// DAC Bit-specific address: (7|200, 6|100, 5|80, 4|40, 3|20, 2|10, 1|08, 0|04)
#define DACOUT                  (*((volatile unsigned long *)0x4000503C))

// Configure PortB for DAC Output
void DAC_Init(void);

// Outputs parameter to PortB
void DAC_Out(unsigned long data);
