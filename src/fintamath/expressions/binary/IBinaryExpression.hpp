#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : virtual public IExpression {
public:
  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

protected:
  virtual std::shared_ptr<IMathObject> preSimplify();

  virtual std::shared_ptr<IMathObject> postSimplify();

  std::shared_ptr<IMathObject> simplify() final;

  void validate() const final;

protected:
  std::shared_ptr<IFunction> func;

  std::shared_ptr<IMathObject> lhsChild;

  std::shared_ptr<IMathObject> rhsChild;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {
public:
  explicit IBinaryExpressionCRTP(const IFunction &func, const std::shared_ptr<IMathObject> &lhsChild,
                                 const std::shared_ptr<IMathObject> &rhsChild) {

    this->func = cast<IFunction>(func.clone());

    this->lhsChild = lhsChild;
    compressChild(this->lhsChild);

    this->rhsChild = rhsChild;
    compressChild(this->rhsChild);
  }
};

}