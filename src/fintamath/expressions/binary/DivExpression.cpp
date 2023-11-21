#include "fintamath/expressions/binary/DivExpression.hpp"

#include <set>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Csch.hpp"
#include "fintamath/functions/hyperbolic/Sech.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Csc.hpp"
#include "fintamath/functions/trigonometry/Sec.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

DivExpression::DivExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Div(), std::move(inLhsChild), std::move(inRhsChild)) {
}

std::string DivExpression::toString() const {
  if (isNegated(lhsChild)) { // TODO! find more efficient solution
    ArgumentPtr innerDiv = divExpr(negExpr(lhsChild)->toMinimalObject(), rhsChild);
    return negExpr(innerDiv)->toString();
  }

  return IBinaryExpression::toString();
}

DivExpression::SimplifyFunctionVector DivExpression::getFunctionsForPreSimplify() const {
  static const DivExpression::SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::constSimplify,
      &DivExpression::divSimplify,
      &DivExpression::mulPreSimplify,
  };
  return simplifyFunctions;
}

DivExpression::SimplifyFunctionVector DivExpression::getFunctionsForPostSimplify() const {
  static const DivExpression::SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::constSimplify,
      &DivExpression::negSimplify,
      &DivExpression::numSimplify,
      &DivExpression::divSimplify,
      &DivExpression::mulPostSimplify,
      &DivExpression::nestedRationalSimplify,
      &DivExpression::gcdSimplify,
      &DivExpression::sumSimplify,
      &DivExpression::mulSecCscSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr DivExpression::callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  return callFunction(func, {lhs, rhs});
}

ArgumentPtr DivExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if ((*lhs == Integer(0) || is<Inf>(lhs) || is<NegInf>(lhs) || is<ComplexInf>(lhs)) &&
      (*rhs == Integer(0) || is<Inf>(rhs) || is<NegInf>(rhs) || is<ComplexInf>(rhs))) {

    return Undefined().clone();
  }

  if (*lhs == Integer(0)) {
    return lhs;
  }

  if (*rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  if ((is<Inf>(rhs) || is<NegInf>(rhs) || is<ComplexInf>(rhs)) &&
      !containsInfinity(lhs)) {

    return Integer(0).clone();
  }

  if (*rhs == Integer(1)) {
    return lhs;
  }

  return {};
}

ArgumentPtr DivExpression::numSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const Integer one = 1;

  if (Div().doArgsMatch({one, *rhs})) {
    ArgumentPtr res = mulExpr(lhs, Div()(one, *rhs));
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtrVector numeratorChildren;
  ArgumentPtrVector denominatorChildren;

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

  ArgumentPtr numerator = makePolynom(Mul(), numeratorChildren);
  ArgumentPtr denominator = makePolynom(Mul(), denominatorChildren);
  ArgumentPtr res = divExpr(numerator, denominator);
  return res;
}

