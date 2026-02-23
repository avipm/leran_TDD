
#include "CppUTest/TestHarness.h"

#include <cstring>

extern "C" {
    #include "sprintf_functions.h"
}

TEST_GROUP(sprintf){
    char output [20];
    const char* expected;

    void setup(){
        memset(output, 0xaa, sizeof(output));
        expected = "";
    }
    void teardown(){
        memset(output, 0, sizeof(output));
        expected = "";
    }  
};

TEST(sprintf, NoFormalOperations){
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}

TEST(sprintf, InsertString){
    LONGS_EQUAL(11, sprintf(output, "Hello %s", "World"));
    STRCMP_EQUAL("Hello World", output);
}

TEST(sprintf, InsertInteger){
    LONGS_EQUAL(16, sprintf(output, "The answer is %d", 10));
    STRCMP_EQUAL("The answer is 10", output);
    CHECK(output[16] == 0);
    CHECK(sprintf(output, "test") != 0);
}
