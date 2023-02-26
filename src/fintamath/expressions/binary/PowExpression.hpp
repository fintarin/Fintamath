#pragma once

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression> {
public:
  explicit PowExpression(const IMathObject &lhs, const IMathObject &rhs);

  explicit PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}