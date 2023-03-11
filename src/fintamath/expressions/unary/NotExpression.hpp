#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(std::unique_ptr<IMathObject> &&rhs);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  IMathObject *simplify() override;
};
}