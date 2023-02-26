#pragma once

#include <cstdint>

#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {
class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  AndExpression() = default; // TODO: remove this

  AndExpression(const IMathObject &rhs);

  explicit AndExpression(PolynomVector inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};

}