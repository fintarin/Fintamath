#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  AndExpression() = default; // TODO: remove this

  explicit AndExpression(ArgumentsPtrVector &&inPolynomVect);

  std::string toString() const override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  const IFunction *getFunction() const override;

protected:
  IMathObject *simplify() override;
};

}