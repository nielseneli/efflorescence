/*
 * Sensor.c - Use 5 VL53L0X sensors
 */
 
#include "Sensor.h"

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;
VL53L0X sensor5;

void sensorSetup() {
  const int SHDN1 = 4;
  const int SHDN2 = 12;
  const int SHDN3 = 7;
  const int SHDN4 = 13;
  const int SHDN5 = 8;

  // Set shutdown pins to output mode
  pinMode(SHDN1, OUTPUT);
  pinMode(SHDN2, OUTPUT);
  pinMode(SHDN3, OUTPUT);
  pinMode(SHDN4, OUTPUT);
  pinMode(SHDN5, OUTPUT);

  // Pull all shutdown pins low
  digitalWrite(SHDN1, LOW);
  digitalWrite(SHDN2, LOW);
  digitalWrite(SHDN3, LOW);
  digitalWrite(SHDN4, LOW);
  digitalWrite(SHDN5, LOW);
  delay(500);

  // Begin
  Wire.begin();
  Serial.begin (9600);

  // Set address for first sensor
  digitalWrite(SHDN1, HIGH);
  delay(150);
  sensor1.init(true);
  delay(100);
  sensor1.setAddress((uint8_t)21);

  // Set address for second sensor
  digitalWrite(SHDN2, HIGH);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress((uint8_t)22);

  // Set address for third sensor
  digitalWrite(SHDN3, HIGH);
  delay(150);
  sensor3.init(true);
  delay(100);
  sensor3.setAddress((uint8_t)23);

  // Set address for fourth sensor
  digitalWrite(SHDN4, HIGH);
  delay(150);
  sensor4.init(true);
  delay(100);
  sensor4.setAddress((uint8_t)24);

  // Set address for fifth sensor
  digitalWrite(SHDN5, HIGH);
  delay(150);
  sensor5.init(true);
  delay(100);
  sensor5.setAddress((uint8_t)25);

  sensor1.startContinuous();
  sensor2.startContinuous();
  sensor3.startContinuous();
  sensor4.startContinuous();
  sensor5.startContinuous();
}

void sensorRead() {
  Serial.print(sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor2.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor3.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor4.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(sensor5.readRangeContinuousMillimeters());
  Serial.println();
  
//  // Uncomment to check for device addresses
//  Serial.println ("I2C scanner. Scanning ...");
//  byte count = 0;
//
//
//  for (byte i = 1; i < 120; i++)
//  {
//
//    Wire.beginTransmission (i);
//    if (Wire.endTransmission () == 0)
//    {
//      Serial.print ("Found address: ");
//      Serial.print (i, DEC);
//      Serial.print (" (0x");
//      Serial.print (i, HEX);
//      Serial.println (")");
//      count++;
//      delay (1);
//    } // end of good response
//  } // end of for loop
//  Serial.println ("Done.");
//  Serial.print ("Found ");
//  Serial.print (count, DEC);
//  Serial.println (" device(s).");
//
//  delay(3000);
}
