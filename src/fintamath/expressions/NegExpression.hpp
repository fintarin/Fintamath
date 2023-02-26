#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  NegExpression(const IMathObject &rhs);

  NegExpression(MathObjectPtr &&rhs);

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};
}