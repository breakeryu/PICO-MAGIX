#include "lcd.h"
#include "led.h"
#include "car_top.h"
#include "sensor.h"
#include "protocol.h"


void setup() {
  modbusSlave_Init();
  ledStrip_Init();
  ledStrip_InitProtocol();
  ledStrip_TurnAllLedOff();
  bsp_InitAllKeyPins();
  
}

void loop() {
  if(modbusSlave_poll()){
    deviceProcessCmd();
  }
  testStateMachine();
  
}

void setup1() {

  lcdInit();
  SensorSysInitAllSensor();

}

void loop1() {

  ledStrip_Run();

}
