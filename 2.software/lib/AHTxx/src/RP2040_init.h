#ifndef _RP2040_INIT_H_
#define _RP2040_INIT_H_

#include <Arduino.h>
#include <Wire.h>


#define AHT_PIN_SDA     8
#define AHT_PIN_SCL     9

void initIIc(void);

#endif
