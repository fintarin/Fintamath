#include "fintamath/expressions/IBinaryExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

std::string IBinaryExpression::toString() const {
  if (auto oper = cast<IOperator>(func)) {
    return binaryOperatorToString(*oper, {lhsChild, rhsChild});
  }

  return functionToString(*func, {lhsChild, rhsChild});
}

std::shared_ptr<IFunction> IBinaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IBinaryExpression::getChildren() const {
  return {lhsChild, rhsChild};
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl->lhsChild);
  preSimplifyChild(simpl->rhsChild);

  if (auto res = simpl->globalSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  postSimplifyChild(simpl->lhsChild);
  postSimplifyChild(simpl->rhsChild);

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->lhsChild, simpl->rhsChild})) {
    return res;
  }

  if (auto res = simpl->globalSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr IBinaryExpression::simplify() const {
  ArgumentPtr simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl);
  postSimplifyChild(simpl);
  return simpl;
}

ArgumentPtr IBinaryExpression::globalSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  const SimplifyFunctionsVector simplFunctions = getFunctionsForSimplify();

  for (const auto &simplFunc : simplFunctions) {
    if (auto res = simplFunc(simpl->lhsChild, simpl->rhsChild)) {
      return res;
    }
  }

  return {};
}

IBinaryExpression::SimplifyFunctionsVector IBinaryExpression::getFunctionsForSimplify() const {
  return {};
}

IBinaryExpression::SimplifyFunctionsVector IBinaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

void IBinaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 2) {
    std::vector<std::string> argNamesVect(childVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect[i] = childVect[i].get()->toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

  lhsChild = childVect[0];
  rhsChild = childVect[1];
}

}
