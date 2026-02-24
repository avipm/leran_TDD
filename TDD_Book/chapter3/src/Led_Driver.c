#include "Led_Driver.h"

static uint16_t* leds;

void LedDriver_Create(uint16_t* address)
{
    leds = address;
    *leds = 0;
}