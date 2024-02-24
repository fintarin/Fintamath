#pragma once

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IntegralExpr final : public IBinaryExpressionCRTP<IntegralExpr> {
public:
  explicit IntegralExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IntegralExpr, "IntegralExpr"};
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr integralSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}