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

void LedDriver_TurnOffSpecificLed(uint8_t ledNumberToTurnOff){
    *leds &= ~(1U << (ledNumberToTurnOff - 1));
}

void LedDriver_TurnOnMultipleLed(uint8_t* ledsNumbers, uint8_t ledsCount){
    if(ledsNumbers == NULL || ledsCount == 0){
        return;
    };
    for(uint8_t itterateLed = 0; itterateLed < ledsCount; itterateLed++ ){
        *leds |= (1U << (ledsNumbers[itterateLed] - 1));
    }
}

void LedDriver_TurnOffMultipleLed(uint8_t* ledsNumbers, uint8_t ledsCount){
        if(ledsNumbers == NULL || ledsCount == 0){
        return;
    };
    for(uint8_t itterateLed = 0; itterateLed < ledsCount; itterateLed++ ){
        *leds &= ~(1U << (ledsNumbers[itterateLed] - 1));
    }
}