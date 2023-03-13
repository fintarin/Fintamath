#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
class FunctionExpression : public IExpressionCRTP<FunctionExpression> {
public:
  FunctionExpression(const FunctionExpression &rhs);

  FunctionExpression(FunctionExpression &&rhs) = default;

  FunctionExpression &operator=(const FunctionExpression &rhs);

  FunctionExpression &operator=(FunctionExpression &&rhs) noexcept = default;

  explicit FunctionExpression(const IFunction &function, ArgumentsPtrVector children);

  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

  void setPrecision(uint8_t precision) override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> simplify() override;

  void validate() const override;

private:
  std::shared_ptr<IFunction> function;

  ArgumentsPtrVector children;

  std::string functionToString() const;
};

}