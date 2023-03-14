#include "fintamath/expressions/unary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Derivative DER;

DerivativeExpression::DerivativeExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(DER, child) {
}

// unique_ptr<IMathObject> DerivativeExpression::simplify(bool isPrecise) const {
// unique_ptr<IMathObject> value;

// if (const auto *expr = cast<IExpression>(child)) {
//   value = expr->simplify(isPrecise);
// } else {
//   value = child->toMinimalObject();
// }

// if (is<IExpression>(value)) {
//   // TODO: implement derivative of expression
//   return make_unique<DerivativeExpression>(move(value));
// }
// if (is<INumber>(value) || is<IConstant>(value)) {
//   return ZERO.clone();
// }
// if (is<Variable>(value)) {
//   return ONE.clone();
// }

// return clone();
// }

ArgumentPtr DerivativeExpression::postSimplify() const {
  if (is<IExpression>(child)) {
    // TODO: implement derivative of expression
    return {};
  }

  if (is<INumber>(child) || is<IConstant>(child)) {
    return ZERO.clone();
  }
  if (is<Variable>(child)) {
    return ONE.clone();
  }

  return {};
}

}
