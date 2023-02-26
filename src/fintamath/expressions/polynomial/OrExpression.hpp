#pragma once

#include <cstdint>

#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class OrExpression : public IPolynomExpressionCRTP<OrExpression> {
public:
  OrExpression() = default; // TODO: remove this

  explicit OrExpression(ArgumentsPtrVector &&inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};

}