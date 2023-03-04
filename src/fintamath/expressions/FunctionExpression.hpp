#pragma once

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {
class FunctionExpression : public IExpressionCRTP<FunctionExpression> {
public:
  FunctionExpression() = default;

  FunctionExpression(const FunctionExpression &rhs);

  FunctionExpression(FunctionExpression &&rhs) = default;

  FunctionExpression &operator=(const FunctionExpression &rhs);

  FunctionExpression &operator=(FunctionExpression &&rhs) noexcept = default;

  explicit FunctionExpression(const IFunction &function, ArgumentsPtrVector &&args);

  std::string toString() const override;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify(bool isPrecise) const override;

  void validate() const override;

protected:
  IMathObject *simplify() override;

private:
  FunctionPtr function;

  ArgumentsPtrVector args;

  std::string functionToString() const;
};
}