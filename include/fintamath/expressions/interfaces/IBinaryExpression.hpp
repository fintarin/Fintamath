#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : virtual public IExpression {
public:
  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  void setChildren(const ArgumentsPtrVector &childVect) final;

protected:
  using SimplifyFunction = std::function<ArgumentPtr(const ArgumentPtr &, const ArgumentPtr &)>;

  using SimplifyFunctionsVector = std::vector<SimplifyFunction>;

  virtual SimplifyFunctionsVector getFunctionsForSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPreSimplify() const;

  virtual SimplifyFunctionsVector getFunctionsForPostSimplify() const;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

  ArgumentPtr simplify() const final;

private:
  ArgumentPtr useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs) const;

protected:
  std::shared_ptr<IFunction> func;

  ArgumentPtr lhsChild;

  ArgumentPtr rhsChild;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {
public:
  explicit IBinaryExpressionCRTP(const IFunction &inFunc, const ArgumentPtr &inLhsChild,
                                 const ArgumentPtr &inRhsChild) {
    this->func = cast<IFunction>(inFunc.clone());

    this->lhsChild = inLhsChild;
    compressChild(this->lhsChild);

    this->rhsChild = inRhsChild;
    compressChild(this->rhsChild);
  }
};

}