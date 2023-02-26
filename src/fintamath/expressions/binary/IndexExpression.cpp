#include "fintamath/expressions/binary/IndexExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Index INDEX;

IndexExpression::IndexExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
  function = cast<IFunction>(INDEX.clone());
}

// std::string IndexExpression::toString() const {
//   // TODO: remove this and use general toString() from BinaryExpression

//   std::string lhsStr = lhsInfo->toString();
//   if (is<IExpression>(lhsInfo)) {
//     lhsStr = "(" + lhsStr + ")";
//   }

//   std::string rhsStr = rhsInfo->toString();
//   if (is<IExpression>(rhsInfo)) {
//     rhsStr = "(" + rhsStr + ")";
//   }

//   return lhsStr + "_" + rhsStr;
// }

MathObjectPtr IndexExpression::toMinimalObject() const {
  return simplify(true);
}

MathObjectPtr IndexExpression::simplify(bool isPrecise) const {
  MathObjectPtr lhs;
  MathObjectPtr rhs;

  if (const auto *expr = cast<IExpression>(lhsChild.get())) {
    lhs = expr->simplify(isPrecise);
  } else {
    lhs = lhsChild->toMinimalObject();
  }

  if (const auto *expr = cast<IExpression>(rhsChild.get())) {
    rhs = expr->simplify(isPrecise);
  } else {
    rhs = rhsChild->toMinimalObject();
  }

  return std::make_unique<IndexExpression>(std::move(lhs), std::move(rhs));
}

IMathObject *IndexExpression::simplify() {
  return this;
}

}
