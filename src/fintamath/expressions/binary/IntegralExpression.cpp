#include "fintamath/expressions/binary/IntegralExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/calculus/Integral.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

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
