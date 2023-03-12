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

std::shared_ptr<IMathObject> OrExpression::simplify() {
  std::shared_ptr<IMathObject> result = children.front();

  for (size_t i = 1; i < children.size(); i++) {
    const std::shared_ptr<IMathObject> &rhsPtr = children[i];

    if (const auto lhsBool = cast<Boolean>(result)) {
      if (*lhsBool == true) {
        result = std::make_shared<Boolean>(true);
      } else {
        *result = *rhsPtr;
      }

      continue;
    }

    if (const auto rhsBool = cast<Boolean>(rhsPtr)) {
      if (*rhsBool == true) {
        result = std::make_shared<Boolean>(true);
      }

      continue;
    }

    if (*result == notL(*rhsPtr)) {
      result = std::make_shared<Boolean>(true);
    }
  }

  return result;
}

}
