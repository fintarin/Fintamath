#pragma once

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/expressions/ExpressionBase.hpp"

namespace fintamath {

class Expression : public ExpressionBase {
  FINTAMATH_CLASS_BODY(Expression, ExpressionBase)

public:
  constexpr ExpressionDeclaration getExpressionDeclaration() const noexcept override {
    return {
      .domainAndRangeVariants = {{
        .returnClass = nullptr,
        .childClasses = {MathObject::getClassStatic()},
      }}
    };
  }
};

}
