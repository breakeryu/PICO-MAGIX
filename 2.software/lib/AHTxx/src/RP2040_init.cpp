#include "RP2040_init.h"



void initIIc(void){
    Wire.setSDA(AHT_PIN_SDA);
    Wire.setSCL(AHT_PIN_SCL);
    Wire.begin();
}


