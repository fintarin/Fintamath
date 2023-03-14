#pragma once

#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class InvalidInputException : public Exception {
public:
  InvalidInputException() = default;

  ~InvalidInputException() override = default;

  InvalidInputException(const string &input) {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  string content = "Invalid input";
};

}
