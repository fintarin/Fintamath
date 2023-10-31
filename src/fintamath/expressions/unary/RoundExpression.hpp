#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class Rational;

class RoundExpression : public IUnaryExpressionCRTP<RoundExpression, true> {
public:
  explicit RoundExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::RoundExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}
