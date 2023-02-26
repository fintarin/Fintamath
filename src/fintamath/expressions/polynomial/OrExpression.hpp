#pragma once

#include <cstdint>

#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class OrExpression : public IPolynomExpressionCRTP<OrExpression> {
public:
  OrExpression() = default; // TODO: remove this

  OrExpression(const IMathObject &rhs);

  explicit OrExpression(PolynomVector inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};

}