#include "fintamath/expressions/binary/IndexExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/expressions/IBinaryExpression.hpp"
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

IndexExpression::IndexExpression(const IMathObject &lhs, const IMathObject &rhs) : IBinaryExpression(lhs, rhs) {
}

IndexExpression::IndexExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
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

const IFunction *IndexExpression::getFunction() const {
  return &INDEX;
}

MathObjectPtr IndexExpression::toMinimalObject() const {
  return simplify(true);
}

MathObjectPtr IndexExpression::simplify(bool isPrecise) const {
  MathObjectPtr lhs;
  MathObjectPtr rhs;

  if (const auto *expr = cast<IExpression>(lhsInfo.get())) {
    lhs = expr->simplify(isPrecise);
  } else {
    lhs = lhsInfo->toMinimalObject();
  }

  if (const auto *expr = cast<IExpression>(rhsInfo.get())) {
    rhs = expr->simplify(isPrecise);
  } else {
    rhs = rhsInfo->toMinimalObject();
  }

  // TODO: implement derivative of expression

  return std::make_unique<IndexExpression>(std::move(lhs), std::move(rhs));
}

}
