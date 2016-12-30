#include <AFMotor.h>         


//AF_Stepper steppername(steps, portnumber);
AF_Stepper motorname(400, 2);                     //<-- 0.9* = 400 steps/rev
/*--------------------------------------------------------
[AF_Stepper PARAMETERS]
steps        - steps/rev on specific motor (0.9* = 400 | 1.8* = 200)
portnumber   - 1 is near reset button, 2 the other one
---------------------------------------------------------*/


void setup()
{
  Serial.begin(9600);

  //motorname.setSpeed(RPMspeed);
  motorname.setSpeed(30);                       //<-- 30 rpm 
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
  motorname.step(400, FORWARD, SINGLE);       //<-- 400 steps forward single style
  motorname.step(200, BACKWARD, DOUBLE);      //<-- 200 steps backwards double stle
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
  ---------------------------------------------------------*/


  motorname.release();
  /*--------------------------------------------------------
  [NOTE]
  Release the holding torque on the motor. This reduces heating and current demand, 
  but the motor will not actively resist rotation.
  --------------------------------------------------------*/
}
