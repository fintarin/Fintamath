#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

ArgumentsPtrVector IExpression::getVariables() const {
  return {};
}

void IExpression::compressChild(ArgumentPtr &child) {
  for (;;) {
    if (const auto expr = cast<IExpression>(child); expr && !expr->getFunction()) {
      child = expr->getChildren().front();
    }
    else {
      break;
    }
  }
}

void IExpression::simplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->simplify()) {
      child = simplObj;
    }
  }
  else if (const auto constChild = cast<IConstant>(child)) {
    ArgumentPtr constVal = (*constChild)();

    if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise()) {
      child = constChild;
    }
    else {
      child = constVal;
    }
  }
}

// void IExpression::setMathObjectPrecision(ArgumentPtr &obj, uint8_t precision) {
//   if (is<INumber>(obj)) {
//     obj = make_shared<Real>(convert<Real>(*obj).precise(precision));
//     return;
//   }

//   if (auto expr = cast<IExpression>(obj)) {
//     expr->setPrecision(precision);
//     return;
//   }
// }

}
