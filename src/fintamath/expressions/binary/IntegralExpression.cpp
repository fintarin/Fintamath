#include "fintamath/expressions/binary/IntegralExpression.hpp"

#include <utility>

#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/calculus/Integral.hpp"

namespace fintamath {

IntegralExpression::IntegralExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Integral{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

IntegralExpression::SimplifyFunctionVector IntegralExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &IntegralExpression::integralSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr IntegralExpression::integralSimplify(const IFunction & /*func*/, const ArgumentPtr & /*lhs*/, const ArgumentPtr & /*rhs*/) {
  // TODO: implement integral simplify
  return {};
}

}
