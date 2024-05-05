#include "fintamath/expressions/binary/PowExpr.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/PowOper.hpp"
#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(PowExpr)

using namespace detail;

constexpr int64_t maxPreciseRoot = 9;

PowExpr::PowExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Pow{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

const std::shared_ptr<IFunction> &PowExpr::getOutputFunction() const {
  static const std::shared_ptr<IFunction> pow = std::make_shared<PowOper>();
  static const std::shared_ptr<IFunction> sqrt = std::make_shared<Sqrt>();
  static const std::shared_ptr<IFunction> root = std::make_shared<Root>();

  if (const auto rhsChildRat = cast<Rational>(rhsChild)) {
    const Integer &numerator = rhsChildRat->numerator();
    const Integer &denominator = rhsChildRat->denominator();

    if (numerator == 1) {
      if (denominator == 2) {
        return sqrt;
      }

      return root;
    }
  }

  if (const auto rhsChildExpr = cast<IExpression>(rhsChild);
      rhsChildExpr &&
      is<Div>(rhsChildExpr->getFunction()) &&
      *rhsChildExpr->getChildren().front() == Integer(1)) {

    return root;
  }

  return pow;
}

std::string PowExpr::toString() const {
  const auto outFunc = getOutputFunction();

  if (is<Sqrt>(outFunc)) {
    return functionToString(Sqrt{}, {lhsChild});
  }

  if (is<Root>(outFunc)) {
    return functionToString(Root{}, {lhsChild, invert(rhsChild)});
  }

  return IBinaryExpression::toString();
}

ArgumentPtr PowExpr::approximate(const bool isTranformOverriden) const {
  if (const auto ratRhsChild = cast<Rational>(rhsChild); ratRhsChild && ratRhsChild->denominator() <= maxPreciseRoot) {
    auto approxExpr = cast<PowExpr>(clone());
    approximateChild(approxExpr->lhsChild);

    if (is<INumber>(approxExpr->lhsChild)) {
      return approxExpr->IBinaryExpression::approximate();
    }

    return approxExpr;
  }

  return IBinaryExpression::approximate(isTranformOverriden);
}

PowExpr::SimplifyFunctionVector PowExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &PowExpr::constSimplify,
      &PowExpr::polynomSimplify,
      &PowExpr::powSimplify,
  };
  return simplifyFunctions;
}

// Uses bites representation for generate all partitions of numbers, using stars and bars method.
// https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
// https://en.wikipedia.org/wiki/Partition_(number_theory)
// This method generate first bit number in sequence of numbers for each partition
Integer PowExpr::generateFirstNum(const Integer &countOfOne) {
  Integer n = 0;

  repeat(countOfOne, [&]() {
    n <<= 1;
    n |= 1;
  });

  return n;
}

// Uses algorithm for generating next number in sequence of partitions.
// https://en.wikipedia.org/wiki/Partition_(number_theory)
// https://en.wikipedia.org/wiki/Combinatorial_number_system#Applications
Integer PowExpr::generateNextNumber(const Integer &n) {
  const Integer u = n & -n;
  const Integer v = u + n;
  return v + (((v ^ n) / u) >> 2);
}

std::vector<Integer> PowExpr::getPartition(Integer bitNumber, const Integer &variableCount) {
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
ArgumentPtr PowExpr::sumPolynomSimplify(const ArgumentPtr &expr, const Integer &power) {
  const auto sumExpr = cast<IExpression>(expr);
  ArgumentPtrVector polynom;

  if (sumExpr && is<Add>(sumExpr->getFunction())) {
    polynom = sumExpr->getChildren();
  }
  else {
    return {};
  }

  const size_t variableCount = polynom.size();
  Integer bitNumber = generateFirstNum(power);
  const Integer combins = combinations(power + variableCount - 1, power);

  ArgumentPtrVector newChildren;

  repeat(combins, [&]() {
    std::vector<Integer> vectOfPows = getPartition(bitNumber, Integer(variableCount));
    bitNumber = generateNextNumber(bitNumber);

    ArgumentPtrVector mulExprChildren;
    mulExprChildren.emplace_back(multinomialCoefficient(vectOfPows).clone());

    for (size_t i = 0; i < variableCount; i++) {
      ArgumentPtr powExprChild = powExpr(polynom[i], vectOfPows[i].clone());
      mulExprChildren.emplace_back(std::move(powExprChild));
    }

    ArgumentPtr mulExprChild = mulExpr(std::move(mulExprChildren));
    newChildren.emplace_back(std::move(mulExprChild));
  });

  return addExpr(std::move(newChildren));
}

ArgumentPtr PowExpr::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    const ArgumentPtr &lhsExprLhsChild = lhsExpr->getChildren().front();
    const ArgumentPtr &lhsExprRhsChild = lhsExpr->getChildren().back();

    bool canMul = is<Integer>(rhs);

    if (const auto lhsExprLhsChildNum = cast<INumber>(lhsExprLhsChild)) {
      canMul = canMul ||
               (!lhsExprLhsChildNum->isComplex() &&
                *MoreEqv{}(*lhsExprLhsChildNum, Integer(0)) == Boolean(true));
    }

    if (canMul) {
      ArgumentPtr newLhs = lhsExprLhsChild;
      ArgumentPtr newRhs = mulExpr(lhsExprRhsChild, rhs);
      return powExpr(std::move(newLhs), std::move(newRhs));
    }
  }

  return {};
}

