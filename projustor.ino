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
const double LENSPOSITION = 10.0; // Defined in terms of distance from sensor.
const double SERVOPOSITION = 5.0; // TODO: Find.
const double TRACKHEIGHT = 10.0; // The height between the track and the servo.
long objectDistance;

Servo servo;

void setup() {
  Serial.begin(9600); // start serial measurement at 9600bps
  servo.attach(SERVOPIN);
}

void loop() {
  long pulse;
  double range;
  double tgtPosition; // of object
  int tgtAngle;
  
  // 1. Get distance from lens to screen.
  pulse = measureDistance();
  Serial.print("Pulse Length (ms): ");
  Serial.print(pulse);
  
  range = pulseToCm(pulse) - LENSPOSITION;
  Serial.print("\t| Screen Position (cm): ");
  Serial.print(range);
  
  // 2. Get desired lens position according to measured screen distance.
  tgtPosition = idealPosition(range);
  Serial.print("\t| Target Position (cm): ");
  Serial.print(tgtPosition);
  
  // 3. Move the object to the desired position.
  tgtAngle = angleForPos(tgtPosition);
  Serial.print("\t| Angle: ");
  Serial.print(tgtAngle);
  
  moveToPos(tgtAngle);
  Serial.println(" | Moved");
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

double idealPosition(double range) {
  double dImage = range - LENSPOSITION;
  double dObject = (double) 1 / FOCALLENGTH - (double) 1 / dImage;
  
  double idealPosition = LENSPOSITION - dObject;
  return idealPosition;
}

int angleForPos(double newPos) {
  double servoRelativePos = newPos - SERVOPOSITION;
  // https://casry.hackpad.com/Servo-Calculations-15QDaQiFuMh
  return (int) ((atan(servoRelativePos / TRACKHEIGHT) * 180.0 / PI) + 90);
}

void moveToPos(int angle) {
  servo.write(angle);
}

