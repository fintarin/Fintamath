#include "fintamath/expressions/binary/PowExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
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

PowExpression::SimplifyFunctionsVector PowExpression::getFunctionsForPostSimplify() const {
  static const PowExpression::SimplifyFunctionsVector simplifyFunctions = {
      &PowExpression::constSimplify,
      &PowExpression::polynomSimplify,
      &PowExpression::powSimplify,
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
    mulExprPolynom.emplace_back(multinomialCoefficient(powValue, vectOfPows).clone());

    for (size_t j = 0; j < size_t(variableCount); j++) {
      ArgumentPtr powExprChild = powExpr(polynom[j], vectOfPows[j].clone());
      mulExprPolynom.emplace_back(powExprChild);
    }

    ArgumentPtr mulExprChild = mulExpr(mulExprPolynom);
    newPolynom.emplace_back(mulExprChild);
  }

  ArgumentPtr res = addExpr(newPolynom);
  return res;
}

ArgumentPtr PowExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    auto lhsExprLhsChild = lhsExpr->getChildren().front();
    auto lhsExprRhsChild = lhsExpr->getChildren().back();

    bool canMul = is<Integer>(rhs) && is<Integer>(lhsExprRhsChild);

    if (auto lhsExprLhsChildNum = cast<INumber>(lhsExprLhsChild)) {
      canMul = canMul ||
               *MoreEqv()(*lhsExprLhsChildNum, Integer(0)) == Boolean(true);
    }

    if (canMul) {
      ArgumentPtr newLhs = lhsExprLhsChild;
      ArgumentPtr newRhs = mulExpr(lhsExprRhsChild, rhs);
      res = powExpr(newLhs, newRhs);
    }
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
    return divExpr(divLhs, divRhs);
  }

  if (const auto rhsComp = cast<IComparable>(rhs);
      is<NegInf>(rhs) ||
      (rhsComp && *rhsComp < Integer(0))) {

    ArgumentPtr divLhs = Integer(1).clone();
    ArgumentPtr divRhs = powExpr(lhs, negExpr(rhs));
    return divExpr(divLhs, divRhs);
  }

  if (is<NegInf>(lhs)) {
    ArgumentPtr mulLhs = powExpr(Integer(-1).clone(), rhs);
    ArgumentPtr mulRhs = powExpr(Inf().clone(), rhs);
    return mulExpr(mulLhs, mulRhs);
  }

  if (is<Inf>(lhs) || is<ComplexInf>(lhs)) {
    if (const auto rhsNum = cast<INumber>(rhs)) {
      if (*rhs == Integer(0)) {
        return Undefined().clone();
      }

      if (rhsNum->isComplex()) {
        return ComplexInf().clone();
      }

      return lhs;
    }

    return {};
  }

  if (*lhs == Integer(0)) {
    return lhs;
  }

  if (is<Inf>(rhs) || is<ComplexInf>(rhs)) {
    if (const auto lhsNum = cast<INumber>(lhs)) {
      if (lhsNum->isComplex()) {
        return Undefined().clone();
      }

      auto lhsNumAbs = cast<INumber>(Abs()(*lhsNum));

      if (*lhsNumAbs == Integer(1)) {
        return Undefined().clone();
      }

      if (*lhsNumAbs > Integer(1)) {
        return ComplexInf().clone();
      }

      return Integer(0).clone();
    }
  }

  if (*lhs == Integer(1)) {
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

  if (auto mulExprChild = cast<IExpression>(lhs); mulExprChild && is<Mul>(mulExprChild->getFunction())) {
    ArgumentsPtrVector args = mulExprChild->getChildren();

    for (auto &arg : args) {
      arg = powExpr(arg, rhs->clone());
    }

    res = mulExpr(args);
  }

  return res;
}

ArgumentPtr PowExpression::divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto divExprChild = cast<IExpression>(lhs); divExprChild && is<Div>(divExprChild->getFunction())) {
    ArgumentPtr numerator = powExpr(divExprChild->getChildren().front(), rhs);
    ArgumentPtr denominator = powExpr(divExprChild->getChildren().back(), rhs);
    res = divExpr(numerator, denominator);
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