ArgumentPtr PowExpr::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (is<ComplexInf>(rhs)) {
    return Undefined{}.clone();
  }

  if (is<NegInf>(rhs)) {
    return powExpr(divExpr(Integer(1).clone(), lhs), Inf{}.clone());
  }

  if (is<Inf>(rhs)) {
    if (isInfinity(lhs)) {
      return ComplexInf{}.clone();
    }

    if (!containsVariable(lhs)) {
      ArgumentPtr approxLhs = lhs;
      approximateChild(approxLhs);

      if (const auto lhsNum = cast<INumber>(approxLhs)) {
        if (lhsNum->isComplex()) {
          return Undefined{}.clone();
        }

        const auto lhsNumAbs = cast<INumber>(Abs{}(*lhsNum));

        if (*lhsNumAbs == Integer(1)) {
          return Undefined{}.clone();
        }

        if (*lhsNumAbs > Integer(1)) {
          return Inf{}.clone();
        }

        return Integer(0).clone();
      }
    }
    else {
      return Undefined{}.clone();
    }
  }

  if (*rhs == Integer(1)) {
    return lhs;
  }

  if (*rhs == Integer(-1)) {
    static const ArgumentPtr one = Integer(1).clone();
    return divExpr(one, lhs);
  }

  if (const auto rhsNum = cast<INumber>(rhs); rhsNum && *rhsNum < Integer(0)) {
    static const ArgumentPtr one = Integer(1).clone();
    ArgumentPtr divRhs = powExpr(lhs, negExpr(rhs));
    return divExpr(one, std::move(divRhs));
  }

  if (is<NegInf>(lhs)) {
    ArgumentPtr mulLhs = powExpr(Integer(-1).clone(), rhs);
    ArgumentPtr mulRhs = powExpr(Inf{}.clone(), rhs);
    return mulExpr(std::move(mulLhs), std::move(mulRhs));
  }

  if (is<Inf>(lhs) || is<ComplexInf>(lhs)) {
    if (!containsVariable(rhs)) {
      ArgumentPtr approxRhs = rhs;
      approximateChild(approxRhs);

      if (const auto rhsComplex = cast<Complex>(approxRhs)) {
        if (rhsComplex->real() == Integer(0)) {
          return Undefined{}.clone();
        }

        return ComplexInf{}.clone();
      }

      if (const auto rhsNum = cast<INumber>(approxRhs)) {
        if (*rhsNum == Integer(0)) {
          return Undefined{}.clone();
        }

        if (*rhsNum < Integer(0)) {
          return Integer(0).clone();
        }

        return lhs;
      }
    }
    else {
      return Undefined{}.clone();
    }
  }

  if (*rhs == Integer(0)) {
    if (isMulInfinity(lhs)) {
      return Undefined{}.clone();
    }

    if (!containsInfinity(lhs)) {
      return Integer(1).clone();
    }
  }

  if (*lhs == Integer(0) || *lhs == Integer(1)) {
    if (isMulInfinity(rhs)) {
      return Undefined{}.clone();
    }

    if (!containsInfinity(rhs)) {
      return lhs;
    }
  }

  return {};
}

ArgumentPtr PowExpr::polynomSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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

ArgumentPtr PowExpr::mulSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (!is<Integer>(rhs)) {
    return {};
  }

  ArgumentPtr res;

  if (const auto mulExprChild = cast<IExpression>(lhs); mulExprChild && is<Mul>(mulExprChild->getFunction())) {
    ArgumentPtrVector args = mulExprChild->getChildren();

    for (auto &arg : args) {
      arg = powExpr(arg, rhs->clone());
    }

    res = mulExpr(std::move(args));
  }

  return res;
}

ArgumentPtr PowExpr::divSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (!is<Integer>(rhs)) {
    return {};
  }

  ArgumentPtr res;

  if (const auto divExprChild = cast<IExpression>(lhs); divExprChild && is<Div>(divExprChild->getFunction())) {
    ArgumentPtr numerator = powExpr(divExprChild->getChildren().front(), rhs);
    ArgumentPtr denominator = powExpr(divExprChild->getChildren().back(), rhs);
    res = divExpr(std::move(numerator), std::move(denominator));
  }

  return res;
}

ArgumentPtr PowExpr::sumSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto rhsInt = cast<Integer>(rhs)) {
    if (auto sumExpr = sumPolynomSimplify(lhs, *rhsInt)) {
      return sumExpr;
    }
  }

  return {};
}
}
