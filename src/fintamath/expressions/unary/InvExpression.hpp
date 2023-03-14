#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class InvExpression : public IUnaryExpressionCRTP<InvExpression> {
public:
  explicit InvExpression(const shared_ptr<IMathObject> &child);

protected:
  shared_ptr<IMathObject> preSimplify() const override;

  shared_ptr<IMathObject> postSimplify() const override;
};

}