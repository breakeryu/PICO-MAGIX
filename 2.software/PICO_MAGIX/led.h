#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "protocol.h"



enum TCOLOR{
    LEDC_RED = 0,   //0
    LEDC_GREEN,     //1
    LEDC_BLUE,      //2
    LEDC_BLACK,     //3
    LEDC_WHITE,     //4
    LEDC_GRAY,      //5
    LEDC_YELLOW,    //6  
    LEDC_GOLD,      //7
    LEDC_SkyBlue,   //8  
    LEDC_SeaGreen   //9 
};



#define NUM_OF_PIXELS   16  //灯带中灯珠总数
#define LED_STRIP_PIN   2   //灯带输出引脚名称



extern void ledStrip_Init(void);
extern void ledStrip_InitProtocol(void);
extern void ledStrip_SetAllPixelColor(TCOLOR color);
extern void ledStrip_TurnAllLedOff(void);
extern void ledStrip_ShowRainBow(void);
extern void ledStrip_ShowTheaterChase(void);

bool ledStrip_ReadCmd(uint16_t address);
void ledStrip_WriteCmd(uint16_t address, bool value);

void ledStrip_ParasCmd(void);
void ledStrip_ParaCmd_SysStatus(void);
void ledStrip_ParaCmd_TestModeStatus(void);
void ledStrip_ParaCmd_TheaterChaseModeStatus(void);
void ledStrip_ParaCmd_RainBowModeStatus(void);

void ledStrip_Run(void);
void ledStrip_RunOpenMode(void);
void ledStrip_RunTestMode(void);
void ledStrip_RunTheaterMode(void);
void ledStrip_RunRainBowMode(void);

static void ledStrip_TheaterChaseMode(uint32_t c,uint8_t wait);
static void ledStrip_RainBowMode(uint8_t wait);
static uint32_t Wheel(byte WheelPos);
static void mSetPixelColor(uint16_t n, TCOLOR color);

void core1_fun(void);
void core2_fun(void);


extern Adafruit_NeoPixel strip;
extern int ledState;
extern bool sysStatus;
#endif
