#include "WS2812test.h"


/*
code reference url : https://www.tweaking4all.com/hardware/arduino/arduino-ws2812-led/
see part :  Programming the Arduino for WS2811/WS2812
            using AdaFruit NeoPixel
*/

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_OF_PIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);



void ledStrip_Init(void)
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}


static void ledStrip_TheaterChaseMode(uint32_t c,uint8_t wait)
{

    for (int j = 0; j < 10; j++) {                      //do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (int i = 0; i < NUM_OF_PIXELS; i=i+3) {
                strip.setPixelColor(i+q, c);        //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (int i = 0; i < NUM_OF_PIXELS; i=i+3) {
                strip.setPixelColor(i+q, 0);       //turn every third pixel off
            }
        }
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


void ledStrip_ShowTheaterChase(void)
{
    ledStrip_TheaterChaseMode(LEDC_RED,50);
    ledStrip_TheaterChaseMode(LEDC_GREEN,50);
    ledStrip_TheaterChaseMode(LEDC_BLUE,50);
}


void ledStrip_ShowRainBow(void)
{
    ledStrip_RainBowMode(50);
}



void ledStrip_TurnAllLedOff(void)
{
    for(uint16_t i = 0; i < NUM_OF_PIXELS; i++) {
        strip.setPixelColor(i, LEDC_BLACK);
    }
    strip.show();
}



void ledStrip_SetAllPixelColor(uint32_t color)
{
    for(uint16_t i = 0; i < NUM_OF_PIXELS; i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}





