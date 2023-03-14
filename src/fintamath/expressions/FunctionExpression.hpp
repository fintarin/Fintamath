#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
class FunctionExpression : public IExpressionCRTP<FunctionExpression> {
public:
  explicit FunctionExpression(const IFunction &function, const ArgumentsPtrVector &children);

  string toString() const override;

  shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

protected:
  shared_ptr<IMathObject> simplify() override;

  // void setPrecision(uint8_t precision) override;

private:
  shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

  string functionToString() const;
};

}