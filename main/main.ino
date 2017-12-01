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
    case 1:                           /* 0         */
      // Begin turning
      if (turnPos >= 35 && turnPos < 69) {
        turnPos += 5;
        turn0.write(turnPos);
        turn1.write(turnPos);
        turn2.write(turnPos);
      }
      // Begin blooming
      if (bloomPos > 0) {
        bloomPos -= 5;
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
      }
      break;
    case 5:                           /* 0   2     */
    case 4:                           /*     2     */
      // Bloom
      if (bloomPos > 0) {
        bloomPos -= 5;
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
      }
      // Turn
      if (turnPos >= 35 && turnPos < 101) {
        turnPos += 5;
        turn0.write(turnPos);
        turn1.write(turnPos);
        turn2.write(turnPos);
      }
      break;
    
    // Sensors 4 or 2,4 or 0,2,4 are triggered
    case 20:                          /*     2   4 */
    case 16:                          /*         4 */
      if (bloomPos < 80) {
        bloomPos += 5;
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
      }
      // Turn
      if (turnPos >= 35 && turnPos< 135) {
        turnPos += 5;
        turn0.write(turnPos);
        turn1.write(turnPos);
        turn2.write(turnPos);
      }
      break;
      
    // No sensors triggered
    case 0:                          /*           */
      // Do nothing if they're both set already
      if (bloomPos == 80 && turnPos == 135) {
        break;
      }
      // Reset turn motor if bloom is set
      while (turnPos < 136 && bloomPos == 80) {
        turn0.write(turnPos);
        turn1.write(turnPos);
        turn2.write(turnPos);
        turnPos++;
        delay(20);
      }
      // Reset bloom motor if turn is set
      while (bloomPos < 81 && turnPos == 135) {
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
        bloomPos++;
        delay(20);
        Serial.print(bloomPos);
        Serial.print(',');
        Serial.println(turnPos);
      }
      // Turn them both if neither are set
      while (bloomPos < 81 && turnPos < 136) {
        bloom0.write(bloomPos);
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
        turn0.write(turnPos);
        turn1.write(turnPos);
        turn2.write(turnPos);
        bloomPos++;
        turnPos++;
        delay(20);
        Serial.print(bloomPos);
        Serial.print(',');
        Serial.println(turnPos);
      }
  }
  delay(10);

}

