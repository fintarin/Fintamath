#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class InvExpression : public IUnaryExpressionCRTP<InvExpression> {
public:
  explicit InvExpression(const ArgumentPtr &child);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;
};

}