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

// Initialize servos
Servo bloom0;
Servo turn0;
Servo bloom1;
Servo turn1;
Servo bloom2;
Servo turn2;
Servo bloom3;
Servo turn3;

// Servo edge values
// Bloom edges
int closed = 60;
int opened = 0;
// Turn edges
int enter = 35;
int leave = 85;

// Set temp bloomPos variables to beginning vals
int bloomPos = closed;
int turnPos = enter;

// Initialize triggered-sensor-holding variable
int triggedSensors;

/* Write a position to all bloom motors */
void writeBlooms(int pos) {
  bloom0.write(pos);
  bloom1.write(pos);
  bloom2.write(pos);
  bloom3.write(pos);
}

/* Write a position to all turn motors */
void writeTurns(int pos) {
  turn0.write(pos);
  turn1.write(pos);
  turn2.write(pos);
  turn3.write(pos);
}

/* Returns value indicating which sensors are activated */
int whichSensors() {
  int whichSensors = 0;

  if (sensorTriggered(sensor0, 300, 700)) {
     whichSensors += 1;
  }
  if (sensorTriggered(sensor1, 400, 600)) {
     whichSensors += 2;
  }
  if (sensorTriggered(sensor2, 300, 450)) {
     whichSensors += 4;
  }
  if (sensorTriggered(sensor3, 400, 600)) {
     whichSensors += 8;
  }
  if (sensorTriggered(sensor4, 300, 700)) {
     whichSensors += 16;
  }
  return whichSensors;
}

void setup() {
  // Set unique IDs for the sensors
  sensorsRename();
  // Begin continuous read mode on sensors
  sensorsBegin();

  // Attach servos
  bloom0.attach(2);
  turn0.attach(3);
  bloom1.attach(10);
  turn1.attach(11);
  bloom2.attach(4);
  turn2.attach(5);
  bloom3.attach(12);
  turn3.attach(13);

  // Set servos to starting position
  writeBlooms(bloomPos);
  writeTurns(turnPos);  
}

void loop() {
  // Check which sensors are triggered
  triggedSensors = whichSensors();

  // Move based on which sensors are triggered
  switch (triggedSensors) {
    case 1:                           /* 0         */
      // Begin turning
      if (turnPos >= 35 && turnPos < 48) {
        turnPos += 5;
        writeTurns(turnPos);
      }
      // Begin blooming
      if (bloomPos > 0) {
        bloomPos -= 5;
        writeBlooms(bloomPos);
      }
      break;
    case 5:                           /* 0   2     */
    case 4:                           /*     2     */
      // Bloom
      if (bloomPos > 0) {
        bloomPos -= 5;
        writeBlooms(bloomPos);
      }
      // Turn
      if (turnPos >= 35 && turnPos < 62) {
        turnPos += 5;
        writeTurns(turnPos);
      }
      break;
    
    // Sensors 4 or 2,4 or 0,2,4 are triggered
    case 20:                          /*     2   4 */
    case 16:                          /*         4 */
      if (bloomPos < 60) {
        bloomPos += 5;
        writeBlooms(bloomPos);
      }
      // Turn
      if (turnPos >= 35 && turnPos< 85) {
        turnPos += 5;
        writeTurns(turnPos);
      }
      break;
      
    // No sensors triggered
    case 0:                          /*           */
      // Do nothing if they're both set already
      if (bloomPos == 60 && turnPos == 35) {
        break;
      }
      // Reset turn motor if bloom is set
      while (turnPos > 35 && bloomPos == 60) {
        writeTurns(turnPos);
        turnPos--;
        delay(20);
      }
      // Reset bloom motor if turn is set
      while (bloomPos < 60 && turnPos == 35) {
        writeBlooms(bloomPos);
        bloomPos++;
        delay(20);
      }
      // Turn them both if neither are set
      while (bloomPos < 60 && turnPos > 35) {
        bloomPos++;
        turnPos--;
        writeBlooms(bloomPos);
        writeTurns(turnPos);
        delay(20);
      }
  }

  // Uncomment to simplify debugging
//  Serial.print(triggedSensors);
//  Serial.print(',');
//  Serial.print(bloomPos);
//  Serial.print(',');
//  Serial.println(turnPos);
  delay(100);

}

