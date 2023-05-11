#include "fintamath/expressions/binary/DivExpression.hpp"

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"

namespace fintamath {

DivExpression::DivExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Div(), inLhsChild, inRhsChild) {
}

DivExpression::SimplifyFunctionsVector DivExpression::getFunctionsForSimplify() const {
  static const DivExpression::SimplifyFunctionsVector simplifyFunctions = {
      &DivExpression::numSimplify, //
      &DivExpression::divSimplify, //
      &DivExpression::mulSimplify, //
  };
  return simplifyFunctions;
}

DivExpression::SimplifyFunctionsVector DivExpression::getFunctionsForPostSimplify() const {
  static const DivExpression::SimplifyFunctionsVector simplifyFunctions = {
      &DivExpression::zeroSimplify, //
      &DivExpression::sumSimplify,  //
  };
  return simplifyFunctions;
}

ArgumentPtr DivExpression::zeroSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs,
                                        const ArgumentPtr & /*rhs*/) {
  if (auto lhsInt = cast<Integer>(lhs); lhsInt && *lhsInt == 0) {
    return lhs;
  }

  return {};
}

ArgumentPtr DivExpression::numSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const Integer one = 1;

  if (*rhs == Integer(0)) {
    throw UndefinedBinaryOperatorException(Div().toString(), lhs->toString(), rhs->toString());
  }

  if (Div().doArgsMatch({one, *rhs})) {
    return makeExprSimpl(Mul(), lhs, Div()(one, *rhs));
  }

  return {};
}

ArgumentPtr DivExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
    numerator = makeExpr(Mul(), numeratorChildren);
  }

  ArgumentPtr denominator;
  if (denominatorChildren.size() == 1) {
    denominator = denominatorChildren.front();
  }
  else {
    denominator = makeExpr(Mul(), denominatorChildren);
  }

  return makeExprSimpl(Div(), numerator, denominator);
}

ArgumentPtr DivExpression::mulSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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

  for (auto &lhsChild : lhsChildren) {
    for (size_t j = 0; j < rhsChildren.size(); j++) {
      if (auto res = divPowerSimplify(lhsChild, rhsChildren[j])) {
        lhsChild = res;
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::iterator::difference_type(j));
        break;
      }

      if (auto res = callFunction(Div(), {lhsChild, rhsChildren[j]})) {
        lhsChild = Div()(*lhsChild, *rhsChildren[j]);
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
    numerator = makeExprSimpl(Mul(), lhsChildren);
  }
  else {
    numerator = lhsChildren.front();
  }

  if (rhsChildren.empty()) {
    return numerator;
  }

  ArgumentPtr denominator;
  if (rhsChildren.size() > 1) {
    denominator = makeExprSimpl(Mul(), rhsChildren);
  }
  else {
    denominator = rhsChildren.front();
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial || rhsChildren.size() != rhsChildrenSizeInitial) {
    return makeExprSimpl(Div(), numerator, denominator);
  }

  return {};
}

ArgumentPtr DivExpression::sumSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto res = sumMulSimplify(lhs, rhs)) {
    simplifyChild(res);
    return res;
  }

  if (auto [lhsRes, rhsRes] = mulSumSimplify(lhs, rhs); lhsRes) {
    if (rhsRes) {
      return makeExprSimpl(Add(), lhsRes, rhsRes);
    }
    return lhsRes;
  }

  if (auto res = sumSumSimplify(lhs, rhs)) {
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::sumSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }

  if (lhsChildren.empty() || rhsChildren.empty()) {
    return {};
  }

  ArgumentsPtrVector answerVect;
  ArgumentsPtrVector restVect;

  for (const auto &child : lhsChildren) {
    auto [result, rest] = mulSumSimplify(child, rhs);
    if (result) {
      answerVect.emplace_back(result);
      if (rest) {
        auto restDiv = cast<DivExpression>(rest);
        restVect.emplace_back(restDiv->getChildren().front());
      }
    }
    else {
      restVect.emplace_back(child);
    }
  }
  if (answerVect.empty()) {
    return {};
  }

  auto restSimplResult = makeExprSimpl(Add(), restVect);
  answerVect.emplace_back(makeExprSimpl(Div(), restSimplResult, rhs));

  return makeExprSimpl(Add(), answerVect);
}

ArgumentPtr DivExpression::sumMulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentsPtrVector lhsChildren;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }

  if (const auto rhsChildExpr = cast<IExpression>(rhs);
      (rhsChildExpr && is<Add>(rhsChildExpr->getFunction())) || lhsChildren.empty()) {
    return {};
  }

  ArgumentsPtrVector divSuccess;
  ArgumentsPtrVector divFailure;

  for (const auto &child : lhsChildren) {
    ArgumentPtr divResult = makeExprSimpl(Div(), child, rhs);

    if (const auto divResultExpr = cast<IExpression>(divResult);
        divResultExpr && is<Div>(divResultExpr->getFunction()) && *divResultExpr->getChildren().back() == *rhs) {
      divFailure.emplace_back(child);
    }
    else {
      divSuccess.emplace_back(divResult);
    }
  }

  if (divFailure.size() == lhsChildren.size()) {
    return {};
  }

  if (!divFailure.empty()) {
    ArgumentPtr divExpr = makeExpr(Div(), makeExpr(Add(), divFailure), rhs);
    divSuccess.emplace_back(divExpr);
  }

  return makeExpr(Add(), divSuccess);
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::mulSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentsPtrVector rhsChildren;

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }

  if (const auto lhsChildExpr = cast<IExpression>(lhs);
      (lhsChildExpr && is<Add>(lhsChildExpr->getFunction())) || rhsChildren.empty()) {
    return {};
  }

  ArgumentPtr divResult = makeExprSimpl(Div(), lhs, rhsChildren.front());

  if (const auto number = cast<INumber>(divResult); number && *number == Integer(0)) {
    return {divResult, nullptr};
  }

  if (const auto divExpr = cast<IExpression>(divResult); divExpr && is<Div>(divExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector multiplicates;

  for (size_t i = 1; i < rhsChildren.size(); i++) {
    multiplicates.emplace_back(makeExpr(Mul(), rhsChildren[i], divResult));
  }

  ArgumentPtr negSum = makeExpr(Neg(), makeExpr(Add(), multiplicates));
  ArgumentPtr div = makeExpr(Div(), negSum, rhs);
  return {divResult, div};
}

ArgumentPtr DivExpression::divPowerSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return std::make_shared<Integer>(1);
  }

  bool negation = false;

  ArgumentPtr lhsChild;
  ArgumentPtr rhsChild;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    negation = !negation;
    lhsChild = lhsExpr->getChildren().front();
  }
  else {
    lhsChild = lhs;
  }

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    negation = !negation;
    rhsChild = rhsExpr->getChildren().front();
  }
  else {
    rhsChild = rhs;
  }

  auto [lhsRate, lhsValue] = getRateValuePair(lhsChild);
  auto [rhsRate, rhsValue] = getRateValuePair(rhsChild);

  ArgumentPtr result;
  if (*lhsValue == *rhsValue) {
    result = addRatesToValue({lhsRate, makeExpr(Neg(), rhsRate)}, lhsValue);
  }

  if (result) {
    if (negation) {
      return makeExprSimpl(Neg(), result);
    }

    return result;
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::getRateValuePair(const ArgumentPtr &rhs) {
  if (const auto &powExpr = cast<IExpression>(rhs); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {std::make_shared<Integer>(1), rhs};
}

ArgumentPtr DivExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeExprSimpl(Add(), rates);
  return makeExpr(Pow(), value, ratesSum);
}

}
