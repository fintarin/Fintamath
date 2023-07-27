#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/constants/Indeterminate.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

PowExpression::PowExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Pow(), inLhsChild, inRhsChild) {
}

std::string PowExpression::toString() const {
  if (auto rhsChildRat = cast<Rational>(rhsChild)) {
    const Integer &numerator = rhsChildRat->numerator();
    const Integer &denominator = rhsChildRat->denominator();

    if (numerator == 1) {
      if (denominator == 2) {
        return functionToString(Sqrt(), {lhsChild});
      }

      return functionToString(Root(), {lhsChild, denominator.clone()});
    }
  }

  if (auto rhsChildExpr = cast<IExpression>(rhsChild); rhsChildExpr && is<Div>(rhsChildExpr->getFunction())) {
    if (*rhsChildExpr->getChildren().front() == Integer(1)) {
      return functionToString(Root(), {lhsChild, rhsChildExpr->getChildren().back()});
    }
  }

  return IBinaryExpression::toString();
}

std::shared_ptr<IFunction> PowExpression::getOutputFunction() const {
  if (auto rhsChildRat = cast<Rational>(rhsChild)) {
    const Integer &numerator = rhsChildRat->numerator();
    const Integer &denominator = rhsChildRat->denominator();

    if (numerator == 1) {
      if (denominator == 2) {
        return std::make_shared<Sqrt>();
      }

      return std::make_shared<Root>();
    }
  }

  if (auto rhsChildExpr = cast<IExpression>(rhsChild); rhsChildExpr && is<Div>(rhsChildExpr->getFunction())) {
    if (*rhsChildExpr->getChildren().front() == Integer(1)) {
      return std::make_shared<Root>();
    }
  }

  return IBinaryExpression::getFunction();
}

ArgumentPtr PowExpression::preciseSimplify() const {
  static const int64_t maxPreciseRoot = 9;

  if (const auto ratRhsChild = cast<Rational>(rhsChild); ratRhsChild && ratRhsChild->denominator() <= maxPreciseRoot) {
    auto preciseExpr = cast<PowExpression>(clone());
    preciseSimplifyChild(preciseExpr->lhsChild);
    return preciseExpr;
  }

  return IBinaryExpression::preciseSimplify();
}

PowExpression::SimplifyFunctionsVector PowExpression::getFunctionsForPreSimplify() const {
  static const PowExpression::SimplifyFunctionsVector simplifyFunctions = {
      &PowExpression::negSimplify, //
      &PowExpression::powSimplify, //
  };
  return simplifyFunctions;
}

PowExpression::SimplifyFunctionsVector PowExpression::getFunctionsForPostSimplify() const {
  static const PowExpression::SimplifyFunctionsVector simplifyFunctions = {
      &PowExpression::constSimplify,   //
      &PowExpression::polynomSimplify, //
      &PowExpression::negSimplify,     //
      &PowExpression::powSimplify,     //
  };
  return simplifyFunctions;
}

// Uses bites representation for generate all partitions of numbers, using stars and bars method.
// https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
// https://en.wikipedia.org/wiki/Partition_(number_theory)
// This method generate first bit number in sequence of numbers for each partition
Integer PowExpression::generateFirstNum(const Integer &countOfOne) {
  Integer n = 0;

  for (int i = 0; i < countOfOne; i++) {
    n = n << 1 | 1;
  }

  return n;
}

// Uses algorithm for generating next number in sequence of partitions.
// https://en.wikipedia.org/wiki/Partition_(number_theory)
// https://en.wikipedia.org/wiki/Combinatorial_number_system#Applications
Integer PowExpression::generateNextNumber(const Integer &n) {
  Integer u = n & -n;
  Integer v = u + n;
  return v + (((v ^ n) / u) >> 2);
}

std::vector<Integer> PowExpression::getPartition(Integer bitNumber, const Integer &variableCount) {
  std::vector<Integer> result;
  Integer counter = 0;

  while (int64_t(result.size()) < variableCount) {
    if (bitNumber % 2 == 1) {
      counter++;
    }

    if (bitNumber % 2 == 0) {
      result.emplace_back(counter);
      counter = 0;
    }

    bitNumber >>= 1;
  }

  return result;
}

