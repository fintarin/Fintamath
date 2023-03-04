#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(MathObjectPtr &&rhs);

  MathObjectPtr simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};
}