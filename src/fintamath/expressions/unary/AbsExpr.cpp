#include "fintamath/expressions/unary/AbsExpr.hpp"

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

AbsExpr::AbsExpr(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Abs{}, std::move(inChild)) {
}

AbsExpr::SimplifyFunctionVector AbsExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AbsExpr::constSimplify,
      &AbsExpr::negSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AbsExpr::constSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isInfinity(rhs)) {
    return Inf{}.clone();
  }

  return {};
}

ArgumentPtr AbsExpr::negSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return absExpr(negExpr(rhs));
  }

  return {};
}

}
