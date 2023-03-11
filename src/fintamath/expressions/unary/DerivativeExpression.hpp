#pragma once

#include <cstdint>

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(std::unique_ptr<IMathObject> &&obj);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  void compress() override;

protected:
  IMathObject *simplify() override;
};

}