ArgumentPtr DivExpression::mulPreSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const DivExpression::SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::constSimplify,
      &DivExpression::callFunctionSimplify,
      &DivExpression::powSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulPostSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const DivExpression::SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::constSimplify,
      &DivExpression::callFunctionSimplify,
      &DivExpression::powSimplify,
      &DivExpression::tanCotSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulSecCscSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const DivExpression::SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::secCscSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulSimplify(const SimplifyFunctionVector &simplFuncs,
                                       const IFunction &func,
                                       const ArgumentPtr &lhs,
                                       const ArgumentPtr &rhs) {

  ArgumentPtrVector lhsChildren = getPolynomChildren(Mul(), lhs);
  ArgumentPtrVector rhsChildren = getPolynomChildren(Mul(), rhs);

  size_t lhsChildrenSizeInitial = lhsChildren.size();
  size_t rhsChildrenSizeInitial = rhsChildren.size();

  // TODO: use more efficient algorithm
  for (auto i : std::views::iota(0U, lhsChildren.size())) {
    auto &lhsChild = lhsChildren[i];

    for (auto j : std::views::iota(0U, rhsChildren.size())) {
      const auto &rhsChild = rhsChildren[j];

      ArgumentPtr res = useSimplifyFunctions(simplFuncs,
                                             func,
                                             lhsChild,
                                             rhsChild);

      if (res && !is<Rational>(res) && *res != *makeExpr(func, lhsChild, rhsChild)) {
        lhsChild = res;
        rhsChildren.erase(rhsChildren.begin() + ptrdiff_t(j));
        break;
      }
    }

    if (rhsChildren.empty()) {
      break;
    }
  }

  ArgumentPtr numerator;
  if (lhsChildren.size() > 1) {
    numerator = mulExpr(lhsChildren);
  }
  else {
    numerator = lhsChildren.front();
  }

  if (rhsChildren.empty()) {
    return numerator;
  }

  ArgumentPtr denominator;
  if (rhsChildren.size() > 1) {
    denominator = mulExpr(rhsChildren);
  }
  else {
    denominator = rhsChildren.front();
  }

  if (lhsChildren.size() != lhsChildrenSizeInitial || rhsChildren.size() != rhsChildrenSizeInitial) {
    ArgumentPtr res = divExpr(numerator, denominator);
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    ArgumentPtr res = divExpr(negExpr(lhs), negExpr(rhs));
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::sumSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto [result, remainder] = mulSumSimplify(lhs, rhs); result) {
    return remainder ? addExpr(result, remainder) : result;
  }

  if (auto [result, remainder] = sumMulSimplify(lhs, rhs); result) {
    return remainder ? addExpr(result, remainder) : result;
  }

  if (auto [result, remainder] = sumSumSimplify(lhs, rhs); result) {
    return remainder ? addExpr(result, remainder) : result;
  }

  if (auto [result, remainder] = sumSumSimplify(rhs, lhs); result && !is<IExpression>(remainder)) {
    ArgumentPtr denominator = remainder ? addExpr(result, remainder) : result;
    return divExpr(Integer(1).clone(), denominator);
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::sumSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtrVector lhsChildren;
  ArgumentPtrVector rhsChildren;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }

  if (lhsChildren.empty() || rhsChildren.empty()) {
    return {};
  }

  ArgumentPtrVector resultVect;
  ArgumentPtrVector remainderVect;

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

  ArgumentPtr result = resultVect.size() > 1 ? addExpr(std::move(resultVect)) : resultVect.front();
  ArgumentPtr remainderAdd = addExpr(std::move(remainderVect));
  ArgumentPtr remainder = divExpr(remainderAdd, rhs);
  simplifyChild(remainder);

  return {result, remainder};
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::sumMulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtrVector lhsChildren;

  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Add>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    return {};
  }

  if (const auto rhsChildExpr = cast<IExpression>(rhs);
      rhsChildExpr &&
      is<Add>(rhsChildExpr->getFunction()) &&
      !containsChild(lhs, rhs)) {

    return {};
  }

  ArgumentPtrVector resultChildren;
  ArgumentPtrVector remainderChildren;

  for (const auto &child : lhsChildren) {
    ArgumentPtr divResult = divExpr(child, rhs);
    simplifyChild(divResult);

    if (const auto divResultExpr = cast<IExpression>(divResult);
        divResultExpr &&
        is<Div>(divResultExpr->getFunction()) &&
        *divResultExpr->getChildren().back() == *rhs) {

      remainderChildren.emplace_back(child);
    }
    else {
      resultChildren.emplace_back(divResult);
    }
  }

  if (remainderChildren.size() == lhsChildren.size()) {
    return {};
  }

  ArgumentPtr result = resultChildren.size() > 1 ? addExpr(std::move(resultChildren)) : resultChildren.front();

  ArgumentPtr remainder;
  if (!remainderChildren.empty()) {
    ArgumentPtr remainderAdd = remainderChildren.size() > 1 ? addExpr(std::move(remainderChildren)) : remainderChildren.front();
    remainder = divExpr(remainderAdd, rhs);
    simplifyChild(remainder);
  }

  return {result, remainder};
}

