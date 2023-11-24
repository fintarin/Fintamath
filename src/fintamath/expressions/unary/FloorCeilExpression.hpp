#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class Rational;

class FloorCeilExpression : public IUnaryExpressionCRTP<FloorCeilExpression, true> {
public:
  explicit FloorCeilExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::FloorCeilExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}
