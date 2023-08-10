#include "fintamath/expressions/unary/InvTrigExpression.hpp"

namespace fintamath {

InvTrigExpression::InvTrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

InvTrigExpression::SimplifyFunctionsVector InvTrigExpression::getFunctionsForPostSimplify() const {
  static const InvTrigExpression::SimplifyFunctionsVector simplifyFunctions = {
      &InvTrigExpression::constSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr InvTrigExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr & /*rhs*/) {
  // TODO! implement
  return {};
}

}
