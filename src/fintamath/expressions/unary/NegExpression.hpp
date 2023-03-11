#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(std::unique_ptr<IMathObject> &&rhs);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};
}