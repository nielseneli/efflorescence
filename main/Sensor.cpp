/*
 * Sensor.c - Use 5 VL53L0X sensors
 */
 
#include "Sensor.h"

// Initialize VL53L0X sensors
extern VL53L0X sensor0;
extern VL53L0X sensor1;
extern VL53L0X sensor2;
extern VL53L0X sensor3;
extern VL53L0X sensor4;

extern int sensorVals[];
extern int minVals[];
extern int maxVals[];

void sensorSetup() {
  // Initialize shutdown pins
  const int SHDN0 = 4;
  const int SHDN1 = 12;
  const int SHDN2 = 7;
  const int SHDN3 = 13;
  const int SHDN4 = 8;

  // Set shutdown pins to output mode
  pinMode(SHDN0, OUTPUT);
  pinMode(SHDN1, OUTPUT);
  pinMode(SHDN2, OUTPUT);
  pinMode(SHDN3, OUTPUT);
  pinMode(SHDN4, OUTPUT);

  // Pull all shutdown pins low
  digitalWrite(SHDN0, LOW);
  digitalWrite(SHDN1, LOW);
  digitalWrite(SHDN2, LOW);
  digitalWrite(SHDN3, LOW);
  digitalWrite(SHDN4, LOW);
  delay(500);

  // Begin
  Wire.begin();
  Serial.begin (9600);

  // Set address for first sensor
  digitalWrite(SHDN0, HIGH);
  delay(150);
  sensor0.init(true);
  delay(100);
  sensor0.setAddress((uint8_t)21);

  // Set address for second sensor
  digitalWrite(SHDN1, HIGH);
  delay(150);
  sensor1.init(true);
  delay(100);
  sensor1.setAddress((uint8_t)22);

  // Set address for third sensor
  digitalWrite(SHDN2, HIGH);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress((uint8_t)23);

  // Set address for fourth sensor
  digitalWrite(SHDN3, HIGH);
  delay(150);
  sensor3.init(true);
  delay(100);
  sensor3.setAddress((uint8_t)24);

  // Set address for fifth sensor
  digitalWrite(SHDN4, HIGH);
  delay(150);
  sensor4.init(true);
  delay(100);
  sensor4.setAddress((uint8_t)25);

  sensor0.startContinuous();
  sensor1.startContinuous();
  sensor2.startContinuous();
  sensor3.startContinuous();
  sensor4.startContinuous();
}

void sensorReadInd(VL53L0X &sensor) {
  Serial.println(sensor.readRangeContinuousMillimeters());
}

int sensorTriggered(VL53L0X &sensor, int minEdge, int maxEdge) {
  if (sensor.readRangeContinuousMillimeters() > minEdge && sensor.readRangeContinuousMillimeters() < maxEdge) {
    return 1; 
  }
  else {
    return 0;
  }
}

void sensorReadSerial() {
  Serial.print(sensor0.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor2.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor3.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor4.readRangeContinuousMillimeters());
  Serial.println();
}
