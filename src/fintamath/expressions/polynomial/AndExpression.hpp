#pragma once

#include <cstdint>

#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  AndExpression() = default; // TODO: remove this

  explicit AndExpression(ArgumentsPtrVector &&inPolynomVect);

  std::string toString() const override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;
};

}