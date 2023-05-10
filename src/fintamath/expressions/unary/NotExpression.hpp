#pragma once

#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

class NotExpression : public IUnaryExpressionCRTP<NotExpression> {
public:
  explicit NotExpression(const ArgumentPtr &inChild);

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callNotFunction(const ArgumentPtr &rhs);

  static ArgumentPtr simplifyLogicNegatable(const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNestedNot(const ArgumentPtr &rhs);
};

}