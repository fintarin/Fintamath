#pragma once

#include <utility>

#include "fintamath/exceptions/Exception.h"

namespace fintamath {
  class InvalidInputException : public Exception {
  public:
    ~InvalidInputException() override = default;

    InvalidInputException(const std::string &object, const std::string &input) {
      content = object + " invalid input: " + input;
    }

    const char *what() const noexcept override {
      return content.c_str();
    }

  private:
    std::string content;
  };
}