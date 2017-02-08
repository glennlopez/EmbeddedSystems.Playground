// WorldShapers.c
// Runs on TM4C123 or MSP432, using MK-II
// Jonathan Valvano and Daniel Valvano
// Lab 4
// October 9, 2016

// Remember to remove R9 and R10 on TM4C123 to use the LCD since R10
// connects PD1 (accelerometer Y) to PB7 (LCD SPI data).

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2016

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// See BSP.c for hardware configuration of MK-II

#include <stdint.h>
#include "BSP.h"
#include "CortexM.h"
#include "Random.h"
#include "Sound.h"
#include "score.h"
#include "images.h"
#include "os.h"
#include "TExaS.h"
#define THREADFREQ 1000   // frequency in Hz of round robin scheduler
// semaphores
int32_t NewData;     // set by real-time tasks to signal graphics update
int32_t RunGame;     // set at 30 Hz
int32_t Button;      // set on button touch
int32_t CreateEnemy; // Set at 10 Hz
int32_t Mutex;
int32_t IntermissionFlag=1;
#define FIX 64    // 1/64 pixels

/*  ****************************************
    *x=0,y=0                      x=127,y=0*
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *                                      *
    *x=0,y=127                  x=127,y=127*
    ****************************************
*/
// *************************** Capture image dimensions out of BMP**********
struct sprite{
  const unsigned short *ImagePt[2]; // two images, animated
  uint32_t AnimationIndex;    // index through images, 0 or 1
  uint32_t AnimationCount;    // count of outputs since last image change
  uint32_t AnimationDuration; // number of outputs per image
  const unsigned short *DeathImagePt;
  short x,y;   // lower left coordinate
  short fx,fy; // lower left coordinate in 1/FIX pixels
  short w,h;   // size of image
  short vx,vy; // motion, change in 1/FIX pixels per video frame
  unsigned short life; // >0 is alive, 0 is dead
};
typedef struct sprite sprite_t;
#define NUMSPRITES 45
#define SHIP 0
#define ROCKETMIN 1
#define ROCKETMAX 15
#define ENEMYMIN 16
#define ENEMYMAX 30
#define EMISSILEMIN 31
#define EMISSILEMAX 44
#define MISSILE2SHIP 5   // hit distance
#define ROCKET2ENEMY 5   // hit distance
#define ENEMY2SHIP 5     // hit distance
#define MISSILE2ROCKET 2 // hit distance
#define CuteSpeed (FIX/16)
#define EnemySpeed (FIX/8)
#define RocketSpeed (FIX*2)
sprite_t Things[NUMSPRITES];
struct level{
  uint32_t KillCount;             // kills required to advance to next level
  uint32_t EnemyMissileThreshold; // enemies fire if random number 0 to 65535 less than this number
  uint32_t EnemyThreshold;        // spawn an enemy if random number 0 to 65535 less than this number
  int32_t  EnemyMissileSpeed;     // fixed point speed      
  uint32_t EnemyLife;             // number of hits required to kill enemy
  uint16_t Landcolor;
  uint16_t MaxLandHeight;
  int32_t  City;
};
typedef struct level level_t;
#define NUMLEVELS 5  // number of levels
level_t Levels[NUMLEVELS] = {
  {3,    0, 2048,  FIX/4, 1, LCD_GREEN,      60,0}, // 0: rolling hills
  {5,    0, 2048,  FIX/4, 1, LCD_BLUE,        8,0}, // 1: over lake 
  {5,  512, 4096,  FIX/2, 2, LCD_ORANGE,     40,0}, // 2: low lands
  {8, 1024, 4096,  FIX,   2, LCD_LIGHTGREEN, 80,0}, // 3: mountains
  {8, 2048, 4096,  FIX,  10, LCD_GREY,       30,1}  // 4: city
};
int CurrentLevel = 0;  // index of current level
uint32_t KillsThisLevel = 0;
short DesiredPlace;  // place to move ship to
uint32_t Score=0;
#define SCREENWIDTH 128
#define SCREENHEIGHT 128
uint32_t FindFreeRocket(void){
  uint32_t i;
  i = ROCKETMIN;
  while(Things[i].life){
    i++;
    if(i>ROCKETMAX) return 0; // no more player rockets can be created
  }
  return i;
}
uint32_t FindFreeEnemy(void){
  uint32_t i;
  i = ENEMYMIN;
  while(Things[i].life){
    i++;
    if(i>ENEMYMAX) return 0; // no more enemies can be created
  }
  return i;
}
uint32_t FindFreeEMissile(void){
  uint32_t i;
  i = EMISSILEMIN;
  while(Things[i].life){
    i++;
    if(i>EMISSILEMAX) return 0; // no more enemy missiles can be created
  }
  return i;
}
#define MAXTERRAIN 512
// Landscape numbers go from 5 to MaxLandHeight (level)
// drawn on bottom of screen as y-coor starting at 122 
unsigned char Landscape[MAXTERRAIN]; 
unsigned char LandCount;    // counter to wait for next movement
unsigned char LandDuration; // number of screen frames for every movement

