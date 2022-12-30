#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

class UndefinedBinaryOpearatorException : public UndefinedException {
public:
  ~UndefinedBinaryOpearatorException() override = default;

  UndefinedBinaryOpearatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

}
