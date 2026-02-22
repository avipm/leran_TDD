#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);

#ifdef __cplusplus
}
#endif

#endif
