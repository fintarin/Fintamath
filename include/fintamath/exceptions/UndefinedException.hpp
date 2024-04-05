#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class UndefinedException : public Exception {
public:
  UndefinedException() noexcept = default;

  explicit UndefinedException(const std::string &input) noexcept {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  std::string content = "Undefined";
};

class UndefinedFunctionException final : public UndefinedException {
public:
  explicit UndefinedFunctionException(const std::string &func, const std::vector<std::string> &argVect) noexcept {
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

class UndefinedBinaryOperatorException final : public UndefinedException {
public:
  explicit UndefinedBinaryOperatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) noexcept {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

class UndefinedUnaryOperatorException final : public UndefinedException {
public:
  enum class Type : uint8_t {
    Prefix,
    Postfix,
  };

public:
  explicit UndefinedUnaryOperatorException(const std::string &oper, const std::string &rhs, const Type type) noexcept {
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
