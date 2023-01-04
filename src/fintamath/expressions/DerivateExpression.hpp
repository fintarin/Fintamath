#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class DerivateExpression : public IExpressionCRTP<DerivateExpression> {
public:
  DerivateExpression() = default;

  DerivateExpression(const DerivateExpression &rhs);

  DerivateExpression(DerivateExpression &&rhs) = default;

  DerivateExpression &operator=(const DerivateExpression &rhs);

  DerivateExpression &operator=(DerivateExpression &&rhs) = default;

  DerivateExpression(const IMathObject &obj);

  std::string toString() const override;

  uint16_t getBaseOperatorPriority() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

private:
  MathObjectPtr info;
};

}