#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class ILogicNegatableExpression : virtual public IExpression {
public:
  virtual ArgumentPtr logicNegate() const = 0;
};

}
