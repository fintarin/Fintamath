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
  virtual ArgumentPtr preSimplify() const;

  virtual ArgumentPtr postSimplify() const;

  ArgumentPtr simplify() const final;

protected:
  shared_ptr<IFunction> func;

  ArgumentPtr lhsChild;

  ArgumentPtr rhsChild;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {
public:
  explicit IBinaryExpressionCRTP(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
    this->func = cast<IFunction>(func.clone());

    this->lhsChild = lhsChild;
    compressChild(this->lhsChild);

    this->rhsChild = rhsChild;
    compressChild(this->rhsChild);
  }
};

}