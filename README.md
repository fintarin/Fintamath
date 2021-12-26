<p align="center">
  <img src="./docs/images/logo.png" alt="drawing" width="250"/>
</p>

---

<p align="center">
  <a href="https://github.com/fintarin/Fintamath/actions/workflows/ci-build.yml">
    <img src="https://github.com/fintarin/Fintamath/actions/workflows/ci-build.yml/badge.svg"/>
  </a>

  <a href="https://sonarcloud.io/summary/new_code?id=fintarin_Fintamath">
    <img src="https://sonarcloud.io/api/project_badges/measure?project=fintarin_Fintamath&metric=alert_status"/>
  </a>

  <a href="https://codecov.io/gh/fintarin/Fintamath">
    <img src="https://codecov.io/gh/fintarin/Fintamath/branch/master/graph/badge.svg?token=JL6F07XOK7"/>
  </a>
</p>

Fintamath is an application for solving mathematical expressions with arbitrary precision.

## Features

* Supports integers & rationals
* Supports basic math operators
* Supports most of the elementary mathematical functions list
* Supports factorials
* Supports mathematical constants

## Examples

<p align="center">
  <img src="./docs/images/example.png" alt="drawing""/>
</p>


## Installation

Tested on Ubuntu 20.04.

### Install dependencies

```sh
sudo apt-get update
sudo apt-get install qt5-default
```

### Clone repository

```sh
git clone https://github.com/fintarin/Fintamath.git
cd Fintamath
git submodule update --init
```

### Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run

```sh
./build/bin/fintamath
```

## Planned features

* Supporting reals
* Supporting variables
* Supporting equations
* Increasing speed & precision
* Protting graphics
* LaTex inputting and outputting
