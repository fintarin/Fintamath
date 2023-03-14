#include "fintamath/expressions/binary/IBinaryExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"

namespace fintamath {

// void IBinaryExpression::setPrecision(uint8_t precision) {
//   setMathObjectPrecision(lhsChild, precision);
//   setMathObjectPrecision(rhsChild, precision);
// }

string IBinaryExpression::toString() const {
  ArgumentsPtrVector values;
  values.emplace_back(lhsChild);
  values.emplace_back(rhsChild);
  return binaryOperatorToString(*cast<IOperator>(getFunction()), values);
}

shared_ptr<IFunction> IBinaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IBinaryExpression::getChildren() const {
  return {lhsChild, rhsChild};
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  return {};
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  return {};
}

ArgumentPtr IBinaryExpression::simplify() const {
  if (auto res = preSimplify()) {
    simplifyChild(res);
    return res;
  }

  auto simpl = cast<IBinaryExpression>(clone());
  simplifyChild(simpl->lhsChild);
  simplifyChild(simpl->rhsChild);

  if (func->isNonExressionEvaluatable() && func->doArgsMatch({*simpl->lhsChild, *simpl->rhsChild})) {
    return (*func)(*simpl->lhsChild, *simpl->rhsChild);
  }

  if (auto res = simpl->preSimplify()) { // TODO: try to remove this
    return res;
  }

  if (auto res = simpl->postSimplify()) {
    return res;
  }

  return simpl;
}

}
