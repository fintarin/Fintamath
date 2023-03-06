#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
  function = cast<IFunction>(POW.clone());
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
      MathObjectPtr invExpr = std::make_unique<InvExpression>(std::move(lhsChild));
      simplifyExpr(invExpr);
      return invExpr.release();
    }
  }

  if (function->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*function)(*lhsChild, *rhsChild).release();
  }
  return this;
}

void PowExpression::invert() {
  lhsChild = std::make_unique<NegExpression>(std::move(lhsChild));
  simplifyExpr(lhsChild);
}

MathObjectPtr PowExpression::polynomialSimplify() {
  auto *simplExpr = simplify();
  if (!is<PowExpression>(simplExpr)) {
    return MathObjectPtr(simplExpr);
  }
  auto *powExpr = cast<PowExpression>(simplExpr);

  if (auto *mulExpr = cast<MulExpression>(powExpr->lhsChild.get())) {
    mulExpr->setPow(powExpr->rhsChild);
    return MathObjectPtr(powExpr->lhsChild.release());
  }

  const auto *rhs = cast<Integer>(powExpr->rhsChild.get());
  if (auto *sumExpr = cast<SumExpression>(powExpr->lhsChild.get()); sumExpr && rhs) {
    *powExpr->lhsChild.get() = *sumPolynomSimplify(*sumExpr, *rhs);
    return MathObjectPtr(powExpr->lhsChild.release());
  }

  return MathObjectPtr(powExpr);
}

Integer PowExpression::generateNextNumber(Integer n) {
  Integer u = n & -n;
  Integer v = u + n;
  n = v + (((v ^ n) / u) >> 2);
  return n;
}

Integer PowExpression::generateFirstNum(const Integer &countOfOne) {
  Integer n = 0;
  for (int i = 0; i < countOfOne; i++) {
    n = n << 1 | 1;
  }
  return n;
}

std::vector<Integer> PowExpression::generateSplit(Integer bitNumber, const Integer &variableCount) {
  std::vector<Integer> result;
  Integer counter = 0;
  while (result.size() < variableCount) {
    if (bitNumber % 2 == 1) {
      counter++;
    }
    if (bitNumber % 2 == 0) {
      result.emplace_back(counter);
      counter = 0;
    }
    bitNumber >>= 1;
  }
  return result;
}

IMathObject *PowExpression::sumPolynomSimplify(const SumExpression &sumExpr, const Integer &pow) {
  auto polynom = sumExpr.getPolynom();
  ArgumentsPtrVector newPolynom;
  Integer variableCount = polynom.size();
  Integer bitNumber = generateFirstNum(pow);
  for (int i = 0; i < combinations(pow + variableCount - 1, pow); i++) {
    auto vectOfPows = generateSplit(bitNumber, variableCount);
    bitNumber = generateNextNumber(bitNumber);

    ArgumentsPtrVector mulExprPolynom;
    mulExprPolynom.emplace_back(std::make_unique<Integer>(split(pow, vectOfPows)));
    for (size_t j = 0; j < variableCount; j++) {
      auto powExpr = std::make_unique<PowExpression>(polynom[j]->clone(), vectOfPows[j].clone());
      mulExprPolynom.emplace_back(powExpr->polynomialSimplify());
    }
    MathObjectPtr mulExpr = std::make_unique<MulExpression>(std::move(mulExprPolynom));
    simplifyExpr(mulExpr);
    newPolynom.emplace_back(std::move(mulExpr));
  }

  MathObjectPtr newSumExpr = std::make_unique<SumExpression>(std::move(newPolynom));
  simplifyExpr(newSumExpr);
  return newSumExpr.release();
}

}
