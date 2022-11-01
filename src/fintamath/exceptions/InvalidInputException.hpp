#pragma once

#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {
  class InvalidInputException : public Exception {
  public:
    ~InvalidInputException() override = default;

    template <typename Obj>
    InvalidInputException(const Obj &obj) {
      content += " of " + obj.getClassName();
    }

    template <typename Obj>
    InvalidInputException(const Obj &obj, const std::string &input) : InvalidInputException(obj) {
      if (!input.empty()) {
        content += ": " + input;
      } else {
        content += " (empty)";
      }
    }

    const char *what() const noexcept override {
      return content.c_str();
    }

  protected:
    std::string content = "Invalid input";
  };
}
