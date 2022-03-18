#include "led.h"


//todo 目前测试各个功能正常，下一步可以进一步封装函数


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_PIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

int ledState = 0;

uint8_t colorTable[][3] =
{
  { 255, 0  , 0   },      //LEDC_RED
  { 0  , 255, 0   },      //LEDC_GREEN
  { 0  , 0  , 255 },      //LEDC_BLUE 
  { 0  , 0  , 0   },      //LEDC_BLACK 
  { 255, 255, 255 },      //LEDC_WHITE 
  { 190, 190, 190 },      //LEDC_GRAY  
  { 255, 255, 0   },      //LEDC_YELLOW
  { 255, 215, 0   },      //LEDC_GOLD   
  { 135, 206, 235 },      //LEDC_SkyBlue
  { 84 , 255, 159 },      //LEDC_SeaGreen

};


bool sysStatus = false;
bool testModeStatus = false;
bool theaterChaseModeStatus = false;
bool rainBowModeStatus = false;

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

    }else{

    }
  }
}



void ledStrip_Init(void)
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}


static void ledStrip_TheaterChaseMode(uint32_t c,uint8_t wait)
{

    for (int j = 0; j < 10; j++) {                      //do 10 cycles of chasing
        for (int q = 0; q < 2; q++) {
            for (int i = 0; i < NUM_OF_PIXELS; i=i+2) {
                strip.setPixelColor(i+q, c);        //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (int i = 0; i < NUM_OF_PIXELS; i=i+2) {
                strip.setPixelColor(i+q, 0);       //turn every third pixel off
            }
        }
    }

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
static uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 8) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 16) {
    WheelPos -= 8;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 16;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

static void ledStrip_RainBowMode(uint8_t wait)
{
    uint16_t i, j;
    for(j=0; j<256; j++) {
        for(i=0; i < NUM_OF_PIXELS; i++) {
          strip.setPixelColor(i, Wheel((i+j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

static void mSetPixelColor(uint16_t n, TCOLOR color)
{
  strip.setPixelColor(n, strip.Color(colorTable[color][0], colorTable[color][1], colorTable[color][2]));
}


void ledStrip_ShowTheaterChase(void)
{
    uint32_t c = strip.Color(255,0,0);
    ledStrip_TheaterChaseMode(c,50);
    c = strip.Color(0,255,0);
    ledStrip_TheaterChaseMode(c,50);
    c = strip.Color(0,0,255);
    ledStrip_TheaterChaseMode(c,50);
}


void ledStrip_ShowRainBow(void)
{
    ledStrip_RainBowMode(50);
}



void ledStrip_TurnAllLedOff(void)
{
    for(uint16_t i = 0; i < NUM_OF_PIXELS; i++) {
      mSetPixelColor(i, LEDC_BLACK);
    }
    strip.show();
}



void ledStrip_SetAllPixelColor(TCOLOR color)
{
    for(uint16_t i = 0; i < NUM_OF_PIXELS; i++) {
        mSetPixelColor(i, color);
    }
    strip.show();
}



void ledStrip_InitProtocol(void){

  //初始化灯带系统状态位
  ledStrip_WriteCmd(LED_STRIP_READ_SYS_STATUS,false);
  ledStrip_WriteCmd(LED_STRIP_READ_THEATER_MODE_STATUS,false);
  ledStrip_WriteCmd(LED_STRIP_READ_RAINBOW_MODE_STATUS,false);
  ledStrip_WriteCmd(LED_STRIP_READ_TEST_MODE_STATUS,false);
  
  //初始化接收灯带设置位
  ledStrip_WriteCmd(LED_STRIP_SET_SYS_OPEN,false);
  ledStrip_WriteCmd(LED_STRIP_SET_THEATER_MODE_OPEN,false);
  ledStrip_WriteCmd(LED_STRIP_SET_RAINBOW_MODE_OPEN,false);
  ledStrip_WriteCmd(LED_STRIP_SET_TEST_MODE_OPEN,false);

  sysStatus = false;
}



bool ledStrip_ReadCmd(uint16_t address){
  return dPara.coil[address];
}


void ledStrip_WriteCmd(uint16_t address, bool value){
  dPara.coil[address] = value;
}


void ledStrip_ParasCmd(void){

  ledStrip_ParaCmd_SysStatus();
  ledStrip_ParaCmd_TestModeStatus();
  ledStrip_ParaCmd_TheaterChaseModeStatus();
  ledStrip_ParaCmd_RainBowModeStatus();
}




void ledStrip_ParaCmd_SysStatus(void){

  bool CurrentState = ledStrip_ReadCmd(LED_STRIP_READ_SYS_STATUS);
  bool setState = ledStrip_ReadCmd(LED_STRIP_SET_SYS_OPEN);

  if( setState != CurrentState ){
    sysStatus = !sysStatus;
    ledStrip_WriteCmd(LED_STRIP_READ_SYS_STATUS,setState);
  }

}


void ledStrip_Run(void){

  ledStrip_RunOpenMode();
  ledStrip_RunTestMode();
  ledStrip_RunTheaterMode();
  ledStrip_RunRainBowMode();
}


void ledStrip_RunOpenMode(void){
  if(sysStatus){
    ledStrip_SetAllPixelColor(LEDC_RED);
    delay(50);
  }else if(testModeStatus == 0 && theaterChaseModeStatus ==0 && rainBowModeStatus ==0){
    ledStrip_TurnAllLedOff();
    delay(50);
  }
}


void ledStrip_ParaCmd_TestModeStatus(void){

  bool CurrentState = ledStrip_ReadCmd(LED_STRIP_READ_TEST_MODE_STATUS);
  bool setState = ledStrip_ReadCmd(LED_STRIP_SET_TEST_MODE_OPEN);

  if( setState != CurrentState ){
    testModeStatus = !testModeStatus;
    ledStrip_WriteCmd(LED_STRIP_READ_TEST_MODE_STATUS,setState);
  }

}


void ledStrip_RunTestMode(void){

  if(testModeStatus){
    ledStrip_SetAllPixelColor(LEDC_YELLOW);
    delay(50);
  }
  
}

void ledStrip_ParaCmd_TheaterChaseModeStatus(void){

  bool CurrentState = ledStrip_ReadCmd(LED_STRIP_READ_THEATER_MODE_STATUS);
  bool setState = ledStrip_ReadCmd(LED_STRIP_SET_THEATER_MODE_OPEN);

  if( setState != CurrentState ){
    theaterChaseModeStatus = !theaterChaseModeStatus;
    ledStrip_WriteCmd(LED_STRIP_READ_THEATER_MODE_STATUS,setState);
  }

}



void ledStrip_RunTheaterMode(void){

  if(theaterChaseModeStatus){
    ledStrip_ShowTheaterChase();
  }
  
}

void ledStrip_ParaCmd_RainBowModeStatus(void){

  bool CurrentState = ledStrip_ReadCmd(LED_STRIP_READ_RAINBOW_MODE_STATUS);
  bool setState = ledStrip_ReadCmd(LED_STRIP_SET_RAINBOW_MODE_OPEN);

  if( setState != CurrentState ){
    rainBowModeStatus = !rainBowModeStatus;
    ledStrip_WriteCmd(LED_STRIP_READ_RAINBOW_MODE_STATUS,setState);
  }

}



void ledStrip_RunRainBowMode(void){

  if(rainBowModeStatus){
    ledStrip_ShowRainBow();
  }
  
}
