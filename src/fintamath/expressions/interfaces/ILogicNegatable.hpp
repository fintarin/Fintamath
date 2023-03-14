#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class ILogicNegatable : virtual public IExpression {
public:
  virtual void logicNegate() = 0;
};

}
