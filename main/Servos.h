/*
 * Servos.h - Code for the servos, partitioned for readability
 */
#ifndef Servos_h
#define Servos_h

#include <Arduino.h>
#include <Servo.h>

void openBlooms(int &bloomPos);
void closeBlooms(int &bloomPos);
void turn(int &turnPos);
void reTurn(int &turnPos);

#endif
