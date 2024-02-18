#pragma once

#include <memory>
#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class FunctionExpression final : public IExpressionCRTP<FunctionExpression> {
public:
  explicit FunctionExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  std::string toString() const override;

  const std::shared_ptr<IFunction> &getFunction() const override;

  const ArgumentPtrVector &getChildren() const override;

  void setChildren(const ArgumentPtrVector &childVect) override;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::FunctionExpression, "FunctionExpression"};
  }

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

}