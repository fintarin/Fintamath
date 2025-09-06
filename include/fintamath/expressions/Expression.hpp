#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpression {
  FINTAMATH_CLASS_BODY(Expression, IExpression)

public:
  const ExpressionDeclaration &getExpressionDeclaration() const noexcept override;

private:
  static const ExpressionDeclaration expressionDeclaration;
};

}
