#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include <memory>

namespace fintamath {

const Or OR;

OrExpression::OrExpression(ArgumentsPtrVector children) : IPolynomExpression(OR, std::move(children)) {
}

std::string OrExpression::toString() const {
  return binaryOperatorToString(OR, children);
}

std::unique_ptr<IMathObject> OrExpression::simplify(bool /*isPrecise*/) const {
  // std::unique_ptr<IMathObject> result = children.front()->clone();
  // for (size_t i = 1; i < children.size(); i++) {
  //   const auto &lhsPtr = result;
  //   const auto &rhsPtr = children[i];
  //   const auto &lhs = *lhsPtr;
  //   const auto &rhs = *rhsPtr;

  //   if (const auto *lhsBool = cast<Boolean>(&lhs)) {
  //     if (*lhsBool == true) {
  //       result = std::make_unique<Boolean>(true);
  //     } else {
  //       *result = *rhsPtr;
  //     }
  //     continue;
  //   }

  //   if (const auto *rhsBool = cast<Boolean>(&rhs)) {
  //     if (*rhsBool == true) {
  //       result = std::make_unique<Boolean>(true);
  //     } else {
  //       *result = *lhsPtr;
  //     }
  //     continue;
  //   }

  //   if (lhs == notL(rhs)) {
  //     result = std::make_unique<Boolean>(true);
  //   }
  // }

  // return result;

  return std::make_unique<OrExpression>(*this);
}

std::shared_ptr<IMathObject> OrExpression::simplifyChildren(const std::shared_ptr<IMathObject> &lhsChild,
                                                            const std::shared_ptr<IMathObject> &rhsChild) {
  if (func->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*func)(*lhsChild, *rhsChild);
  }

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? std::make_shared<Boolean>(true) : rhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? std::make_shared<Boolean>(true) : lhsChild;
  }

  if (*lhsChild == notL(*rhsChild)) {
    return std::make_shared<Boolean>(true);
  }

  return nullptr;
}

}
