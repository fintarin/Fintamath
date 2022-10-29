#pragma once

#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {
  class InvalidInputException : public Exception {
  public:
    InvalidInputException() = default;

    ~InvalidInputException() override = default;

    InvalidInputException(const std::string &object) {
      content += " of " + object;
    }

    InvalidInputException(const std::string &object, const std::string &input) : InvalidInputException(object) {
      content += ": " + input;
    }

    InvalidInputException(const std::string &object, const std::string &input, const std::string &comment)
        : InvalidInputException(object, input) {
      content += ". " + comment;
    }

    const char *what() const noexcept override {
      return content.c_str();
    }

  protected:
    std::string content = "Invalid input";
  };
}
