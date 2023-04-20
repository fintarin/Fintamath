#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  string toString() const override;

  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

protected:
  ArgumentPtr simplify() const final;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  string postfixToString() const;

  string prefixToString() const;

  string functionToString() const;

protected:
  shared_ptr<IFunction> func;

  ArgumentPtr child;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {
public:
  explicit IUnaryExpressionCRTP(const IFunction &func, const ArgumentPtr &child) {
    this->func = cast<IFunction>(func.clone());

    this->child = child;
    compressChild(this->child);
  }
};

}