//------------------------------------------------------------------------
// move terrain left, rotating with random, prepopulated terrain
//------------------------------------------------------------------------
void MoveLand(void){
  uint32_t i,first;
  LandCount--; // decrement counter to wait for next movement
  // it's time to move land along Y axis
  if(LandCount == 0){
    LandCount = LandDuration;
    // scrolls actual terrain to the left
    first = Landscape[0];
    for(i=0; i<MAXTERRAIN-1; i++){
      Landscape[i] = Landscape[i+1];
    }
    Landscape[MAXTERRAIN-1] = first+Random()/64;  // rotate image
  }
}
//------------------------------------------------------------------------
// create a initial terrain
// inputs:
//    X speed for terrain
//  max height
//  city=1 for cityscape
//------------------------------------------------------------------------
void CreateLand(uint32_t duration, uint32_t max, int32_t city){
  uint32_t i; uint32_t Rnd,change,Range; int32_t t;
  Landscape[0] = 5; Range = 5;
  for(i=1; i<MAXTERRAIN-32; i++){
    if(city){
      if((i%Range)==0){
        Rnd = ((max-5)*Random16())/65536+5; // 5 to max
        Range = (4*Random16())/65536+5; // 5 to 9
      }
      Landscape[i] = Rnd;
    }else{

      Rnd = Random16();
      if((i%5)==0){
        Range = Random16(); // used to make terrain creation more random
      }
      // random Y screen coordinate, limited to Y=60 as max altitude
      change = (unsigned char) Rnd%(Range%3+2); // random number
      Landscape[i] = Landscape[i-1] + change - 1;
      if (Landscape[i] > max) {
        Landscape[i] = max;
      }
      if (Landscape[i] < 5 ) {
        Landscape[i] = 5;
      }
    }
  }
  for(i=MAXTERRAIN-32; i<MAXTERRAIN; i++) {
    t = ((i-(MAXTERRAIN-32))*(Landscape[0]-Landscape[MAXTERRAIN-33]))/32
       +Landscape[MAXTERRAIN-33] + (Random()/64);
    Landscape[i] = t - 1;
    if (Landscape[i] > max) {
      Landscape[i] = max;
    }
    if (Landscape[i] < 5 ) {
      Landscape[i] = 5;
    }
  }
  LandDuration = duration; // number of frames before moving
  LandCount = duration;
}
// returns maximum of |x1-x2| and |y1-y2| of centers of objects
uint32_t Distance(uint32_t n1, uint32_t n2){  // put your answer here
  int32_t x1,x2,y1,y2,d1,d2;
  x1 = Things[n1].x+Things[n1].w/2;
  y1 = Things[n1].y-Things[n1].h/2;
  x2 = Things[n2].x+Things[n2].w/2;
  y2 = Things[n2].y-Things[n2].h/2;
  if(x1>x2){
    d1 = x1-x2;
  }else{
    d1 = x2-x1;
  }
  if(y1>y2){
    d2 = y1-y2;
  }else{
    d2 = y2-y1;
  }
  if(d1>d2) return d1;
  return d2;
}

