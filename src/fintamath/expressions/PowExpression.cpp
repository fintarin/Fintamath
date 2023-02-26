#include "fintamath/expressions/PowExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/InvExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(const IMathObject &lhs, const IMathObject &rhs) : IBinaryExpression(lhs, rhs) {
}

PowExpression::PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
}

MathObjectPtr PowExpression::simplify() const {
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
      return InvExpression(MathObjectPtr(lhsPtr)).simplify(isPrecise);
    }

    // TODO: implement this logic when Polynom will be implemented
    // Integer rhs = *rhsPtr;
    // MulElement lhs = std::move(lhsInfo);
    //  if (rhs < ZERO) {
    //    lhs.inverted = true;
    //    rhs = -rhs;
    //  }

    // MulExpression mul;
    // for (size_t i = 0; i < rhs; i++) {
    //   mul.addElement(lhs);
    // }

    // info = mul.simplify();
    // children.clear();
  }

  return exprObj;
}

const IFunction *PowExpression::getFunction() const {
  return &POW;
}

}
