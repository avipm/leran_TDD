#include "CppUTest/TestHarness.h"

extern "C" {
    #include "Led_Driver.h"
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