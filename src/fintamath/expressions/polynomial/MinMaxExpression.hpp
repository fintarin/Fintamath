#pragma once

#include "fintamath/expressions/interfaces/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"

namespace fintamath {

class MinMaxExpression : public IPolynomExpressionCRTP<MinMaxExpression> {
public:
  explicit MinMaxExpression(const IFunction &inFunc, const ArgumentsPtrVector &inChildren);
};

}