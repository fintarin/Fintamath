#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class InvExpression : public IUnaryExpressionCRTP<InvExpression> {
public:
  explicit InvExpression(MathObjectPtr &&rhs);

  MathObjectPtr simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};
}