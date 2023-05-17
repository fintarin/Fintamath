#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(const ArgumentPtr &inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::NegExpression;
  }

protected:
  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callNegFunction(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNegatable(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNestedNeg(const IFunction &func, const ArgumentPtr &rhs);
};

}