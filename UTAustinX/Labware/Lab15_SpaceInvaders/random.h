/*Random number generator;
  Linear congruential generator 
  from Numerical Recipes by Press et al.
  Jonathan Valvano

  How to use: 
  Call Random_Init once with a seed. For example
      Random_Init(1);
      Random_Init(NVIC_CURRENT_R);
  Call Random over and over to get a new random number. For example
      m = Random32()%60; // returns a random number from 0 to 59
      p = Random();      // returns a random number 0 to 255
*/
void Random_Init(unsigned long seed);

unsigned long Random(void);
unsigned long Random32(void);
