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
const int closed = 60;
const int opened = 0;
const int bloomDiff = 60;
// Turn edges
const int enter = 35;
const int leave = 105;
const int turnDiff = 70;

// millis
unsigned long prevMillis = 0;
const int checkDelay = 1000;

// Set temp bloomPos variables to beginning vals
int bloomPos = closed;
int turnPos = enter;

// Initialize triggered-sensor-holding variable
int triggedSensors;

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

/* Functions to turn and return the flowers */
void turn(int &turnPos) {
  turnPos += 5;
  turnLeft.write(turnPos);
  turnRight.write(140-turnPos);
  delay(10);
}
void reTurn(int &turnPos) {
  turnPos -= 5;
  turnLeft.write(turnPos);
  turnRight.write(140-turnPos);
  delay(10);
}

/* Returns value indicating which sensors are activated */
int whichSensors() {
  int whichSensors = 0;

  if (sensorTriggered(sensor0, 250, 900)) {
    whichSensors += 1;
  }
  if (sensorTriggered(sensor1, 250, 900)) {
    whichSensors += 2;
  }
  if (sensorTriggered(sensor2, 150, 900)) {
    whichSensors += 4;
  }
  if (sensorTriggered(sensor3, 300, 1000)) {
    whichSensors += 8;
  }
  if (sensorTriggered(sensor4, 250, 1000)) {
    whichSensors += 16;
  }
  return whichSensors;
}

void setup() {
  // Set unique IDs for the sensors
  sensorsRename();
  // Begin continuous read mode on sensors
  sensorsBegin();
  Serial.println("everything still fine");
  // Attach servos
  bloomLeft.attach(5);
  turnLeft.attach(6);
  bloomRight.attach(10);
  turnRight.attach(11);

  // Set servos to starting position
  bloomLeft.write(bloomPos);
  turnLeft.write(turnPos);
  bloomRight.write(bloomPos);
  turnRight.write(140-turnPos);
}

void loop() {
  // test the sensors
//  sensorReadSerial();
  // Check which sensors are triggered
  triggedSensors = whichSensors();
  Serial.print(triggedSensors);
  Serial.print(",");
  sensorReadSerial();

//  while (bloomPos >= opened) {
//    openBlooms(bloomPos);
//    delay(50);
//  }
//  while (bloomPos <= closed) {
//    closeBlooms(bloomPos);
//    delay(50);
//  }
//  while (turnPos <= leave) {
//    turn(turnPos);
//    delay(50);
//  }
//  while (turnPos >= enter) {
//    reTurn(turnPos);
//    delay(50);
//  }

  // Move based on which sensors are triggered
//  switch (triggedSensors) {
//    case 1:                           /* 0         */
//    case 3:                           /* 0 1       */
//      prevMillis = millis();
//      // Begin turning
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // Begin blooming
//      if (bloomPos > opened) {
//        openBlooms(bloomPos);
//      }
//      break;
//    case 7:                           /* 0 1 2     */
//    case 2:                           /*   1       */
//      prevMillis = millis();
//      // Turn some more
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // Bloom some more
//      if (bloomPos > opened) {
//        openBlooms(bloomPos);
//      }
//      break;
//    case 6:                           /*   1 2     */
//      prevMillis = millis();
//      // Keep on turning
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // This is about when we want it to be fully bloomed
//      if (bloomPos > opened) {
//        openBlooms(bloomPos);
//      }
//      break;
//    case 14:                          /*   1 2 3   */
//    case 4:                           /*     2     */
//    case 12:                          /*     2 3   */
//      prevMillis = millis();
//      // Keep on turning
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // Start unblooming
//      if (bloomPos > enter) {
//        openBlooms(bloomPos);
//      }
//      break;
//    case 28:                          /*     2 3 4 */
//    case 8:                           /*       3   */
//      prevMillis = millis();
//      // Keep on turning
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // Keep unblooming
//      if (bloomPos < closed) {
//        closeBlooms(bloomPos);
//      }
//      break;
//    case 24:                          /*       3 4 */
//    case 16:                          /*         4 */
//      prevMillis = millis();
//      // Keep on turning
//      if (turnPos >= enter && turnPos < leave) {
//        turn(turnPos);
//      }
//      // Start unblooming
//      if (bloomPos < closed) {
//        closeBlooms(bloomPos);
//      }
//      break;
//    case 0:                          /*           */
//      // check millis
//      int currentMillis = millis();
//      if (currentMillis - prevMillis <= checkDelay) {
//        break;
//      }
//      // Do nothing if they're both set already
//      if (bloomPos == 60 && turnPos == 35) {
//        break;
//      }
//      // Reset turn motor if bloom is set
//      while (turnPos > 35 && bloomPos == 60) {
//        reTurn(turnPos);
//        delay(30);
//      }
//      // Reset bloom motor if turn is set
//      while (bloomPos < 60 && turnPos == 35) {
//        closeBlooms(bloomPos);
//        delay(30);
//      }
//      // Turn them both if neither are set
//      while (bloomPos < 60 && turnPos > 35) {
//        closeBlooms(bloomPos);
//        reTurn(turnPos);
//        delay(30);
//      }
//  }
//  

  // Uncomment to simplify debugging
  //  Serial.print(triggedSensors);
  //  Serial.print(',');
  //  Serial.print(bloomPos);
  //  Serial.print(',');
  //  Serial.println(turnPos);

}

