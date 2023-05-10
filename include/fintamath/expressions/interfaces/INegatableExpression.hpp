#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class INegatableExpression : virtual public IExpression {
public:
  virtual ArgumentPtr negate() const = 0;
};
}