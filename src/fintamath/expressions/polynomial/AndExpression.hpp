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
  std::shared_ptr<IMathObject> simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                const std::shared_ptr<IMathObject> &rhsChild) override;
};

}