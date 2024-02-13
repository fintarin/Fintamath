#include "fintamath/expressions/unary/AbsExpression.hpp"

#include <utility>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/constants/Inf.hpp"

namespace fintamath {

using namespace detail;

AbsExpression::AbsExpression(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Abs{}, std::move(inChild)) {
}

AbsExpression::SimplifyFunctionVector AbsExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AbsExpression::constSimplify,
      &AbsExpression::negSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AbsExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isInfinity(rhs)) {
    return Inf{}.clone();
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
