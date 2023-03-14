#include "fintamath/expressions/binary/IBinaryExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"

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

shared_ptr<IMathObject> IBinaryExpression::preSimplify() const {
  return {};
}

shared_ptr<IMathObject> IBinaryExpression::postSimplify() const {
  return {};
}

shared_ptr<IMathObject> IBinaryExpression::simplify() {
  if (auto res = preSimplify()) {
    simplifyChild(res);
    return res;
  }

  simplifyChild(lhsChild);
  simplifyChild(rhsChild);

  if (func->isNonExressionEvaluatable() && func->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*func)(*lhsChild, *rhsChild);
  }

  if (auto res = preSimplify()) { // TODO: try to remove this
    return res;
  }

  if (auto res = postSimplify()) {
    return res;
  }

  return {};
}

}
