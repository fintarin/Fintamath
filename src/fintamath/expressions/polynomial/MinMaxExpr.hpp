#pragma once

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class MinMaxExpr : public IPolynomExpressionCRTP<MinMaxExpr> {
  FINTAMATH_CLASS_BODY(MinMaxExpr, IPolynomExpression)

public:
  explicit MinMaxExpr(const IFunction &inFunc, ArgumentPtrVector inChildren);
};

}