// Uses multinomial theorem for exponentiation of sum.
// https://en.wikipedia.org/wiki/Multinomial_theorem
ArgumentPtr PowExpression::sumPolynomSimplify(const ArgumentPtr &expr, const Integer &powValue) {
  auto sumExpr = cast<IExpression>(expr);
  ArgumentsPtrVector polynom;

  if (sumExpr && is<Add>(sumExpr->getFunction())) {
    polynom = sumExpr->getChildren();
  }
  else {
    return {};
  }

  ArgumentsPtrVector newPolynom;
  Integer variableCount = int64_t(polynom.size());

  Integer bitNumber = generateFirstNum(powValue);

  for (int i = 0; i < combinations(powValue + variableCount - 1, powValue); i++) {
    std::vector<Integer> vectOfPows = getPartition(bitNumber, variableCount);
    bitNumber = generateNextNumber(bitNumber);

    ArgumentsPtrVector mulExprPolynom;
    mulExprPolynom.emplace_back(std::make_shared<Integer>(multinomialCoefficient(powValue, vectOfPows)));

    for (size_t j = 0; j < size_t(variableCount); j++) {
      ArgumentPtr powExpr = makeExpr(Pow(), polynom[j], std::make_shared<Integer>(std::move(vectOfPows[j])));
      mulExprPolynom.emplace_back(powExpr);
    }

    ArgumentPtr mulExpr = makeExpr(Mul(), mulExprPolynom);
    newPolynom.emplace_back(mulExpr);
  }

  ArgumentPtr res = makeExpr(Add(), newPolynom);
  return res;
}

ArgumentPtr PowExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    ArgumentPtr lhsMul = makeExpr(Pow(), std::make_shared<Integer>(-1), rhs);
    ArgumentPtr rhsMul = makeExpr(Pow(), lhsExpr->getChildren().front(), rhs);
    res = makeExpr(Mul(), lhsMul, rhsMul);
  }

  return res;
}

ArgumentPtr PowExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    ArgumentPtr lhsPow = lhsExpr->getChildren().front();
    ArgumentPtr rhsPow = makeExpr(Mul(), lhsExpr->getChildren().back(), rhs);
    res = makeExpr(Pow(), lhsPow, rhsPow);
  }

  return res;
}

ArgumentPtr PowExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*rhs == Integer(1)) {
    return lhs;
  }

  if (*rhs == Integer(-1)) {
    ArgumentPtr divLhs = Integer(1).clone();
    ArgumentPtr divRhs = lhs;
    return makeExpr(Div(), divLhs, divRhs);
  }

  if (const auto rhsComp = cast<IComparable>(rhs); is<NegInf>(rhs) || (rhsComp && *rhsComp < Integer(0))) {
    ArgumentPtr divLhs = Integer(1).clone();
    ArgumentPtr divRhs = makeExpr(Pow(), lhs, makeExpr(Neg(), rhs));
    return makeExpr(Div(), divLhs, divRhs);
  }

  if (is<NegInf>(lhs)) {
    ArgumentPtr mulLhs = makeExpr(Pow(), Integer(-1).clone(), rhs);
    ArgumentPtr mulRhs = makeExpr(Pow(), Inf().clone(), rhs);
    return makeExpr(Mul(), mulLhs, mulRhs);
  }

  if (is<Inf>(lhs)) {
    if (*rhs == Integer(0)) {
      return Indeterminate().clone();
    }

    return lhs;
  }

  if (*lhs == Integer(0)) {
    return lhs;
  }

  if (*lhs == Integer(1)) {
    if (is<Inf>(rhs)) {
      return Indeterminate().clone();
    }

    return lhs;
  }

  if (*rhs == Integer(0)) {
    return Integer(1).clone();
  }

  return {};
}

ArgumentPtr PowExpression::polynomSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto res = mulSimplify(lhs, rhs)) {
    return res;
  }

  if (auto res = sumSimplify(lhs, rhs)) {
    return res;
  }

  if (auto res = divSimplify(lhs, rhs)) {
    return res;
  }

  return {};
}

ArgumentPtr PowExpression::mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto mulExpr = cast<IExpression>(lhs); mulExpr && is<Mul>(mulExpr->getFunction())) {
    ArgumentsPtrVector args = mulExpr->getChildren();

    for (auto &arg : args) {
      arg = makeExpr(Pow(), arg, rhs->clone());
    }

    res = makeExpr(Mul(), args);
  }

  return res;
}

ArgumentPtr PowExpression::divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto divExpr = cast<IExpression>(lhs); divExpr && is<Div>(divExpr->getFunction())) {
    ArgumentPtr numerator = makeExpr(Pow(), divExpr->getChildren().front(), rhs);
    ArgumentPtr denominator = makeExpr(Pow(), divExpr->getChildren().back(), rhs);
    res = makeExpr(Div(), numerator, denominator);
  }

  return res;
}

ArgumentPtr PowExpression::sumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto rhsInt = cast<Integer>(rhs)) {
    if (auto sumExpr = sumPolynomSimplify(lhs, *rhsInt)) {
      return sumExpr;
    }
  }

  return {};
}

}
