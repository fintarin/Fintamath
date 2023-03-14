#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Pow POW;

PowExpression::PowExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild)
    : IBinaryExpressionCRTP(POW, lhsChild, rhsChild) {
}

// unique_ptr<IMathObject> PowExpression::simplify(bool isPrecise) const {
// auto exprObj = make_unique<PowExpression>(*this);

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
// }

// ArgumentPtr PowExpression::mulSimplify() {
//   ArgumentPtr simplExpr = IBinaryExpression::simplify();

//   if (!is<PowExpression>(simplExpr)) {
//     return simplExpr;
//   }

//   auto powExpr = cast<PowExpression>(simplExpr);

//   if (auto mulExpr = cast<MulExpression>(powExpr->lhsChild)) {
//     mulExpr->setPow(powExpr->rhsChild);
//     ArgumentPtr mulExprResult =
//     make_shared<MulExpression>(ArgumentsPtrVector{powExpr->lhsChild}); simplifyChild(mulExprResult); return
//     mulExprResult;
//   }

//   return powExpr;
// }

// ArgumentPtr PowExpression::sumSimplify() {
//   ArgumentPtr simplExpr = IBinaryExpression::simplify();
//   if (!is<PowExpression>(simplExpr)) {
//     return simplExpr;
//   }
//   auto powExpr = cast<PowExpression>(simplExpr);

//   if (const auto rhs = cast<Integer>(powExpr->rhsChild)) {
//     if (const auto sumExpr = cast<SumExpression>(powExpr->lhsChild)) {
//       return sumPolynomSimplify(*sumExpr, *rhs);
//     }
//   }

//   return powExpr;
// }

// Integer PowExpression::generateNextNumber(Integer n) {
//   Integer u = n & -n;
//   Integer v = u + n;
//   n = v + (((v ^ n) / u) >> 2);
//   return n;
// }

// Integer PowExpression::generateFirstNum(const Integer &countOfOne) {
//   Integer n = 0;
//   for (int i = 0; i < countOfOne; i++) {
//     n = n << 1 | 1;
//   }
//   return n;
// }

// vector<Integer> PowExpression::generateSplit(Integer bitNumber, const Integer &variableCount) {
//   vector<Integer> result;
//   Integer counter = 0;
//   while (result.size() < variableCount) {
//     if (bitNumber % 2 == 1) {
//       counter++;
//     }
//     if (bitNumber % 2 == 0) {
//       result.emplace_back(counter);
//       counter = 0;
//     }
//     bitNumber >>= 1;
//   }
//   return result;
// }

// ArgumentPtr PowExpression::sumPolynomSimplify(const SumExpression &sumExpr, Integer pow) {
//   ArgumentsPtrVector polynom = sumExpr.getPolynom();
//   ArgumentsPtrVector newPolynom;
//   Integer variableCount = int64_t(polynom.size());

//   bool invert = false;
//   if (pow < ZERO) {
//     pow = abs(pow);
//     invert = true;
//   }

//   Integer bitNumber = generateFirstNum(pow);
//   for (int i = 0; i < combinations(pow + variableCount - 1, pow); i++) {
//     vector<Integer> vectOfPows = generateSplit(bitNumber, variableCount);
//     bitNumber = generateNextNumber(bitNumber);

//     ArgumentsPtrVector mulExprPolynom;
//     mulExprPolynom.emplace_back(make_shared<Integer>(split(pow, vectOfPows)));
//     for (size_t j = 0; j < variableCount; j++) {
//       auto powExpr = make_shared<PowExpression>(polynom[j],
//       make_shared<Integer>(move(vectOfPows[j]))); mulExprPolynom.emplace_back(powExpr->polynomSimplify());
//     }
//     ArgumentPtr mulExpr = make_shared<MulExpression>(mulExprPolynom);
//     simplifyChild(mulExpr);
//     newPolynom.emplace_back(mulExpr);
//   }

//   ArgumentPtr newSumExpr = make_shared<SumExpression>(newPolynom);
//   simplifyChild(newSumExpr);
//   if (invert) {
//     ArgumentPtr invertExpr = make_shared<InvExpression>(newSumExpr);
//     simplifyChild(invertExpr);
//     return invertExpr;
//   }
//   return newSumExpr;
// }

// ArgumentPtr PowExpression::getValue() {
//   return lhsChild;
// }

// ArgumentPtr PowExpression::getPow() {
//   return rhsChild;
// }

// ArgumentPtr PowExpression::polynomSimplify() {
//   ArgumentPtr result = mulSimplify();
//   if (auto powExpr = cast<PowExpression>(result)) {
//     return powExpr->sumSimplify();
//   }
//   return result;
// }

ArgumentPtr PowExpression::invert() const {
  auto inv = make_shared<PowExpression>(*this);
  inv->rhsChild = makeFunctionExpression(Neg(), {inv->rhsChild});
  return inv;
}

ArgumentPtr PowExpression::postSimplify() const {
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
      return makeFunctionExpression(Inv(), {lhsChild});
    }
  }

  return {};
}

}
