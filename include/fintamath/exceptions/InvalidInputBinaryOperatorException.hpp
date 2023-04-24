#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputBinaryOperatorException : public InvalidInputException {
public:
  ~InvalidInputBinaryOperatorException() override = default;

  InvalidInputBinaryOperatorException(const string &oper, const string &lhs, const string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
