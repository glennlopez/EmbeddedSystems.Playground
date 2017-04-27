#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define DACOUT                  (*((volatile unsigned long *)0x4000503C))

// Configure PortB for DAC Output
void DAC_Init(void);

// Outputs parameter to PortB
void DAC_Out(unsigned long data);
