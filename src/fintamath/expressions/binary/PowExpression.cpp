#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
// #include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
  function = cast<IFunction>(POW.clone());
}

MathObjectPtr PowExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr PowExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<PowExpression>(*this);

  auto *lhsPtr = cast<IExpression>(exprObj->lhsChild.get());
  auto *rhsPtr = cast<Integer>(exprObj->rhsChild.get());

  if (lhsPtr && rhsPtr && !is<Expression>(lhsPtr)) {
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

    /*MulExpression mul(MulExpression::ArgumentsPtrVector{});
    for (size_t i = 0; i < rhs; i++) {
      mul.addElement(exprObj->lhsInfo);
    }

    if (isInverted) {
      return InvExpression(mul.simplify()).simplify();
    }
    return mul.simplify();*/
  }

  if (is<INumber>(exprObj->lhsChild) && is<INumber>(exprObj->rhsChild)) {
    return POW(*exprObj->lhsChild, *exprObj->rhsChild);
  }
  return exprObj;
}

IMathObject *PowExpression::simplify() {
  simplifyExpr(lhsChild);
  simplifyExpr(rhsChild);

  auto *lhsPtr = cast<IExpression>(lhsChild.get());
  auto *rhsPtr = cast<Integer>(rhsChild.get());

  if (lhsPtr && rhsPtr) {
    if (*rhsPtr == ZERO) {
      return ONE.clone().release();
    }
    if (*lhsPtr == ONE || *rhsPtr == ONE) {
      return lhsPtr;
    }
    if (*rhsPtr == NEG_ONE) {
      return nullptr;
    }

    // TODO: add logic for (x+y)^10
  }

  if (function->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*function)(*lhsChild, *rhsChild).release();
  }
  return this;
}

}
