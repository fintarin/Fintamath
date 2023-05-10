#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class IntegralExpression : public IBinaryExpressionCRTP<IntegralExpression> {
public:
  explicit IntegralExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr integralSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}