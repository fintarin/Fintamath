#include "fintamath/expressions/polynomial/MulExpression.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

using namespace detail;

MulExpression::MulExpression(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Mul{}, std::move(inChildren)) {
}

std::string MulExpression::toString() const {
  auto [childNumerator, childDenominator] = splitRational(children.front());

  if (*childDenominator != Integer(1)) {
    const bool isChildNumeratorPosOne = *childNumerator == Integer(1);
    const bool isChildNumeratorNegOne = *childNumerator == Integer(-1);

    ArgumentPtrVector numeratorChildren = children;

    if (isChildNumeratorPosOne || isChildNumeratorNegOne) {
      numeratorChildren.erase(numeratorChildren.begin());
    }
    else {
      numeratorChildren.front() = childNumerator;
    }

    ArgumentPtr numerator = makePolynom(Mul{}, std::move(numeratorChildren));
    ArgumentPtr denominator = childDenominator;
    const ArgumentPtr res = divExpr(std::move(numerator), std::move(denominator));

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
    return Neg{}.toString();
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
  static const SimplifyFunctionVector simplifyFunctions = {
      &MulExpression::rationalSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
  };
  return simplifyFunctions;
}

MulExpression::SimplifyFunctionVector MulExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &MulExpression::constSimplify,
      &MulExpression::polynomSimplify,
      &MulExpression::divSimplify,
      &MulExpression::powSimplify,
      &MulExpression::trigDoubleAngleSimplify,
  };
  return simplifyFunctions;
}

bool MulExpression::isConstantGreaterThanVariable() const {
  return true;
}

ArgumentPtr MulExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == Integer(0)) {
    if (isMulInfinity(rhs)) {
      return Undefined{}.clone();
    }

    if (!containsInfinity(rhs)) {
      return lhs;
    }
  }

  if (is<ComplexInf>(lhs) || is<ComplexInf>(rhs)) {
    return ComplexInf{}.clone();
  }

  if (is<NegInf>(lhs) && is<Inf>(rhs)) {
    return lhs;
  }

  if (is<NegInf>(rhs) && isComplexNumber(lhs)) {
    return mulExpr(negExpr(lhs), Inf{}.clone());
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
        return is<Inf>(rhs) ? NegInf{}.clone() : Inf{}.clone();
      }

      if (!isComplexNumber(rate) && !containsVariable(rate)) {
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
    return divExpr(std::move(numerator), std::move(denominator));
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
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr &&
      rhsExpr &&
      !is<Add>(lhsExpr->getFunction()) &&
      !is<Add>(rhsExpr->getFunction())) {

    return {};
  }

  if ((lhsExpr && is<Log>(lhsExpr->getFunction())) ||
      (rhsExpr && is<Log>(rhsExpr->getFunction()))) {

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
  auto [lhsChildBase, lhsChildRate] = splitPowExpr(lhs);
  auto [rhsChildBase, rhsChildRate] = splitPowExpr(rhs);

  if (*lhsChildBase == *rhsChildBase) {
    ArgumentPtr ratesSum = addExpr(std::move(lhsChildRate), std::move(rhsChildRate));
    return powExpr(std::move(lhsChildBase), std::move(ratesSum));
  }

  const auto lhsChildValueNum = cast<INumber>(lhsChildBase);
  const auto rhsChildValueNum = cast<INumber>(rhsChildBase);

  if (lhsChildValueNum &&
      rhsChildValueNum &&
      !lhsChildValueNum->isComplex() &&
      !rhsChildValueNum->isComplex() &&
      *lhsChildValueNum >= Integer(0) &&
      *rhsChildValueNum >= Integer(0) &&
      *lhsChildRate == *rhsChildRate &&
      *rhsChildRate != Integer(1)) {

    ArgumentPtr valuesMul = mulExpr(std::move(lhsChildBase), std::move(rhsChildBase));
    return powExpr(std::move(valuesMul), std::move(lhsChildRate));
  }

  return {};
}

ArgumentPtr MulExpression::trigDoubleAngleSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr ||
      !rhsExpr ||
      !is<Sin>(lhsExpr->getFunction()) ||
      !is<Cos>(rhsExpr->getFunction())) {

    return {};
  }

  auto lhsChild = lhsExpr->getChildren().front();
  const auto rhsChild = rhsExpr->getChildren().front();

  if (*lhsChild != *rhsChild || containsInfinity(lhsChild)) {
    return {};
  }

  ArgumentPtr doubleSin = sinExpr(
      mulExpr(std::move(lhsChild), Integer(2).clone()));

  return divExpr(doubleSin, Integer(2).clone());
}
}
