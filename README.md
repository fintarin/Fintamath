<p align="center">
  <img src="./docs/images/logo.png" alt="drawing" width="250"/>
</p>

---

<p align="center">
  <a href="https://github.com/fintarin/Fintamath/actions/workflows/build.yml">
    <img src="https://github.com/fintarin/Fintamath/actions/workflows/build.yml/badge.svg"/>
  </a>
  <a href="https://sonarcloud.io/summary/new_code?id=fintarin_Fintamath">
    <img src="https://sonarcloud.io/api/project_badges/measure?project=fintarin_Fintamath&metric=alert_status"/>
  </a>
  <a href="https://sonarcloud.io/summary/new_code?id=fintarin_Fintamath">
    <img src="https://sonarcloud.io/api/project_badges/measure?project=fintarin_Fintamath&metric=coverage"/>
  </a>
</p>

Fintamath is an algebra & analysis library written in pure C++.

## Requirements

* C++ 17
* CMake 3.16 or higher
* C++ Compiler:
  * GCC 9 or higher
  * Clang 11 or higher
  * MSVC 14 or higher
* OS:
  * Linux
  * Windows
  * macOS

## Build

### Standalone Project

Clone repository

```sh
git clone https://github.com/fintarin/Fintamath.git
cd Fintamath
```

Build

```sh
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Incorporating Into An Existing CMake Project

Add to your CMakeLists.txt:

```cmake
add_subdirectory(Fintamath)

add_executable(example example.cpp)
target_link_libraries(example fintamath)
```
