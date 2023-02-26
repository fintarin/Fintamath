#pragma once

#include <cstdint>

#include "fintamath/expressions/IBinaryExpression.hpp"

namespace fintamath {

class IndexExpression : public IBinaryExpressionCRTP<IndexExpression> {
public:
  explicit IndexExpression(const IMathObject &lhs, const IMathObject &rhs);

  explicit IndexExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  const IFunction *getFunction() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;
};

}