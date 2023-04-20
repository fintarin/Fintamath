#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class INegatable : virtual public IExpression {
public:
  virtual ArgumentPtr negate() const = 0;
};
}