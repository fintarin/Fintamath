#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

class UndefinedBinaryOpearatorException : public UndefinedException {
public:
  ~UndefinedBinaryOpearatorException() override = default;

  UndefinedBinaryOpearatorException(const string &oper, const string &lhs, const string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
