#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class IntegralExpression : public IBinaryExpressionCRTP<IntegralExpression> {
public:
  explicit IntegralExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::IntegralExpression;
  }

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr integralSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}