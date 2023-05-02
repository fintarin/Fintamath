#include "fintamath/expressions/binary/DivExpression.hpp"

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Div DIV;

const DivExpression::SimplifyFunctionsVector DivExpression::simplifyFunctions = {
    &DivExpression::numbersSimplify, //
    &DivExpression::divSimplify,     //
    &DivExpression::mulSimplify,     //
    &DivExpression::sumSimplify,     //
};

DivExpression::DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(DIV, inLhsChild, inRhsChild) {
}

ArgumentPtr DivExpression::invert() const {
  auto inv = std::make_shared<DivExpression>(*this);
  std::swap(inv->lhsChild, inv->rhsChild);
  return inv;
}

std::string DivExpression::toString() const {
  std::string res = IBinaryExpression::toString();

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
      throw UndefinedBinaryOperatorException(DIV.toString(), simplExpr->lhsChild->toString(),
                                             simplExpr->rhsChild->toString());
    }

    if (*rhsInt == ONE) {
      return simplExpr->lhsChild;
    }

    if (*rhsInt == NEG_ONE) {
      return makeFunctionExpression(Neg(), {simplExpr->lhsChild});
    }

    if (*rhsInt < ZERO) {
      return makeFunctionExpression(Div(), {makeRawFunctionExpression(Neg(), {simplExpr->lhsChild}),
                                            makeRawFunctionExpression(Neg(), {simplExpr->rhsChild})});
    }
  }

  if (lhsInt && *lhsInt == ZERO) {
    return simplExpr->lhsChild;
  }

  return simpl;
}

DivExpression::SimplifyFunctionsVector DivExpression::getFunctionsForSimplify() const {
  return simplifyFunctions;
}

ArgumentPtr DivExpression::numbersSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (DIV.doArgsMatch({ONE, *rhs})) {
    return makeFunctionExpression(Mul(), {lhs, DIV(ONE, *rhs)});
  }

  return {};
}

ArgumentPtr DivExpression::divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentsPtrVector numeratorChildren;
  ArgumentsPtrVector denominatorChildren;

  bool containsDivExpression = false;

  if (auto lhsDivExpr = cast<DivExpression>(lhs)) {
    numeratorChildren.emplace_back(lhsDivExpr->getChildren().front());
    denominatorChildren.emplace_back(lhsDivExpr->getChildren().back());
    containsDivExpression = true;
  }
  else {
    numeratorChildren.emplace_back(lhs);
  }

  if (auto rhsDivExpr = cast<DivExpression>(rhs)) {
    denominatorChildren.emplace_back(rhsDivExpr->getChildren().front());
    numeratorChildren.emplace_back(rhsDivExpr->getChildren().back());
    containsDivExpression = true;
  }
  else {
    denominatorChildren.emplace_back(rhs);
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

ArgumentPtr DivExpression::mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentsPtrVector lhsChildren;
  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Mul>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren = {lhs};
  }

  ArgumentsPtrVector rhsChildren;
  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Mul>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren = {rhs};
  }

  size_t lhsChildrenSizeInitial = lhsChildren.size();
  size_t rhsChildrenSizeInitial = rhsChildren.size();

  for (size_t i = 0; i < lhsChildren.size(); i++) {
    for (size_t j = 0; j < rhsChildren.size(); j++) {
      if (auto res = divPowerSimplify(lhsChildren[i], rhsChildren[j])) {
        lhsChildren[i] = res;
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::iterator::difference_type(j));
        break;
      }

      if (auto res = callFunction(DIV, {lhsChildren[i], rhsChildren[j]})) {
        lhsChildren[i] = DIV(*lhsChildren[i], *rhsChildren[j]);
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::iterator::difference_type(j));
        break;
      }
    }

    if (rhsChildren.empty()) {
      break;
    }
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

  if (rhsChildren.empty()) {
    return numerator;
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial || rhsChildren.size() != rhsChildrenSizeInitial) {
    return makeFunctionExpression(Div(), {numerator, denominator});
  }

  return {};
}

ArgumentPtr DivExpression::sumSimplify(const ArgumentPtr & /*lhs*/, const ArgumentPtr & /*rhs*/) {
  // TODO: implement
  return {};
}

ArgumentPtr DivExpression::divPowerSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return ONE.clone();
  }

  auto [lhsRate, lhsValue] = getRateValuePair(lhs);
  auto [rhsRate, rhsValue] = getRateValuePair(rhs);

  if (*lhsValue == *rhsValue) {
    return addRatesToValue({lhsRate, makeRawFunctionExpression(Neg(), {rhsRate})}, lhsValue);
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::getRateValuePair(const ArgumentPtr &rhs) {
  if (const auto &powExpr = cast<IExpression>(rhs); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {ONE.clone(), rhs};
}

ArgumentPtr DivExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeFunctionExpression(Add(), rates);
  return makeRawFunctionExpression(Pow(), {value, ratesSum});
}
}
