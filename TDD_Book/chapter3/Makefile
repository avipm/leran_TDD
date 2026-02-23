CPPUTEST_HOME := C:/msys64/ucrt64

CPPFLAGS := -Iinclude \
            -I$(CPPUTEST_HOME)/include

CXXFLAGS := -g -Wall

LDFLAGS := -L$(CPPUTEST_HOME)/lib \
           -lCppUTest \
           -lCppUTestExt

SRC := src/Led_Driver.c
TEST_SRC := test/LedDriver.cpp test/AllTests.cpp

all: test_runner

test_runner:
	g++ $(CPPFLAGS) $(CXXFLAGS) $(SRC) $(TEST_SRC) $(LDFLAGS) -o test_runner

run: test_runner
	./test_runner

clean:
	rm -f test_runner
