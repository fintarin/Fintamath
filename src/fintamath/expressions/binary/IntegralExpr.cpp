#include "fintamath/expressions/binary/IntegralExpr.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/calculus/Integral.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(IntegralExpr)

IntegralExpr::IntegralExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Integral{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

IntegralExpr::SimplifyFunctionVector IntegralExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &IntegralExpr::integralSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr IntegralExpr::integralSimplify(const IFunction & /*func*/, const ArgumentPtr & /*lhs*/, const ArgumentPtr & /*rhs*/) {
  // TODO: implement integral simplify
  return {};
}

}
