#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const shared_ptr<IMathObject> &child);

protected:
  shared_ptr<IMathObject> preSimplify() const override;

  shared_ptr<IMathObject> postSimplify() const override;
};

}