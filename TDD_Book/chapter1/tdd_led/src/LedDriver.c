#include "LedDriver.h"

static uint16_t* leds;


void LedDriver_Create(uint16_t* address){
leds = address;
*leds = 0;
}

void LedDriver_TurnOn(int ledNumber){
*leds |= (1 << (ledNumber - 1));
}
