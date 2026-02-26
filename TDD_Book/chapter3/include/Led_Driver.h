#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file Led_Driver.h
 * @brief LED driver for a 16-bit memory-mapped LED register.
 *
 * LEDs are numbered 1–16 (1-indexed). LED N maps to bit (N-1) of the register.
 */

/**
 * @brief Initializes the LED driver and turns off all LEDs.
 * @param address Pointer to the 16-bit memory-mapped LED register.
 */
void LedDriver_Create(uint16_t* address);

/**
 * @brief Sets all 16 LEDs to the given value.
 * @param allLEDS Bitmask to write directly to the LED register (0xFFFF = all on).
 */
void LedDriver_TurnOnAll(uint16_t allLEDS);

/**
 * @brief Reads the current state of the LED register.
 * @param ledStatus Output pointer; receives the current register value.
 */
void LedDriver_getLedStatus(uint16_t* ledStatus);

/**
 * @brief Turns on a single LED without affecting others.
 * @param ledNumberToTurnOn LED number to turn on (1–16).
 */
void LedDriver_TurnOnSpecificLed(uint8_t ledNumberToTurnOn);

/**
 * @brief Turns off a single LED without affecting others.
 * @param ledNumberToTurnOff LED number to turn off (1–16).
 */
void LedDriver_TurnOffSpecificLed(uint8_t ledNumberToTurnOff);

/**
 * @brief Turns on multiple LEDs.
 * @param ledsNumbers Array of LED numbers to turn on (1–16 each).
 * @param ledsCounts  Number of led involved.
 */
void LedDriver_TurnOnMultipleLed(uint8_t* ledsNumbers, uint8_t ledsCounts);

/**
 * @brief Turns off multiple LEDs.
 * @param ledsNumbers Array of LED numbers to turn off (1–16 each).
 * @param ledsCount   Number of led involved.
 */
void LedDriver_TurnOffMultipleLed(uint8_t* ledsNumbers, uint8_t ledsCount);

#ifdef __cplusplus
}
#endif

#endif