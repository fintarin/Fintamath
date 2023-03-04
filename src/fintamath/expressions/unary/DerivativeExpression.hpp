#pragma once

#include <cstdint>

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(MathObjectPtr &&obj);

  MathObjectPtr simplify(bool isPrecise) const override;

  void compress() override;

protected:
  IMathObject *simplify() override;
};

}