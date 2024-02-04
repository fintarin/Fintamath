#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class InvalidInputException : public Exception {
public:
  InvalidInputException() = default;

  explicit InvalidInputException(const std::string &input) {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  std::string content = "Invalid input";
};

class InvalidInputFunctionException final : public InvalidInputException {
public:
  explicit InvalidInputFunctionException(const std::string &func, const std::vector<std::string> &argVect) {
    content += ": " + func + "(";

    if (!argVect.empty()) {
      for (const auto &arg : argVect) {
        content += arg + ',';
      }

      content.pop_back();
    }

    content += ")";
  }

  const char *what() const noexcept override {
    return content.c_str();
  }
};

class InvalidInputBinaryOperatorException final : public InvalidInputException {
public:
  explicit InvalidInputBinaryOperatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

class InvalidInputUnaryOperatorException final : public InvalidInputException {
public:
  enum class Type : uint8_t {
    Prefix,
    Postfix,
  };

public:
  explicit InvalidInputUnaryOperatorException(const std::string &oper, const std::string &rhs, const Type type) {
    switch (type) {
      case Type::Prefix:
        content += ": " + oper + "(" + rhs + ")";
        break;
      case Type::Postfix:
        content += ": (" + rhs + ")" + oper;
        break;
    }
  }
};

}
