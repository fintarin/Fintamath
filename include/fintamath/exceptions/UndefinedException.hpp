#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class UndefinedException : public Exception {
public:
  explicit UndefinedException(std::string inMessage) : Exception(std::move(inMessage)) {
  }
};

class UndefinedFunctionException final : public UndefinedException {
public:
  explicit UndefinedFunctionException(const std::string &func, const std::vector<std::string> &)
      : UndefinedException(func) {
  }
};

class UndefinedBinaryOperatorException final : public UndefinedException {
public:
  explicit UndefinedBinaryOperatorException(const std::string &oper, const std::string &, const std::string &)
      : UndefinedException(oper) {
  }
};

class UndefinedUnaryOperatorException final : public UndefinedException {
public:
  enum class Type : uint8_t {
    Prefix,
    Postfix,
  };

public:
  explicit UndefinedUnaryOperatorException(const std::string &oper, const std::string &, const Type)
      : UndefinedException(oper) {
  }
};

}
