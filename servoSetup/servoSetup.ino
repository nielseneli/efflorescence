
#include <Servo.h>

// Initialize servos

Servo bloomLeft;
Servo turnLeft;
Servo bloomRight;
Servo turnRight;

int bloomPos = 60;
int turnPos = 35;

void setup() {
  Serial.begin(9600);
  
  // Attach servos
  bloomLeft.attach(5);
  turnLeft.attach(6);
  bloomRight.attach(10);
  turnRight.attach(11);
  Serial.println("attached");

  bloomLeft.write(bloomPos);
  bloomRight.write(bloomPos);
  turnLeft.write(turnPos);
  turnRight.write(140-turnPos);

}

void loop() {
  Serial.print(":)");

  // Uncomment to watch them turn and bloom
  for (bloomPos = 60; bloomPos >= 0; bloomPos -= 1) {
    bloomLeft.write(bloomPos);
    bloomRight.write(bloomPos);
    delay(30);
    Serial.println(bloomPos);
  }
  for (bloomPos = 0; bloomPos <= 60; bloomPos += 1) {
    bloomLeft.write(bloomPos);
    bloomRight.write(bloomPos);
    delay(30);
    Serial.println(bloomPos);
  }

  for (turnPos = 35; turnPos <= 105; turnPos += 1) {
    turnLeft.write(turnPos);
    turnRight.write(140-turnPos);
    delay(30);
    Serial.println(turnPos);
  }
  for (turnPos = 105; turnPos >= 35; turnPos -= 1) {
    turnLeft.write(turnPos);
    turnRight.write(140-turnPos);
    delay(30);
    Serial.println(turnPos);
  }
  delay(1000);
}
