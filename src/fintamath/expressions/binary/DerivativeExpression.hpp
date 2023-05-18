#pragma once

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IBinaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::DerivativeExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr derivativeSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs);
};

}