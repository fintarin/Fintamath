#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

class UndefinedBinaryOperatorException : public UndefinedException {
public:
  ~UndefinedBinaryOperatorException() override = default;

  UndefinedBinaryOperatorException(const string &oper, const string &lhs, const string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
