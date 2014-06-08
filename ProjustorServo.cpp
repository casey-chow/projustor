#include "ProjustorServo.h"
#include <Servo.h>

ProjustorServo::ProjustorServo(int pin)
{
   _pin = pin;
}
/*Begin the detection and get the pulse back signal*/
void ProjustorServo::MoveObjToPos(long newPosition) {
  
}

void ProjustorServo::MoveObjToAng(int newAng) {
  int pulse = pulseLength(newPosition);
  
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(_pin,LOW);
}



int ProjustorServo::pulseLength(long tgtPosition) {
  // 5V for 500 microseconds = 0.5 milliseconds and corresponds to 0 degrees
  // 5V for 1500 microseconds = 1.5 milliseconds and corresponds to 90 degrees
  // 5V for 2500 microseconds = 2.5 milliseconds and corresponds to 180 degrees
  
}
