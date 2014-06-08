/*
  Projustor
  
  Adjusts lens distance based on distance to screen.
 */
#include "Arduino.h"

const int ULTRASONICPIN = 22; // pin corresponding to the ultrasonic sensor
const int SERVOPIN = 7; // pin corresponding to servo

const long FOCALLENGTH; // TODO: Find focal length.
const long LENSPOSITION; // Defined in terms of distance from sensor.
long objectDistance;

Ultrasonic ultrasonic(ULTRASONICPIN);

void setup() {
  Serial.begin(9600); // start serial measurement at 9600bps
}

void loop() {
  long range;
  long tgtPosition; // of object
  
  // 1. Get distance of screen.
  ultrasonic.DistanceMeasure();
  range = ultrasonic.microsecondsToCentimeters();
  //1a. Subtract distance to the lens
  
  // 2. Get desired lens position according to measured screen distance.
  tgtPosition = idealPosition(range, FOCALLENGTH, LENSPOSITON);
  //Adjusting the Object to the desired Position
  servo.MoveObj(tgtPosition);
  delay(100);
}

long idealPosition(long range, long focalLength, long lensPostion) {
  long dImage = range - lensPosition;
  long dObject = (float) 1 / focalLength - (float) 1 / dImage;
  long idealPosition = lensPosition - dObject;
  return idealPosition;
}

