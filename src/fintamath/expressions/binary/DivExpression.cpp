#include "fintamath/expressions/binary/DivExpression.hpp"

#include <cstddef>
#include <functional>
#include <ranges>
#include <string>
#include <unordered_set>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionComparator.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
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
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

DivExpression::DivExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Div{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

std::string DivExpression::toString() const {
  if (isNegated(lhsChild)) { // TODO! find more efficient solution
    ArgumentPtr innerDiv = divExpr(negExpr(lhsChild)->toMinimalObject(), rhsChild);
    return negExpr(innerDiv)->toString();
  }

  return IBinaryExpression::toString();
}

DivExpression::SimplifyFunctionVector DivExpression::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::divSimplify,
      &DivExpression::mulPreSimplify,
  };
  return simplifyFunctions;
}

DivExpression::SimplifyFunctionVector DivExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
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

ArgumentPtr DivExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if ((*lhs == Integer(0) && *rhs == Integer(0)) ||
      (isMulInfinity(lhs) && isMulInfinity(rhs))) {

    return Undefined{}.clone();
  }

  if (*rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  if (isMulInfinity(rhs)) {
    return Integer(0).clone();
  }

  if (*lhs == Integer(0)) {
    return lhs;
  }

  if (*rhs == Integer(1)) {
    return lhs;
  }

  return {};
}

ArgumentPtr DivExpression::numSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const Integer one = 1;

  if (*rhs != Integer(0) && Div{}.doArgsMatch({one, *rhs})) {
    ArgumentPtr res = mulExpr(lhs, Div{}(one, *rhs));
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (containsDivTrigFunction(lhs) || containsDivTrigFunction(rhs)) {
    return {};
  }

  ArgumentPtrVector numeratorChildren;
  ArgumentPtrVector denominatorChildren;

  bool containsDivExpression = false;

  if (const auto lhsDivExpr = cast<DivExpression>(lhs)) {
    numeratorChildren.emplace_back(lhsDivExpr->getChildren().front());
    denominatorChildren.emplace_back(lhsDivExpr->getChildren().back());
    containsDivExpression = true;
  }
  else {
    numeratorChildren.emplace_back(lhs);
  }

  if (const auto rhsDivExpr = cast<DivExpression>(rhs)) {
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

  ArgumentPtr numerator = makePolynom(Mul{}, std::move(numeratorChildren));
  ArgumentPtr denominator = makePolynom(Mul{}, std::move(denominatorChildren));
  ArgumentPtr res = divExpr(numerator, denominator);

  return res;
}

ArgumentPtr DivExpression::mulPreSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::powSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulPostSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::constSimplify,
      &DivExpression::equalSimplify,
      &DivExpression::powSimplify,
      &DivExpression::tanCotSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulSecCscSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  static const SimplifyFunctionVector simplifyFunctions = {
      &DivExpression::secCscSimplify,
  };
  return mulSimplify(simplifyFunctions, func, lhs, rhs);
}

ArgumentPtr DivExpression::mulSimplify(const SimplifyFunctionVector &simplFuncs,
                                       const IFunction &func,
                                       const ArgumentPtr &lhs,
                                       const ArgumentPtr &rhs) {

  ArgumentPtrVector lhsChildren = getPolynomChildren(Mul{}, lhs);
  ArgumentPtrVector rhsChildren = getPolynomChildren(Mul{}, rhs);

  const size_t lhsChildrenSizeInitial = lhsChildren.size();
  const size_t rhsChildrenSizeInitial = rhsChildren.size();

  // TODO: use more efficient algorithm
  for (const auto i : stdv::iota(0U, lhsChildren.size())) {
    auto &lhsChild = lhsChildren[i];

    for (const auto j : stdv::iota(0U, rhsChildren.size())) {
      const auto &rhsChild = rhsChildren[j];

      ArgumentPtr res = useSimplifyFunctions(simplFuncs,
                                             func,
                                             lhsChild,
                                             rhsChild);

      if (res && !is<Rational>(res) && *res != *makeExpr(func, lhsChild, rhsChild)) {
        lhsChild = res;
        rhsChildren.erase(rhsChildren.begin() + static_cast<ptrdiff_t>(j));
        break;
      }
    }

    if (rhsChildren.empty()) {
      break;
    }
  }

  ArgumentPtr numerator = makePolynom(Mul{}, lhsChildren);

  if (rhsChildren.empty()) {
    return numerator;
  }

  ArgumentPtr denominator = makePolynom(Mul{}, rhsChildren);

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
    if (auto [result, remainder] = mulSumSimplify(child, rhs); result) {
      resultVect.emplace_back(result);

      if (remainder) {
        const auto remainderDiv = cast<DivExpression>(remainder);
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

  ArgumentPtr result = makePolynom(Add{}, std::move(resultVect));
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

  ArgumentPtr result = makePolynom(Add{}, std::move(resultChildren));

  ArgumentPtr remainder;
  if (!remainderChildren.empty()) {
    ArgumentPtr remainderAdd = makePolynom(Add{}, std::move(remainderChildren));
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

  if (containsDivTrigFunction(result) || is<DivExpression>(result)) {
    return {};
  }

  ArgumentPtrVector multiplicators;

  for (const auto &rhsChild : rhsChildren | stdv::drop(1)) {
    multiplicators.emplace_back(mulExpr(rhsChild, result));
  }

  ArgumentPtr remainderAdd = negExpr(makePolynom(Add{}, std::move(multiplicators)));
  simplifyChild(remainderAdd);

  if (const ArgumentPtr remainderAddFirstChild = getPolynomChildren(Add{}, remainderAdd).front();
      compare(lhs, remainderAddFirstChild) != std::strong_ordering::greater) {

    return {};
  }

  ArgumentPtr remainder = divExpr(remainderAdd, rhs);

  return {result, remainder};
}

ArgumentPtr DivExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs && !containsInfinity(lhs)) {
    return Integer(1).clone();
  }

  return {};
}

ArgumentPtr DivExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsChildBase, lhsChildRate] = splitPowExpr(lhs);
  auto [rhsChildBase, rhsChildRate] = splitPowExpr(rhs);

  const auto lhsChildBaseNum = cast<INumber>(rhsChildBase);
  const auto lhsChildRateNum = cast<INumber>(lhsChildRate);
  const auto rhsChildBaseNum = cast<INumber>(rhsChildBase);
  const auto rhsChildRateNum = cast<INumber>(rhsChildRate);

  if (lhsChildBaseNum && rhsChildBaseNum &&
      lhsChildRateNum && rhsChildRateNum &&
      *lhsChildRateNum < *rhsChildRateNum) {

    return {};
  }

  if (*lhsChildBase == *rhsChildBase && !containsInfinity(rhsChildBase)) {
    return powExpr(rhsChildBase, addExpr(lhsChildRate, negExpr(rhsChildRate)));
  }

  if (rhsChildBaseNum) {
    if (const auto rhsChildRateRat = cast<Rational>(rhsChildRate)) {
      ArgumentPtr numeratorPow = Pow{}(*rhsChildBase, 1 - (*rhsChildRateRat));
      ArgumentPtr numerator = mulExpr(lhs, numeratorPow);
      return divExpr(numerator, rhsChildBase);
    }
  }

  return {};
}

