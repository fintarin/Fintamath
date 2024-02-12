#pragma once

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class MinMaxExpression final : public IPolynomExpressionCRTP<MinMaxExpression> {
public:
  explicit MinMaxExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::MinMaxExpression;
  }
};

}
