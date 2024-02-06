<p align="center">
  <img src="./docs/images/logo.svg" alt="drawing" width="250"/>
</p>

---

<p align="center">
  <a href="https://github.com/fintarin/Fintamath/actions/workflows/build.yml"><img src="https://github.com/fintarin/Fintamath/actions/workflows/build.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=fintarin_Fintamath"><img src="https://sonarcloud.io/api/project_badges/measure?project=fintarin_Fintamath&metric=alert_status"/></a>
  <a href='https://coveralls.io/github/fintarin/Fintamath'><img src='https://coveralls.io/repos/github/fintarin/Fintamath/badge.svg?branch=master' alt='Coverage Status'/></a>
</p>

Fintamath is a C++ library for symbolic mathematics, supporting both the input of expressions in mathematical format and the use of functions from the library. It is fully featured performing operations on mathematical expressions (polynomials, powers, logarithms, trigonometry, etc.) and solving equations. Using arbitrary precision integers, exact fractions and floating point numbers, Fintamath yields highly accurate numerical results. The library is extensively tested and has 100% line coverage.

[Usage Examples](tests/src/FintamathTests.cpp)

## Features

* [Expression](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/expressions/Expression.hpp) — the main class representing mathematical expressions
  * Parsing from string
  * Getting string representation
  * Setting variables
  * Arithmetic operators

* [ExpressionFunctions](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/expressions/ExpressionFunctions.hpp) — a set of functions on expressions
  * Arithmetic functions
  * Comparison functions
  * Powers and logarithms
  * Trigonometric functions
  * Hyperbolic functions
  * Derivative
  * Logic functions
  * Mathematical constants
  * Rounding functions
  * Percent, degrees, factorial, index
  * Solving equations
  * Approximating

* [Integer](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/Integer.hpp) — a class representing integers of arbitrary precision
  * Arithmetic operators
  * Comparison operators
  * Bitwise operators

* [IntegerFunctions](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/IntegerFunctions.hpp) — a set of functions on integers
  * Power and absolute value
  * Number theory functions
  * Combinatorics functions

* [Rational](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/Rational.hpp) — a class representing exact fractions
  * Arithmetic operators
  * Comparison operators

* [RationalFunctions](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/RationalFunctions.hpp) — a set of functions on rationals
  * Rounding functions
  * Absolute value

* [Real](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/Real.hpp) — a class representing high precision floats (up to 80 decimal places)
  * Arithmetic operators
  * Comparison operators

* [RealFunctions](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/RealFunctions.hpp) — a set of functions on reals
  * Rounding functions
  * Absolute value
  * Powers and logarithms
  * Trigonometric functions
  * Mathematical constants
  * Gamma function

* [Complex](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/numbers/Complex.hpp) — a class representing complex numbers
  * Arithmetic operators

* [Variable](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/literals/Variable.hpp) — a class representing a letter of the English alphabet with or without unsigned integer index

* [Boolean](https://github.com/fintarin/Fintamath/blob/master/include/fintamath/literals/Boolean.hpp) — a bool wrapper class

* [Functions](https://github.com/fintarin/Fintamath/tree/master/include/fintamath/functions) — classes of mathematical functions supported in expressions

## Requirements

* C++ 20 or higher
* CMake 3.5 or higher
* C++ compilers:
  * GCC 11 or higher
  * Clang 16 or higher
  * MSVC 19.30  or higher
  * Apple Clang 14.0.3 or higher
* Operating systems:
  * Linux
  * Windows
  * macOS
  * Android
* Libraries:
  * [GMP](https://gmplib.org/) 6.2.0 or higher
  * [MPFR](https://www.mpfr.org/) 4.2.0 or higher

Note: Fintamath uses pre-built GMP and MPFR if you are building on Windows or Android. But if you are building on Linux or macOS, you should install these libraries using your package manager.

## Build

Clone repository.

```sh
git clone --recurse-submodules https://github.com/fintarin/Fintamath.git fintamath
```

### Standalone Project

Build in Release mode.

```sh
cd fintamath
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Incorporating into an Existing CMake Project

Add the following lines to your CMakeLists.txt.

```cmake
add_subdirectory(fintamath)
add_executable(example example.cpp)
target_link_libraries(example fintamath)
```

## Development

Build in Debug mode with tests enabled.

```sh
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -Dfintamath_build_tests=ON
cmake --build build
```

Run tests.

```sh
cd build
ctest -CDEBUG --verbose
cd ..
```

Run clang-format.

```sh
cmake -Bbuild -Dfintamath_enable_clangformat=ON
cmake --build build --target clangformat
```
