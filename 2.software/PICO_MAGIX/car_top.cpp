#include "car_top.h"

int keyPin[8] = {3,10,11,12,13,14,15,28};
int keyValue[8];

SEM_EVENT_TYPE mNewEventNo = SE_RESET;
SEM_EVENT_TYPE mLastEventNo = SE_RESET;

void bsp_InitAllKeyPins(void){
  for(int i = 0; i < 8; i++){
    pinMode(keyPin[i],INPUT);
    keyValue[i] = 0;
  }
  ledInit();
  carSysVSInitAll();
  carSysVSDeductEx(mNewEventNo);
}

/*
 * 功能描述：PICO开发板灯初始化
 */
void ledInit(void){
    pinMode(DOOR1LED,OUTPUT);
    pinMode(DOOR2LED,OUTPUT);
    pinMode(DOOR3LED,OUTPUT);
    pinMode(DOOR4LED,OUTPUT);
    pinMode(LIGHTLED,OUTPUT);
    digitalWrite(DOOR1LED,HIGH);
    digitalWrite(DOOR2LED,HIGH);
    digitalWrite(DOOR3LED,HIGH);
    digitalWrite(DOOR4LED,HIGH);
    digitalWrite(LIGHTLED,HIGH);
}


bool ReadAllKeyPinState(void){

  return 0;
}


void log_PrintKeyState(void){
  for(int i = 0; i < 8; i++){
    Serial1.print("keyState");
    Serial1.print(i+1);
    Serial1.print(" : ");
    Serial1.print(digitalRead(keyPin[i]));
    Serial1.print("  ");
  }
  Serial1.println();
  delay(100);
}



void testStateMachine(void){
    //log_PrintKeyState();
    CarStateCheck();
}

void CarStateCheck(void){
  
  ReadAndCheckCarPowerState();
  ReadAndCheckCarLockedState();
  ReadAndCheckDoorLockedState();  
  ReadAndCheckDoor1State();
  ReadAndCheckDoor2State();
  ReadAndCheckDoor3State();
  ReadAndCheckDoor4State();
  ReadAndChecklightState();

}

bool powerNewState = TURNOFF;
bool powerLastState = TURNOFF;

