#pragma once

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class MinMaxExpr final : public IPolynomExpressionCRTP<MinMaxExpr> {
public:
  explicit MinMaxExpr(const IFunction &inFunc, ArgumentPtrVector inChildren);

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::MinMaxExpr, "MinMaxExpr"};
  }
};

}
