#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  // void setPrecision(uint8_t precision) final;

  string toString() const final;

  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

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