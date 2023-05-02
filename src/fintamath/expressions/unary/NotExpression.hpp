#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const ArgumentPtr &inChild);

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

private:
  static ArgumentPtr simplifyNot(const ArgumentPtr &rhs);

private:
  static const SimplifyFunctionsVector simplifyFunctions;
};

}