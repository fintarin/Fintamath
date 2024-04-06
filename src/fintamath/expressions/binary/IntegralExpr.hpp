#pragma once

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IntegralExpr : public IBinaryExpressionCRTP<IntegralExpr> {
  FINTAMATH_CLASS_BODY(IntegralExpr, IBinaryExpression)

public:
  explicit IntegralExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr integralSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}