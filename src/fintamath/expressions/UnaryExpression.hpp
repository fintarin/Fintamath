#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

template <typename Derived>
class UnaryExpressionCRTP : public IExpressionCRTP<Derived> {
public:
  void setPrecision(uint8_t precision) final {
    if (is<IExpression>(info)) {
      auto expr = cast<IExpression>(std::move(info));
      expr->setPrecision(precision);
      info = std::move(expr);
      return;
    }

    if (is<IConstant>(info)) {
      info = (*cast<IConstant>(std::move(info)))();
    }

    if (is<INumber>(info)) {
      info = convert<Real>(*info).precise(precision).clone();
    }
  }

protected:
  MathObjectPtr info;
};

}