#include <Arduino.h>
#include <Servo.h>

Servo servoright;
Servo servoleft;

//timings
int firsttime = 15250;
int turn1 = 975;
int secondtime = 21250;
int turn2 = 850;
int thirdtime = 15250;
int stoptime = 2000;

//calibration data software jank
int min = 1590;
int max = 1300;

int calibrationenabled = 0;

void setup()
{
  //setup
  servoright.attach(12);
  servoleft.attach(13);

  if (calibrationenabled == 1){
  //calibration
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);

  delay(100000);
  }

  delay(5000);
  //first straightaway
  servoright.writeMicroseconds(min);
  servoleft.writeMicroseconds(max);


  delay(firsttime);

  //stop 1

  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);

  delay(stoptime);
  
  //turn 1

  servoright.writeMicroseconds(min);
  servoleft.writeMicroseconds(min);

  delay(turn1);

  //straight 2

  servoright.writeMicroseconds(min);
  servoleft.writeMicroseconds(max);

  delay(secondtime);

  //turn 2

  servoright.writeMicroseconds(max);
  servoleft.writeMicroseconds(max);

  delay(turn2);

  //straight 3

  servoright.writeMicroseconds(min);
  servoleft.writeMicroseconds(max);

  delay(thirdtime);

  //stop 3
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1500);


}


void loop()
{
 //Add code that repeats automatically here.
} 