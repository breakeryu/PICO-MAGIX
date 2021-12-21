#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include <AHTxx.h>
#include <RP2040_init.h>
#include <Wire.h>


#define PIN_LIGHT_SENSOR  A0
#define PIN_GAS_SENSOR    A1
#define PIN_VSYS          A3

enum ANALOG_SENSOR_TYPE{
  T_LIGHT = 0,
  T_GAS,
  T_VSYS
};


void AhtSensorInit(void);
void AhtTestUnit(void);
void printStatus();

void lightSensor_Init(void);
void read_LightSensor(void);
int filter(ANALOG_SENSOR_TYPE mysensor);

extern ANALOG_SENSOR_TYPE _sensorType;
#endif

 
