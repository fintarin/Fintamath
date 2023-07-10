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
      &DivExpression::zeroSimplify,      //
      &DivExpression::negSimplify,       //
      &DivExpression::sumSimplify,       //
      &DivExpression::nestedDivSimplify, //
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
    ArgumentPtr res = makeExpr(Mul(), lhs, Div()(one, *rhs));
    return res;
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

  ArgumentPtr res = makeExpr(Div(), numerator, denominator);
  return res;
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
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::difference_type(j));
        isResFound = true;
      }
      else if (auto callFuncRes = callFunction(Div(), {lhsChild, rhsChildren[j]});
               callFuncRes && !is<Rational>(callFuncRes)) {
        lhsChild = Div()(*lhsChild, *rhsChildren[j]);
        rhsChildren.erase(rhsChildren.begin() + ArgumentsPtrVector::difference_type(j));
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
    numerator = makeExpr(Mul(), lhsChildren);
  }
  else {
    numerator = lhsChildren.front();
  }

  if (rhsChildren.empty()) {
    return numerator;
  }

  ArgumentPtr denominator;
  if (rhsChildren.size() > 1) {
    denominator = makeExpr(Mul(), rhsChildren);
  }
  else {
    denominator = rhsChildren.front();
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial || rhsChildren.size() != rhsChildrenSizeInitial) {
    ArgumentPtr res = makeExpr(Div(), numerator, denominator);
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (isNeg(rhs)) {
    ArgumentPtr res = makeExpr(Div(), makeExpr(Neg(), lhs), makeExpr(Neg(), rhs));
    return res;
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
    return res;
  }

  if (auto [lhsRes, rhsRes] = mulSumSimplify(lhs, rhs); lhsRes) {
    ArgumentPtr res = makeExpr(Add(), lhsRes, rhsRes);
    return res;
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

  ArgumentsPtrVector resultVect;
  ArgumentsPtrVector remainderVect;

  for (const auto &child : lhsChildren) {
    auto [result, remainder] = mulSumSimplify(child, rhs);

    if (result) {
      resultVect.emplace_back(result);

      if (remainder) {
        auto remainderDiv = cast<DivExpression>(remainder);
        remainderVect.emplace_back(remainderDiv->getChildren().front());
      }
    }
    else {
      remainderVect.emplace_back(child);
    }
  }
  if (resultVect.empty()) {
    return {};
  }

  resultVect.emplace_back(makeExpr(Div(), makeExpr(Add(), remainderVect), rhs));

  ArgumentPtr result = makeExpr(Add(), resultVect);
  return result;
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

  ArgumentsPtrVector result;
  ArgumentsPtrVector remainder;

  for (const auto &child : lhsChildren) {
    ArgumentPtr divResult = makeExpr(Div(), child, rhs);

    if (const auto divResultExpr = cast<IExpression>(divResult);
        divResultExpr && is<Div>(divResultExpr->getFunction()) && *divResultExpr->getChildren().back() == *rhs) {
      remainder.emplace_back(child);
    }
    else {
      result.emplace_back(divResult);
    }
  }

  if (remainder.size() == lhsChildren.size()) {
    return {};
  }

  if (!remainder.empty()) {
    ArgumentPtr divExpr = makeExpr(Div(), makeExpr(Add(), remainder), rhs);
    result.emplace_back(divExpr);
  }

  return makeExpr(Add(), result);
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

  ArgumentPtr result = makeExpr(Div(), lhs, rhsChildren.front());

  if (const auto divExpr = cast<IExpression>(result); divExpr && is<Div>(divExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector multiplicator;

  for (size_t i = 1; i < rhsChildren.size(); i++) {
    multiplicator.emplace_back(makeExpr(Mul(), rhsChildren[i], result));
  }

  ArgumentPtr negSum = makeExpr(Neg(), makeExpr(Add(), multiplicator));
  ArgumentPtr remainder = makeExpr(Div(), negSum, rhs);
  return {result, remainder};
}

ArgumentPtr DivExpression::divPowSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return std::make_shared<Integer>(1);
  }

  bool isResultNegated = false;

  ArgumentPtr lhsChild;
  ArgumentPtr rhsChild;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    isResultNegated = !isResultNegated;
    lhsChild = lhsExpr->getChildren().front();
  }
  else {
    lhsChild = lhs;
  }

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    isResultNegated = !isResultNegated;
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

    if (isResultNegated) {
      result = makeExpr(Neg(), result);
    }
  }

  return result;
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::getRateValuePair(const ArgumentPtr &rhs) {
  if (const auto &powExpr = cast<IExpression>(rhs); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {std::make_shared<Integer>(1), rhs};
}

ArgumentPtr DivExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeExpr(Add(), rates);
  return makeExpr(Pow(), value, ratesSum);
}

ArgumentPtr DivExpression::nestedDivSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs,
                                             const ArgumentPtr &rhs) {
  ArgumentPtr result;

  if (const auto &lhsExpr = cast<IExpression>(lhs)) {
    if (is<Mul>(lhsExpr->getFunction())) {
      result = nestedDivInNumeratorMulSimplify(lhsExpr->getChildren(), rhs);
    }
    else if (is<Add>(lhsExpr->getFunction())) {
      result = nestedDivInNumeratorSumSimplify(lhsExpr->getChildren(), rhs);
    }
  }

  if (result) {
    return result;
  }

  if (const auto &rhsExpr = cast<IExpression>(rhs)) {
    if (is<Add>(rhsExpr->getFunction())) {
      result = nestedDivInDenominatorSumSimplify(lhs, rhs, rhsExpr->getChildren());
    }
  }

  return result;
}

