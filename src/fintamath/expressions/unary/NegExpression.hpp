#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression> {
public:
  explicit NegExpression(const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::NegExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr callNegFunction(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNegatable(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyNestedNeg(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr simplifyConst(const IFunction &func, const ArgumentPtr &rhs);
};

}