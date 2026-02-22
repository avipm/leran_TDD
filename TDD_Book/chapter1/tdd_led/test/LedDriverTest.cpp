#include "CppUTest/TestHarness.h"

extern "C" {
#include "LedDriver.h"
}

TEST_GROUP(LedDriver)
{
    uint16_t virtualLeds;

    void setup()
    {
        LedDriver_Create(&virtualLeds);
    }
};

TEST(LedDriver, LedsOffAfterCreate)
{
    LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    LONGS_EQUAL(1, virtualLeds);
}
