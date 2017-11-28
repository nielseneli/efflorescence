/*
  Sprint Two Integrate

  Causes flower to bloom and turn when the sensor detects motion
  within two feet of the front of the archway. Plays the C scale
  at the same time.
*/

#include <Servo.h>
#include "pitches.h"
#include "Sensor.h"

Servo bloom;
Servo turn;

const int speaker = 3;

int bloomPos = 80;
int turnPos = 35;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  sensorSetup();
//  bloom.attach(6);
//  turn.attach(10);
//
//  bloom.write(bloomPos);
//  turn.write(turnPos);
//  
//  Serial.begin(9600);
}

void loop() {
  sensorRead();
//  // read sensor value regularly
//  sensorVal = analogRead(sensor);
//  Serial.println(sensorVal);
//
//  // if sensor value surpasses threshold
//  if (sensorVal > 400) {
//
//    // open petals
//    for (bloomPos = 80; bloomPos >= 0; bloomPos -= 1) {
//      bloom.write(bloomPos);
//      delay(20);
//    }
//
//    // turn flower to "follow" person through archway
//    for (turnPos = 35; turnPos <= 135; turnPos += 1) {
//      turn.write(turnPos);
//      delay(20);
//    }
//
//    // play obnoxious melody
//    // iterate over the notes of the melody:
//    for (int thisNote = 0; thisNote < 8; thisNote++) {
//  
//      // to calculate the note duration, take one second divided by the note type.
//      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//      int noteDuration = 1000 / noteDurations[thisNote];
//      tone(speaker, melody[thisNote], noteDuration);
//  
//      // to distinguish the notes, set a minimum time between them.
//      // the note's duration + 30% seems to work well:
//      int pauseBetweenNotes = noteDuration * 1.30;
//      delay(pauseBetweenNotes);
//      // stop the tone playing:
//      noTone(speaker);
//    }
//
//    // turn back to original position
//    for (turnPos = 135; turnPos >= 35; turnPos -= 1) {
//      turn.write(turnPos);
//      delay(20);
//    }
//
//    // close petals
//    for (bloomPos = 0; bloomPos <= 80; bloomPos += 1) {
//      bloom.write(bloomPos);
//      delay(20);
//    }
//  }
}

