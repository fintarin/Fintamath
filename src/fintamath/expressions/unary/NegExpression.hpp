#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(const ArgumentPtr &inChild);

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callNegFunction(const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNegatable(const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNestedNeg(const ArgumentPtr &rhs);
};

}