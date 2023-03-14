#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : virtual public IExpression {
public:
  // void setPrecision(uint8_t precision) final;

  string toString() const final;

  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

protected:
  virtual shared_ptr<IMathObject> preSimplify() const;

  virtual shared_ptr<IMathObject> postSimplify() const;

  shared_ptr<IMathObject> simplify() final;

  void validate() const final;

protected:
  shared_ptr<IFunction> func;

  shared_ptr<IMathObject> lhsChild;

  shared_ptr<IMathObject> rhsChild;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {
public:
  explicit IBinaryExpressionCRTP(const IFunction &func, const shared_ptr<IMathObject> &lhsChild,
                                 const shared_ptr<IMathObject> &rhsChild) {

    this->func = cast<IFunction>(func.clone());

    this->lhsChild = lhsChild;
    compressChild(this->lhsChild);

    this->rhsChild = rhsChild;
    compressChild(this->rhsChild);
  }
};

}