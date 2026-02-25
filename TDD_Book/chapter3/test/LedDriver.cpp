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
    // FAIL("Start Here");
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, LedDriver_TurnOffAllLed){
    LedDriver_Create(&virtualLeds); 
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, LedDriver_TurnOnAllLed){
    uint16_t allLeds = 0xFFFF;
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOnAll(allLeds);
    LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, LedDriver_getLedStatus){
    LedDriver_Create(&virtualLeds);
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