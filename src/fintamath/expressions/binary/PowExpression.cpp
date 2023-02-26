#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
// #include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
}

MathObjectPtr PowExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr PowExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<PowExpression>(*this);

  auto *lhsPtr = cast<IExpression>(exprObj->lhsInfo.get());
  auto *rhsPtr = cast<Integer>(exprObj->rhsInfo.get());

  if (lhsPtr && rhsPtr && !is<Expression>(lhsPtr)) {
    lhsPtr = cast<IExpression>(lhsPtr->simplify(isPrecise).get());
    if (*rhsPtr == ZERO) {
      return ONE.clone();
    }
    if (*lhsPtr == ONE || *rhsPtr == ONE) {
      return lhsPtr->clone();
    }
    if (*rhsPtr == NEG_ONE) {
      return InvExpression(lhsPtr->clone()).simplify(isPrecise);
    }

    Integer rhs = *rhsPtr;

    bool isInverted = false;
    if (rhs < ZERO) {
      isInverted = true;
      rhs = -rhs;
    }

    // MulExpression mul(MulExpression::ArgumentsPtrVector{});
    /*
    for (size_t i = 0; i < rhs; i++) {
      mul.addElement(exprObj->lhsInfo);
    }

    if (isInverted) {
      return InvExpression(mul.simplify()).simplify();
    }
    return mul.simplify();*/
  }

  return exprObj;
}

const IFunction *PowExpression::getFunction() const {
  return &POW;
}

}
