#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/literals/constants/False.hpp"
#include <memory>

namespace fintamath {

const And AND;

AndExpression::AndExpression(ArgumentsPtrVector &&inPolynomVect) : IPolynomExpression(std::move(inPolynomVect)) {
  if (!polynomVect.empty()) {
    compress();
  }
}

std::string AndExpression::toString() const {
  return binaryOperatorToString(AND, polynomVect);
}

std::unique_ptr<IMathObject> AndExpression::simplify(bool /*isPrecise*/) const {
  std::unique_ptr<IMathObject> result = polynomVect.front()->clone();
  for (size_t i = 1; i < polynomVect.size(); i++) {
    const std::unique_ptr<IMathObject> &lhsPtr = result;
    const std::unique_ptr<IMathObject> &rhsPtr = polynomVect[i];
    const IMathObject &lhs = *lhsPtr;
    const IMathObject &rhs = *rhsPtr;

    if (const auto *lhsBool = cast<Boolean>(&lhs)) {
      if (*lhsBool == true) {
        *result = *rhsPtr;
      } else {
        result = std::make_unique<Boolean>(false);
      }
      continue;
    }

    if (const auto *rhsBool = cast<Boolean>(&rhs)) {
      if (*rhsBool == true) {
        *result = *lhsPtr;
      } else {
        result = std::make_unique<Boolean>(false);
      }
      continue;
    }

    if (lhs == notL(rhs)) {
      result = std::make_unique<Boolean>(false);
    }
  }

  return result;
}

const IFunction *AndExpression::getFunction() const {
  return &AND;
}

IMathObject *AndExpression::simplify() {
  auto *result = polynomVect.front().release();

  for (size_t i = 1; i < polynomVect.size(); i++) {
    const auto *rhsPtr = polynomVect[i].get();

    if (const auto *lhsBool = cast<Boolean>(result)) {
      if (*lhsBool == true) {
        *result = *rhsPtr;
      } else {
        result = std::make_unique<Boolean>(false).release(); // TODO: new False() instead??
      }

      continue;
    }

    if (const auto *rhsBool = cast<Boolean>(rhsPtr)) {
      if (*rhsBool != true) {
        result = std::make_unique<Boolean>(false).release(); // TODO: new False() instead??
      }

      continue;
    }

    if (*result == notL(*rhsPtr)) {
      result = std::make_unique<Boolean>(false).release(); // TODO: new False() instead??
    }
  }

  return result;
}

}