ArgumentPtr DivExpression::nestedDivInNumeratorSumSimplify(const ArgumentsPtrVector &lhsChildren,
                                                           const ArgumentPtr &rhs) {
  ArgumentsPtrVector newNumerator;
  ArgumentsPtrVector resultPolynom;

  for (const auto &child : lhsChildren) {
    ArgumentPtr childForCheck = child;
    bool isNeg = unwrapNeg(childForCheck);

    if (const auto &exprChild = cast<IExpression>(childForCheck); exprChild && is<Mul>(exprChild->getFunction())) {
      if (auto result = nestedDivInNumeratorMulSimplify(exprChild->getChildren(), rhs)) {
        resultPolynom.emplace_back(result);
        continue;
      }
    }
    else if (const auto &divChild = cast<DivExpression>(childForCheck)) {
      ArgumentPtr childForAdd = makeExpr(Div(), divChild->lhsChild, makeExpr(Mul(), divChild->rhsChild, rhs));
      resultPolynom.emplace_back(isNeg ? makeExpr(Neg(), childForAdd) : childForAdd);
      continue;
    }
    else if (const auto &rationalChild = cast<Rational>(childForCheck)) {
      ArgumentPtr childForAdd =
          makeExpr(Div(), std::make_shared<const Integer>(rationalChild->numerator()),
                   makeExpr(Mul(), std::make_shared<const Integer>(rationalChild->denominator()), rhs));
      resultPolynom.emplace_back(isNeg ? makeExpr(Neg(), childForAdd) : childForAdd);
      continue;
    }

    newNumerator.emplace_back(child);
  }

  if (resultPolynom.empty()) {
    return {};
  }

  if (!newNumerator.empty()) {
    resultPolynom.emplace_back(
        makeExpr(Div(), newNumerator.size() > 1 ? makeExpr(Add(), newNumerator) : newNumerator.front(), rhs));
  }

  return makeExpr(Add(), resultPolynom);
}

ArgumentPtr DivExpression::nestedDivInNumeratorMulSimplify(const ArgumentsPtrVector &lhsChildren,
                                                           const ArgumentPtr &rhs) {
  ArgumentsPtrVector numeratorChildren;
  ArgumentsPtrVector denominatorChildren;

  for (const auto &child : lhsChildren) {
    if (const auto &rationalChild = cast<Rational>(child)) {
      numeratorChildren.emplace_back(std::make_shared<const Integer>(rationalChild->numerator()));
      denominatorChildren.emplace_back(std::make_shared<const Integer>(rationalChild->denominator()));
      continue;
    }

    numeratorChildren.emplace_back(child);
  }

  if (!denominatorChildren.empty()) {
    denominatorChildren.emplace_back(rhs);
    ArgumentPtr numerator = makeExpr(Mul(), numeratorChildren);
    ArgumentPtr denominator = makeExpr(Mul(), denominatorChildren);
    return makeExpr(Div(), numerator, denominator);
  }

  return {};
}

bool DivExpression::unwrapNeg(ArgumentPtr &lhs) {
  if (const auto &exprLhs = cast<IExpression>(lhs); exprLhs && is<Neg>(exprLhs->getFunction())) {
    lhs = exprLhs->getChildren().front();
    return true;
  }
  return false;
}

ArgumentPtr DivExpression::nestedDivInDenominatorSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs,
                                                             const ArgumentsPtrVector &rhsChildren) {
  ArgumentsPtrVector multiplicator;

  for (const auto &child : rhsChildren) {
    ArgumentPtr childForCheck = child;
    unwrapNeg(childForCheck);

    if (const auto &divChild = cast<DivExpression>(childForCheck)) {
      multiplicator.emplace_back(divChild->rhsChild);
      continue;
    }

    if (const auto &rationalChild = cast<Rational>(childForCheck)) {
      multiplicator.emplace_back(std::make_shared<Integer>(rationalChild->denominator()));
      continue;
    }

    if (const auto &exprChild = cast<IExpression>(childForCheck); exprChild && is<Mul>(exprChild->getFunction())) {
      if (const auto &childForAdd = nestedDivInDenominatorMulSimplify(exprChild->getChildren())) {
        multiplicator.emplace_back(childForAdd);
      }
    }
  }

  if (multiplicator.empty()) {
    return {};
  }

  ArgumentsPtrVector numeratorChildren = multiplicator;
  numeratorChildren.emplace_back(lhs);
  ArgumentPtr numerator = makeExpr(Mul(), numeratorChildren);

  ArgumentsPtrVector denominatorChildren = multiplicator;
  denominatorChildren.emplace_back(rhs);
  ArgumentPtr denominator = makeExpr(Mul(), denominatorChildren);

  return makeExpr(Div(), numerator, denominator);
}

ArgumentPtr DivExpression::nestedDivInDenominatorMulSimplify(const ArgumentsPtrVector &rhsChildren) {
  ArgumentsPtrVector multiplicator;

  for (const auto &child : rhsChildren) {
    if (const auto &rationalChild = cast<Rational>(child)) {
      multiplicator.emplace_back(std::make_shared<Integer>(rationalChild->denominator()));
    }
  }

  if (multiplicator.empty()) {
    return {};
  }

  return multiplicator.size() == 1 ? multiplicator.front() : makeExpr(Mul(), multiplicator);
}

}
