#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const ArgumentPtr &child);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;
};

}