std::pair<ArgumentPtr, ArgumentPtr> DivExpression::mulSumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (!containsVariable(rhs)) {
    return {};
  }

  ArgumentPtrVector rhsChildren;

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Add>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    return {};
  }

  if (const auto lhsChildExpr = cast<IExpression>(lhs);
      lhsChildExpr &&
      is<Add>(lhsChildExpr->getFunction())) {

    return {};
  }

  ArgumentPtr result = divExpr(lhs, rhsChildren.front());
  simplifyChild(result);

  if (containsDivFunction(result)) {
    return {};
  }

  ArgumentPtrVector multiplicators;

  for (auto i : std::views::iota(1U, rhsChildren.size())) {
    multiplicators.emplace_back(mulExpr(rhsChildren[i], result));
  }

  ArgumentPtr remainderAdd = multiplicators.size() > 1 ? addExpr(std::move(multiplicators)) : multiplicators.front();
  ArgumentPtr remainderNegAdd = negExpr(remainderAdd);
  simplifyChild(remainderNegAdd);
  ArgumentPtr remainder = divExpr(remainderNegAdd, rhs);

  return {result, remainder};
}

ArgumentPtr DivExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return Integer(1).clone();
  }

  auto [lhsChildRate, lhsChildValue] = splitPowExpr(lhs);
  auto [rhsChildRate, rhsChildValue] = splitPowExpr(rhs);

  auto lhsChildValueNum = cast<INumber>(lhsChildValue);
  auto lhsChildRateNum = cast<INumber>(lhsChildRate);
  auto rhsChildValueNum = cast<INumber>(rhsChildValue);
  auto rhsChildRateNum = cast<INumber>(rhsChildRate);

  if (lhsChildValueNum && rhsChildValueNum &&
      lhsChildRateNum && rhsChildRateNum &&
      *lhsChildRateNum < *rhsChildRateNum) {

    return {};
  }

  if (*lhsChildValue == *rhsChildValue) {
    return powExpr(lhsChildValue, addExpr(lhsChildRate, negExpr(rhsChildRate)));
  }

  if (lhsChildValueNum &&
      rhsChildValueNum &&
      *lhsChildRate == *rhsChildRate &&
      *rhsChildRate != Integer(1)) {

    ArgumentPtr valuesDiv = divExpr(lhsChildValue, rhsChildValue);
    return powExpr(valuesDiv, lhsChildRate);
  }

  if (rhsChildValueNum) {
    if (const auto rhsChildRateRat = cast<Rational>(rhsChildRate)) {
      ArgumentPtr numeratorPow = Pow()(*rhsChildValue, 1 - (*rhsChildRateRat));
      ArgumentPtr numerator = mulExpr(lhs, numeratorPow);
      return divExpr(numerator, rhsChildValue);
    }
  }

  return {};
}

ArgumentPtr DivExpression::nestedRationalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtrVector lhsChildren = getPolynomChildren(Mul(), lhs);
  ArgumentPtrVector rhsChildren = getPolynomChildren(Mul(), rhs);

  if (auto res = nestedNumeratorRationalSimplify(lhsChildren, rhs)) {
    return res;
  }

  if (auto res = nestedNumeratorRationalSimplify(rhsChildren, lhs)) {
    auto resDiv = cast<DivExpression>(res->clone());
    std::swap(resDiv->lhsChild, resDiv->rhsChild);
    return resDiv;
  }

  return {};
}

ArgumentPtr DivExpression::gcdSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtrVector lhsChildren = getPolynomChildren(Add(), lhs);
  ArgumentPtrVector rhsChildren = getPolynomChildren(Add(), rhs);

  Integer lhsGcdNum = getGcd(lhsChildren);
  Integer rhsGcdNum = getGcd(rhsChildren);

  if (lhsGcdNum <= 1 || rhsGcdNum <= 1) {
    return {};
  }

  Integer gcdNum = gcd(lhsGcdNum, rhsGcdNum);

  if (gcdNum <= 1) {
    return {};
  }

  ArgumentPtr numerator = divExpr(lhs, gcdNum.clone());
  simplifyChild(numerator);

  ArgumentPtr denominator = divExpr(rhs, gcdNum.clone());
  simplifyChild(denominator);

  return divExpr(numerator, denominator);
}

Integer DivExpression::getGcd(const ArgumentPtrVector &lhsChildren) {
  Integer gcdNum;

  for (auto child : lhsChildren) {
    if (const auto childExpr = cast<IExpression>(child); childExpr && is<Mul>(childExpr->getFunction())) {
      child = childExpr->getChildren().front();
    }

    if (const auto childInt = cast<Integer>(child)) {
      Integer childIntAbs = abs(*childInt);
      gcdNum = gcdNum != 0 ? gcd(gcdNum, childIntAbs) : childIntAbs;
    }
    else {
      return 1;
    }
  }

  return gcdNum;
}

