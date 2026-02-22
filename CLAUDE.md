# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a TDD (Test-Driven Development) learning project based on *Test Driven Development for Embedded C* by James W. Grenning. It implements embedded C modules with C++ unit tests using the CppUTest framework.

## Build and Test Commands

All commands are run from a chapter's module directory (e.g., `TDD_Book/chapter1/tdd_led/`):

```bash
make          # Build the test runner
make run      # Build and run all tests
make clean    # Remove build artifacts
./test_runner # Run tests directly after building
```

**Dependencies:**
- CppUTest installed at `C:/Users/avila/cpputest` (hardcoded in Makefiles)
- GCC/G++ compiler

## Architecture

### Project Layout

Each chapter contains one or more modules following this structure:

```
TDD_Book/
└── chapterN/
    └── <module_name>/
        ├── include/      # Public C headers (.h)
        ├── src/          # C implementation files (.c)
        ├── test/         # C++ test files using CppUTest (.cpp)
        └── Makefile
```

### TDD Pattern Used

- Production code is written in **C** (`src/*.c`, `include/*.h`)
- Tests are written in **C++** (`test/*.cpp`) using CppUTest macros
- Each test file uses `TEST_GROUP` with `setup()`/`teardown()` methods
- Tests drive implementation: functions may be declared in headers before being implemented

### CppUTest Conventions

- `TEST_GROUP(GroupName) { ... }` defines a test fixture with setup/teardown
- `TEST(GroupName, TestName) { ... }` defines individual tests
- `CHECK_EQUAL(expected, actual)` is the primary assertion macro
- The test runner is a compiled executable (`test_runner`) — there is no test discovery via external tools

### Current Modules

**`TDD_Book/chapter1/tdd_led/`** — LED driver for a 16-bit hardware register
- `LedDriver_Create(uint16_t* address)` — binds the driver to a memory-mapped register and clears all LEDs
- `LedDriver_TurnOn(int ledNumber)` — sets the bit for the given LED (1-indexed, mapped to bit `ledNumber - 1`)
- `LedDriver_TurnOff(int ledNumber)` — declared but not yet implemented
- Tests use a local `uint16_t` variable as a fake hardware register
