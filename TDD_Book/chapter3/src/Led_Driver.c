#include "Led_Driver.h"

static uint16_t* leds;

void LedDriver_Create(uint16_t* address)
{
    leds = address;
    *leds = 0;
    // *address = 0;
}
void LedDriver_TurnOnAll(uint16_t allLEDS){
    *leds = allLEDS;
}