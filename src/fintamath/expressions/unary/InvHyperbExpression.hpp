#pragma once

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class InvHyperbExpression final : public IUnaryExpressionCRTP<InvHyperbExpression> {
public:
  explicit InvHyperbExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::InvHyperbExpression;
  }
};

}
