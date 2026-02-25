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