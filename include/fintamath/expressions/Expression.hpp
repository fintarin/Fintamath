#pragma once

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpression {
  FINTAMATH_CLASS_BODY(Expression, IExpression)

public:
  constexpr ExpressionDeclaration getExpressionDeclaration() const noexcept override;
};

constexpr Expression::ExpressionDeclaration Expression::getExpressionDeclaration() const noexcept {
  return {
    .domainAndRangeVariants = {{
      .returnClass = nullptr,
      .childClasses = {IMathObject::getClassStatic()},
    }}
  };
}

}
