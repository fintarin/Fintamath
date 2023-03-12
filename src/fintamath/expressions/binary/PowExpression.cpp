#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/expressions/unary/InvExpression.hpp"
#include "fintamath/expressions/unary/NegExpression.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

#include <memory>

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(std::shared_ptr<IMathObject> lhsChild, std::shared_ptr<IMathObject> rhsChild)
    : IBinaryExpression(POW, std::move(lhsChild), std::move(rhsChild)) {
}

std::unique_ptr<IMathObject> PowExpression::simplify(bool isPrecise) const {
  // auto exprObj = std::make_unique<PowExpression>(*this);

  // auto *lhsPtr = cast<IExpression>(exprObj->lhsChild);
  // auto *rhsPtr = cast<Integer>(exprObj->rhsChild);

  // if (lhsPtr && rhsPtr && !is<Expression>(lhsPtr)) {
  //   if (*rhsPtr == ZERO) {
  //     return ONE.clone();
  //   }
  //   if (*lhsPtr == ONE || *rhsPtr == ONE) {
  //     return lhsPtr->clone();
  //   }
  //   if (*rhsPtr == NEG_ONE) {
  //     return InvExpression(lhsPtr->clone()).simplify(isPrecise);
  //   }
  // }

  // if (is<INumber>(exprObj->lhsChild) && is<INumber>(exprObj->rhsChild)) {
  //   return POW(*exprObj->lhsChild, *exprObj->rhsChild);
  // }
  // return exprObj;

  return std::make_unique<PowExpression>(*this);
}

void PowExpression::invert() {
  rhsChild = Expression::makeRawFunctionExpression(Inv(), {rhsChild});
  simplifyExpr(rhsChild);
}

std::shared_ptr<IMathObject> PowExpression::mulSimplify() {
  std::shared_ptr<IMathObject> simplExpr = IBinaryExpression::simplify();

  if (!is<PowExpression>(simplExpr)) {
    return simplExpr;
  }

  auto powExpr = cast<PowExpression>(simplExpr);

  if (auto mulExpr = cast<MulExpression>(powExpr->lhsChild)) {
    mulExpr->setPow(powExpr->rhsChild);
    std::shared_ptr<IMathObject> mulExprResult = std::make_shared<MulExpression>(ArgumentsPtrVector{powExpr->lhsChild});
    simplifyExpr(mulExprResult);
    return mulExprResult;
  }

  return powExpr;
}

std::shared_ptr<IMathObject> PowExpression::sumSimplify() {
  std::shared_ptr<IMathObject> simplExpr = IBinaryExpression::simplify();
  if (!is<PowExpression>(simplExpr)) {
    return simplExpr;
  }
  auto powExpr = cast<PowExpression>(simplExpr);

  if (const auto rhs = cast<Integer>(powExpr->rhsChild)) {
    if (const auto sumExpr = cast<SumExpression>(powExpr->lhsChild)) {
      return sumPolynomSimplify(*sumExpr, *rhs);
    }
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

std::shared_ptr<IMathObject> PowExpression::sumPolynomSimplify(const SumExpression &sumExpr, Integer pow) {
  ArgumentsPtrVector polynom = sumExpr.getPolynom();
  ArgumentsPtrVector newPolynom;
  Integer variableCount = int64_t(polynom.size());

  bool invert = false;
  if (pow < ZERO) {
    pow = abs(pow);
    invert = true;
  }

  Integer bitNumber = generateFirstNum(pow);
  for (int i = 0; i < combinations(pow + variableCount - 1, pow); i++) {
    std::vector<Integer> vectOfPows = generateSplit(bitNumber, variableCount);
    bitNumber = generateNextNumber(bitNumber);

    ArgumentsPtrVector mulExprPolynom;
    mulExprPolynom.emplace_back(std::make_shared<Integer>(split(pow, vectOfPows)));
    for (size_t j = 0; j < variableCount; j++) {
      auto powExpr = std::make_shared<PowExpression>(polynom[j], std::make_shared<Integer>(std::move(vectOfPows[j])));
      mulExprPolynom.emplace_back(powExpr->polynomSimplify());
    }
    std::shared_ptr<IMathObject> mulExpr = std::make_shared<MulExpression>(mulExprPolynom);
    simplifyExpr(mulExpr);
    newPolynom.emplace_back(mulExpr);
  }

  std::shared_ptr<IMathObject> newSumExpr = std::make_shared<SumExpression>(newPolynom);
  simplifyExpr(newSumExpr);
  if (invert) {
    std::shared_ptr<IMathObject> invertExpr = std::make_shared<InvExpression>(newSumExpr);
    simplifyExpr(invertExpr);
    return invertExpr;
  }
  return newSumExpr;
}

std::shared_ptr<IMathObject> PowExpression::getValue() {
  return lhsChild;
}

std::shared_ptr<IMathObject> PowExpression::getPow() {
  return rhsChild;
}

std::shared_ptr<IMathObject> PowExpression::simplifyChildren() {
  if (func->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*func)(*lhsChild, *rhsChild);
  }

  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsInt = cast<Integer>(rhsChild);

  if (lhsExpr && rhsInt) {
    if (*rhsInt == ZERO) {
      return ONE.clone();
    }
    if (*lhsExpr == ONE || *rhsInt == ONE) {
      return lhsChild;
    }
    if (*rhsInt == NEG_ONE) {
      std::shared_ptr<IMathObject> invExpr = std::make_shared<InvExpression>(lhsChild);
      simplifyExpr(invExpr);
      return invExpr;
    }
  }

  return nullptr;
}

std::shared_ptr<IMathObject> PowExpression::polynomSimplify() {
  std::shared_ptr<IMathObject> result = mulSimplify();
  if (auto powExpr = cast<PowExpression>(result)) {
    return powExpr->sumSimplify();
  }
  return result;
}

}
