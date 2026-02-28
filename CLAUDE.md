# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a TDD (Test-Driven Development) learning project based on *Test Driven Development for Embedded C* by James W. Grenning. It implements embedded C modules with C++ unit tests using the CppUTest framework.

## Build and Test Commands

All commands are run from a chapter's module directory (e.g., `TDD_Book/chapter1/tdd_led/`):

```bash
make          # Build the test runner
make run      # Build and run all tests
make clean    # Remove build artifacts (only removes test_runner — no object files)
./test_runner # Run tests directly after building
```

**Run a specific test group or test:**
```bash
./test_runner -g LedDriver           # Run all tests in the LedDriver group
./test_runner -t TurnOnLedOne        # Run tests matching name
./test_runner -v                     # Verbose output (show each test name)
```

**Dependencies:**
- CppUTest installed via MSYS2: `pacman -S mingw-w64-ucrt-x86_64-cpputest` (installed at `C:/msys64/ucrt64`)
- GCC/G++ from MSYS2 ucrt64 — requires `/c/msys64/ucrt64/bin` in PATH (added to `~/.bashrc`)
- `CPPUTEST_HOME := C:/msys64/ucrt64` in Makefiles

## CI/CD

**GitHub Actions** (`.github/workflows/`):
- `tests.yml` — runs on every push and PR; auto-discovers all Makefiles under `TDD_Book/` using `find` and runs `make run CPPUTEST_HOME=/usr` in each. All chapters run even if one fails; the job fails at the end if any chapter did.
- `claude-review.yml` — triggers on PR open/update and `@claude` comments; uses `anthropics/claude-code-action@v1` with `ANTHROPIC_API_KEY` repository secret. Requires `id-token: write` permission.

**Pre-push hook** (local, blocks push if tests fail):
```bash
cp scripts/pre-push .git/hooks/pre-push && chmod +x .git/hooks/pre-push
```

## Architecture

### Project Layout

Chapters 1 and 2 each contain a named module subdirectory. Chapter 3 currently sits directly under `chapter3/` without a subdirectory (no module subdirectory):

```
TDD_Book/
├── chapter1/tdd_led/        # named module subdirectory
├── chapter2/sprintf_test/   # named module subdirectory
└── chapter3/                # Makefile lives directly here (no subdirectory)
```

Each module has `include/`, `src/`, `test/`, and `Makefile`.

### Build Model

The Makefile compiles everything in a **single g++ invocation** (source + test + CppUTest runner). There are no intermediate object files, so `make clean` only removes the `test_runner` binary. New modules copy this same Makefile pattern, updating `SRC` and `TEST_SRC`.

### C/C++ Interop Pattern

C headers use `#ifdef __cplusplus extern "C"` guards so they compile cleanly in both C and C++ translation units. Test files include C headers directly; the guard in the header handles linkage:

```c
#ifdef __cplusplus
extern "C" {
#endif
// C declarations here
#ifdef __cplusplus
}
#endif
```

### TDD Workflow

Follow the strict red → green → refactor cycle the book prescribes:
1. **Red** — write one failing test; it must compile but fail
2. **Green** — write the *minimum* code to make it pass (even a hardcoded return is valid)
3. **Refactor** — clean up without breaking tests

When helping with implementation, only implement enough to pass the current failing test. Do not implement functions that have no tests yet.

### Scaffolding a New Module

To start a new chapter module (e.g., `TDD_Book/chapter2/circular_buffer/`):

```bash
mkdir -p TDD_Book/chapter2/circular_buffer/{include,src,test}
cp TDD_Book/chapter1/tdd_led/Makefile TDD_Book/chapter2/circular_buffer/Makefile
```

Then edit the new Makefile: update `SRC` and `TEST_SRC` to point to the new module's files.

Every module needs a `test/AllTests.cpp` entry point (the installed CppUTest library does not include a `main()`):

```cpp
#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
```

### CppUTest Conventions

**Assertions:**
- `CHECK(condition)` — true/false check
- `CHECK_EQUAL(expected, actual)` — generic equality (uses `==`)
- `LONGS_EQUAL(expected, actual)` — integer equality with better failure messages
- `DOUBLES_EQUAL(expected, actual, tolerance)` — floating point comparison
- `STRCMP_EQUAL(expected, actual)` — C string comparison
- `POINTERS_EQUAL(expected, actual)` — pointer comparison
- `FAIL("message")` — unconditional failure (use as a placeholder for unwritten code)

**Test control:**
- `IGNORE_TEST(Group, Name) { ... }` — skips the test but reports it as ignored (use while writing the next test)
- `TEST_GROUP(GroupName) { ... }` — fixture with `setup()` and `teardown()` methods
- `setup()` runs before each test; `teardown()` runs after — always initialize the module under test in `setup()`

**Pattern:** Tests use a local variable (e.g., `uint16_t virtualLeds`) as a fake hardware register, passed to the module's `_Create` function in `setup()`.

### Test Doubles (Book Vocabulary)

The book uses these terms — understand the distinction when the book introduces each:
- **Fake** — simplified working implementation (e.g., a local variable standing in for a hardware register)
- **Stub** — returns hard-coded canned values; used to control indirect inputs
- **Spy** — records calls so the test can verify them afterward
- **Mock** — pre-programmed with expectations; verifies interactions automatically

### Current Modules

**`TDD_Book/chapter1/tdd_led/`** — LED driver for a 16-bit hardware register
- `LedDriver_Create(uint16_t* address)` — binds driver to a memory-mapped register and clears all LEDs
- `LedDriver_TurnOn(int ledNumber)` — sets bit for the given LED (1-indexed → bit `ledNumber - 1`)
- `LedDriver_TurnOff(int ledNumber)` — declared in header, not yet implemented

**`TDD_Book/chapter2/sprintf_test/`** — exercises CppUTest with standard library `sprintf`
- Tests cover: plain string output, `%s` interpolation, `%d` interpolation, null termination
- Uses `teardown()` to clear the output buffer after each test

**`TDD_Book/chapter3/`** — LED driver restart (book re-derives the driver from scratch)
- Currently has one passing smoke test (`LedsOffAfterCreate`) to keep CI green while the chapter is in progress
