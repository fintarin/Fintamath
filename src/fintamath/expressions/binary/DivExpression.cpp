#include "fintamath/expressions/binary/DivExpression.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Div DIV;

DivExpression::DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(DIV, inLhsChild, inRhsChild) {
}

ArgumentPtr DivExpression::invert() const {
  auto inv = make_shared<DivExpression>(*this);
  std::swap(inv->lhsChild, inv->rhsChild);
  return inv;
}

string DivExpression::toString() const {
  string res = IBinaryExpression::toString();

  if (const auto lhsExpr = cast<IExpression>(lhsChild)) {
    if (const auto lhsOper = cast<IOperator>(lhsExpr->getFunction());
        lhsOper && lhsOper->getOperatorPriority() != Sub().getOperatorPriority()) {
      if (res.size() > 1 && res[0] == '(' && res[1] == Sub().toString()[0]) {
        res.erase(1, 1);
        res = Sub().toString() + res;
      }
    }
  }

  return res;
}

ArgumentPtr DivExpression::preSimplify() const {
  auto simpl = IBinaryExpression::preSimplify();
  auto simplExpr = cast<DivExpression>(simpl);

  if (!simplExpr || *simplExpr->getChildren().back() == ZERO) {
    return simpl;
  }

  if (auto res = simplExpr->globalSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr DivExpression::postSimplify() const {
  auto simpl = IBinaryExpression::postSimplify();
  auto simplExpr = cast<DivExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  auto lhsInt = cast<Integer>(simplExpr->lhsChild);
  auto rhsInt = cast<Integer>(simplExpr->rhsChild);

  if (rhsInt) {
    if (*rhsInt == ZERO) {
      // TODO: return infinity or undefined
      throw UndefinedBinaryOpearatorException(DIV.toString(), simplExpr->lhsChild->toString(),
                                              simplExpr->rhsChild->toString());
    }

    if (*rhsInt == ONE) {
      return simplExpr->lhsChild;
    }

    if (*rhsInt == NEG_ONE) {
      return makeFunctionExpression(Neg(), {simplExpr->lhsChild});
    }

    if (*rhsInt < ZERO) {
      return makeRawFunctionExpression(Div(), {makeFunctionExpression(Neg(), {simplExpr->lhsChild}),
                                               makeFunctionExpression(Neg(), {simplExpr->rhsChild})});
    }
  }

  if (lhsInt && *lhsInt == ZERO) {
    return simplExpr->lhsChild;
  }

  if (auto res = simplExpr->globalSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr DivExpression::globalSimplify() const {
  if (DIV.doArgsMatch({ONE, *rhsChild})) {
    return makeFunctionExpression(Mul(), {lhsChild, DIV(ONE, *rhsChild)});
  }

  if (auto res = divSimplify()) {
    return res;
  }

  if (auto res = mulSimplify()) {
    return res;
  }

  if (auto res = sumSimplify()) {
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::divSimplify() const {
  ArgumentsPtrVector numeratorChildren;
  ArgumentsPtrVector denominatorChildren;

  bool containsDivExpression = false;

  if (auto lhsDivExpr = cast<DivExpression>(lhsChild)) {
    numeratorChildren.emplace_back(lhsDivExpr->getChildren().front());
    denominatorChildren.emplace_back(lhsDivExpr->getChildren().back());
    containsDivExpression = true;
  }
  else {
    numeratorChildren.emplace_back(lhsChild);
  }

  if (auto rhsDivExpr = cast<DivExpression>(rhsChild)) {
    denominatorChildren.emplace_back(rhsDivExpr->getChildren().front());
    numeratorChildren.emplace_back(rhsDivExpr->getChildren().back());
    containsDivExpression = true;
  }
  else {
    denominatorChildren.emplace_back(rhsChild);
  }

  if (!containsDivExpression) {
    return {};
  }

  ArgumentPtr numerator;
  if (numeratorChildren.size() == 1) {
    numerator = numeratorChildren.front();
  }
  else {
    numerator = makeRawFunctionExpression(Mul(), numeratorChildren);
  }

  ArgumentPtr denominator;
  if (denominatorChildren.size() == 1) {
    denominator = denominatorChildren.front();
  }
  else {
    denominator = makeRawFunctionExpression(Mul(), denominatorChildren);
  }

  return makeFunctionExpression(DIV, {numerator, denominator});
}

ArgumentPtr DivExpression::mulSimplify() const {
  ArgumentsPtrVector lhsChildren;
  if (const auto lhsExpr = cast<IExpression>(lhsChild); lhsExpr && *lhsExpr->getFunction() == Mul()) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren = {lhsChild};
  }

  ArgumentsPtrVector rhsChildren;
  if (const auto rhsExpr = cast<IExpression>(rhsChild); rhsExpr && *rhsExpr->getFunction() == Mul()) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren = {rhsChild};
  }

  size_t lhsChildrenSizeInitial = lhsChildren.size();

  for (size_t i = 0; i < lhsChildren.size(); i++) {
    for (size_t j = 0; j < rhsChildren.size(); j++) {
      if (*lhsChildren[i] == *rhsChildren[j]) {
        // TODO: divide powers
        lhsChildren.erase(lhsChildren.begin() + int64_t(i));
        rhsChildren.erase(rhsChildren.begin() + int64_t(j));
        i--;
        break;
      }

      if (auto res = callFunction(DIV, {lhsChildren[i], rhsChildren[j]})) {
        lhsChildren[i] = DIV(*lhsChildren[i], *rhsChildren[j]);
        rhsChildren.erase(rhsChildren.begin() + int64_t(j));
        break;
      }
    }

    if (rhsChildren.empty()) {
      break;
    }
  }

  if (lhsChildren.empty() && rhsChildren.empty()) {
    return ONE.clone();
  }

  // TODO: pass negations from denominator to numerator: 28/(-x) => -28/x

  ArgumentPtr numerator;
  if (lhsChildren.size() > 1) {
    numerator = makeFunctionExpression(Mul(), lhsChildren);
  }
  else {
    numerator = lhsChildren.front();
  }

  ArgumentPtr denominator;
  if (rhsChildren.size() > 1) {
    denominator = makeFunctionExpression(Mul(), rhsChildren);
  }
  else {
    denominator = rhsChildren.front();
  }

  if (lhsChildren.empty()) {
    return makeFunctionExpression(Div(), {ONE.clone(), denominator});
  }

  if (rhsChildren.empty()) {
    return numerator;
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial) {
    return makeFunctionExpression(Div(), {numerator, denominator});
  }

  return {};
}

ArgumentPtr DivExpression::sumSimplify() const {
  // TODO: implement
  return {};
}

}
