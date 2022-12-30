#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputBinaryOpearatorException : public InvalidInputException {
public:
  ~InvalidInputBinaryOpearatorException() override = default;

  InvalidInputBinaryOpearatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
