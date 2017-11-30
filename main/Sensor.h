/*
 * Sensor.h - Use 5 VL53L0X sensors
 */
#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

void sensorSetup();
void sensorReadInd(VL53L0X &sensor);
void sensorReadSerial();

#endif
