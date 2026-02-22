CPPUTEST_HOME := C:/Users/avila/cpputest
CPPUTEST_BUILD := C:/Users/avila/cpputest/build

CPPFLAGS := -Iinclude \
            -I$(CPPUTEST_HOME)/include

CXXFLAGS := -g -Wall

LDFLAGS := -L$(CPPUTEST_BUILD)/src/CppUTest \
           -L$(CPPUTEST_BUILD)/src/CppUTestExt \
           -lCppUTest \
           -lCppUTestExt

SRC := src/LedDriver.c
TEST_SRC := test/LedDriverTest.cpp
RUNNER := $(CPPUTEST_HOME)/src/CppUTest/CommandLineTestRunner.cpp

all: test_runner

test_runner:
	g++ $(CPPFLAGS) $(CXXFLAGS) $(SRC) $(TEST_SRC) $(RUNNER) $(LDFLAGS) -o test_runner

run: test_runner
	./test_runner

clean:
	rm -f test_runner
