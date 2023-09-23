#pragma once

#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class MinMaxExpression : public IPolynomExpressionCRTP<MinMaxExpression, true> {
public:
  explicit MinMaxExpression(const IFunction &inFunc, const ArgumentPtrVector &inChildren);

  static MathObjectType getTypeStatic() {
    return MathObjectType::MinMaxExpression;
  }
};

}