void ReadAndCheckCarPowerState(void){

  if(digitalRead(keyPin[POWERKEY]) == 1){
    powerNewState = TURNON;
    if(powerNewState != powerLastState){
      mNewEventNo = eSysOpen;
      powerLastState = powerNewState;
      Serial1.println(" SYS OPEN !");
    }  
  }else{
    powerNewState = TURNOFF;
    if(powerNewState != powerLastState){
      mNewEventNo = eSysClose;
      powerLastState = powerNewState;
      Serial1.println(" SYS CLOSED !");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

bool carLockNewState = TURNOFF;
bool carLockLastState = TURNOFF;

void ReadAndCheckCarLockedState(void){

  if(digitalRead(keyPin[CARKEY]) == 1){
    carLockNewState = TURNON;
    if(carLockNewState != carLockLastState){
      mNewEventNo = eCarUnlock;
      carLockLastState = carLockNewState;
      Serial1.println(" CAR UNLOCK !");
    }  
  }else{
    carLockNewState = TURNOFF;
    if(carLockNewState != carLockLastState){
      mNewEventNo = eCarLocked;
      carLockLastState = carLockNewState;
      Serial1.println(" CAR LOCKED !");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

bool doorLockNewState = TURNOFF;
bool doorLockLastState = TURNOFF;

void ReadAndCheckDoorLockedState(void){

  if(digitalRead(keyPin[LOCK]) == 1){
    doorLockNewState = TURNON;
    if(doorLockNewState != doorLockLastState){
      mNewEventNo = eLockDoor;
      doorLockLastState = doorLockNewState;
      Serial1.println(" Door LOCKED !");
    }  
  }else{
    doorLockNewState = TURNOFF;
    if(doorLockNewState != doorLockLastState){
      mNewEventNo = eUnLockDoor;
      doorLockLastState = doorLockNewState;
      Serial1.println(" Door UNLOCK !");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

bool door1NewState = TURNOFF;
bool door1LastState = TURNOFF;

void ReadAndCheckDoor1State(void){

  if(digitalRead(keyPin[DOOR1]) == 1){
    door1NewState = TURNON;
    if(door1NewState != door1LastState){
      mNewEventNo = eOpenDoor1;
      door1LastState = door1NewState;
      Serial1.println(" Door1 ON");
    }  
  }else{
    door1NewState = TURNOFF;
    if(door1NewState != door1LastState){
      mNewEventNo = eCloseDoor1;
      door1LastState = door1NewState;
      Serial1.println(" Door1 OFF");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

bool door2NewState = TURNOFF;
bool door2LastState = TURNOFF;

void ReadAndCheckDoor2State(void){

  if(digitalRead(keyPin[DOOR2]) == 1){
    door2NewState = TURNON;
    if(door2NewState != door2LastState){
      mNewEventNo = eOpenDoor2;
      door2LastState = door2NewState;
      Serial1.println("Door2 ON");
    }  
  }else{
    door2NewState = TURNOFF;
    if(door2NewState != door2LastState){
      mNewEventNo = eCloseDoor2;
      door2LastState = door2NewState;
      Serial1.println("Door2 OFF");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}


bool door3NewState = TURNOFF;
bool door3LastState = TURNOFF;

void ReadAndCheckDoor3State(void){

  if(digitalRead(keyPin[DOOR3]) == 1){
    door3NewState = TURNON;
    if(door3NewState != door3LastState){
      mNewEventNo = eOpenDoor3;
      door3LastState = door3NewState;
      Serial1.println("Door3 ON");
    }  
  }else{
    door3NewState = TURNOFF;
    if(door3NewState != door3LastState){
      mNewEventNo = eCloseDoor3;
      door3LastState = door3NewState;
      Serial1.println("Door3 OFF");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}


bool door4NewState = TURNOFF;
bool door4LastState = TURNOFF;

void ReadAndCheckDoor4State(void){

  if(digitalRead(keyPin[DOOR4]) == 1){
    door4NewState = TURNON;
    if(door4NewState != door4LastState){
      mNewEventNo = eOpenDoor4;
      door4LastState = door4NewState;
      Serial1.println("Door4 ON");
    }  
  }else{
    door4NewState = TURNOFF;
    if(door4NewState != door4LastState){
      mNewEventNo = eCloseDoor4;
      door4LastState = door3NewState;
      Serial1.println("Door4 OFF");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

bool lightNewState = TURNOFF;
bool lightLastState = TURNOFF;

void ReadAndChecklightState(void){

  if(digitalRead(keyPin[LEDKEY]) == 1){
    lightNewState = TURNON;
    if(lightNewState != lightLastState){
      mNewEventNo = eChangeSwitchOn;
      lightLastState = lightNewState;
      Serial1.println("LED KEY ON");
    }  
  }else{
    lightNewState = TURNOFF;
    if(lightNewState != lightLastState){
      mNewEventNo = eChangeSwitchOff;
      lightLastState = lightNewState;
      Serial1.println("LED KEY OFF");
    } 
  }

  if(mNewEventNo != mLastEventNo){
    carSysVSDeductEx(mNewEventNo);
    mLastEventNo = mNewEventNo;
  }

}

void aTurnLightOff (void){
    digitalWrite(LIGHTLED,HIGH);
    Serial1.println("Light OFF");
}

void aTurnLightOn (void){
    digitalWrite(LIGHTLED,LOW);
    Serial1.println("Light ON");
}

void aTurnOffDoor1 (void){
    digitalWrite(DOOR1LED,HIGH);
    Serial1.println("Door1 OFF");
}

void aTurnOffDoor2 (void) {
    digitalWrite(DOOR2LED,HIGH);
    Serial1.print("Door2 OFF");
}

void aTurnOffDoor3 (void) {
    digitalWrite(DOOR3LED,HIGH);
    Serial1.println("Door3 OFF");
}

void aTurnOffDoor4 (void) {
    digitalWrite(DOOR4LED,HIGH);
    Serial1.print("Door4 OFF");
}

void aTurnOnDoor1 (void) {
    digitalWrite(DOOR1LED,LOW);
    Serial1.println("Door1 ON");
}

void aTurnOnDoor2 (void) {
    digitalWrite(DOOR2LED,LOW);
    Serial1.println("Door2 ON");
}

void aTurnOnDoor3 (void) {
    digitalWrite(DOOR3LED,LOW);
    Serial1.println("Door3 ON");
}

void aTurnOnDoor4 (void) {
    digitalWrite(DOOR4LED,LOW);
    Serial1.println("Door4 ON");
}
