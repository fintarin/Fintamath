#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(MathObjectPtr &&rhs);

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};
}