//------------------------------------------------------------------------
// draw the land on the screen
//------------------------------------------------------------------------
void ReDrawLand(uint16_t color, uint16_t bgcolor){
  int i;
  BSP_LCD_DrawFastVLine(0, 0, SCREENHEIGHT, bgcolor);
  for(i=1; i<SCREENWIDTH; i=i+1){
    BSP_LCD_DrawFastVLine(i, SCREENHEIGHT-Landscape[i], Landscape[i], color);
    BSP_LCD_DrawFastVLine(i, 0, SCREENHEIGHT-Landscape[i]-1, bgcolor);
  }
}
void DrawLand(uint16_t color, uint16_t bgcolor){
  int i; int16_t lasty,newy;
  for(i=1; i<SCREENWIDTH; i=i+1){
    lasty = SCREENHEIGHT-Landscape[i-1];
    newy = SCREENHEIGHT-Landscape[i];
    if(lasty < newy){ // up         
      BSP_LCD_DrawFastVLine(i, lasty,  newy-lasty, bgcolor);
    } 
    if(lasty > newy){ // down     
      BSP_LCD_DrawFastVLine(i, newy+1, lasty-newy, color);
    }
  }
}

void DrawSprites(void){int i;
	OS_Wait(&Mutex);
  for(i=0; i<NUMSPRITES; i++){
    if(Things[i].life){ 
      BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].ImagePt[Things[i].AnimationIndex], Things[i].w,Things[i].h);
      Things[i].AnimationCount--;
      if(Things[i].AnimationCount == 0){
        Things[i].AnimationCount = Things[i].AnimationDuration; // how many frames before change image
        Things[i].AnimationIndex ^= 0x01; // index goes 0,1,0,1,0,1...
      }
    }
  }
	OS_Signal(&Mutex);
}
void MissileHitsShip(void){ // check for enemy missiles hitting player ship
  uint32_t i,d;
  for(i=EMISSILEMIN; i<=EMISSILEMAX; i++){
    if(Things[i].life){
      d = Distance(SHIP,i); // distance from ship to missile
      if(d <= MISSILE2SHIP){
        if(Things[SHIP].life) Things[SHIP].life--; // lose one life
        if(Score > 10){
          Score = Score-10;
        }else{
          Score = 0;
        }
        Sound_Explosion(); 
        Things[i].life = 0;        
        BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].DeathImagePt, Things[i].w,Things[i].h);
      }
    }
  }
}
void EnemyHitsShip(void){ // check for enemies hitting player ship
  uint32_t i,d;
  for(i=ENEMYMIN; i<=ENEMYMAX; i++){
    if(Things[i].life){
      d = Distance(SHIP,i); // distance from ship to enemy
      if(d <= ENEMY2SHIP){
        if((CurrentLevel==0)&&(KillsThisLevel==0)){
          Score = Score+100;  // good thing
          Sound_EyesOfTexasPieces();
        }else{
          if(Things[SHIP].life) Things[SHIP].life--; // lose one life
          if(Score > 10){
            Score = Score-10;
          }else{
            Score = 0;
          }
          Sound_Explosion(); 
        }
        Things[i].life = 0;        
        BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].DeathImagePt, Things[i].w,Things[i].h);
      }
    }
  }
}
void ShipHitsLand(void){ // check for ship hitting land
  uint32_t t;
  int i;
  t = 0;
  for(i=(Things[SHIP].x); i<(Things[SHIP].x+Things[SHIP].w); i++){
    if((i >= 0) && (i < MAXTERRAIN)){
      if(Landscape[i] > t){ // find highest land under ship
        t = Landscape[i];   // max land Y under ship
      }
    }
  }
  t = SCREENHEIGHT -t; // screen position of highest land
  if(Things[SHIP].y >= t){
    Things[SHIP].fy = FIX*(t-1); // hit land, bounce off
    Things[SHIP].y = Things[SHIP].fy/FIX;
    Things[SHIP].vy = 0;
    if(Score >= 5){
      Score = Score-5;  // loose points for hitting land
    }else{
      Score = 0;
    }
    Sound_Explosion(); 
  }
}
void RocketHitsMissile(void){ // check for rockets hitting missiles
  uint32_t i,j,d;
  for(i=ROCKETMIN; i<=ROCKETMAX; i++){
    if(Things[i].life){
      for(j=EMISSILEMIN; j<=EMISSILEMAX; j++){
        if(Things[j].life){
          d = Distance(j,i); // distance from rocket to missile
          if(d <= MISSILE2ROCKET){
            Things[i].life = 0;      // both destroyed on collision  
            Things[j].life = 0;        
            Sound_MissileRocket();
            BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].DeathImagePt, Things[i].w,Things[i].h);
            BSP_LCD_DrawBitmap(Things[j].x, Things[j].y, Things[j].DeathImagePt, Things[j].w,Things[j].h);
          }
        }
      }
    }
  }
}          
void RocketHitsEnemy(void){ // check for rockets hitting enemies
  uint32_t i,j,d;
  for(i=ROCKETMIN; i<=ROCKETMAX; i++){
    if(Things[i].life){
      for(j=ENEMYMIN; j<=ENEMYMAX; j++){
        if(Things[j].life){
          d = Distance(j,i); // distance from rocket to enemy
          if(d <= ROCKET2ENEMY){
            Things[j].life--;
            if(Things[j].life == 0){
              Score = Score+10;
              KillsThisLevel = KillsThisLevel+1;
              Sound_Killed(); 
              Things[j].life = 0;        
              BSP_LCD_DrawBitmap(Things[j].x, Things[j].y, Things[j].DeathImagePt, Things[j].w,Things[j].h);
            }
            BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].DeathImagePt, Things[i].w,Things[i].h);
            Things[i].life = 0;   
          }            
        }
      }
    }
  }
}        

