#include "led.h"

int ledState = 0;

/*
 * 功能描述：PICO开发板灯初始化
 */
void ledInit(void){
  pinMode(PIN_LED,OUTPUT);
}

/*
 * 功能描述：双核测试——内核1运行函数，主要功能是间隔1s更新ledState变量，送入fifo
 */
void core1_fun(void){
  rp2040.fifo.push_nb(ledState);
  delay(1000);
  ledState = ~ledState;
}

/*
 * 功能描述：双核测试——内核2运行函数，主要功能是查询fifo中数据，
 *          接收fifo数据到tempState中，并更新led状态
 */       
void core2_fun(void){
   if(rp2040.fifo.available()){
    int tempState = rp2040.fifo.pop();
    if(tempState == 0){
      digitalWrite(PIN_LED,LOW);
    }else{
      digitalWrite(PIN_LED,HIGH);
    }
  }
}
