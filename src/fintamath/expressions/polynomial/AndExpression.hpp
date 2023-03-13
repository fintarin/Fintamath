#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {
class AndExpression : public IPolynomExpressionCRTP<AndExpression> {
public:
  explicit AndExpression(ArgumentsPtrVector children);

  std::string toString() const override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) override;
};

}