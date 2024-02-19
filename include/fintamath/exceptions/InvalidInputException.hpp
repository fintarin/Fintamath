#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class InvalidInputException : public Exception {
public:
  explicit InvalidInputException(std::string inMessage) : Exception(std::move(inMessage)) {
  }
};

class InvalidInputFunctionException final : public InvalidInputException {
public:
  explicit InvalidInputFunctionException(const std::string &func, const std::vector<std::string> &)
      : InvalidInputException(func) {
  }
};

class InvalidInputBinaryOperatorException final : public InvalidInputException {
public:
  explicit InvalidInputBinaryOperatorException(const std::string &oper, const std::string &, const std::string &)
      : InvalidInputException(oper) {
  }
};

class InvalidInputUnaryOperatorException final : public InvalidInputException {
public:
  enum class Type : uint8_t {
    Prefix,
    Postfix,
  };

public:
  explicit InvalidInputUnaryOperatorException(const std::string &oper, const std::string &, const Type)
      : InvalidInputException(oper) {
  }
};

}
