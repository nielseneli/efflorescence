
#include <Servo.h>

// Initialize servos

Servo bloomLeft;
Servo turnLeft;
Servo bloomRight;
Servo turnRight;

int bloomPos = 60;
int turnPos = 85;

void setBloomServoPos(Servo &servo) {
  int currentPos = servo.read();
  int i;
  for (i = currentPos; i <= 60; i += 1) {
    servo.write(i);
    bloomRight.write(i);
    delay(20);
  }
}

void setTurnServoPos(Servo &servo) {
  int currentPos = servo.read();
  int i;
  for (i = currentPos; i >= 35; i -= 1) {
    turnLeft.write(i);
    turnRight.write(140 - i);
    delay(20);
  }
}

void setup() {
  // Attach servos
  bloomLeft.attach(5);
  turnLeft.attach(6);
  bloomRight.attach(10);
  turnRight.attach(11);

  

  Serial.begin(9600);
  Serial.println("attached");
  

}

void loop() {
  Serial.print(":)");

  // Uncomment to watch them turn and bloom
//  for (bloomPos = 60; bloomPos >= 5; bloomPos -= 1) {
//    bloomLeft.write(bloomPos);
//    bloomRight.write(bloomPos);
//    delay(30);
//    Serial.println(bloomPos);
//  }
//  for (bloomPos = 5; bloomPos <= 60; bloomPos += 1) {
//    bloomLeft.write(bloomPos);
//    bloomRight.write(bloomPos);
//    delay(30);
//    Serial.println(bloomPos);
//  }
//    delay(1000);
//
//  for (turnPos = 85; turnPos >= 10; turnPos -= 1) {
//    turnLeft.write(turnPos);
//    turnRight.write(turnPos);
//    delay(20);
//    Serial.println(turnPos);
//  }
//  for (turnPos = 10; turnPos <= 85; turnPos += 1) {
//    turnLeft.write(turnPos);
//    turnRight.write(turnPos);
//    delay(20);
//    Serial.println(turnPos);
//  }
}
