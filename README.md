# TDD for Embedded C — CppUTest Reference

Practice project for *Test-Driven Development for Embedded C* by James W. Grenning, using CppUTest.

---

## CppUTest Assertion Macros

### Integer / Boolean

| Macro | Use |
|---|---|
| `CHECK(condition)` | Passes if `condition` is true |
| `CHECK_TRUE(condition)` | Same as `CHECK` |
| `CHECK_FALSE(condition)` | Passes if `condition` is false |
| `LONGS_EQUAL(expected, actual)` | Integer equality — best failure messages for int/long |
| `UNSIGNED_LONGS_EQUAL(expected, actual)` | Unsigned integer equality |
| `LONGLONGS_EQUAL(expected, actual)` | 64-bit integer equality |
| `CHECK_EQUAL(expected, actual)` | Generic equality using `==` (works for any type with `==`) |
| `BYTES_EQUAL(expected, actual)` | Single byte (8-bit) equality |

### Floating Point

| Macro | Use |
|---|---|
| `DOUBLES_EQUAL(expected, actual, tolerance)` | Passes if `|expected - actual| <= tolerance` |

### Strings (C strings)

| Macro | Use |
|---|---|
| `STRCMP_EQUAL(expected, actual)` | C string equality using `strcmp` |
| `STRNCMP_EQUAL(expected, actual, n)` | First `n` characters equal |
| `STRCMP_NOCASE_EQUAL(expected, actual)` | Case-insensitive string equality |
| `STRCMP_CONTAINS(expected, actual)` | `actual` contains `expected` as a substring |

### Pointers / Memory

| Macro | Use |
|---|---|
| `POINTERS_EQUAL(expected, actual)` | Pointer address equality |
| `CHECK_EQUAL(nullptr, ptr)` | Check pointer is null |

### Unconditional

| Macro | Use |
|---|---|
| `FAIL("message")` | Always fails — use as a placeholder for unwritten code |

---

## Test Structure Macros

```cpp
// Define a test group (fixture) with optional setup/teardown
TEST_GROUP(GroupName)
{
    // member variables shared across tests in this group
    int someVar;

    void setup()
    {
        // runs before every TEST in this group
    }

    void teardown()
    {
        // runs after every TEST in this group
    }
};

// Define a test
TEST(GroupName, TestName)
{
    // assertions here
}

// Skip a test but show it as ignored in output
IGNORE_TEST(GroupName, TestName)
{
    // body still present but not executed
}
```

---

## Test Runner (AllTests.cpp)

Every module needs this entry point:

```cpp
#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
```

---

## Command Line Flags

Run from the module directory after `make`:

```bash
./test_runner                    # Run all tests
./test_runner -v                 # Verbose — print each test name
./test_runner -g GroupName       # Run only tests in this group
./test_runner -t TestName        # Run only tests matching this name
./test_runner -r 3               # Repeat all tests 3 times

Options that do not run tests but query:
  -h                 - this wonderful help screen. Joy!
  -lg                - print a list of group names, separated by spaces
  -ln                - print a list of test names in the form of group.name, separated by spaces

Options that change the output format:
  -c                - colorize output, print green if OK, or red if failed
  -v                - verbose, print each test name as it runs
  -vv               - very verbose, print internal information during test run

Options that change the output location:
  -oteamcity       - output to xml files (as the name suggests, for TeamCity)
  -ojunit          - output to JUnit ant plugin style xml files (for CI systems)
  -k package name  - Add a package name in JUnit output (for classification in CI systems)


Options that control which tests are run:
  -g group         - only run test whose group contains the substring group
  -n name          - only run test whose name contains the substring name
  -t group.name    - only run test whose name contains the substring group and name
  -sg group        - only run test whose group exactly matches the string group
  -sn name         - only run test whose name exactly matches the string name
  -xg group        - exclude tests whose group contains the substring group (v3.8)
  -xn name         - exclude tests whose name contains the substring name (v3.8)
  TEST(group,name) - only run test whose group and name matches the strings group and name.
                     This can be used to copy-paste output from the -v option on the command line.

Options that control how the tests are run:
  -t group.name    - only run test whose name contains the substring group and name
  -sg group        - only run test whose group exactly matches the string group
  -sn name         - only run test whose name exactly matches the string name
  -xg group        - exclude tests whose group contains the substring group (v3.8)
  -xn name         - exclude tests whose name contains the substring name (v3.8)
  TEST(group,name) - only run test whose group and name matches the strings group and name.
                     This can be used to copy-paste output from the -v option on the command line.

Options that control how the tests are run:
  -p               - run tests in a separate process.
  -b               - run the tests backwards, reversing the normal way
  -s [seed]        - shuffle tests randomly. Seed is optional
  -r#              - repeat the tests some number (#) of times, or twice if # is not specified.
  -t group.name    - only run test whose name contains the substring group and name
  -sg group        - only run test whose group exactly matches the string group
  -sn name         - only run test whose name exactly matches the string name
  -xg group        - exclude tests whose group contains the substring group (v3.8)
  -xn name         - exclude tests whose name contains the substring name (v3.8)
  TEST(group,name) - only run test whose group and name matches the strings group and name.
                     This can be used to copy-paste output from the -v option on the command line.

Options that control how the tests are run:
  -p               - run tests in a separate process.
  TEST(group,name) - only run test whose group and name matches the strings group and name.
                     This can be used to copy-paste output from the -v option on the command line.

Options that control how the tests are run:
Options that control how the tests are run:
  -p               - run tests in a separate process.
  -b               - run the tests backwards, reversing the normal way
  -s [seed]        - shuffle tests randomly. Seed is optional
  -s [seed]        - shuffle tests randomly. Seed is optional
  -r#              - repeat the tests some number (#) of times, or twice if # is not specified.
```

---

## C Header Guard (for C/C++ interop)

Every C header used in C++ tests needs this:

```c
#ifndef MY_MODULE_H
#define MY_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

// your C declarations here

#ifdef __cplusplus
}
#endif

#endif
```

---

## Test Doubles (Book Vocabulary)

| Term | What it does |
|---|---|
| **Fake** | Simplified working implementation (e.g. a `uint16_t` variable standing in for a hardware register) |
| **Stub** | Returns hard-coded canned values to control indirect inputs |
| **Spy** | Records calls so tests can verify them afterward |
| **Mock** | Pre-programmed with expectations; verifies interactions automatically |

---

## Build Commands

Run from the module directory (e.g. `TDD_Book/chapter1/tdd_led/`):

```bash
make          # Build test runner
make run      # Build and run all tests
make clean    # Remove test_runner binary
```