void MoveSprites(void){int i;
	OS_Wait(&Mutex);
  for(i=0; i<NUMSPRITES; i++){
    if(Things[i].life){
      Things[i].fx = Things[i].fx+Things[i].vx;
      Things[i].x = Things[i].fx/FIX;
      if((Things[i].x<0)||(Things[i].x>127)){
        Things[i].life = 0;
      }
      Things[i].fy = Things[i].fy+Things[i].vy;
      Things[i].y = Things[i].fy/FIX;
      if((Things[i].y<0)||(Things[i].y>127)){
        Things[i].life = 0;
      }     
      if(Things[i].life==0){
        BSP_LCD_DrawBitmap(Things[i].x, Things[i].y, Things[i].DeathImagePt, Things[i].w,Things[i].h);
      }
    }
  }
	OS_Signal(&Mutex);
}
void CreateSprite(int i, 
  const unsigned short *livePt, const unsigned short *livePt2,
  uint32_t animationDuration,
  const unsigned short *deadPt,
  short initx, short inity,
  short width, unsigned height,
  short initvx, short initvy, int alive){
	OS_Wait(&Mutex);
  Things[i].ImagePt[0] = livePt;
  Things[i].ImagePt[1] = livePt2;
  Things[i].AnimationIndex = 0;
  Things[i].AnimationCount = animationDuration;
  Things[i].AnimationDuration = animationDuration;
  Things[i].DeathImagePt = deadPt;
  Things[i].x = initx;
  Things[i].y = inity;
  Things[i].fx = FIX*initx;
  Things[i].fy = FIX*inity;
  Things[i].w = width;
  Things[i].h = height;  
  Things[i].vx = initvx;
  Things[i].vy = initvy;
  Things[i].life  = alive;    
	OS_Signal(&Mutex);
}

int abs(int x){
  if(x<0) return -x;
  return x;
}


