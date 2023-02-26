#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/logic/And.hpp"
#include <memory>

namespace fintamath {

const And AND;

AndExpression::AndExpression(PolynomVector inPolynomVect) : IPolynomExpression(std::move(inPolynomVect)) {
  if (!polynomVect.empty()) {
    compress();
  }
}

AndExpression::AndExpression(const IMathObject &rhs) {
  if (const auto *rhsPtr = cast<AndExpression>(&rhs)) {
    *this = *rhsPtr;
    return;
  }

  polynomVect.emplace_back(rhs.clone());
}

std::string AndExpression::toString() const {
  return binaryOperatorToString(AND, polynomVect);
}

MathObjectPtr AndExpression::simplify() const {
  return simplify(false);
}

MathObjectPtr AndExpression::simplify(bool isPrecise) const {
  MathObjectPtr result = polynomVect.front()->clone();
  for (size_t i = 1; i < polynomVect.size(); i++) {
    auto &lhsPtr = result;
    auto &rhsPtr = polynomVect[i];
    auto &lhs = *lhsPtr;
    auto &rhs = *rhsPtr;

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
}
