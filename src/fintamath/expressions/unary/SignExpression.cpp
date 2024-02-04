#include "fintamath/expressions/unary/SignExpression.hpp"

#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

SignExpression::SignExpression(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Sign{}, std::move(inChild)) {
}

SignExpression::SimplifyFunctionVector SignExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &SignExpression::constSimplify,
      &SignExpression::negSimplify,
      &SignExpression::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr SignExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (is<Inf>(rhs)) {
    return Integer(1).clone();
  }

  if (is<NegInf>(rhs)) {
    return Integer(-1).clone();
  }

  if (is<ComplexInf>(rhs)) {
    return Undefined{}.clone();
  }

  return {};
}

ArgumentPtr SignExpression::intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  if (const auto approxNum = cast<INumber>(approx); approxNum && !approxNum->isComplex()) {
    return callFunction(func, {approx});
  }

  return {};
}

ArgumentPtr SignExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(signExpr(negExpr(rhs)));
  }

  return {};
}

}
