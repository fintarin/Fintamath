#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputBinaryOperatorException : public InvalidInputException {
public:
  ~InvalidInputBinaryOperatorException() override = default;

  InvalidInputBinaryOperatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
