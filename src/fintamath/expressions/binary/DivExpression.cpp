#include "fintamath/expressions/binary/DivExpression.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Rational.hpp"

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
      &DivExpression::zeroSimplify,    //
      &DivExpression::negSimplify,     //
      &DivExpression::sumSimplify,     //
      &DivExpression::polynomSimplify, //
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
    return makeExpr(Mul(), lhs, Div()(one, *rhs))->toMinimalObject();
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

  return makeExpr(Div(), numerator, denominator)->toMinimalObject();
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
      bool isResFound = false;

      if (auto divPowRes = divPowSimplify(lhsChild, rhsChildren[j])) {
        lhsChild = divPowRes;
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::iterator::difference_type(j));
        isResFound = true;
      }
      else if (auto callFuncRes = callFunction(Div(), {lhsChild, rhsChildren[j]});
               callFuncRes && !is<Rational>(callFuncRes)) {
        lhsChild = Div()(*lhsChild, *rhsChildren[j]);
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::iterator::difference_type(j));
        isResFound = true;
      }

      if (isResFound) {
        break;
      }
    }

    if (rhsChildren.empty()) {
      break;
    }
  }

  ArgumentPtr numerator;
  if (lhsChildren.size() > 1) {
    numerator = makeExpr(Mul(), lhsChildren)->toMinimalObject();
  }
  else {
    numerator = lhsChildren.front();
  }

  if (rhsChildren.empty()) {
    return numerator;
  }

  ArgumentPtr denominator;

  if (rhsChildren.size() > 1) {
    denominator = makeExpr(Mul(), rhsChildren)->toMinimalObject();
  }
  else {
    denominator = rhsChildren.front();
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial || rhsChildren.size() != rhsChildrenSizeInitial) {
    return makeExpr(Div(), numerator, denominator)->toMinimalObject();
  }

  return {};
}

ArgumentPtr DivExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (isNeg(rhs)) {
    return makeExpr(Div(), makeExpr(Neg(), lhs), makeExpr(Neg(), rhs))->toMinimalObject();
  }

  return {};
}

bool DivExpression::isNeg(const ArgumentPtr &expr) {
  ArgumentPtr checkValue;
  if (auto exprChild = cast<IExpression>(expr); exprChild && is<Add>(exprChild->getFunction())) {
    checkValue = exprChild->getChildren().front();
  }
  else {
    checkValue = expr;
  }

  if (auto exprValue = cast<IExpression>(checkValue); exprValue && is<Neg>(exprValue->getFunction())) {
    return true;
  }

  return false;
}

ArgumentPtr DivExpression::sumSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto res = sumMulSimplify(lhs, rhs)) {
    simplifyChild(res);
    return res;
  }

  if (auto [lhsRes, rhsRes] = mulSumSimplify(lhs, rhs); lhsRes) {
    return makeExpr(Add(), lhsRes, rhsRes)->toMinimalObject();
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

  auto restSimplResult = makeExpr(Add(), restVect);
  answerVect.emplace_back(makeExpr(Div(), restSimplResult, rhs));
  return makeExpr(Add(), answerVect)->toMinimalObject();
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
    ArgumentPtr divResult = makeExpr(Div(), child, rhs)->toMinimalObject();

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

  ArgumentPtr divResult = makeExpr(Div(), lhs, rhsChildren.front())->toMinimalObject();

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

ArgumentPtr DivExpression::divPowSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
      return makeExpr(Neg(), result)->toMinimalObject();
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
  ArgumentPtr ratesSum = makeExpr(Add(), rates)->toMinimalObject();
  return makeExpr(Pow(), value, ratesSum);
}

ArgumentPtr DivExpression::polynomSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto &lhsExpr = cast<IExpression>(lhs)) {
    if (is<Add>(lhsExpr->getFunction())) {
      return sumPolynomSimplify(lhsExpr->getChildren(), rhs);
    }
    if (is<Mul>(lhsExpr->getFunction())) {
      return mulPolynomSimplify(lhsExpr->getChildren(), rhs);
    }
  }
  return {};
}

ArgumentPtr DivExpression::sumPolynomSimplify(const ArgumentsPtrVector &lhs, const ArgumentPtr &rhs) {
  return {};
}

ArgumentPtr DivExpression::mulPolynomSimplify(const ArgumentsPtrVector &lhsChildren, const ArgumentPtr &rhs) {
  ArgumentsPtrVector newNumerator;
  ArgumentsPtrVector newDenominator;
  for (const auto &child : lhsChildren) {
    if (const auto &divChild = cast<DivExpression>(child)) {
      newNumerator.emplace_back(divChild->lhsChild);
      newDenominator.emplace_back(divChild->rhsChild);
    }
    else if (const auto &rationalChild = cast<Rational>(child)) {
      newNumerator.emplace_back(std::make_shared<Integer>(rationalChild->numerator()));
      newDenominator.emplace_back(std::make_shared<Integer>(rationalChild->denominator()));
    }
    else {
      newNumerator.emplace_back(child);
    }
  }

  if (!newDenominator.empty()) {
    newDenominator.emplace_back(rhs);
    auto denominator = makeExpr(Mul(), newDenominator);
    auto numerator = makeExpr(Mul(), newNumerator);
    return makeExpr(Div(), numerator, denominator)->toMinimalObject();
  }

  return {};
}
}
