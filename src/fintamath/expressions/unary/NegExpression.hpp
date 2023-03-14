#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(const shared_ptr<IMathObject> &child);

protected:
  shared_ptr<IMathObject> preSimplify() const override;

  shared_ptr<IMathObject> postSimplify() const override;
};

}