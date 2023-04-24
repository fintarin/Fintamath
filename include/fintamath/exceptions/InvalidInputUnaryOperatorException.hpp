#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputUnaryOperatorException : public InvalidInputException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  ~InvalidInputUnaryOperatorException() override = default;

  InvalidInputUnaryOperatorException(const string &oper, const string &rhs, Type type) {
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
