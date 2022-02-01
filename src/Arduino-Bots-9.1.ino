#include <Arduino.h>
#include <Servo.h>

//def servos
Servo servoright;
Servo servoleft;


//*** HARDWARE SETTINGS ****
//variables for the pins
int pinright = 12;
int pinleft = 13;


//***** HARDWARE DRIVE TRAIN CALIBRATION ***
//set this to 1 in order to enable the motors to just be at 1500 1500 to tune their 0 points, do this first before
//the software calibration
//how to calibrate:
//(1) set this value to 1 and upload the code.
//(2) use a fine screwdriver on the back of the servo motor (looks like a small screw) to set the 0 point of the motor
//    by slowly turning "the screw" (a potentiometer) on the back until the motor is completely still. This requires 
//    very fine control and it may take a while.
//(3) reset this value to 0 and reupload the code.
int calibrationenabled = 0;


//***** SOFTWARE DRIVE TRAIN CALIBRATION ****
//calibration data software jank 
//how to calibrate:
//(1) start with 1300 and 1700 and make sure that the robot is driving in the right direction, if not, you will have to 
//    switch the 1300 and 1700 around.
//(2) see which way the robot is veering
//(3) if the robot is veering to the left, then you will need to increase the left value proportionally to the right
//    value. This means you can bring the right value closer to 1500 slightly, decreasing the speed on the right motor
//(4) if the robot is verring to the right, then you need to do the opposite, increasing the right value proportionally
//    to the left value. This means you can bring the left value closer to 1500, decreasing the speed on the right motor.
//(5) continue adjusting in increments of 50 at first, then 10, and then down to +-1. Small changes make a large
//    difference here, especially the closer you are to 1500. You'll notice that you've gotten close by the 
//    direction the robot is veering in changing. Once that happens, you can slowly tweak the value back in the other 
//    direction to get the precise value.
//(6) enjoy!
int right = 1590;
int left = 1300;


// *** COURSE DETAILS ***
//timings for how long to go on each section of the course and turn, in milliseconds.  
//how to calibrate:
//(1) run the robot, see if the robot stopped in the right place on the first marker, if it was too early
//    increase the firsttime variable, save and reupload the code. And decrease it if it was too late. 
//    Tweak until you are satisfied.
//(2) run the robot and see if the robot turns correctly in the first marker. If the robot turns too far, decrease
//    the turn1 variable. If it was too little of a turn, increase the time. Tweak until satisfied.
//(3) continue this process for the other 3 variables, secondtime, turn2 and thirdtime for the length of time
//    the robot should move on the second part of the track, the length of time for the second turn, and the 
//    time the robot should move on the third part of the track correspondingly. Use the procedure outlined in
//    steps 1&2 until everything is too your liking and the robot completes the course. Remember to reupload after
//    every change!
//(4) leave stoptime as is. It doesn't need calibration. 
//(5) enjoy!
int firsttime = 15250;
int turn1 = 975;
int secondtime = 21250;
int turn2 = 850;
int thirdtime = 15250;
int stoptime = 2000;

void setup()
{
  //setup the motor pins
  servoright.attach(pinright);
  servoleft.attach(pinleft);

  //calibration script, simply set the motors to 1500, 1500 for 900 seconds so you can trim the pots.
  if (calibrationenabled == 1){
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);
  delay(900000);
  }


  //initial delay to make things a lot easier to start
  delay(5000);


  //straight 1, go for time firsttime using our calibrated rightleft values in order to ensure a straight
  //drive train.
  //In this case, the right motor has to work harder than the left motor, as in my case a constant rightwards
  //veer was noticable at 1300 and 1700. Using 1300 and 1590 instead produced much nicer driving.
  //There is nothing in the code right now to autocalculate these values, so it is a little bit of guess
  //and check and is dependent on a lot of factors (IE: changing wheels made me go from 1580 to 1590) and
  //this code will likely not be as successful on other's robots.
  servoright.writeMicroseconds(right);
  servoleft.writeMicroseconds(left);
  delay(firsttime);

  //stop 1 for length stoptime (this is why calibration on the motor pots must still be done with this code)
  //this simply ensures better traction as going from speed seems to cause slipping when telling the motor to simply
  //change its direction entirely.
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);
  delay(stoptime);
  
  //turn 1 (in this case, move both wheels in the same direction as the right wheel to get it to turn to the right)
  servoright.writeMicroseconds(right);
  servoleft.writeMicroseconds(right);
  delay(turn1);

  //straight 2, matches previous however with second time instead
  servoright.writeMicroseconds(right);
  servoleft.writeMicroseconds(left);
  delay(secondtime);

  //turn 2 (in this case, move both wheels in the same direction as the left wheel to cause a leftwards turn)
  servoright.writeMicroseconds(left);
  servoleft.writeMicroseconds(left);
  delay(turn2);

  //straight 3
  servoright.writeMicroseconds(right);
  servoleft.writeMicroseconds(left);
  delay(thirdtime);

  //stop, forever :)
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);
}


void loop()
{
 //Add code that repeats automatically here.
} 