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

MulExpression::MulExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(Mul(), inChildren) {
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

    ArgumentPtr numerator =
        numeratorChildren.size() > 1 ? makeExpr(Mul(), numeratorChildren) : numeratorChildren.front();
    ArgumentPtr denominator = firstChildRat->denominator().clone();
    ArgumentPtr res = makeExpr(Div(), numerator, denominator);

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
      &MulExpression::simplifyConst,        //
      &MulExpression::simplifyCallFunction, //
      &MulExpression::simplifyRationals,    //
      &MulExpression::simplifyDivisions,    //
      &MulExpression::simplifyPowers,       //
      &MulExpression::simplifyNegations,    //
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionsVector MulExpression::getFunctionsForPostSimplify() const {
  static const MulExpression::SimplifyFunctionsVector simplifyFunctions = {
      &MulExpression::simplifyConst,     //
      &MulExpression::mulPolynoms,       //
      &MulExpression::simplifyDivisions, //
      &MulExpression::simplifyPowers,    //
      &MulExpression::simplifyNegations, //
  };
  return simplifyFunctions;
}

std::pair<ArgumentPtr, ArgumentPtr> MulExpression::getRateValuePair(const ArgumentPtr &rhsChild) {
  if (const auto &powExpr = cast<IExpression>(rhsChild); powExpr && is<Pow>(powExpr->getFunction())) {
    ArgumentsPtrVector powExprChildren = powExpr->getChildren();
    return {powExprChildren[1], powExprChildren[0]};
  }

  return {std::make_shared<Integer>(1), rhsChild};
}

ArgumentPtr MulExpression::simplifyConst(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                         const ArgumentPtr &rhsChild) {

  if (*lhsChild == Integer(0) && (is<Inf>(rhsChild) || is<NegInf>(rhsChild) || is<ComplexInf>(rhsChild))) {
    return Undefined().clone();
  }

  if (is<ComplexInf>(lhsChild) || is<ComplexInf>(rhsChild)) {
    return ComplexInf().clone();
  }

  if (is<NegInf>(lhsChild) && is<Inf>(rhsChild)) {
    return lhsChild;
  }

  if (is<Inf>(rhsChild) || is<NegInf>(rhsChild) || is<ComplexInf>(rhsChild)) {
    if (const auto lhsNum = cast<INumber>(lhsChild)) {
      return *lhsNum < Integer(0) ? makeExpr(Neg(), rhsChild) : rhsChild;
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

ArgumentPtr MulExpression::simplifyRationals(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {

  if (const auto lhsRat = cast<Rational>(lhsChild)) {
    ArgumentPtr numerator = makeExpr(Mul(), lhsRat->numerator().clone(), rhsChild);
    ArgumentPtr denominator = lhsRat->denominator().clone();
    return makeExpr(Div(), numerator, denominator);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyCallFunction(const IFunction &func, const ArgumentPtr &lhsChild,
                                                const ArgumentPtr &rhsChild) {
  return callFunction(func, {lhsChild, rhsChild});
}

ArgumentPtr MulExpression::simplifyDivisions(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {

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
    numerator = makeExpr(Mul(), lhsExpr->getChildren().front(), rhsExpr->getChildren().front());
    denominator = makeExpr(Mul(), lhsExpr->getChildren().back(), rhsExpr->getChildren().back());
  }
  else if (isLhsDiv) {
    numerator = makeExpr(Mul(), lhsExpr->getChildren().front(), rhsChild);
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = makeExpr(Mul(), lhsChild, rhsExpr->getChildren().front());
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  ArgumentPtr res = makeExpr(Div(), numerator, denominator);
  return res;
}

ArgumentPtr MulExpression::mulPolynoms(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                       const ArgumentPtr &rhsChild) {

  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && !is<Add>(lhsExpr->getFunction()) && !is<Add>(rhsExpr->getFunction())) {
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
      resultVect.emplace_back(makeExpr(Mul(), lhsSubChild, rhsSubChild));
    }
  }

  ArgumentPtr res = makeExpr(Add(), resultVect);
  return res;
}

ArgumentPtr MulExpression::simplifyPowers(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                          const ArgumentPtr &rhsChild) {

  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    ArgumentPtr ratesSum = makeExpr(Add(), lhsChildRate, rhsChildRate);
    return makeExpr(Pow(), lhsChildValue, ratesSum);
  }

  if (*lhsChildRate == *rhsChildRate && *rhsChildRate != Integer(1) && is<INumber>(lhsChildValue) &&
      is<INumber>(rhsChildValue)) {

    ArgumentPtr valuesMul = makeExpr(Mul(), lhsChildValue, rhsChildValue);
    return makeExpr(Pow(), valuesMul, lhsChildRate);
  }

  return {};
}

ArgumentPtr MulExpression::simplifyNegations(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                             const ArgumentPtr &rhsChild) {
  const auto &lhsExpr = cast<IExpression>(lhsChild);
  const auto &rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr && is<Neg>(lhsExpr->getFunction()) && is<Neg>(rhsExpr->getFunction())) {
    ArgumentPtr res = makeExpr(Mul(), lhsExpr->getChildren().front(), rhsExpr->getChildren().front());
    return res;
  }

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    return makeExpr(Mul(), lhsExpr->getChildren().front(), std::make_shared<Integer>(-1), rhsChild);
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    return makeExpr(Mul(), rhsExpr->getChildren().front(), std::make_shared<Integer>(-1), lhsChild);
  }

  return {};
}

bool MulExpression::isTermsOrderInversed() const {
  return true;
}

}
