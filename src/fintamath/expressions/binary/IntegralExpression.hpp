#pragma once

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IntegralExpression final : public IBinaryExpressionCRTP<IntegralExpression> {
public:
  explicit IntegralExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::IntegralExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr integralSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}