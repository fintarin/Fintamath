#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class MinMaxExpression final : public IPolynomExpressionCRTP<MinMaxExpression, true> {
public:
  explicit MinMaxExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  static MathObjectType getTypeStatic() {
    return MathObjectType::MinMaxExpression;
  }
};

}
