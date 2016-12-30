#include <AFMotor.h>       


//AF_Stepper steppername(steps, portnumber);
AF_Stepper motorname1a(400, 1);                     //<-- assign "motorname1a" to port 1
AF_Stepper motorname1b(400, 1);                     //<-- assign "motorname1b" to port 1

AF_Stepper motorname2a(400, 2);                     //<-- stepper 2 @ 400 steps/rev
AF_Stepper motorname2b(400, 2);                     //<-- stepper 2 @ 400 steps/rev
/*--------------------------------------------------------
[AF_Stepper PARAMETERS]
steps        - steps/rev on specific motor (0.9* = 400 | 1.8* = 200)
portnumber   - 1 is near reset button, 2 the other one
---------------------------------------------------------*/


void setup()
{
  Serial.begin(9600);

  //motorname.setSpeed(RPMspeed);
  motorname1a.setSpeed(30);                        //<-- stepper 2 @ 30 rpm
  motorname1b.setSpeed(100);                       //<-- stepper 2 @ 100 rpm  

  motorname2a.setSpeed(30);                        //<-- stepper 2 @ 30 rpm
  motorname2b.setSpeed(100);                       //<-- stepper 2 @ 100 rpm  
  /*--------------------------------------------------------
  [NOTE]
  The resulting step speed is based on the 'steps' parameter in the constructor. 
  If this does not match the number of steps for your motor, you actual speed will
  be off as well.
  --------------------------------------------------------*/
}


void loop() 
{
  //motorname.step(steps, direction, style);
  motorname1a.step(400, FORWARD, SINGLE);         //<-- stepper1 400 steps forward single style
  motorname1b.step(200, BACKWARD, DOUBLE);        //<-- stepper1 200 steps backwards double stle
  motorname1a.release();                          //<-- PREVENTS MOTORS FROM DRAWING CURENT
  motorname1b.release();

  motorname2a.step(400, FORWARD, SINGLE);         //<-- stepper2 400 steps forward single style
  motorname2b.step(200, BACKWARD, DOUBLE);        //<-- stepper2 200 steps backwards double stle
  motorname2a.release();                          //<-- PREVENTS MOTORS FROM DRAWING CURENT
  motorname2b.release(); 
  /*--------------------------------------------------------
  [STEP PARAMETERS]
  steps       - number of steps to turn (DO NOT MIXUP WITH steps/rev)
  direction   - direction of rotation (FORWARD or BACKWARD)
  style       - the style of stepping (SEE NOTES BELOW)

  [STYLE PARAMETERS]
  SINGLE      - one coil energized at a time
  DOUBLE      - two coils energized at a time
  INTERLEAVE  - smoother but slows rotation by half
  MICROSTEP   - finer resolution

  [RELEASE PARAMETERS]
  By default, the motor will 'hold' the position after its done stepping. 
  If you want to release all the coils, so that it can spin freely, call release()
  ---------------------------------------------------------*/
}