#define SCREENCHARCOLS 26                 // total number of character columns in the screen
#define SCREENCHARROWS 13                 // total number of character rows in the screen
uint16_t RevealScreen[SCREENCHARCOLS];    // set a bit in this array to reveal the character at corresponding row; LSB = row0
// Hide all characters for next call to revealchar().
// Input: none
// Output: none
void hideallscreen(void){
  uint16_t mask = ((1<<13) - 1);  // all rows
  int i;
  for(i=0; i<SCREENCHARCOLS; i=i+1){
    RevealScreen[i] &= ~mask;
  }
}
// Reveal all characters for next call to revealchar().
// Input: none
// Output: none
void revealallscreen(void){
  uint16_t mask = ((1<<13) - 1);  // all rows
  int i;
  for(i=0; i<SCREENCHARCOLS; i=i+1){
    RevealScreen[i] |= mask;
  }
}
// Attempt to reveal a character at the given row and
// column.  If the character has already been revealed, it
// will be printed.  If not, a random 16-bit number will be
// compared with the 'revealChance' parameter.  If the
// random number is smaller, the character will be revealed
// and printed.  Otherwise, the character will remain
// hidden, and a random character will be printed in the
// 16-bit color 'falseColor'.
// Input: x            columns from the left edge (0 to 25)
//        y            rows from the top edge (0 to 12)
//        pt           pointer to a character to be printed
//        textColor    16-bit color of the revealed character
//        falseColor   16-bit color of the hidden character
//        revealChance 16-bit chance of revealing character
// bgColor is Black and size is 1
// Output: none
void revealchar(uint16_t x, uint16_t y, char *pt, int16_t textColor, int16_t falseColor, uint16_t revealChance){
  if((x >= SCREENCHARCOLS) || (y >= SCREENCHARROWS)){
    return;
  }
  if(RevealScreen[x]&(1<<y)){
    // character is revealed
    BSP_LCD_DrawChar(x*6, y*10, *pt, textColor, LCD_BLACK, 1);
  } else{
    // character is hidden
    if(Random16() < revealChance){
      // reveal the character
      RevealScreen[x] |= (1<<y);
      BSP_LCD_DrawChar(x*6, y*10, *pt, textColor, LCD_BLACK, 1);
    } else{
      // character is still hidden
      BSP_LCD_DrawChar(x*6, y*10, ('0' + (Random16()%75)), falseColor, LCD_BLACK, 1);
    }
  }
}
#define NUMRANDCOLORS 12                  // length of random color array
const uint16_t RandomColors[NUMRANDCOLORS] = {
  0x801F,  // 255, 0, 128
  0x001F,  // 255, 0, 0
  0x041F,  // 255, 128, 0
  0x07FF,  // 255, 255, 0
  0x07F0,  // 128, 255, 0
  0x07E0,  // 0, 255, 0
  0x87E0,  // 0, 255, 128
  0xFFE0,  // 0, 255, 255
  0xFC00,  // 0, 128, 255
  0xF800,  // 0, 0, 255
  0xF810,  // 128, 0, 255
  0xF81F,  // 255, 0, 255
};
// Reveal a left vertical string on the given row.
// Input: y         rows from the top edge (0 to 12)
//        pt        pointer to a null terminated string to be printed
//        textColor 16-bit color of the characters
// bgColor is Black and size is 1
// Output: number of characters printed
uint32_t revealstring(uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  uint16_t x = 0;
  char *c = pt;
  while(*c){
    x = x + 1;
    c = c + 1;
  }
  x = 0; //13 - x/2;
  if(y>12) return 0;
  while(*pt){
    revealchar(x, y, pt, textColor, RandomColors[Random()%NUMRANDCOLORS], 6554);
    pt++;
    x = x+1;
    if(x>25) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}
// Pause the game and display a message for intermission.
// Pause is crudely implemented by turning off interrupts
// and busy-waiting.
// Input: delay10ms  number of 10ms delays while message is on screen
//        level      level message index (<NUMLEVELS for level victory)
// Output: none
void Intermission(uint32_t delay10ms, int32_t level){
  int i;
  IntermissionFlag=0; // game engine stops, sounds continue
  hideallscreen();
  BSP_LCD_FillScreen(0x0000);            // set screen to black
  for(i=0; i<12; i=i+1){
    if(i == 11){
      revealallscreen();                // show any still hidden characters
    }
    if(level < 0){ // limit to 21 characters
      revealstring(3,  "The World Shapers",     LCD_WHITE);
      revealstring(5,  "We do love to fly",     LCD_WHITE);
      revealstring(7,  "On wallpapers",         LCD_WHITE);
      revealstring(9,  "Of beautiful sky",      LCD_WHITE);
    } else if(level == 0){
      revealstring(4,  "Oh, my dearest friend", LCD_YELLOW);
      revealstring(6,  "Why must we defend?",   LCD_YELLOW);
    } else if(level == 1){
      revealstring(5,  "You're shooting at us", LCD_ORANGE);
      revealstring(7,  "You're shooting at us", LCD_ORANGE);
      revealstring(9,  "Why make such a fuss?", LCD_ORANGE);
    } else if(level == 2){
      revealstring(3,  "MONSTERS MONSTERS",     LCD_LIGHTGREEN);
      revealstring(5,  "CAN WE DISCUSS!",       LCD_LIGHTGREEN);
      revealstring(7,  "SADDNESS HORRORS!",     LCD_LIGHTGREEN);
      revealstring(9,  "SOMEONE SAVE US!",      LCD_LIGHTGREEN);
    } else if(level == 3){
      revealstring(3,  "WALLS YOU GO THROUGH",  LCD_CYAN);
      revealstring(5,  "FINE CITIES AND THUS",  LCD_CYAN);
      revealstring(7,  "OH, WHAT CAN WE DO?",   LCD_CYAN);
      revealstring(9,  "SOMEONE SAVE US!",      LCD_ORANGE);
    } else if(level == 4){
      revealstring(2,  "YOU EVIL HUMAN!",       LCD_WHITE);
      revealstring(4,  "HAVE DESTROYED",        LCD_WHITE);
      revealstring(6,  "OUR FLEET AND ARE",     LCD_WHITE);
      revealstring(8,  "INVADING OUR HOME!",    LCD_WHITE);
      revealstring(10, "WE ARE VANQUISHED!",    LCD_WHITE);
    } else if(level == 5){
      revealstring(2,  "Oh, my dear friend",    LCD_YELLOW);
      revealstring(4,  "To you we now share",   LCD_YELLOW);
      revealstring(6,  "The special dividend",  LCD_YELLOW);
      revealstring(8,  "Of our best software!", LCD_YELLOW);
    } else if(level > 5){
      revealstring(1,  "YOU CAME WITH CAPRICE", LCD_WHITE);
      revealstring(3,  "YOU ACTED SO BADLY",    LCD_WHITE);
      revealstring(5,  "WE OFFERED YOU PEACE",  LCD_WHITE);
      revealstring(7,  "YOU FIRED SO GLADLY",   LCD_WHITE);
      revealstring(9,  "WE GIVE YOU RELEASE",   LCD_WHITE);
      revealstring(11, "VANQUISHED SO SADLY",   LCD_WHITE);
    }
    OS_Sleep(120);
  }
  if(level >= 4){
    Score_OutHorizontal(Score,122,141);
    while(1){};
  }
  OS_Sleep(delay10ms*10);
  BSP_LCD_FillScreen(0x0000);            // set screen to black
  // clear all player rockets and enemy missiles
  for(i=ROCKETMIN; i<=ROCKETMAX; i=i+1){
    Things[i].life = 0;
  }
  for(i=EMISSILEMIN; i<=EMISSILEMAX; i=i+1){
    Things[i].life = 0;
  }
  CreateLand(8,Levels[level+1].MaxLandHeight,Levels[level+1].City);
  ReDrawLand(Levels[level+1].Landcolor, LCD_BLACK);
  DrawSprites();
  Score_OutVertical(Things[SHIP].life,80,6);
  Score_OutVertical(Score,101,6);
  IntermissionFlag=1;            // game engine restarts, sounds continue
  if(RunGame>0) OS_InitSemaphore(&RunGame,0);  // don't queue up flags
}
void GameTask(void){ // runs at 30 Hz
  uint16_t x,y; uint8_t button;
  Intermission(300, -1);
  while(Things[SHIP].life){
    OS_Wait(&RunGame);
    if(IntermissionFlag){
      TExaS_Task0();     // records system time in array, toggles virtual logic analyzer
      BSP_Joystick_Input(&x,&y,&button);
      DesiredPlace = ((113*(1023-y))>>10)+5; // 0 to 1023 mapped to 5 to 117
      if(DesiredPlace > Things[SHIP].y){
        if(DesiredPlace > Things[SHIP].y+1){
          Things[SHIP].vy = 2*FIX;  // move down fast
        }else{
          Things[SHIP].vy = FIX;    // move down
        }
      }else if(DesiredPlace < Things[SHIP].y){
        if(DesiredPlace < Things[SHIP].y-1){
          Things[SHIP].vy = -2*FIX;  // move up fast
        }else{
          Things[SHIP].vy = -FIX;    // move up
        }
      }else{
      Things[SHIP].vy = 0;  // stay put
      }
  //if joystick pushed to right and not too close to right, set velocity to go right
  // else if not too far left, set velocity go left
  // if at left velocity =0
      Things[SHIP].vx = 0;  // stay put
      if(x>650){
        if((Things[SHIP].x < (SCREENWIDTH - 1)) && (Things[SHIP].y > Landscape[Things[SHIP].x])){
          Things[SHIP].vx = FIX;  // move right
        }
      } else if(x<300){
        if((Things[SHIP].x > 10) && (Things[SHIP].y > Landscape[Things[SHIP].x])){
          Things[SHIP].vx = -FIX;  // move left
        }
      } else {
        if(Things[SHIP].x > 0){
          Things[SHIP].vx = -2*LandDuration;  // move left
        }
      }
      MoveSprites();
      MoveLand(); // terrain movement
      DrawLand(Levels[CurrentLevel].Landcolor, LCD_BLACK);
      EnemyHitsShip();
      RocketHitsMissile();
      RocketHitsEnemy();
      MissileHitsShip();
      ShipHitsLand();
      DrawSprites();  
      Score_OutVertical(Things[SHIP].life,80,6);
      Score_OutVertical(Score,101,6);
      if((CurrentLevel==0)&&(Score>=1000)){
        Intermission(300, 5); // game win
      }
      if(KillsThisLevel >= Levels[CurrentLevel].KillCount){
        KillsThisLevel = 0;
        Things[SHIP].life++; 
        Intermission(300, CurrentLevel);
        CurrentLevel = CurrentLevel + 1;
      }
    }
  }
  Intermission(300, 6);
  while(1);
}
//------------EnemyTask controls the enemies -------
// multiple threads each running this same program
// AI of enemy
void EnemyTask(void){ uint32_t me; uint32_t t,j,initY,ok,trys;
  me = FindFreeEnemy(); 
  if(me==0){
		OS_Kill(); // no sprites left to use
	}
  t = 0;     // landscape 0 means bottom of screen     
  for(j=SCREENWIDTH-20; j<SCREENWIDTH;j++){
     if(Landscape[j] > t){
       t = Landscape[j];  // max land height on right of screen
     }
  }
  t = SCREENHEIGHT-t; // screen y coordinate of highest land 
  Things[me].x = 118; // start on right
  ok = 1;
  trys = 0;
  while(ok){
    ok = 0; // assume it is ok
    initY = ((t-15)*Random())/256+10; // 10 to t-5
    Things[me].y = initY;
    for(j=ENEMYMIN; j<=ENEMYMAX; j++){
      if(Things[j].life){
        if(Distance(me,j)<10) ok = 1; // too close to other enemies
      }
    }
    trys++;
	  if(trys==40) OS_Kill(); // no room on screen
  }
  if(Random() > 64){
    if(((CurrentLevel==0)&&(Score >= 500))||(CurrentLevel>3)){
      CreateSprite(me,big0,big1,10,big3,118,initY,21,21,-EnemySpeed,0,Levels[CurrentLevel].EnemyLife);
    }else{
      CreateSprite(me,bender0,bender1,10,bender3,118,initY,11,10,-EnemySpeed,0,Levels[CurrentLevel].EnemyLife);
    }
  }else{
    CreateSprite(me,cute0,cute1,10,cute3,118,initY,11,11,-CuteSpeed,0,Levels[CurrentLevel].EnemyLife);
  }
  while(Things[me].life){ int dx,dy;
    OS_Sleep(100);
    if(CurrentLevel>1){ // move towards ship
      dx = Things[SHIP].fx - Things[me].fx;
			if(dx>0) dx=0; // can't back up
      dy = Things[SHIP].fy-8*FIX - Things[me].fy;
      while((dx*dx+dy*dy)>(EnemySpeed*EnemySpeed)){
        dx = (3*dx)/4;
        dy = (3*dy)/4;
      }
      Things[me].vx = dx;
      Things[me].vy = dy+(((FIX/2)*Random())/256 - FIX/4); // wiggles around
    }else{
      Things[me].vy = ((FIX)*Random())/256 - FIX/2; // wiggles around
    }
    t=0; // closest land to this enemy
    if(Things[me].x<=20){
      j = 0;
    }else{
      j = Things[me].x-20;
    }
    while(j <= (Things[me].x+Things[me].w)){
      if(Landscape[j] > t){
        t = Landscape[j];  // max land in front of enemy
      }
      j++;
    }
    t = SCREENHEIGHT - t ; // largest y allowed
    if(Things[me].y >= t-5){
      Things[me].vy = -FIX; // move up fast
    }else if(Things[me].y >= t-10){
      Things[me].vy = -FIX/2; // move up slower
    }
    if(Random16() < Levels[CurrentLevel].EnemyMissileThreshold){ // 0 to 65535
      j = FindFreeEMissile();
      if(j){
        int MissileSpeed = Levels[CurrentLevel].EnemyMissileSpeed;
        if(CurrentLevel<2){
          CreateSprite(j,missile0,missile1,10,missile3,Things[me].x-2,Things[me].y-2,5,5,-MissileSpeed,0,1);
        }else{ int dx,dy;
          dx = Things[SHIP].fx - Things[me].fx;
          dy = Things[SHIP].fy-8*FIX - Things[me].fy;
          while((dx*dx+dy*dy)>(MissileSpeed*MissileSpeed)){
            dx = (3*dx)/4;
            dy = (3*dy)/4;
          }
          CreateSprite(j,missile0,missile1,10,missile3,Things[me].x-2,Things[me].y-2,5,5,dx,dy,1); 
        }
      }
    }
  }
  OS_Kill();
}
//------------EnemyCreateTask creates new enemies randomly -------
void EnemyCreateTask(void){
  while(1){
    OS_Wait(&CreateEnemy); // runs at about 10 Hz
    if(IntermissionFlag){  // halt game during intermissions
      TExaS_Task1();       // records system time in array, toggles virtual logic analyzer
      if(Random16() < Levels[CurrentLevel].EnemyThreshold){ // 0 to 65535
        OS_AddThread(&EnemyTask,0); // thread will create itself
      }
    }
  }
}
//------------ButtonTask handles switch input -------
// *********ButtonTask*********
// Main thread scheduled by OS priority scheduler
// real-time task, signaled on touch
//   with bouncing, may also be called on release
// checks the switches, creates player rockets
// Inputs:  none
// Outputs: none
void ButtonTask(void){uint32_t i;
  uint8_t current;
	OS_InitSemaphore(&Button,0); // signaled on touch button1
  while(1){
		OS_Wait(&Button);      // OS signals on touch
    TExaS_Task3();         // records system time in array, toggles virtual logic analyzer
    OS_Sleep(10);          // debounce the switches
    current = BSP_Button1_Input();
    if(current == 0){     // Button1 was pressed 
      i = FindFreeRocket();
      if(i){
        Sound_Shoot();
        if(Score > 1) Score--;
        CreateSprite(i,rocket0,rocket1,10,rocket3,Things[SHIP].x+8,Things[SHIP].y-5,8,3,RocketSpeed,0,1);
      }
    }
		OS_EdgeTrigger_Restart();
  }
}

int Freetime;
void IdleTask(void){ // dummy task
  Freetime = 0;      // this task cannot block, sleep or kill
  while(1){
    Freetime++; 
  }
}
int main(void){uint16_t x,y; uint8_t button;
  DisableInterrupts();
  BSP_Clock_InitFastest();
  BSP_Joystick_Init();
  BSP_LCD_Init();
  BSP_Button1_Init();
  BSP_Joystick_Input(&x,&y,&button);

  Random_Init(x*y);
  Sound_Init(); // initialize sound channel

  DesiredPlace = 64;
  CurrentLevel = 0;
  OS_Init();
  OS_PeriodTrigger0_Init(&RunGame,33); // timing engine for game
  OS_PeriodTrigger1_Init(&CreateEnemy,100); // create enemies 10 times a second
	OS_EdgeTrigger_Init(&Button, 3);     // effect of button touch
  TExaS_Init(LOGICANALYZER,BSP_Clock_GetFreq());
 // Sound_EyesOfTexas();
  OS_InitSemaphore(&RunGame,0);     // signaled by timer to run engine
  OS_InitSemaphore(&Mutex,1);       // access to sprites
  OS_InitSemaphore(&CreateEnemy,0); // signaled by time to create enemies
	OS_AddThread(&GameTask,0);
  OS_AddThread(&ButtonTask,0);   // high priority, signaled on button touch
  OS_AddThread(&EnemyCreateTask,2);
  OS_AddThread(&IdleTask,7);     // lowest priority, dummy task
  CreateSprite(SHIP,ship0,ship1,2,ship3,0,DesiredPlace,18,13,0,0,10);
  OS_Launch(BSP_Clock_GetFreq()/THREADFREQ); // doesn't return, interrupts enabled in here
  while(1){ // does not get here
  }
}


