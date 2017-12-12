/*
 * Servos.cpp - Code for the servos, partitioned for readability
 */

#include "Servos.h"

// Initialize servos
extern Servo bloomLeft;
extern Servo turnLeft;
extern Servo bloomRight;
extern Servo turnRight;

void servosAttach() {
  bloomLeft.attach(5);
  turnLeft.attach(6);
  bloomRight.attach(10);
  turnRight.attach(11);
}

/* Write to the bloom servos */
void writeBlooms(int &bloomPos) {
  bloomLeft.write(bloomPos);
  bloomRight.write(bloomPos);
}

/* Write to the turn servos */
void writeTurns(int &turnPos) {
  turnLeft.write(turnPos);
  turnRight.write(140 - turnPos);
}

/* Functions to open and close the flowers */
void openBlooms(int &bloomPos) {
  bloomPos -= 10;
  writeBlooms(bloomPos);
}
void closeBlooms(int &bloomPos) {
  bloomPos += 10;
  writeBlooms(bloomPos);
}

/* Functions to turn and return the flowers */
void turn(int &turnPos) {
  turnPos += 10;
  writeTurns(turnPos);
  delay(10);
}
void reTurn(int &turnPos) {
  turnPos -= 10;
  writeTurns(turnPos);
  delay(10);
}
