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

IndexExpression::IndexExpression(std::shared_ptr<IMathObject> lhsChild, std::shared_ptr<IMathObject> rhsChild)
    : IBinaryExpression(INDEX, std::move(lhsChild), std::move(rhsChild)) {
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

std::unique_ptr<IMathObject> IndexExpression::simplify(bool isPrecise) const {
  // std::unique_ptr<IMathObject> lhs;
  // std::unique_ptr<IMathObject> rhs;

  // if (const auto *expr = cast<IExpression>(lhsChild)) {
  //   lhs = expr->simplify(isPrecise);
  // } else {
  //   lhs = lhsChild->toMinimalObject();
  // }

  // if (const auto *expr = cast<IExpression>(rhsChild)) {
  //   rhs = expr->simplify(isPrecise);
  // } else {
  //   rhs = rhsChild->toMinimalObject();
  // }

  // return std::make_unique<IndexExpression>(std::move(lhs), std::move(rhs));

  return std::make_unique<IndexExpression>(*this);
}

std::shared_ptr<IMathObject> IndexExpression::simplifyChildren() {
  return nullptr;
}

}
