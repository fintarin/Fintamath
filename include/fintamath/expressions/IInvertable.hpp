#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IInvertable : virtual public IExpression {
public:
  virtual ArgumentPtr invert() const = 0;
};
}