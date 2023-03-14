#include "fintamath/expressions/binary/IndexExpression.hpp"

#include "fintamath/functions/other/Index.hpp"

namespace fintamath {

const Index INDEX;

IndexExpression::IndexExpression(const shared_ptr<IMathObject> &lhsChild, const shared_ptr<IMathObject> &rhsChild)
    : IBinaryExpressionCRTP(INDEX, lhsChild, rhsChild) {
}

// string IndexExpression::toString() const {
//   // TODO: remove this and use general toString() from BinaryExpression

//   string lhsStr = lhsInfo->toString();
//   if (is<IExpression>(lhsInfo)) {
//     lhsStr = "(" + lhsStr + ")";
//   }

//   string rhsStr = rhsInfo->toString();
//   if (is<IExpression>(rhsInfo)) {
//     rhsStr = "(" + rhsStr + ")";
//   }

//   return lhsStr + "_" + rhsStr;
// }

// unique_ptr<IMathObject> IndexExpression::simplify(bool isPrecise) const {
// unique_ptr<IMathObject> lhs;
// unique_ptr<IMathObject> rhs;

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

// return make_unique<IndexExpression>(move(lhs), move(rhs));
// }

}
