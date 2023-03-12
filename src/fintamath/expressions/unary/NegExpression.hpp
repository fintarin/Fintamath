#pragma once

#include "fintamath/expressions/unary/IUnaryExpression.hpp"

namespace fintamath {

class NegExpression : public IUnaryExpressionCRTP<NegExpression>, public std::enable_shared_from_this<NegExpression> {
public:
  explicit NegExpression(std::shared_ptr<IMathObject> child);

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> simplifyChildren() override;
};

}