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

## Supported Platforms

* C++ 17 or higher
* CMake 3.5 or higher
* C++ Compilers:
  * GCC 9 or higher
  * Clang 11 or higher
  * MSVC v142 or higher
* Operating systems:
  * Linux
  * Windows
  * macOS
  * Android

## Build

Clone repository.

```sh
git clone https://github.com/fintarin/Fintamath.git fintamath
```

### Standalone Project

Build shared in Release mode.

```sh
cd fintamath
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -Dfintamath_build_shared=ON
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
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -Dfintamath_build_shared=OFF -Dfintamath_build_tests=ON
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
