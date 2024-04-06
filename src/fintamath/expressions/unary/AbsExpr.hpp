#pragma once

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class AbsExpr : public IUnaryExpressionCRTP<AbsExpr> {
  FINTAMATH_CLASS_BODY(AbsExpr, IUnaryExpression)

public:
  explicit AbsExpr(ArgumentPtr inChild);

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}
