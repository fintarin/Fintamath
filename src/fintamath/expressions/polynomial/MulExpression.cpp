#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <algorithm>
#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

MulExpression::MulExpression(const ArgumentsPtrVector &inChildren)
    : IPolynomExpressionCRTP(Mul(), inChildren) {
}

std::string MulExpression::toString() const {
  if (const auto firstChildRat = cast<Rational>(children.front())) {
    ArgumentsPtrVector numeratorChildren = children;

    if (const Integer firstChildNumeratorAbs = abs(firstChildRat->numerator()); firstChildNumeratorAbs != 1) {
      numeratorChildren.front() = firstChildNumeratorAbs.clone();
    }
    else {
      numeratorChildren.erase(numeratorChildren.begin());
    }

    ArgumentPtr numerator = numeratorChildren.size() > 1 ? mulExpr(numeratorChildren) : numeratorChildren.front();
    ArgumentPtr denominator = firstChildRat->denominator().clone();
    ArgumentPtr res = divExpr(numerator, denominator);

    std::string resStr = res->toString();
    if (firstChildRat->numerator() < Integer(0)) {
      resStr.insert(0, Neg().toString());
    }

    return resStr;
  }

  return IPolynomExpression::toString();
}

std::string MulExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  if (!prevChild && *inChild == Integer(-1)) {
    return Neg().toString();
  }

  return (prevChild && *prevChild != Integer(-1) ? " " : "") + inChild->toString();
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForPreSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::constSimplify,
      &MulExpression::callFunctionSimplify,
      &MulExpression::rationalSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForPostSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::constSimplify,
      &MulExpression::polynomSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
  };
  return simplifyFunctions;
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateValuePair(const ArgumentPtr &rhsChild) {
  if (const auto &powExpr = cast<IExpression>(rhsChild);
      powExpr && is<Pow>(powExpr->getFunction())) {

    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {std::make_shared<Integer>(1), rhsChild};
}

ArgumentPtr MulExpression::constSimplify(const IFunction & /*func*/,
                                         const ArgumentPtr &lhsChild,
                                         const ArgumentPtr &rhsChild) {

  if (*lhsChild == Integer(0) &&
      (is<Inf>(rhsChild) || is<NegInf>(rhsChild) || is<ComplexInf>(rhsChild))) {
    return Undefined().clone();
  }

  if (is<ComplexInf>(lhsChild) || is<ComplexInf>(rhsChild)) {
    return ComplexInf().clone();
  }

  if (is<NegInf>(lhsChild) && is<Inf>(rhsChild)) {
    return lhsChild;
  }

  if (const auto lhsNum = cast<INumber>(lhsChild)) {
    bool isNegated = *lhsNum < Integer(0);

    if (is<Inf>(rhsChild)) {
      return isNegated ? NegInf().clone() : rhsChild;
    }

    if (is<NegInf>(rhsChild)) {
      return isNegated ? Inf().clone() : rhsChild;
    }
  }

  if (*lhsChild == Integer(0)) {
    return lhsChild;
  }

  if (*lhsChild == Integer(1)) {
    return rhsChild;
  }

  return {};
}

ArgumentPtr MulExpression::rationalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsRat = cast<Rational>(lhsChild)) {
    ArgumentPtr numerator = mulExpr(lhsRat->numerator().clone(), rhsChild);
    ArgumentPtr denominator = lhsRat->denominator().clone();
    return divExpr(numerator, denominator);
  }

  return {};
}

ArgumentPtr MulExpression::callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  return callFunction(func, {lhsChild, rhsChild});
}

ArgumentPtr MulExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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
    numerator = mulExpr(lhsExpr->getChildren().front(), rhsExpr->getChildren().front());
    denominator = mulExpr(lhsExpr->getChildren().back(), rhsExpr->getChildren().back());
  }
  else if (isLhsDiv) {
    numerator = mulExpr(lhsExpr->getChildren().front(), rhsChild);
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = mulExpr(lhsChild, rhsExpr->getChildren().front());
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  ArgumentPtr res = divExpr(numerator, denominator);
  return res;
}

ArgumentPtr MulExpression::polynomSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr &&
      !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhsChild);
  }

  if (rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhsChild);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(mulExpr(lhsSubChild, rhsSubChild));
    }
  }

  ArgumentPtr res = addExpr(resultVect);
  return res;
}

ArgumentPtr MulExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    ArgumentPtr ratesSum = addExpr(lhsChildRate, rhsChildRate);
    return powExpr(lhsChildValue, ratesSum);
  }

  if (is<INumber>(lhsChildValue) &&
      is<INumber>(rhsChildValue) &&
      *lhsChildRate == *rhsChildRate &&
      *rhsChildRate != Integer(1)) {

    ArgumentPtr valuesMul = mulExpr(lhsChildValue, rhsChildValue);
    return powExpr(valuesMul, lhsChildRate);
  }

  return {};
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

}
