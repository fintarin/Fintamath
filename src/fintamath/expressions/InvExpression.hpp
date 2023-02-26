#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class InvExpression : public IUnaryExpressionCRTP<InvExpression> {
public:
  InvExpression(const IMathObject &rhs);

  explicit InvExpression(MathObjectPtr &&rhs);

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}