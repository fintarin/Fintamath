#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)
    : IBinaryExpressionCRTP(POW, lhsChild, rhsChild) {
}

ArgumentPtr PowExpression::mulSimplify() const {
  auto powExpr = cast<PowExpression>(clone());

  if (auto mulExpr = cast<IExpression>(powExpr->lhsChild); mulExpr && is<Mul>(mulExpr->getFunction())) {
    ArgumentsPtrVector args = mulExpr->getChildren();

    for (auto &arg : args) {
      arg = makeFunctionExpression(Pow(), {arg, powExpr->rhsChild->clone()});
    }

    return makeFunctionExpression(Mul(), args);
  }

  return powExpr;
}

ArgumentPtr PowExpression::sumSimplify() const {
  auto powExpr = cast<PowExpression>(clone());

  if (const auto rhs = cast<Integer>(powExpr->rhsChild)) {
    if (auto sumExpr = sumPolynomSimplify(powExpr->lhsChild, *rhs)) {
      return sumExpr;
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

vector<Integer> PowExpression::generateSplit(Integer bitNumber, const Integer &variableCount) {
  vector<Integer> result;
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

ArgumentPtr PowExpression::sumPolynomSimplify(const ArgumentPtr &expr, Integer powValue) {
  auto sumExpr = cast<IExpression>(expr);
  ArgumentsPtrVector polynom;

  if (sumExpr && is<Add>(sumExpr->getFunction())) {
    polynom = sumExpr->getChildren();
  }
  else {
    return {};
  }

  ArgumentsPtrVector newPolynom;
  Integer variableCount = int64_t(polynom.size());

  bool isResultInverted = false;

  if (powValue < ZERO) {
    powValue = abs(powValue);
    isResultInverted = true;
  }

  Integer bitNumber = generateFirstNum(powValue);

  for (int i = 0; i < combinations(powValue + variableCount - 1, powValue); i++) {
    vector<Integer> vectOfPows = generateSplit(bitNumber, variableCount);
    bitNumber = generateNextNumber(bitNumber);

    ArgumentsPtrVector mulExprPolynom;
    mulExprPolynom.emplace_back(make_shared<Integer>(split(powValue, vectOfPows)));

    for (size_t j = 0; j < variableCount; j++) {
      auto powExpr = makeRawFunctionExpression(Pow(), {polynom[j], make_shared<Integer>(move(vectOfPows[j]))});
      mulExprPolynom.emplace_back(powExpr);
    }

    ArgumentPtr mulExpr = makeRawFunctionExpression(Mul(), mulExprPolynom);
    newPolynom.emplace_back(mulExpr);
  }

  ArgumentPtr newSumExpr = makeRawFunctionExpression(Add(), newPolynom);

  if (isResultInverted) {
    return makeRawFunctionExpression(Inv(), {newSumExpr})->toMinimalObject();
  }

  return newSumExpr->toMinimalObject();
}

ArgumentPtr PowExpression::polynomSimplify() const {
  ArgumentPtr result = mulSimplify();

  if (auto powExpr = cast<PowExpression>(result)) {
    return powExpr->sumSimplify();
  }

  return result;
}

ArgumentPtr PowExpression::invert() const {
  auto inv = make_shared<PowExpression>(*this);
  inv->rhsChild = makeFunctionExpression(Neg(), {inv->rhsChild});
  return inv;
}

ArgumentPtr PowExpression::preSimplify() const {
  auto simpl = IBinaryExpression::preSimplify();
  auto simplExpr = cast<PowExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (auto lhsExpr = cast<IExpression>(simplExpr->lhsChild); lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    auto lhsMul = makeFunctionExpression(Pow(), {NEG_ONE.clone(), simplExpr->rhsChild});
    auto rhsMul = makeFunctionExpression(Pow(), {lhsExpr->getChildren()[0], simplExpr->rhsChild});
    return makeFunctionExpression(Mul(), {lhsMul, rhsMul});
  }

  if (auto lhsExpr = cast<IExpression>(simplExpr->lhsChild); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    auto lhsPow = lhsExpr->getChildren().front();
    auto rhsPow = makeFunctionExpression(Mul(), {lhsExpr->getChildren()[1], simplExpr->rhsChild});
    return makeRawFunctionExpression(Pow(), {lhsPow, rhsPow});
  }

  return simpl;
}

ArgumentPtr PowExpression::postSimplify() const {
  auto simpl = IBinaryExpression::postSimplify();
  auto simplExpr = cast<PowExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  auto rhsInt = cast<Integer>(simplExpr->rhsChild);

  if (rhsInt) {
    if (*rhsInt == ZERO) {
      return ONE.clone();
    }

    if (*simplExpr->lhsChild == ONE || *rhsInt == ONE) {
      return simplExpr->lhsChild;
    }

    if (*rhsInt == NEG_ONE) {
      return makeFunctionExpression(Inv(), {simplExpr->lhsChild});
    }

    if (*rhsInt < 0) {
      return makeRawFunctionExpression(
          Inv(), {makeFunctionExpression(Pow(), {simplExpr->lhsChild, makeFunctionExpression(Neg(), {rhsInt})})});
    }
  }

  return simplExpr->polynomSimplify();
}

}
