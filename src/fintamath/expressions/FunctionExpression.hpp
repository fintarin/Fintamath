#pragma once

#include <memory>
#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class FunctionExpression : public IExpressionCRTP<FunctionExpression>, public std::enable_shared_from_this<FunctionExpression> {
  FINTAMATH_CLASS_BODY(FunctionExpression, IExpression)

public:
  explicit FunctionExpression(const IFunction &inFunc, ArgumentPtrVector inChildren);

  const std::shared_ptr<IFunction> &getFunction() const override;

  const ArgumentPtrVector &getChildren() const override;

  std::string toString() const override;

private:
  std::shared_ptr<IFunction> func;

  ArgumentPtrVector children;
};

}