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
VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;

VL53L0X sensors[] = {
  sensor0, sensor1, sensor2, sensor3, sensor4
};

// Initialize sensor value holder array
int sensorVals[] = {
  0, 0, 0, 0, 0
};

// Initialize bounds arrays
int minVals[] = {
  400, 400, 400, 400, 400
};
int maxVals[] = {
  600, 600, 600, 600, 600
};

Servo bloom0;
Servo turn0;
Servo bloom1;
Servo turn1;
Servo bloom2;
Servo turn2;

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
  
  bloom0.attach(3);
  turn0.attach(5);
  bloom1.attach(6);
  turn1.attach(9);
  bloom2.attach(10);
  turn2.attach(11);

  bloom0.write(bloomPos);
  turn0.write(turnPos);
  bloom1.write(bloomPos);
  turn1.write(turnPos);
  bloom2.write(bloomPos);
  turn2.write(turnPos);  
}

void loop() {
  // Figure out which sensors are triggered
  int whichSensors = 0;

  if (sensorTriggered(sensor0, 400, 600)) {
     whichSensors += 1;
  }
  if (sensorTriggered(sensor1, 400, 600)) {
     whichSensors += 2;
  }
  if (sensorTriggered(sensor2, 400, 600)) {
     whichSensors += 4;
  }
  if (sensorTriggered(sensor3, 400, 600)) {
     whichSensors += 8;
  }
  if (sensorTriggered(sensor4, 400, 600)) {
     whichSensors += 16;
  }

  Serial.println(whichSensors);

  // Move based on which sensors are triggered
  switch (whichSensors) {
    // Sensors 0 or 2 or 0,2 are triggered
    case 1:
    case 4:
    case 5:
      if (bloomPos <= 0) {
        break;
      }
      bloomPos -= 5;
      bloom0.write(bloomPos);
      bloom1.write(bloomPos);
      bloom2.write(bloomPos);
      break;

    // Sensors 4 or 2,4 or 0,2,4 are triggered
    case 16:
    case 20:
    case 21:
      if (bloomPos >= 80) {
        break;
      }
      bloomPos += 5;
      bloom0.write(bloomPos);
      bloom1.write(bloomPos);
      bloom2.write(bloomPos);
      break;

    // No sensors triggered
    case 0:
      if (bloomPos == 80) {
        break;
      }
      while (bloomPos < 81) {
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
        bloomPos++;
        delay(20);
        Serial.println(bloomPos);
      }
      break;
  }
  delay(10);

}