ArgumentPtr DivExpression::nestedRationalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const ArgumentPtrVector lhsChildren = getPolynomChildren(Mul{}, lhs);

  if (auto res = nestedNumeratorRationalSimplify(lhsChildren, rhs)) {
    return res;
  }

  return {};
}

ArgumentPtr DivExpression::gcdSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const ArgumentPtrVector lhsChildren = getPolynomChildren(Add{}, lhs);
  const ArgumentPtrVector rhsChildren = getPolynomChildren(Add{}, rhs);

  const Integer lhsGcdNum = getGcd(lhsChildren);
  const Integer rhsGcdNum = getGcd(rhsChildren);

  if (lhsGcdNum <= 1 || rhsGcdNum <= 1) {
    return {};
  }

  const Integer gcdNum = gcd(lhsGcdNum, rhsGcdNum);

  if (gcdNum <= 1) {
    return {};
  }

  ArgumentPtr numerator = divExpr(lhs, gcdNum.clone());
  simplifyChild(numerator);

  ArgumentPtr denominator = divExpr(rhs, gcdNum.clone());
  simplifyChild(denominator);

  return divExpr(numerator, denominator);
}

Integer DivExpression::getGcd(const ArgumentPtrVector &children) {
  Integer gcdNum;

  for (auto child : children) {
    if (const auto childExpr = cast<IExpression>(child); childExpr && is<Mul>(childExpr->getFunction())) {
      child = childExpr->getChildren().front();
    }

    if (const auto childInt = cast<Integer>(child)) {
      const Integer childIntAbs = abs(*childInt);
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
    if (auto [childNumerator, childDenominator] = splitRational(child);
        *childDenominator != Integer(1)) {

      numeratorChildren.emplace_back(childNumerator);
      denominatorChildren.emplace_back(childDenominator);
    }
    else {
      numeratorChildren.emplace_back(child);
    }
  }

  if (!denominatorChildren.empty()) {
    denominatorChildren.emplace_back(rhs);

    ArgumentPtr numerator = makePolynom(Mul{}, std::move(numeratorChildren));
    ArgumentPtr denominator = makePolynom(Mul{}, std::move(denominatorChildren));

    return divExpr(numerator, denominator);
  }

  return {};
}

ArgumentPtr DivExpression::tanCotSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsChildBase, lhsChildRate] = splitPowExpr(lhs);
  auto [rhsChildBase, rhsChildRate] = splitPowExpr(rhs);

  if (*lhsChildRate != *rhsChildRate) {
    return {};
  }

  const auto lhsChildValueExpr = cast<IExpression>(lhsChildBase);
  const auto rhsChildValueExpr = cast<IExpression>(rhsChildBase);

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
  auto [rhsChildBase, rhsChildRate] = splitPowExpr(rhs);

  if (const auto rhsChildValueExpr = cast<IExpression>(rhsChildBase)) {
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

bool DivExpression::containsDivTrigFunction(const ArgumentPtr &arg) {
  static const std::unordered_set<std::string> functionStrings = {
      Tan{}.toString(),
      Cot{}.toString(),
      Sec{}.toString(),
      Csc{}.toString(),
      Tanh{}.toString(),
      Coth{}.toString(),
      Sech{}.toString(),
      Csch{}.toString(),
  };

  return containsIf(arg, [](const ArgumentPtr &inArg) {
    const auto expr = cast<IExpression>(inArg);
    return expr && functionStrings.contains(expr->getFunction()->toString());
  });
}
}
