/*
  Sprint One Integrate
  Causes flower to open and close when the sensor sees something within it's threshold.
 
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int sensorPin = A0;
int sensorVal = 0;
int startPos = 80;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  sensorVal = analogRead(sensorPin);
  Serial.println(sensorVal);
  //myservo.write(startPos);

  if (sensorVal > 300) {
    for (pos = 80; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                       // waits 15ms for the servo to reach the position
    }
    delay(500);
    for (pos = 0; pos <= 80; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                       // waits 15ms for the servo to reach the position
    }
    }
}
