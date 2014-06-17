/*
  Projustor
  
  Adjusts lens distance based on distance to screen.
 */
#include "Arduino.h"
#include "Servo.h"
#include <math.h>

const int ULTRASONICPIN = 22; // pin corresponding to the ultrasonic sensor
const int SERVOPIN = 7; // pin corresponding to servo

const double FOCALLENGTH = 10.0;
const double P_LENS = 7.5; // Defined in terms of distance from sensor.
const double P_SERVO = -3.0; // TODO: Find.
const double TRACKHEIGHT = 10.1; // The height between the track and the servo.

double angleLast = 0.0;

Servo servo;

void setup() {
  Serial.begin(9600); // start serial measurement at 9600bps
  servo.attach(SERVOPIN);
  
  moveToAngle(90);
}

void loop() {
  // Quick note on naming:
  // p in a variable refers to position. Position is relative to the range sensor.
  // d in a variable refers to a distance. Distance must have two objects specified.
  //   Distance is a kind of a misnomer because we're measuring negative values. Whatevs.
  
  // 1a. Get position of screen.
  double pScreen = pulseToCm(measureDistance());
  Serial.print("pScreen: ");
  Serial.print(pScreen);
  
  // 1b. Get distance from lens to screen.
  double dLensImage = pScreen - P_LENS;
  
  // 2a. Calculate necessary distance from object to lens.
  double dLensObject = idealDObject(dLensImage);
  Serial.print("\t| dLensObject (cm): ");
  Serial.print(dLensObject);
  
  // 2b. Calculate necessary position of object.
  double pObject = P_LENS - dLensObject;
  
  // 3b. Calculate distance of object relative to servo.
  double dServoObject = pObject - P_SERVO;
  Serial.print("\t|dServoObject (cm): ");
  Serial.print(dServoObject);
  
  // 3b. Move the object to the desired position.
  int tgtAngle = angleForPos(dServoObject);
  Serial.print("\t| tgtAngle: ");
  Serial.print(tgtAngle);
  
  if (tgtAngle > 55 && tgtAngle < 125 && tgtAngle != angleLast) { 
    moveToAngle(tgtAngle);
    Serial.println(" | Moved");
    angleLast = tgtAngle;
  } else {
    Serial.println("");
  }
  
  delay(100);
}

long measureDistance(void) {
  pinMode(ULTRASONICPIN, OUTPUT);
  digitalWrite(ULTRASONICPIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(ULTRASONICPIN, HIGH);
  delayMicroseconds(5);
  
  digitalWrite(ULTRASONICPIN,LOW);
  pinMode(ULTRASONICPIN,INPUT);
  return pulseIn(ULTRASONICPIN,HIGH);
}

double pulseToCm(long pulseLength) {
  return (double) pulseLength / 58;
}

double idealDObject(double dImage) {
  return 1.0 / ( 1.0 / FOCALLENGTH - 1.0 / dImage );
}

int angleForPos(double newPos) {
  // https://casry.hackpad.com/Servo-Calculations-15QDaQiFuMh
  return (int) (90 + (atan(newPos / TRACKHEIGHT) * 180.0 / M_PI));
}

void moveToAngle(int angle) {
  servo.write(angle);
}

