#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class InvTrigonometryExpression : public IUnaryExpressionCRTP<InvTrigonometryExpression, true> {
public:
  explicit InvTrigonometryExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::InvTrigonometryExpression);
  }

protected:
  SimplifyFunctionsVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr constantsSimplify(const IFunction &func, const ArgumentPtr &rhs);
};

}