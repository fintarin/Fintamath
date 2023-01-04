#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class DerivativeExpression : public IExpressionCRTP<DerivativeExpression> {
public:
  DerivativeExpression() = default;

  DerivativeExpression(const DerivativeExpression &rhs);

  DerivativeExpression(DerivativeExpression &&rhs) = default;

  DerivativeExpression &operator=(const DerivativeExpression &rhs);

  DerivativeExpression &operator=(DerivativeExpression &&rhs) = default;

  DerivativeExpression(const IMathObject &obj);

  std::string toString() const override;

  uint16_t getBaseOperatorPriority() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

private:
  MathObjectPtr info;
};

}