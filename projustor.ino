/*
  Projustor
  
  Adjusts lens distance based on distance to screen.
 */
#include "Arduino.h"
#include "Servo.h"
#include "ProjustorServo.h"
#include "UltrasonicRangeSensor.h"

const int ULTRASONICPIN = 22; // pin corresponding to the ultrasonic sensor
const int SERVOPIN = 7; // pin corresponding to servo

const long FOCALLENGTH = 10; // TODO: Find focal length.
const long LENSPOSITION = 10; // Defined in terms of distance from sensor.
const long TRACKHEIGHT = 10; // The height between the track and the servo.
long objectDistance;

Ultrasonic ultrasonic(ULTRASONICPIN);
ProjustorServo servo(SERVOPIN);

void setup() {
  Serial.begin(9600); // start serial measurement at 9600bps
}

void loop() {
  long tgtPosition; // of object
  
  // 1. Get distance from lens to screen.
  ultrasonic.DistanceMeasure();
  long range = ultrasonic.microsecondsToCentimeters() - LENSPOSITION;
  
  // 2. Get desired lens position according to measured screen distance.
  tgtPosition = idealPosition(range, FOCALLENGTH, LENSPOSITION);
  
  // 3. Move the object to the desired position.
  servo.MoveObjToPos(tgtPosition, TRACKHEIGHT);
  delay(100);
}

long idealPosition(long range, long focalLength, long lensPosition) {
  long dImage = range - lensPosition;
  long dObject = (long) 1 / focalLength - (long) 1 / dImage;
  long idealPosition = lensPosition - dObject;
  return idealPosition;
}

