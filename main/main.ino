/*
  Main

  Causes flower to bloom and turn when the sensor detects motion
  within two feet of the front of the archway. Plays the C scale
  at the same time.
*/

#include <Servo.h>
#include "pitches.h"
#include "Sensor.h"
#include <VL53L0X.h>

// Initialize VL53L0X sensors
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;

// Initialize sensor value holders

Servo bloom1;
Servo turn1;
Servo bloom2;
Servo turn2;
Servo bloom3;
Servo turn3;

//const int speaker = 3;

int bloomPos = 80;
int turnPos = 35;

int sensorVal = 0;

//// notes in the melody:
//int melody[] = {
//  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
//};
//
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
//int noteDurations[] = {
//  4, 8, 8, 4, 4, 4, 4, 4
//};

void setup() {
  sensorSetup();
  
  bloom1.attach(3);
  turn1.attach(5);
  bloom2.attach(6);
  turn2.attach(9);
  bloom3.attach(10);
  turn3.attach(11);

  bloom1.write(bloomPos);
  turn1.write(turnPos);
  bloom2.write(bloomPos);
  turn2.write(turnPos);
  bloom3.write(bloomPos);
  turn3.write(turnPos);  
}

void loop() {
  // if sensor value surpasses threshold
  Serial.print(sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.println(sensorTriggered(sensor1, 400, 600));
}

