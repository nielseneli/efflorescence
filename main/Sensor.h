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
int sensorTriggered(VL53L0X &sensor, int minEdge, int maxEdge);
//void whichSensorTriggered(VL53L0X &sensor0, VL53L0X &sensor1, VL53L0X &sensor2, VL53L0X &sensor3, VL53L0X &sensor4, int sensorVals, int minVals, int maxVals);
void sensorReadSerial();

#endif
