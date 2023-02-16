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

  explicit DerivativeExpression(MathObjectPtr &&obj);

  std::string toString() const override;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  // TODO: remove this
  void validate() const override;

  void compress() override;

private:
  MathObjectPtr info;
};

}