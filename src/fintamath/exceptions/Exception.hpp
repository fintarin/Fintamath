#pragma once

#include <stdexcept>

namespace fintamath {
  class Exception : public std::exception {
  public:
    ~Exception() override = default;

    const char *what() const noexcept override {
      return "Something went wrong...";
    }
  };
}
