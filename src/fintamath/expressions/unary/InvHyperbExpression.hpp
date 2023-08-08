#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class InvHyperbExpression : public IUnaryExpressionCRTP<InvHyperbExpression, true> {
public:
  explicit InvHyperbExpression(const IFunction &inFunc, const ArgumentPtr &inChild);

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::InvHyperbExpression);
  }
};

}