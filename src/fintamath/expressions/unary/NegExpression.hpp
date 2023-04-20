#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(const ArgumentPtr &child);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;
};

}