#include "CppUTest/TestHarness.h"

extern "C" {
    #include "Led_Driver.h"
}

TEST_GROUP(LedDriver){
    uint16_t virtualLeds = 0xFFFF;

    void setup(){
        LedDriver_Create(&virtualLeds);
    }
};

TEST(LedDriver, LedsOffAfterCreate){
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, LedDriver_TurnOffAllLed){
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, LedDriver_TurnOnAllLed){
    uint16_t allLeds = 0xFFFF;
    LedDriver_TurnOnAll(allLeds);
    LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, LedDriver_getLedStatus){
    uint16_t ledStatus;
    uint16_t allLeds = 0xFFFF;
    LedDriver_TurnOnAll(allLeds);
    LedDriver_getLedStatus(&ledStatus);
    LONGS_EQUAL(allLeds, ledStatus);
}

TEST(LedDriver, LedDriver_TurnOnSpecificLed){
    uint8_t ledNumberToTurnOn = 5;
    uint16_t ledStatus, currentLedStatus;
    LedDriver_getLedStatus(&ledStatus);
    LedDriver_TurnOnSpecificLed(ledNumberToTurnOn);
    LedDriver_getLedStatus(&currentLedStatus);
    CHECK_EQUAL(ledStatus | (1U << (ledNumberToTurnOn - 1)), currentLedStatus);
}

TEST(LedDriver, LedDriver_TurnOffSpecificLed){
    uint8_t ledNumberToTurnOff = 4;
    uint16_t ledStatus, currentLedStatus;
    LedDriver_TurnOnSpecificLed(ledNumberToTurnOff);
    LedDriver_getLedStatus(&ledStatus);
    LedDriver_TurnOffSpecificLed(ledNumberToTurnOff);
    LedDriver_getLedStatus(&currentLedStatus);
    CHECK_EQUAL(ledStatus & ~(1U << (ledNumberToTurnOff - 1)), currentLedStatus);
}

TEST(LedDriver, LedDriver_TurnOnMultipleLed){
    uint8_t ledsNumbers[] = {2,5,8};
    uint8_t ledCount = sizeof(ledsNumbers) / sizeof(ledsNumbers[0]);
    uint16_t ledStatus, currentLedStatus;
    LedDriver_getLedStatus(&ledStatus);
    for(uint8_t itterateLed = 0; itterateLed < ledCount; itterateLed++ ){
        ledStatus |= (1U << (ledsNumbers[itterateLed] - 1));
    }
    LedDriver_TurnOnMultipleLed(ledsNumbers, ledCount);
    LedDriver_getLedStatus(&currentLedStatus);
    CHECK_EQUAL(ledStatus, currentLedStatus);
}

TEST(LedDriver, LedDriver_TurnOffMultipleLed){
    uint8_t ledsNumbers[] = {1,4,7};
    uint8_t ledCount =  sizeof(ledsNumbers) / sizeof(ledsNumbers[0]);
    uint16_t ledStatus, currentLedStatus;
    LedDriver_TurnOnMultipleLed(ledsNumbers, ledCount);
    LedDriver_getLedStatus(&ledStatus);
    for(uint8_t itterateLed = 0; itterateLed < ledCount; itterateLed++ ){
        ledStatus &= ~(1U << (ledsNumbers[itterateLed] - 1));
    }
    LedDriver_TurnOffMultipleLed(ledsNumbers, ledCount);
    LedDriver_getLedStatus(&currentLedStatus);
    CHECK_EQUAL(ledStatus, currentLedStatus);

}