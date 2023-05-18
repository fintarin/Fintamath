#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class FunctionExpression : public IExpressionCRTP<FunctionExpression, true> {
public:
  explicit FunctionExpression(const IFunction &inFunc, const ArgumentsPtrVector &inChildren);

  std::string toString() const override;

  std::shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::FunctionExpression);
  }

protected:
  ArgumentPtr simplify() const override;

  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentsPtrVector children;
};

}