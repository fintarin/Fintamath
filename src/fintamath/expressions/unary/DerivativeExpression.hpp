#pragma once

#include <cstdint>

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression>,
                             public std::enable_shared_from_this<DerivativeExpression> {
public:
  explicit DerivativeExpression(std::shared_ptr<IMathObject> child);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> simplify() override;
};

}