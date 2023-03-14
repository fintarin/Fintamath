#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/polynomial/OrExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/literals/constants/False.hpp"

namespace fintamath {

const And AND;

AndExpression::AndExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(AND, children) {
}

string AndExpression::toString() const {
  return binaryOperatorToString(AND, children);
}

// unique_ptr<IMathObject> AndExpression::simplify(bool /*isPrecise*/) const {
// unique_ptr<IMathObject> result = polynomVect.front()->clone();
// for (size_t i = 1; i < polynomVect.size(); i++) {
//   const unique_ptr<IMathObject> &lhsPtr = result;
//   const unique_ptr<IMathObject> &rhsPtr = polynomVect[i];
//   const IMathObject &lhs = *lhsPtr;
//   const IMathObject &rhs = *rhsPtr;

//   if (const auto *lhsBool = cast<Boolean>(&lhs)) {
//     if (*lhsBool == true) {
//       *result = *rhsPtr;
//     } else {
//       result = make_unique<Boolean>(false);
//     }
//     continue;
//   }

//   if (const auto *rhsBool = cast<Boolean>(&rhs)) {
//     if (*rhsBool == true) {
//       *result = *lhsPtr;
//     } else {
//       result = make_unique<Boolean>(false);
//     }
//     continue;
//   }

//   if (lhs == notL(rhs)) {
//     result = make_unique<Boolean>(false);
//   }
// }

// return result;
// }

void AndExpression::logicNegate() {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(Expression::makeRawFunctionExpression(Not(), {child}));
  }

  children = {make_shared<OrExpression>(negChildren)};
}

shared_ptr<IMathObject> AndExpression::postSimplify(size_t lhsChildNum, size_t rhsChildNum) const {
  const shared_ptr<IMathObject> &lhsChild = children[lhsChildNum];
  const shared_ptr<IMathObject> &rhsChild = children[rhsChildNum];

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? rhsChild : lhsChild;
  }
  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? lhsChild : rhsChild;
  }

  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  if (const auto lhsNot = cast<NotExpression>(lhsChild); lhsNot && *lhsNot->getChildren().front() == *rhsChild) {
    return make_shared<Boolean>(false);
  }
  if (const auto rhsNot = cast<NotExpression>(rhsChild); rhsNot && *rhsNot->getChildren().front() == *lhsChild) {
    return make_shared<Boolean>(false);
  }

  return {};
}

}
