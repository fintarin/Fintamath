#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {
  class UndefinedBinaryOpearatorException : public UndefinedException {
  public:
    ~UndefinedBinaryOpearatorException() override = default;

    UndefinedBinaryOpearatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
      content = lhs + " " + oper + " " + rhs + " is undefined";
    }

    const char *what() const noexcept override {
      return content.c_str();
    }

  private:
    std::string content;
  };
}
