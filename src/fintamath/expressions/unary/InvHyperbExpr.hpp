#pragma once

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class InvHyperbExpr : public IUnaryExpressionCRTP<InvHyperbExpr> {
  FINTAMATH_CLASS_BODY(InvHyperbExpr, IUnaryExpression)

public:
  explicit InvHyperbExpr(const IFunction &inFunc, ArgumentPtr inChild);
};

}
