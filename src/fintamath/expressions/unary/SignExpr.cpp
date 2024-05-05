#include "fintamath/expressions/unary/SignExpr.hpp"

#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
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

FINTAMATH_CLASS_IMPLEMENTATION(SignExpr)

using namespace detail;

SignExpr::SignExpr(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Sign{}, std::move(inChild)) {
}

SignExpr::SimplifyFunctionVector SignExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &SignExpr::constSimplify,
      &SignExpr::negSimplify,
      &SignExpr::intApproximate,
  };
  return simplifyFunctions;
}

ArgumentPtr SignExpr::constSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
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

ArgumentPtr SignExpr::intApproximate(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateChild(approx);
  approx = cast<SignExpr>(makeExpr(func, rhs))->callFunction();

  if (auto res = cast<INumber>(approx)) {
    return res;
  }

  return {};
}

ArgumentPtr SignExpr::negSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(signExpr(negExpr(rhs)));
  }

  return {};
}

}
