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
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

constexpr int64_t maxPreciseRoot = 9;

PowExpression::PowExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Pow(), std::move(inLhsChild), std::move(inRhsChild)) {
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

  if (auto rhsChildExpr = cast<IExpression>(rhsChild);
      rhsChildExpr &&
      is<Div>(rhsChildExpr->getFunction()) &&
      *rhsChildExpr->getChildren().front() == Integer(1)) {

    return std::make_shared<Root>();
  }

  return IBinaryExpression::getFunction();
}

ArgumentPtr PowExpression::approximateSimplify() const {
  if (const auto ratRhsChild = cast<Rational>(rhsChild); ratRhsChild && ratRhsChild->denominator() <= maxPreciseRoot) {
    auto approxExpr = cast<PowExpression>(clone());
    approximateSimplifyChild(approxExpr->lhsChild);

    if (is<INumber>(approxExpr->lhsChild)) {
      return approxExpr->IBinaryExpression::approximateSimplify();
    }

    return approxExpr;
  }

  return IBinaryExpression::approximateSimplify();
}

ArgumentPtr PowExpression::setPrecision(unsigned precision, const Integer &maxInt) const {
  if (const auto ratRhsChild = cast<Rational>(rhsChild); ratRhsChild && ratRhsChild->denominator() <= maxPreciseRoot) {
    auto approxExpr = cast<PowExpression>(clone());
    setPrecisionChild(approxExpr->lhsChild, precision, maxInt);
    return approxExpr;
  }

  return IBinaryExpression::setPrecision(precision, maxInt);
}

PowExpression::SimplifyFunctionVector PowExpression::getFunctionsForPostSimplify() const {
  static const PowExpression::SimplifyFunctionVector simplifyFunctions = {
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

  for ([[maybe_unused]] const auto _ : stdv::iota(0U, countOfOne)) {
    n <<= 1;
    n |= 1;
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

  while (result.size() < variableCount) {
    if (bitNumber % 2 == 1) {
      ++counter;
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
ArgumentPtr PowExpression::sumPolynomSimplify(const ArgumentPtr &expr, const Integer &power) {
  auto sumExpr = cast<IExpression>(expr);
  ArgumentPtrVector polynom;

  if (sumExpr && is<Add>(sumExpr->getFunction())) {
    polynom = sumExpr->getChildren();
  }
  else {
    return {};
  }

  size_t variableCount = polynom.size();
  Integer bitNumber = generateFirstNum(power);
  Integer combins = combinations(power + variableCount - 1, power);

  ArgumentPtrVector newChildren;

  for ([[maybe_unused]] const auto _ : stdv::iota(0U, combins)) {
    std::vector<Integer> vectOfPows = getPartition(bitNumber, Integer(variableCount));
    bitNumber = generateNextNumber(bitNumber);

    ArgumentPtrVector mulExprChildren;
    mulExprChildren.emplace_back(multinomialCoefficient(power, vectOfPows).clone());

    for (const auto i : stdv::iota(0U, variableCount)) {
      ArgumentPtr powExprChild = powExpr(polynom[i], vectOfPows[i].clone());
      mulExprChildren.emplace_back(powExprChild);
    }

    ArgumentPtr mulExprChild = mulExpr(std::move(mulExprChildren));
    newChildren.emplace_back(mulExprChild);
  }

  return addExpr(std::move(newChildren));
}

ArgumentPtr PowExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    const ArgumentPtr &lhsExprLhsChild = lhsExpr->getChildren().front();
    const ArgumentPtr &lhsExprRhsChild = lhsExpr->getChildren().back();

    bool canMul = is<Integer>(rhs);

    if (auto lhsExprLhsChildNum = cast<INumber>(lhsExprLhsChild)) {
      canMul = canMul ||
               (!lhsExprLhsChildNum->isComplex() &&
                *MoreEqv()(*lhsExprLhsChildNum, Integer(0)) == Boolean(true));
    }

    if (canMul) {
      ArgumentPtr newLhs = lhsExprLhsChild;
      ArgumentPtr newRhs = mulExpr(lhsExprRhsChild, rhs);
      return powExpr(newLhs, newRhs);
    }
  }

  return {};
}

ArgumentPtr PowExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (is<ComplexInf>(rhs)) {
    return Undefined().clone();
  }

  if (is<NegInf>(rhs)) {
    return powExpr(divExpr(Integer(1).clone(), lhs), Inf().clone());
  }

  if (is<Inf>(rhs)) {
    if (isInfinity(lhs)) {
      return ComplexInf().clone();
    }

    if (!containsVariable(lhs)) {
      ArgumentPtr approxLhs = lhs;
      approximateSimplifyChild(approxLhs);

      if (const auto lhsNum = cast<INumber>(approxLhs)) {
        if (lhsNum->isComplex()) {
          return Undefined().clone();
        }

        auto lhsNumAbs = cast<INumber>(Abs()(*lhsNum));

        if (*lhsNumAbs == Integer(1)) {
          return Undefined().clone();
        }

        if (*lhsNumAbs > Integer(1)) {
          return Inf().clone();
        }

        return Integer(0).clone();
      }
    }
    else {
      return Undefined().clone();
    }
  }

  if (*rhs == Integer(1)) {
    return lhs;
  }

  if (*rhs == Integer(-1)) {
    ArgumentPtr divLhs = Integer(1).clone();
    ArgumentPtr divRhs = lhs;
    return divExpr(divLhs, divRhs);
  }

  if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum < Integer(0)) {
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
    if (!containsVariable(rhs)) {
      ArgumentPtr approxRhs = rhs;
      approximateSimplifyChild(approxRhs);

      if (const auto rhsComplex = cast<Complex>(approxRhs)) {
        if (rhsComplex->real() == Integer(0)) {
          return Undefined().clone();
        }

        return ComplexInf().clone();
      }

      if (const auto rhsNum = cast<INumber>(approxRhs)) {
        if (*rhsNum == Integer(0)) {
          return Undefined().clone();
        }

        if (*rhsNum < Integer(0)) {
          return Integer(0).clone();
        }

        return lhs;
      }
    }
    else {
      return Undefined().clone();
    }
  }

  if (*rhs == Integer(0)) {
    if (isMulInfinity(lhs)) {
      return Undefined().clone();
    }

    if (!containsInfinity(lhs)) {
      return Integer(1).clone();
    }
  }

  if (*lhs == Integer(0) || *lhs == Integer(1)) {
    if (isMulInfinity(rhs)) {
      return Undefined().clone();
    }

    if (!containsInfinity(rhs)) {
      return lhs;
    }
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
  if (!is<Integer>(rhs)) {
    return {};
  }

  ArgumentPtr res;

  if (auto mulExprChild = cast<IExpression>(lhs); mulExprChild && is<Mul>(mulExprChild->getFunction())) {
    ArgumentPtrVector args = mulExprChild->getChildren();

    for (auto &arg : args) {
      arg = powExpr(arg, rhs->clone());
    }

    res = mulExpr(std::move(args));
  }

  return res;
}

ArgumentPtr PowExpression::divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (!is<Integer>(rhs)) {
    return {};
  }

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
