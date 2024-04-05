#pragma once

#include <memory>
#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class FunctionExpression final : public IExpressionCRTP<FunctionExpression> {
  FINTAMATH_CLASS_BODY(FunctionExpression)

public:
  explicit FunctionExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  std::string toString() const noexcept override;

  const std::shared_ptr<IFunction> &getFunction() const noexcept override;

  const ArgumentPtrVector &getChildren() const noexcept override;

  void setChildren(const ArgumentPtrVector &childVect) override;

protected:
  ArgumentPtr preSimplify() const override;

  ArgumentPtr postSimplify() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

}