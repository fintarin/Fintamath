#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class SignExpression : public IUnaryExpressionCRTP<SignExpression> {
public:
  explicit SignExpression(ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::SignExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}
