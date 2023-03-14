#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IInvertable : virtual public IExpression {
public:
  virtual void invert() = 0;
};
}