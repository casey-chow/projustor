/*
  Projustor
  
  Adjusts lens distance based on distance to screen.
 */
#include "Arduino.h"
#define 

Ultrasonic ultrasonic(7);
const long FOCALLENGTH; // TODO: Find focal length.
const long LENSPOSITION; // Defined in terms of distance from sensor.
long objectDistance;


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
  tgtPosition = getIdealPosition(range, FOCALLENGTH, LENSPOSITON);
  //Adjusting the Object to the desired Position
  if (objectDistance < tgtPosition)
  delay(100);
}

long getIdealPosition(long range, long focalLength, long lensPostion) {
  long dImage = range - lensPosition;
  long dObject = (float) 1 / focalLength - (float) 1 / dImage;
  long idealPosition = lensPosition - dObject;
  return idealPosition;
}
