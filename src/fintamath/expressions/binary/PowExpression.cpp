#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(std::unique_ptr<IMathObject> &&lhs, std::unique_ptr<IMathObject> &&rhs)
    : IBinaryExpression(std::move(lhs), std::move(rhs)) {
  function = cast<IFunction>(POW.clone());
}

std::unique_ptr<IMathObject> PowExpression::simplify(bool isPrecise) const {
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
      std::unique_ptr<IMathObject> invExpr = std::make_unique<InvExpression>(std::move(lhsChild));
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
  rhsChild = std::make_unique<NegExpression>(std::move(rhsChild));
  simplifyExpr(rhsChild);
}

IMathObject *PowExpression::mulSimplify() {
  auto *simplExpr = simplify();
  if (!is<PowExpression>(simplExpr)) {
    return simplExpr;
  }
  auto *powExpr = cast<PowExpression>(simplExpr);

  if (auto *mulExpr = cast<MulExpression>(powExpr->lhsChild.get())) {
    mulExpr->setPow(powExpr->rhsChild);
    std::unique_ptr<IMathObject> mulExprResult(powExpr->lhsChild.release());
    simplifyExpr(mulExprResult);
    return mulExprResult.release();
  }
  return powExpr;
}

IMathObject *PowExpression::sumSimplify() {
  auto *simplExpr = simplify();
  if (!is<PowExpression>(simplExpr)) {
    return simplExpr;
  }
  auto *powExpr = cast<PowExpression>(simplExpr);

  const auto *rhs = cast<Integer>(powExpr->rhsChild.get());
  if (auto *sumExpr = cast<SumExpression>(powExpr->lhsChild.get()); sumExpr && rhs) {
    return std::unique_ptr<IMathObject>(sumPolynomSimplify(*sumExpr, *rhs)).release();
  }

  return powExpr;
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

IMathObject *PowExpression::sumPolynomSimplify(const SumExpression &sumExpr, Integer pow) {
  auto polynom = sumExpr.getPolynom();
  ArgumentsPtrVector newPolynom;
  Integer variableCount = polynom.size();

  bool invert = false;
  if (pow < ZERO) {
    pow = abs(pow);
    invert = true;
  }

  Integer bitNumber = generateFirstNum(pow);
  for (int i = 0; i < combinations(pow + variableCount - 1, pow); i++) {
    auto vectOfPows = generateSplit(bitNumber, variableCount);
    bitNumber = generateNextNumber(bitNumber);

    ArgumentsPtrVector mulExprPolynom;
    mulExprPolynom.emplace_back(std::make_unique<Integer>(split(pow, vectOfPows)));
    for (size_t j = 0; j < variableCount; j++) {
      auto *powExpr = new PowExpression(polynom[j]->clone(), vectOfPows[j].clone());
      mulExprPolynom.emplace_back(powExpr->polynomSimplify());
    }
    std::unique_ptr<IMathObject> mulExpr = std::make_unique<MulExpression>(std::move(mulExprPolynom));
    simplifyExpr(mulExpr);
    newPolynom.emplace_back(std::move(mulExpr));
  }

  std::unique_ptr<IMathObject> newSumExpr = std::make_unique<SumExpression>(std::move(newPolynom));
  simplifyExpr(newSumExpr);
  if (invert) {
    std::unique_ptr<IMathObject> invertExpr = std::make_unique<InvExpression>(std::move(newSumExpr));
    simplifyExpr(invertExpr);
    return invertExpr.release();
  }
  return newSumExpr.release();
}

std::unique_ptr<IMathObject> PowExpression::getValue() {
  return std::move(lhsChild);
}

std::unique_ptr<IMathObject> PowExpression::getPow() {
  return std::move(rhsChild);
}

IMathObject *PowExpression::polynomSimplify() {
  auto *result = mulSimplify();
  if (auto *powExpr = cast<PowExpression>(result)) {
    return powExpr->sumSimplify();
  }
  return result;
}

}
