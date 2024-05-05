#pragma once

#include <memory>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class Rational;

class FloorCeilExpr : public IUnaryExpressionCRTP<FloorCeilExpr> {
  FINTAMATH_CLASS_BODY(FloorCeilExpr, IUnaryExpression)

public:
  explicit FloorCeilExpr(const IFunction &inFunc, ArgumentPtr inChild);

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr intApproximate(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}
