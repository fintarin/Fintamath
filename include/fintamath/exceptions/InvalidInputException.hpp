#pragma once

#include <string>
#include <utility>
#include <vector>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class InvalidInputException : public Exception {
public:
  InvalidInputException() = default;

  ~InvalidInputException() override = default;

  InvalidInputException(const std::string &input) {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  std::string content = "Invalid input";
};

class InvalidInputFunctionException : public InvalidInputException {
public:
  ~InvalidInputFunctionException() override = default;

  InvalidInputFunctionException(const std::string &func, const std::vector<std::string> &argsVect) {
    content += ": " + func + "(";

    if (!argsVect.empty()) {
      for (const auto &arg : argsVect) {
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

class InvalidInputBinaryOperatorException : public InvalidInputException {
public:
  ~InvalidInputBinaryOperatorException() override = default;

  InvalidInputBinaryOperatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

class InvalidInputUnaryOperatorException : public InvalidInputException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  ~InvalidInputUnaryOperatorException() override = default;

  InvalidInputUnaryOperatorException(const std::string &oper, const std::string &rhs, Type type) {
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
