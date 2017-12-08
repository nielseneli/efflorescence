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

Servo bloomLeft;
Servo turnLeft;
Servo bloomRight;
Servo turnRight;

// Servo edge values
// Bloom edges
int closed = 60;
int opened = 0;
int bloomDiff = 60;
// Turn edges
int enter = 35;
int leave = 85;
int turnDiff = 50;

// Set temp bloomPos variables to beginning vals
int bloomPos = closed;
int turnPos = enter;

// Initialize triggered-sensor-holding variable
int triggedSensors;

/* Write a position to all bloom motors */
void writeBlooms(int pos) {
  bloomLeft.write(pos);
  bloomRight.write(pos);
}


/* Functions to open and close the flowers */
void openBlooms(int &bloomPos) {
  bloomPos -= 5;
  bloomLeft.write(bloomPos);
  bloomRight.write(bloomPos);
}
void closeBlooms(int &bloomPos) {
  bloomPos += 5;
  bloomLeft.write(bloomPos);
  bloomRight.write(bloomPos);
}

/* Write a position to all turn motors */
void writeTurns(int pos) {
  turnLeft.write(pos);
  turnRight.write(pos);
}

/* Functions to turn and return the flowers */
void turn(int &turnPos) {
  turnPos += 5;
  turnLeft.write(turnPos);
  turnRight.write(120-turnPos);
}
void reTurn(int &turnPos) {
  turnPos -= 5;
  turnLeft.write(turnPos);
  turnRight.write(120-turnPos);
}

/* Returns value indicating which sensors are activated */
int whichSensors() {
  int whichSensors = 0;

  if (sensorTriggered(sensor0, 300, 700)) {
    whichSensors += 1;
  }
  if (sensorTriggered(sensor1, 250, 550)) {
    whichSensors += 2;
  }
  if (sensorTriggered(sensor2, 200, 700)) {
    whichSensors += 4;
  }
  if (sensorTriggered(sensor3, 150, 600)) {
    whichSensors += 8;
  }
  if (sensorTriggered(sensor4, 200, 750)) {
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
  bloomLeft.attach(3);
  turnLeft.attach(5);
  bloomRight.attach(6);
  turnRight.attach(9);

  // Set servos to starting position
  writeBlooms(bloomPos);
  writeTurns(turnPos);
}

void loop() {
  // test the sensors
//  sensorReadSerial();
  // Check which sensors are triggered
  triggedSensors = whichSensors();
  Serial.println(triggedSensors);

  // Move based on which sensors are triggered
  switch (triggedSensors) {
    case 1:                           /* 0         */
    case 3:                           /* 0 1       */
      // Begin turning
      if (turnPos >= enter && turnPos < enter + turnDiff/5) {
        turn(turnPos);
      }
      // Begin blooming
      if (bloomPos > opened) {
        openBlooms(bloomPos);
      }
    case 7:                           /* 0 1 2     */
    case 2:                           /*   1       */
      // Turn some more
      if (turnPos >= enter && turnPos < enter + turnDiff/3) {
        turn(turnPos);
      }
      // Bloom some more
      if (bloomPos > opened) {
        openBlooms(bloomPos);
      }
    case 6:                           /*   1 2     */
      // Keep on turning
      if (turnPos >= enter && turnPos < leave - turnDiff/3) {
        turn(turnPos);
      }
      // This is about when we want it to be fully bloomed
      if (bloomPos > opened) {
        openBlooms(bloomPos);
      }
    case 14:                          /*   1 2 3   */
    case 4:                           /*     2     */
    case 12:                          /*     2 3   */
      // Keep on turning
      if (turnPos >= enter && turnPos < leave - turnDiff/5) {
        turn(turnPos);
      }
      // Start unblooming
      if (bloomPos < closed) {
        closeBlooms(bloomPos);
      }
    case 28:                          /*     2 3 4 */
    case 8:                           /*       3   */
      // Keep on turning
      if (turnPos >= enter && turnPos < leave - turnDiff/5) {
        turn(turnPos);
      }
      // Keep unblooming
      if (bloomPos < closed) {
        closeBlooms(bloomPos);
      }
    case 24:                          /*       3 4 */
    case 16:                          /*         4 */
      // Keep on turning
      if (turnPos >= enter && turnPos < leave) {
        turn(turnPos);
      }
      // Start unblooming
      if (bloomPos < closed) {
        closeBlooms(bloomPos);
      }
    case 0:                          /*           */
      // Do nothing if they're both set already
      if (bloomPos == 60 && turnPos == 35) {
        break;
      }
      // Reset turn motor if bloom is set
      while (turnPos > 35 && bloomPos == 60) {
        reTurn(turnPos);
        delay(20);
      }
      // Reset bloom motor if turn is set
      while (bloomPos < 60 && turnPos == 35) {
        closeBlooms(bloomPos);
        delay(20);
      }
      // Turn them both if neither are set
      while (bloomPos < 60 && turnPos > 35) {
        closeBlooms(bloomPos);
        reTurn(turnPos);
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

