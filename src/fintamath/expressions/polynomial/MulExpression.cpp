#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Mul MUL;

MulExpression::MulExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(MUL, inChildren) {
}

std::string MulExpression::childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  if (!prevChild && *inChild == NEG_ONE) {
    return Neg().toString();
  }

  std::string result;

  if (auto sumExpr = cast<IExpression>(inChild); sumExpr && is<Add>(sumExpr->getFunction())) {
    result = putInBrackets(sumExpr->toString());
  }
  else {
    result = inChild->toString();
  }

  result = (prevChild && *prevChild != NEG_ONE ? " " : "") + result;

  return result;
}

ArgumentPtr MulExpression::negate() const {
  MulExpression mulExpr = *this;
  mulExpr.addElement(NEG_ONE.clone());
  return mulExpr.simplify();
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateValuePair(const ArgumentPtr &rhsChild) {
  if (const auto &powExpr = cast<IExpression>(rhsChild); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren.front()};
  }

  return {ONE.clone(), rhsChild};
}

ArgumentPtr MulExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeFunctionExpression(Add(), rates);
  return makeRawFunctionExpression(Pow(), {value, ratesSum});
}

ArgumentPtr MulExpression::simplifyNumbers(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == ZERO) {
    return lhsChild;
  }
  if (*rhsChild == ZERO) {
    return rhsChild;
  }

  if (*lhsChild == ONE) {
    return rhsChild;
  }
  if (*rhsChild == ONE) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr MulExpression::simplifyDivisions(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  const std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  bool isLhsDiv = false;
  bool isRhsDiv = false;

  if (lhsExpr && is<Div>(lhsExpr->getFunction())) {
    isLhsDiv = true;
  }

  if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    isRhsDiv = true;
  }

  ArgumentPtr numerator;
  ArgumentPtr denominator;

  if (isLhsDiv && isRhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});
    denominator = makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().back(), rhsExpr->getChildren().back()});
  }
  else if (isLhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), {lhsExpr->getChildren().front(), rhsChild});
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = makeRawFunctionExpression(Mul(), {lhsChild, rhsExpr->getChildren().front()});
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  return makeFunctionExpression(Div(), {numerator, denominator});
}

ArgumentPtr MulExpression::mulPolynoms(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  ArgumentPtr lhs = lhsChild;
  ArgumentPtr rhs = rhsChild;

  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhs);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhs);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(
          makeFunctionExpression(Mul(), ArgumentsPtrVector{lhsSubChild->clone(), rhsSubChild->clone()}));
    }
  }

  return makeFunctionExpression(Add(), resultVect);
}

ArgumentPtr MulExpression::mulRates(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyNegations(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForSimplify() const {
  return {
      &MulExpression::simplifyNegations, //
      &MulExpression::simplifyDivisions, //
      &MulExpression::mulRates,          //
      &MulExpression::simplifyNumbers,   //
      &MulExpression::mulPolynoms,       //
  };
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

}
