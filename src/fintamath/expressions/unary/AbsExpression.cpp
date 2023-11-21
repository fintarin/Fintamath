#include "fintamath/expressions/unary/AbsExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

AbsExpression::AbsExpression(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Abs(), std::move(inChild)) {
}

AbsExpression::SimplifyFunctionVector AbsExpression::getFunctionsForPostSimplify() const {
  static const AbsExpression::SimplifyFunctionVector simplifyFunctions = {
      &AbsExpression::constSimplify,
      &AbsExpression::negSimplify,
      &AbsExpression::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AbsExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isInfinity(rhs)) {
    return Inf().clone();
  }

  return {};
}

ArgumentPtr AbsExpression::intApproximateSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  if (const auto approxNum = cast<INumber>(approx); approxNum && *approxNum < Integer(0)) {
    return absExpr(negExpr(rhs));
  }

  return {};
}

ArgumentPtr AbsExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return absExpr(negExpr(rhs));
  }

  return {};
}

}
