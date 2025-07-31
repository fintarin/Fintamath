#pragma once

#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpression {
  FINTAMATH_CLASS_BODY(Expression, IExpression)

public:
  constexpr const ExpressionDeclaration &getExpressionDeclaration() const noexcept override {
    return expressionDeclaration;
  }

private:
  FINTAMATH_EXPORT static const ExpressionDeclaration expressionDeclaration;
};

}
