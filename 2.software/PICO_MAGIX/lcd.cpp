#include "lcd.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke library

/*
 * LCD初始化代码，如果要测试代码，将字符部分注释去掉
 * 
 */
void lcdInit(void){
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
//  tft.setTextColor(TFT_GREEN, TFT_BLACK);
//  tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);
//  tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
//  tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
//  tft.drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
}
