#pragma once

#include <cstdint>

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(const std::shared_ptr<IMathObject> &child);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> postSimplify() const override;
};

}