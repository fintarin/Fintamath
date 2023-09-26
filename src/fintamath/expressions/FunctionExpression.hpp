#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class FunctionExpression : public IExpressionCRTP<FunctionExpression, true> {
public:
  explicit FunctionExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const override;

  const ArgumentPtrVector &getChildren() const override;

  void setChildren(const ArgumentPtrVector &childVect) override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::FunctionExpression;
  }

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

}