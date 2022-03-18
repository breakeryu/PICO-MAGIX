#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include "lcd.h"
#include "pico/stdlib.h"
#include "protocol.h"
#include <AHTxx.h>
#include <Wire.h>
#include "src/vl6180/vl6180x.h"



#define MYFONT  1 //6*6
#define FILTER_N 20
#define PIN_LIGHT_SENSOR  A0
#define PIN_GAS_SENSOR    A1
#define PIN_VSYS          A3

#define PIN_ALX_SDA       6
#define PIN_ALX_SCL       7


enum ANALOG_SENSOR_TYPE{
  T_LIGHT = 0,
  T_GAS,
  T_VSYS
};


bool ReadAllSensorsDate(struct repeating_timer *t);
void SensorSysInitAllSensor(void);

void sensor_WriteSingleHoldingRegister(uint16_t address,uint16_t date);
void sensor_update_SysVoltage(float voltage);
void sensor_update_gasDensity(uint16_t desity);
void sensor_update_lightIntensity(uint16_t intensity);
void sensor_update_Distance(uint16_t distance);
void sensor_update_Temperture(float temperture);
void sensor_update_Humidity(float humidity);


int Filter(int Pin);
int ReadAnalogSensorType(ANALOG_SENSOR_TYPE mysensor);

void AhtSensorInit(void);
void AhtTestUnit(void);

void vl6180x_Init(void);
void Run_Vl6180_RW_RegisterMode(void);
bool VL6180x_RW_IsReadEnable(void);
bool VL6180x_RW_IsWriteEnable(void);
bool VL6180x_R_IsReadResultEnable(void);
void VL6180x_WriteAll_RW_Registers(void);
void VL6180x_ReadAll_RW_Registers(void);
void VL6180x_ReadOnly_R_Registers(void);
void Vl6180_Start_Range_Measurement(void);
void Vl6180_Read_RangeData(void);


void GasSensorInit(void);
void ReadGasSensor(void);

void SysVoltageSensorInit(void);
void ReadVoltageSensor(void);

void lightSensorInit(void);
void ReadLightSensor(void);



extern ANALOG_SENSOR_TYPE _sensorType;

#endif /* _SENSOR_H_ */
