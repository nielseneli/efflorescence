/*
 * Sensor.h - Use 5 VL53L0X sensors
 */
#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

void sensorSetup();
void modifySomething(int something);
void sensorReadVals(int sensorVal1, int sensorVal2, int sensorVal3, int sensorVal4, int sensorVal5);
void sensorReadSerial();

#endif
