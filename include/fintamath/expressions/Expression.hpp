#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"

namespace fintamath {

class Expression : public ExpressionBase {
  FINTAMATH_CLASS_BODY(Expression, ExpressionBase)

public:
  const ExpressionBaseDeclaration &getDeclaration() const noexcept override;
};

}
