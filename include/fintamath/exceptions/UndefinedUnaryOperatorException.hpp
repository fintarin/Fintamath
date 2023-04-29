#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

class UndefinedUnaryOperatorException : public UndefinedException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  ~UndefinedUnaryOperatorException() override = default;

  UndefinedUnaryOperatorException(const std::string &oper, const std::string &rhs, Type type) {
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
