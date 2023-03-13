#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
class FunctionExpression : public IExpressionCRTP<FunctionExpression> {
public:
  explicit FunctionExpression(const IFunction &function, const ArgumentsPtrVector &children);

  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

protected:
  std::shared_ptr<IMathObject> simplify() override;

  // void setPrecision(uint8_t precision) override;

  void validate() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

  std::string functionToString() const;
};

}