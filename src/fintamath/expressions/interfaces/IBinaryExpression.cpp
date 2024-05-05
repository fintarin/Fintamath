#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IBinaryExpression)

using namespace detail;

IBinaryExpression::IBinaryExpression(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
    : func(cast<IFunction>(inFunc.clone())),
      lhsChild(std::move(lhs)),
      rhsChild(std::move(rhs)) {
}

std::string IBinaryExpression::toString() const {
  const auto &outFunc = getOutputFunction();
  const auto outOper = cast<IOperator>(outFunc);

  if (!outOper) {
    return functionToString(*outFunc, {lhsChild, rhsChild});
  }

  return binaryOperatorToString(*outOper, lhsChild, rhsChild);
}

const std::shared_ptr<IFunction> &IBinaryExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &IBinaryExpression::getChildren() const {
  childrenCached = {lhsChild, rhsChild};
  return childrenCached;
}

ArgumentPtr IBinaryExpression::tranform(const State newState) const {
  ArgumentPtr res;

  switch (newState) {
    case State::PreSimplify: {
      res = useSimplifyFunctions(getFunctionsForPreSimplify(), *func, lhsChild, rhsChild);
      break;
    }
    case State::Simplify: {
      res = useSimplifyFunctions(getFunctionsForPostSimplify(), *func, lhsChild, rhsChild);
      break;
    }
    default: {
      break;
    }
  }

  if (res) {
    return res;
  }

  return IExpression::tranform(newState);
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

}
