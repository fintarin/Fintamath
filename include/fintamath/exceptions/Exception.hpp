#pragma once

#include <stdexcept>

#include "fintamath/core/CoreDefines.hpp"

namespace fintamath {

class Exception : public std::exception {
public:
  ~Exception() override = default;

  const char *what() const noexcept override {
    return "Something went wrong...";
  }
};

}
