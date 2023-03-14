#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputBinaryOpearatorException : public InvalidInputException {
public:
  ~InvalidInputBinaryOpearatorException() override = default;

  InvalidInputBinaryOpearatorException(const string &oper, const string &lhs, const string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
