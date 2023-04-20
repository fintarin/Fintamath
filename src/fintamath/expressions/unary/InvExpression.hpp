#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class InvExpression : public IUnaryExpressionCRTP<InvExpression> {
public:
  explicit InvExpression(const ArgumentPtr &child);

  string toString() const override;

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;
};

}