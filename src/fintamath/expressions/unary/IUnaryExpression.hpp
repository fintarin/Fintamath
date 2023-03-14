#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  // void setPrecision(uint8_t precision) final;

  string toString() const final;

  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  // void simplifyValue(bool isPrecise);

protected:
  shared_ptr<IMathObject> simplify() final;

  virtual shared_ptr<IMathObject> preSimplify() const;

  virtual shared_ptr<IMathObject> postSimplify() const;

private:
  string postfixToString() const;

  string prefixToString() const;

  string functionToString() const;

protected:
  shared_ptr<IFunction> func;

  shared_ptr<IMathObject> child;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {
public:
  explicit IUnaryExpressionCRTP(const IFunction &func, const shared_ptr<IMathObject> &child) {
    this->func = cast<IFunction>(func.clone());

    this->child = child;
    compressChild(this->child);
  }
};

}