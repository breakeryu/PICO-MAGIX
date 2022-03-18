#include "lcd.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke library

/*
 * LCD初始化代码，如果要测试代码，将字符部分注释去掉
 * 
 */
void lcdInit(void){
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
}