ArgumentPtr DivExpression::nestedNumeratorRationalSimplify(const ArgumentPtrVector &lhsChildren, const ArgumentPtr &rhs) {
  ArgumentPtrVector numeratorChildren;
  ArgumentPtrVector denominatorChildren;

  for (const auto &child : lhsChildren) {
    if (const auto &rationalChild = cast<Rational>(child)) {
      numeratorChildren.emplace_back(rationalChild->numerator().clone());
      denominatorChildren.emplace_back(rationalChild->denominator().clone());
    }
    else {
      numeratorChildren.emplace_back(child);
    }
  }

  if (!denominatorChildren.empty()) {
    denominatorChildren.emplace_back(rhs);

    ArgumentPtr numerator = makePolynom(Mul(), numeratorChildren);
    ArgumentPtr denominator = makePolynom(Mul(), denominatorChildren);
    return divExpr(numerator, denominator);
  }

  return {};
}

ArgumentPtr DivExpression::tanCotSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsChildRate, lhsChildValue] = splitPowExpr(lhs);
  auto [rhsChildRate, rhsChildValue] = splitPowExpr(rhs);

  if (*lhsChildRate != *rhsChildRate) {
    return {};
  }

  auto lhsChildValueExpr = cast<IExpression>(lhsChildValue);
  auto rhsChildValueExpr = cast<IExpression>(rhsChildValue);

  if (lhsChildValueExpr && rhsChildValueExpr &&
      *lhsChildValueExpr->getChildren().front() == *rhsChildValueExpr->getChildren().front()) {

    if (is<Sin>(lhsChildValueExpr->getFunction()) && is<Cos>(rhsChildValueExpr->getFunction())) {
      return powExpr(tanExpr(*lhsChildValueExpr->getChildren().front()), lhsChildRate);
    }

    if (is<Cos>(lhsChildValueExpr->getFunction()) && is<Sin>(rhsChildValueExpr->getFunction())) {
      return powExpr(cotExpr(*lhsChildValueExpr->getChildren().front()), lhsChildRate);
    }

    if (is<Sinh>(lhsChildValueExpr->getFunction()) && is<Cosh>(rhsChildValueExpr->getFunction())) {
      return powExpr(tanhExpr(*lhsChildValueExpr->getChildren().front()), lhsChildRate);
    }

    if (is<Cosh>(lhsChildValueExpr->getFunction()) && is<Sinh>(rhsChildValueExpr->getFunction())) {
      return powExpr(cothExpr(*lhsChildValueExpr->getChildren().front()), lhsChildRate);
    }
  }

  return {};
}

ArgumentPtr DivExpression::secCscSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [rhsChildRate, rhsChildValue] = splitPowExpr(rhs);

  if (auto rhsChildValueExpr = cast<IExpression>(rhsChildValue)) {
    if (is<Sin>(rhsChildValueExpr->getFunction())) {
      return mulExpr(lhs, powExpr(cscExpr(*rhsChildValueExpr->getChildren().front()), rhsChildRate));
    }

    if (is<Cos>(rhsChildValueExpr->getFunction())) {
      return mulExpr(lhs, powExpr(secExpr(*rhsChildValueExpr->getChildren().front()), rhsChildRate));
    }

    if (is<Sinh>(rhsChildValueExpr->getFunction())) {
      return mulExpr(lhs, powExpr(cschExpr(*rhsChildValueExpr->getChildren().front()), rhsChildRate));
    }

    if (is<Cosh>(rhsChildValueExpr->getFunction())) {
      return mulExpr(lhs, powExpr(sechExpr(*rhsChildValueExpr->getChildren().front()), rhsChildRate));
    }
  }

  return {};
}

bool DivExpression::containsDivFunction(const ArgumentPtr &arg) {
  static const std::set<std::string> divFunctionStrings = {
      Div().toString(),
      Tan().toString(),
      Cot().toString(),
      Sec().toString(),
      Csc().toString(),
      Tanh().toString(),
      Coth().toString(),
      Sech().toString(),
      Csch().toString(),
  };

  return containsIf(arg, [](const ArgumentPtr &inArg) {
    const auto expr = cast<IExpression>(inArg);
    return expr && divFunctionStrings.contains(expr->getFunction()->toString());
  });
}
}
