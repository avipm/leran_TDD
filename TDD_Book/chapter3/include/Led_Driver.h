#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOnAll(uint16_t allLEDS);

#ifdef __cplusplus
}
#endif

#endif