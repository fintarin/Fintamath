#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Mul MUL;

MulExpression::MulExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(MUL, children) {
}

string MulExpression::toString() const {
  ArgumentsPtrVector nonInvertedChild;
  ArgumentsPtrVector invertedChild;
  for (const auto &child : children) {
    if (const auto &childExpr = cast<IExpression>(child); childExpr && is<Inv>(childExpr->getFunction())) {
      invertedChild.emplace_back(child);
    }
    else {
      nonInvertedChild.emplace_back(child);
    }
  }

  string result;
  switch (nonInvertedChild.size()) {
  case 0: {
    result += childToString(invertedChild.front(), true);
    for (size_t i = 1; i < invertedChild.size(); i++) {
      result += childToString(invertedChild[i]);
    }
    break;
  }
  case 1: {
    result += childToString(nonInvertedChild.front(), true);
    for (const auto &child : invertedChild) {
      result += childToString(child);
    }
    break;
  }
  default: {
    result += childToString(nonInvertedChild.front(), true);
    for (size_t i = 1; i < nonInvertedChild.size(); i++) {
      result += childToString(nonInvertedChild[i], result == "-");
    }
    if (!invertedChild.empty()) {
      result = putInBrackets(result);
    }
    for (const auto &child : invertedChild) {
      result += childToString(child);
    }
  }
  }

  return result;
}

string MulExpression::childToString(const ArgumentPtr &inChild, bool isFirst) const {
  if (const auto &number = cast<INumber>(inChild); number && isFirst && *number == NEG_ONE) {
    return Neg().toString();
  }

  bool invert = false;
  ArgumentPtr child = inChild;

  if (auto invExpr = cast<IExpression>(inChild); invExpr && is<Inv>(invExpr->getFunction())) {
    child = invExpr->getChildren()[0];
    invert = true;
  }

  string result;

  if (auto sumExpr = cast<IExpression>(child); sumExpr && is<Add>(sumExpr->getFunction())) {
    result = putInBrackets(sumExpr->toString());
  }
  else {
    result = child->toString();
  }

  if (invert) {
    result = (isFirst ? "1/" : "/") + result;
  }
  else {
    result = (isFirst ? "" : " ") + result;
  }

  return result;
}

ArgumentPtr MulExpression::negate() const {
  MulExpression neg = *this;
  neg.addElement(make_shared<Integer>(NEG_ONE));
  return neg.simplify();
}

ArgumentPtr MulExpression::invert() const {
  auto inv = cast<MulExpression>(clone());

  for (auto &child : inv->children) {
    child = makeFunctionExpression(Inv(), {child});
  }

  return inv->simplify();
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateAndValue(const ArgumentPtr &rhsChild) {
  if (const auto &exprVal = cast<IExpression>(rhsChild); exprVal && is<Pow>(exprVal->getFunction())) {
    ArgumentsPtrVector args = exprVal->getChildren();
    return {args[1], args.front()};
  }

  if (const auto &exprVal = cast<IExpression>(rhsChild); exprVal && is<Inv>(exprVal->getFunction())) {
    ArgumentsPtrVector args = exprVal->getChildren();
    std::pair<ArgumentPtr, ArgumentPtr> result = getRateAndValue(args.front());
    result.first = makeFunctionExpression(Neg(), {result.first});
    return result;
  }

  return {ONE.clone(), rhsChild};
}

ArgumentPtr MulExpression::addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value) {
  ArgumentPtr rateSum = makeFunctionExpression(Add(), rate);
  return makeRawFunctionExpression(Pow(), {value, rateSum});
}

ArgumentPtr MulExpression::simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsInt = cast<INumber>(lhsChild); lhsInt && *lhsInt == ZERO) {
    return lhsChild;
  }
  if (const auto rhsInt = cast<INumber>(rhsChild); rhsInt && *rhsInt == ZERO) {
    return rhsChild;
  }

  if (const auto lhsInt = cast<INumber>(lhsChild); lhsInt && *lhsInt == ONE) {
    return rhsChild;
  }
  if (const auto rhsInt = cast<INumber>(rhsChild); rhsInt && *rhsInt == ONE) {
    return lhsChild;
  }

  bool lhsInv = false;
  bool rhsInv = false;

  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  shared_ptr<const INumber> lhsNum = nullptr;
  shared_ptr<const INumber> rhsNum = nullptr;

  if (lhsExpr && is<Inv>(lhsExpr->getFunction())) {
    lhsInv = true;
    lhsNum = cast<INumber>(lhsExpr->getChildren().front());
  }
  else {
    lhsNum = cast<INumber>(lhsChild);
  }

  if (rhsExpr && is<Inv>(rhsExpr->getFunction())) {
    rhsInv = true;
    rhsNum = cast<INumber>(rhsExpr->getChildren().front());
  }
  else {
    rhsNum = cast<INumber>(rhsChild);
  }

  if (lhsNum && rhsNum) {
    if (lhsInv) {
      return Div()(*rhsNum, *lhsNum);
    }
    if (rhsInv) {
      return Div()(*lhsNum, *rhsNum);
    }
    if (lhsInv && rhsInv) {
      return makeFunctionExpression(Inv(), {Mul()(*lhsNum, *rhsNum)});
    }
    return Mul()(*lhsNum, *rhsNum);
  }

  return nullptr;
}

