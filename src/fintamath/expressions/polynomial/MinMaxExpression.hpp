#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class MinMaxExpression : public IPolynomExpressionCRTP<MinMaxExpression> {
public:
  explicit MinMaxExpression(const IFunction &inFunc, const ArgumentsPtrVector &inChildren);
};

}