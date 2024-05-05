#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IUnaryExpression)

using namespace detail;

IUnaryExpression::IUnaryExpression(const IFunction &inFunc, ArgumentPtr rhs)
    : func(cast<IFunction>(inFunc.clone())),
      child(std::move(rhs)) {
}

std::string IUnaryExpression::toString() const {
  const auto &outFunc = getOutputFunction();
  const auto outOper = cast<IOperator>(outFunc);

  if (!outOper) {
    return functionToString(*outFunc, {child});
  }

  if (outOper->getPriority() == IOperator::Priority::PostfixUnary) {
    return postfixUnaryOperatorToString(*outOper, child);
  }

  return prefixUnaryOperatorToString(*outOper, child);
}

const std::shared_ptr<IFunction> &IUnaryExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &IUnaryExpression::getChildren() const {
  childrenCached = {child};
  return childrenCached;
}

IUnaryExpression::SimplifyFunctionVector IUnaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IUnaryExpression::SimplifyFunctionVector IUnaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

ArgumentPtr IUnaryExpression::tranform(const State newState) const {
  ArgumentPtr res;

  switch (newState) {
    case State::PreSimplify: {
      res = useSimplifyFunctions(getFunctionsForPreSimplify(), *func, child);
      break;
    }
    case State::Simplify: {
      res = useSimplifyFunctions(getFunctionsForPostSimplify(), *func, child);
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

}