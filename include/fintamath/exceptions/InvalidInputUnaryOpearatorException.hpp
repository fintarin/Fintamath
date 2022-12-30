#pragma once

#include <utility>

#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class InvalidInputUnaryOpearatorException : public InvalidInputException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  ~InvalidInputUnaryOpearatorException() override = default;

  InvalidInputUnaryOpearatorException(const std::string &oper, const std::string &rhs, Type type) {
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
