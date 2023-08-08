#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class InvTrigExpression : public IUnaryExpressionCRTP<InvTrigExpression, true> {
public:
  explicit InvTrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::InvTrigExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constantsSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}