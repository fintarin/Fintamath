#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class AbsExpression : public IUnaryExpressionCRTP<AbsExpression> {
public:
  explicit AbsExpression(ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::AbsExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}
