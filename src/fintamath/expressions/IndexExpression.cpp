#include "fintamath/expressions/IndexExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
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

IndexExpression::IndexExpression(const IndexExpression &rhs)
    : lhsInfo(rhs.lhsInfo->clone()), rhsInfo(rhs.rhsInfo->clone()) {
}

IndexExpression &IndexExpression::operator=(const IndexExpression &rhs) {
  if (this != &rhs) {
    lhsInfo = rhs.lhsInfo->clone();
    rhsInfo = rhs.rhsInfo->clone();
  }

  return *this;
}

IndexExpression::IndexExpression(const IMathObject &lhs, const IMathObject &rhs)
    : lhsInfo(lhs.clone()), rhsInfo(rhs.clone()) {
}

IndexExpression::IndexExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : lhsInfo(std::move(lhs)), rhsInfo(std::move(rhs)) {
}

std::string IndexExpression::toString() const {
  // TODO: remove this and use general toString() from BinaryExpression

  std::string lhsStr = lhsInfo->toString();
  if (is<IExpression>(lhsInfo)) {
    lhsStr = "(" + lhsStr + ")";
  }

  std::string rhsStr = rhsInfo->toString();
  if (is<IExpression>(rhsInfo)) {
    rhsStr = "(" + rhsStr + ")";
  }

  return lhsStr + "_" + rhsStr;
}

const IFunction *IndexExpression::getFunction() const {
  return &INDEX;
}

void IndexExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(lhsInfo.get())) {
    expr->setPrecision(precision);
  }

  if (auto *expr = cast<IExpression>(rhsInfo.get())) {
    expr->setPrecision(precision);
  }
}

MathObjectPtr IndexExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr IndexExpression::simplify(bool isPrecise) const {
  MathObjectPtr lhs;
  MathObjectPtr rhs;

  if (const auto *expr = cast<IExpression>(lhsInfo.get())) {
    lhs = expr->simplify(isPrecise);
  } else {
    lhs = lhsInfo->simplify();
  }

  if (const auto *expr = cast<IExpression>(rhsInfo.get())) {
    rhs = expr->simplify(isPrecise);
  } else {
    rhs = rhsInfo->simplify();
  }

  // TODO: implement derivative of expression

  return std::make_unique<IndexExpression>(std::move(lhs), std::move(rhs));
}

}
