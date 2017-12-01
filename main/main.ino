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

Servo bloom1;
Servo turn1;
Servo bloom2;
Servo turn2;
Servo bloom3;
Servo turn3;

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
  
  bloom1.attach(3);
  turn1.attach(5);
  bloom2.attach(6);
  turn2.attach(9);
  bloom3.attach(10);
  turn3.attach(11);

  bloom1.write(bloomPos);
  turn1.write(turnPos);
  bloom2.write(bloomPos);
  turn2.write(turnPos);
  bloom3.write(bloomPos);
  turn3.write(turnPos);  
}

void loop() {
//  // if sensor value surpasses threshold
//  Serial.print(sensor0.readRangeContinuousMillimeters());
//  Serial.print(',');
//  Serial.println(sensorTriggered(sensor0, 400, 600));

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

  switch (whichSensors) {
    // Sensor 0 is triggered
    case 1:
    case 2:
    case 3:
      if (bloomPos <= 0) {
        break;
      }
      bloomPos -= 5;
      bloom1.write(bloomPos);
      bloom2.write(bloomPos);
      bloom3.write(bloomPos);
      break;

    // Any of sensor 4, sensors 2 and 4, or sensors 0, 2, 4 are triggered
    case 16:
    case 20:
    case 21:
      if (bloomPos >= 80) {
        break;
      }
      bloomPos += 5;
      bloom1.write(bloomPos);
      bloom2.write(bloomPos);
      bloom3.write(bloomPos);
      break;

    // No sensors triggered
    case 0:
      if (bloomPos == 80) {
        break;
      }
      while (bloomPos < 81) {
        bloom1.write(bloomPos);
        bloom2.write(bloomPos);
        bloom3.write(bloomPos);
        bloomPos++;
        delay(20);
        Serial.println(bloomPos);
      }
      break;
  }
  delay(10);

//  
//  
//  if (sensorTriggered(sensor0, 400, 600)) {
//    // open petals
//    for (bloomPos = 80; bloomPos >= 0; bloomPos -= 1) {
//      bloom1.write(bloomPos);
//      bloom2.write(bloomPos);
//      bloom3.write(bloomPos);
//      delay(20);
//    }
//  
//    // turn flower to "follow" person through archway
//    for (turnPos = 35; turnPos <= 135; turnPos += 1) {
//      turn1.write(turnPos);
//      turn2.write(turnPos);
//      turn3.write(turnPos);
//      delay(20);
//    }
//
////    // play obnoxious melody
////    // iterate over the notes of the melody:
////    for (int thisNote = 0; thisNote < 8; thisNote++) {
////  
////      // to calculate the note duration, take one second divided by the note type.
////      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
////      int noteDuration = 1000 / noteDurations[thisNote];
////      tone(speaker, melody[thisNote], noteDuration);
////  
////      // to distinguish the notes, set a minimum time between them.
////      // the note's duration + 30% seems to work well:
////      int pauseBetweenNotes = noteDuration * 1.30;
////      delay(pauseBetweenNotes);
////      // stop the tone playing:
////      noTone(speaker);
////    }
////
//    // turn back to original position
//    for (turnPos = 135; turnPos >= 35; turnPos -= 1) {
//      turn1.write(turnPos);
//      turn2.write(turnPos);
//      turn3.write(turnPos);
//      delay(20);
//    }
//    
//    // close petals
//    for (bloomPos = 0; bloomPos <= 80; bloomPos += 1) {
//      bloom1.write(bloomPos);
//      bloom2.write(bloomPos);
//      bloom3.write(bloomPos);
//      delay(20);
//    }
//  }
}

