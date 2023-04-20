#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class FunctionExpression : public IExpressionCRTP<FunctionExpression> {
public:
  explicit FunctionExpression(const IFunction &function, const ArgumentsPtrVector &children);

  string toString() const override;

  shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

protected:
  ArgumentPtr simplify() const override;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

  string functionToString() const;
};

}