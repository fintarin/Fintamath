#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IUnaryExpression : virtual public IExpression {
public:
  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const ArgumentPtr &)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  ArgumentPtr simplify() const final;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  virtual SimplifyFunctionsVector getFunctionsForSimplify() const;

private:
  ArgumentPtr globalSimplify() const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr child;
};

template <typename Derived>
class IUnaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IUnaryExpression {
public:
  explicit IUnaryExpressionCRTP(const IFunction &inFunc, const ArgumentPtr &inChild) {
    this->func = cast<IFunction>(inFunc.clone());

    this->child = inChild;
    compressChild(this->child);
  }
};

}