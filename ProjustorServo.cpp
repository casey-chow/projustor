#include "ProjustorServo.h"
#include <math.h>
#include <Servo.h>

ProjustorServo::ProjustorServo(int pin)
{
   _pin = pin;
   servo.attach(pin);
}

void ProjustorServo::MoveObjToPos(long newPosition, long height) {
  // https://casry.hackpad.com/Servo-Calculations-15QDaQiFuMh
  int angle = (int) atan((long) newPosition / height) + 90;
  MoveObjToAng(angle);
}

void ProjustorServo::MoveObjToAng(int newAng) {
  servo.write(newAng);
}
