#include "lcd.h"
#include "led.h"


void setup() {
  lcdInit();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  core1_fun();
}
 
void setup1() {
  // put your setup code here, to run once:
  ledInit();
}

void loop1() {
  // put your main code here, to run repeatedly:
  core2_fun(); 
}
