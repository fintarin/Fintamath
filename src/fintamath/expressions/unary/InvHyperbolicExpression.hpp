#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class InvHyperbolicExpression : public IUnaryExpressionCRTP<InvHyperbolicExpression, true> {
public:
  explicit InvHyperbolicExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::InvHyperbolicExpression);
  }
};

}