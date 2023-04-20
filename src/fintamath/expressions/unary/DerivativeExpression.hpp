#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(const ArgumentPtr &child);

protected:
  ArgumentPtr postSimplify() const override;
};

}