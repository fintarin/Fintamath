#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

MulExpression::MulExpression(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Mul(), std::move(inChildren)) {
}

std::string MulExpression::toString() const {
  auto [childNumerator, childDenominator] = splitRational(children.front());

  if (*childDenominator != Integer(1)) {
    bool isChildNumeratorPosOne = *childNumerator == Integer(1);
    bool isChildNumeratorNegOne = *childNumerator == Integer(-1);

    ArgumentPtrVector numeratorChildren = children;

    if (isChildNumeratorPosOne || isChildNumeratorNegOne) {
      numeratorChildren.erase(numeratorChildren.begin());
    }
    else {
      numeratorChildren.front() = childNumerator;
    }

    ArgumentPtr numerator = makePolynom(Mul(), std::move(numeratorChildren));
    ArgumentPtr denominator = childDenominator;
    ArgumentPtr res = divExpr(numerator, denominator);

    std::string resStr = res->toString();

    if (isChildNumeratorNegOne) {
      resStr.insert(resStr.begin(), '-');
    }

    return resStr;
  }

  return IPolynomExpression::toString();
}

std::string MulExpression::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  if (!prevChild && *inChild == Integer(-1)) {
    return Neg().toString();
  }

  std::string operStr;
  if (prevChild && *prevChild != Integer(-1)) {
    if (is<INumber>(inChild) && is<INumber>(prevChild)) {
      operStr = oper.toString();
    }
    else {
      operStr = " ";
    }
  }

  return operStr + operatorChildToString(oper, inChild);
}

MulExpression::SimplifyFunctionVector MulExpression::getFunctionsForPreSimplify() const {
  static const MulExpression::SimplifyFunctionVector simplifyFunctions = {
      &MulExpression::rationalSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionVector MulExpression::getFunctionsForPostSimplify() const {
  static const MulExpression::SimplifyFunctionVector simplifyFunctions = {
      &MulExpression::constSimplify,
      &MulExpression::polynomSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
      &MulExpression::trigDoubleAngleSimplify,
  };
  return simplifyFunctions;
}

bool MulExpression::isConstantOrderInversed() const {
  return true;
}

ArgumentPtr MulExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == Integer(0)) {
    if (isMulInfinity(rhs)) {
      return Undefined().clone();
    }

    if (!containsInfinity(rhs)) {
      return lhs;
    }
  }

  if (is<ComplexInf>(lhs) || is<ComplexInf>(rhs)) {
    return ComplexInf().clone();
  }

  if (is<NegInf>(lhs) && is<Inf>(rhs)) {
    return lhs;
  }

  if (is<NegInf>(rhs) && isComplexNumber(lhs)) {
    return mulExpr(negExpr(lhs), Inf().clone());
  }

  if (*lhs == Integer(1)) {
    return rhs;
  }

  {
    ArgumentPtr inf;
    ArgumentPtr rate;

    if (is<Inf>(lhs) || is<NegInf>(lhs)) {
      inf = lhs;
      rate = rhs;
    }
    else if (is<Inf>(rhs) || is<NegInf>(rhs)) {
      inf = rhs;
      rate = lhs;
    }

    if (rate && inf) {
      if (*lhs == Integer(-1)) {
        return is<Inf>(rhs) ? NegInf().clone() : Inf().clone();
      }

      if (!isComplexNumber(rate)) {
        if (const auto rateExpr = cast<IExpression>(rate); !rateExpr || !is<Sign>(rateExpr->getFunction())) {
          return mulExpr(signExpr(rate), inf);
        }
      }
    }
  }

  return {};
}

ArgumentPtr MulExpression::rationalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto lhsRat = cast<Rational>(lhs)) {
    ArgumentPtr numerator = mulExpr(lhsRat->numerator().clone(), rhs);
    ArgumentPtr denominator = lhsRat->denominator().clone();
    return divExpr(numerator, denominator);
  }

  return {};
}

ArgumentPtr MulExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

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
    numerator = mulExpr(lhsExpr->getChildren().front(), rhs);
    denominator = lhsExpr->getChildren().back();
  }
  else if (isRhsDiv) {
    numerator = mulExpr(lhs, rhsExpr->getChildren().front());
    denominator = rhsExpr->getChildren().back();
  }
  else {
    return {};
  }

  ArgumentPtr res = divExpr(numerator, denominator);
  return res;
}

ArgumentPtr MulExpression::polynomSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr &&
      rhsExpr &&
      !is<Add>(lhsExpr->getFunction()) &&
      !is<Add>(rhsExpr->getFunction())) {

    return {};
  }

  ArgumentPtrVector lhsChildren;
  ArgumentPtrVector rhsChildren;

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
    if (!containsVariable(lhs) && containsVariable(rhs)) {
      return {};
    }

    rhsChildren.emplace_back(rhs);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(mulExpr(lhsSubChild, rhsSubChild));
    }
  }

  ArgumentPtr res = addExpr(std::move(resultVect));
  return res;
}

ArgumentPtr MulExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsChildRate, lhsChildValue] = splitPowExpr(lhs);
  auto [rhsChildRate, rhsChildValue] = splitPowExpr(rhs);

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

ArgumentPtr MulExpression::trigDoubleAngleSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr ||
      !rhsExpr ||
      !is<Sin>(lhsExpr->getFunction()) ||
      !is<Cos>(rhsExpr->getFunction())) {

    return {};
  }

  auto lhsChild = lhsExpr->getChildren().front();
  auto rhsChild = rhsExpr->getChildren().front();

  if (*lhsChild != *rhsChild || containsInfinity(lhsChild)) {
    return {};
  }

  ArgumentPtr doubleSin = sinExpr(
      mulExpr(lhsChild, Integer(2).clone()));

  return divExpr(doubleSin, Integer(2).clone());
}

}
