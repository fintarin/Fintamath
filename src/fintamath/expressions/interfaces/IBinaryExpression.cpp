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

using namespace detail;

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IBinaryExpression)

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
  childrenCached.front() = lhsChild;
  childrenCached.back() = rhsChild;
  return childrenCached;
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  const auto simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl->lhsChild);
  preSimplifyChild(simpl->rhsChild);
  return simpl->simplifyRec(false);
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  const auto simpl = cast<IBinaryExpression>(clone());
  postSimplifyChild(simpl->lhsChild);
  postSimplifyChild(simpl->rhsChild);
  return simpl->simplifyRec(true);
}

ArgumentPtr IBinaryExpression::simplifyRec(const bool isPostSimplify) const {
  if (ArgumentPtr res = simplifyUndefined(*func, lhsChild, rhsChild)) {
    return res;
  }

  if (ArgumentPtr res = callFunction(*func, {lhsChild, rhsChild})) {
    return res;
  }

  ArgumentPtr res = isPostSimplify ? useSimplifyFunctions(getFunctionsForPostSimplify(),
                                                          *func,
                                                          lhsChild,
                                                          rhsChild)
                                   : useSimplifyFunctions(getFunctionsForPreSimplify(),
                                                          *func,
                                                          lhsChild,
                                                          rhsChild);

  if (res && *res != *this) {
    if (isPostSimplify) {
      postSimplifyChild(res);
    }
    else {
      preSimplifyChild(res);
    }

    return res;
  }

  return clone();
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

void IBinaryExpression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.size() != 2) {
    throw InvalidInputFunctionException(toString(), argumentVectorToStringVector(childVect));
  }

  lhsChild = childVect[0];
  rhsChild = childVect[1];
}

}
