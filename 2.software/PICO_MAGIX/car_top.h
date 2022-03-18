#ifndef _CAR_TOP_H_
#define _CAR_TOP_H_

#include <Arduino.h>

#include "carSys.h"



#define   DOOR1  0
#define   DOOR2  1 
#define   DOOR3  2
#define   DOOR4  3
#define   LOCK   4
#define   CARKEY 7
#define   LEDKEY 6
#define   POWERKEY 5


#define DOOR1LED 22
#define DOOR2LED 23
#define DOOR3LED 24
#define DOOR4LED 25
#define LIGHTLED 17


#define TURNON   1
#define TURNOFF  0

void bsp_InitAllKeyPins(void);
void ledInit(void);
bool ReadAllKeyPinState(void);
void log_PrintKeyState(void);
void testStateMachine(void);



void CarStateCheck(void);
void ReadAndCheckCarPowerState(void);
void ReadAndCheckCarLockedState(void);
void ReadAndCheckDoorLockedState(void);
void ReadAndCheckDoor1State(void);
void ReadAndCheckDoor2State(void);
void ReadAndCheckDoor3State(void);
void ReadAndCheckDoor4State(void);
void ReadAndChecklightState(void);


void aTurnLightOff (void);
void aTurnLightOn (void);
void aTurnOffDoor1 (void);
void aTurnOffDoor2 (void);
void aTurnOffDoor3 (void);
void aTurnOffDoor4 (void);
void aTurnOnDoor1 (void);
void aTurnOnDoor2 (void);
void aTurnOnDoor3 (void);
void aTurnOnDoor4 (void);

#endif
