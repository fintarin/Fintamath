#include "fintamath/expressions/unary/InvTrigonometryExpression.hpp"

namespace fintamath {

InvTrigonometryExpression::InvTrigonometryExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

InvTrigonometryExpression::SimplifyFunctionsVector InvTrigonometryExpression::getFunctionsForPostSimplify() const {
  static const InvTrigonometryExpression::SimplifyFunctionsVector simplifyFunctions = {
      &InvTrigonometryExpression::constantsSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr InvTrigonometryExpression::constantsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  // TODO! implement
  return {};
}

}
