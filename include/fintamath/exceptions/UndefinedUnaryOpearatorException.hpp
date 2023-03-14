#pragma once

#include <utility>

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

class UndefinedUnaryOpearatorException : public UndefinedException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  ~UndefinedUnaryOpearatorException() override = default;

  UndefinedUnaryOpearatorException(const string &oper, const string &rhs, Type type) {
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
