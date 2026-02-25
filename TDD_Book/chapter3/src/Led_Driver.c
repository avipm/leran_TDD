#include "Led_Driver.h"
#include <stdio.h>

static uint16_t* leds;

void LedDriver_Create(uint16_t* address)
{
    leds = address;
    *leds = 0x0000;
}

void LedDriver_TurnOnAll(uint16_t allLEDS){
    *leds = allLEDS;
}

void LedDriver_getLedStatus(uint16_t* ledStatus){
    *ledStatus = *leds;
}

void LedDriver_TurnOnSpecificLed(uint8_t ledNumberToTurnOn){
    *leds |= (1U << (ledNumberToTurnOn - 1));
}