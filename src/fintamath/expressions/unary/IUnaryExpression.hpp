#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  void simplifyValue(bool isPrecise);

protected:
  virtual std::shared_ptr<IMathObject> preSimplify() const;

  virtual std::shared_ptr<IMathObject> postSimplify() const;

  std::shared_ptr<IMathObject> simplify() final;

  void validate() const final;

private:
  std::string postfixToString() const;

  std::string prefixToString() const;

  std::string functionToString() const;

protected:
  std::shared_ptr<IFunction> func;

  std::shared_ptr<IMathObject> child;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {
public:
  explicit IUnaryExpressionCRTP(const IFunction &func, const std::shared_ptr<IMathObject> &child) {
    this->func = cast<IFunction>(func.clone());

    this->child = child;
    compressChild(this->child);
  }
};

}