ArgumentPtr MulExpression::simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Inv>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return make_shared<Integer>(ONE);
  }
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Inv>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return make_shared<Integer>(ONE);
  }

  return {};
}

ArgumentPtr MulExpression::multiplicateBraces(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  bool inverted = false;
  ArgumentPtr lhsVal = lhsChild;
  ArgumentPtr rhsVal = rhsChild;
  shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsVal);
  shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsVal);

  if (lhsExpr && rhsExpr && is<Inv>(lhsExpr->getFunction()) && is<Inv>(rhsExpr->getFunction())) {
    inverted = true;
    lhsVal = lhsExpr->getChildren()[0];
    rhsVal = rhsExpr->getChildren()[0];
    lhsExpr = cast<IExpression>(lhsVal);
    rhsExpr = cast<IExpression>(rhsVal);
  }

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsVect;
  ArgumentsPtrVector rhsVect;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsVect = lhsExpr->getChildren();
  }
  else {
    lhsVect.emplace_back(lhsVal);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsVect = rhsExpr->getChildren();
  }
  else {
    rhsVect.emplace_back(rhsVal);
  }

  if (lhsVect.size() == 1 && rhsVect.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;
  for (const auto &lhsChildValue : lhsVect) {
    for (const auto &rhsChildValue : rhsVect) {
      resultVect.emplace_back(
          makeFunctionExpression(Mul(), ArgumentsPtrVector{lhsChildValue->clone(), rhsChildValue->clone()}));
    }
  }

  if (inverted) {
    return makeFunctionExpression(Inv(), {makeFunctionExpression(Add(), resultVect)});
  }

  return makeFunctionExpression(Add(), resultVect);
}

ArgumentPtr MulExpression::coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::pair<ArgumentPtr, ArgumentPtr> lhsRateValue = getRateAndValue(lhsChild);
  std::pair<ArgumentPtr, ArgumentPtr> rhsRateValue = getRateAndValue(rhsChild);

  ArgumentPtr lhsChildRate = lhsRateValue.first;
  ArgumentPtr rhsChildRate = rhsRateValue.first;

  ArgumentPtr lhsChildValue = lhsRateValue.second;
  ArgumentPtr rhsChildValue = rhsRateValue.second;

  if (lhsChildValue->toString() == rhsChildValue->toString()) {
    return addRateToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const auto &lhsExpr = cast<IExpression>(lhsChild);
  const auto &rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && is<Neg>(lhsExpr->getFunction()) && is<Neg>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(),
                                  ArgumentsPtrVector{lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});
  }

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().front(), NEG_ONE.clone(), rhsChild});
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    return makeRawFunctionExpression(Mul(), {rhsExpr->getChildren().front(), NEG_ONE.clone(), lhsChild});
  }

  return {};
}

MulExpression::FunctionsVector MulExpression::getSimplifyFunctions() const {
  return {
      &MulExpression::simplifyNegation,       //
      &MulExpression::simplifyDivisions,      //
      &MulExpression::coefficientsProcessing, //
      &MulExpression::simplifyNumber,         //
      &MulExpression::multiplicateBraces,     //
  };
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

int MulExpression::comparatorOverride(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  bool isLhsInverted = lhsExpr && *lhsExpr->getFunction() == Inv();

  auto rhsExpr = cast<IExpression>(rhs);
  bool isRhsInverted = rhsExpr && *rhsExpr->getFunction() == Inv();

  if (isLhsInverted && !isRhsInverted) {
    return 1;
  }

  if (!isLhsInverted && isRhsInverted) {
    return -1;
  }

  return 0;
}

}
