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
  static ArgumentPtr callFunctionSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negatableSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr nestedNegSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr constSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}