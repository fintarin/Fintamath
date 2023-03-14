#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IUnaryExpressionCRTP<DerivativeExpression> {
public:
  explicit DerivativeExpression(const shared_ptr<IMathObject> &child);

protected:
  shared_ptr<IMathObject> postSimplify() const override;
};

}