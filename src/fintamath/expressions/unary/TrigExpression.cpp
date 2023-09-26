#include "fintamath/expressions/unary/TrigExpression.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

using TrigonometryFunctionTable = std::map<std::string, std::function<ArgumentPtr(const Rational &)>, std::less<>>;

using TrigonometryTable = std::map<Rational, ArgumentPtr>;

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key, bool isNegated);

TrigExpression::TrigExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

TrigExpression::SimplifyFunctionVector TrigExpression::getFunctionsForPreSimplify() const {
  static const TrigExpression::SimplifyFunctionVector simplifyFunctions = {
      &TrigExpression::oppositeFunctionsSimplify,
      &TrigExpression::tanSimplify,
      &TrigExpression::cotSimplify,
  };
  return simplifyFunctions;
}

TrigExpression::SimplifyFunctionVector TrigExpression::getFunctionsForPostSimplify() const {
  static const TrigExpression::SimplifyFunctionVector simplifyFunctions = {
      &TrigExpression::constSimplify,
      &TrigExpression::oppositeFunctionsSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr TrigExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

ArgumentPtr TrigExpression::tanSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Tan>(func)) {
    return divExpr(sinExpr(rhs), cosExpr(rhs));
  }

  return {};
}

ArgumentPtr TrigExpression::cotSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Cot>(func)) {
    return divExpr(cosExpr(rhs), sinExpr(rhs));
  }

  return {};
}

ArgumentPtr TrigExpression::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (*rhs == Pi()) {
    return trigTableSimplify(func, 1);
  }

  if (*rhs == *negExpr(Pi())) {
    return trigTableSimplify(func, -1);
  }

  const auto rhsExpr = cast<IExpression>(rhs);
  if (!rhsExpr || !is<Mul>(rhsExpr->getFunction())) {
    return {};
  }

  const auto rhsChildren = rhsExpr->getChildren();
  if (rhsChildren.size() != 2 || !is<Pi>(rhsChildren.back())) {
    return {};
  }

  const auto rhsChildRat = convert<Rational>(*rhsChildren.front());
  if (!rhsChildRat) {
    return {};
  }

  return trigTableSimplify(func, *rhsChildRat);
}

ArgumentPtr TrigExpression::trigTableSimplify(const IFunction &func, const Rational &rhs) {
  static const TrigonometryFunctionTable trigTable = {
      {Sin().toString(), &trigTableSinSimplify},
      {Cos().toString(), &trigTableCosSimplify},
  };

  if (auto iter = trigTable.find(func.toString()); iter != trigTable.end()) {
    Rational rhsShifted = phaseShiftPeriod(rhs);
    return iter->second(rhsShifted);
  }

  return {};
}

ArgumentPtr TrigExpression::trigTableSinSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(0).clone()},                                       // 0    | 0
      {Rational(1, 6), Rational(1, 2).clone()},                                // π/6  | 1/2
      {Rational(1, 4), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(2)))}, // π/4  | √2/2
      {Rational(1, 3), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(3)))}, // π/3  | √3/2
      {Rational(1, 2), Integer(1).clone()},                                    // π/2  | 1
      {Rational(2, 3), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(3)))}, // 2π/3 | √3/2
      {Rational(3, 4), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(2)))}, // 3π/4 | √2/2
      {Rational(5, 6), Rational(1, 2).clone()},                                // 5π/6 | 1/2
      {Rational(1), Integer(0).clone()},                                       // π    | 0
  };
  auto [rhsShifted, isNegated] = phaseShiftSin(rhs);
  return findValue(trigTable, rhsShifted, isNegated);
}

ArgumentPtr TrigExpression::trigTableCosSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(1).clone()},                                        // 0    | 1
      {Rational(1, 6), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(3)))},  // π/6  | √3/2
      {Rational(1, 4), mulExpr(Rational(1, 2).clone(), sqrtExpr(Integer(2)))},  // π/4  | √2/2
      {Rational(1, 3), Rational(1, 2).clone()},                                 // π/3  | 1/2
      {Rational(1, 2), Integer(0).clone()},                                     // π/2  | 0
      {Rational(2, 3), Rational(-1, 2).clone()},                                // 2π/3 | -1/2
      {Rational(3, 4), mulExpr(Rational(-1, 2).clone(), sqrtExpr(Integer(2)))}, // 3π/4 | -√2/2
      {Rational(5, 6), mulExpr(Rational(-1, 2).clone(), sqrtExpr(Integer(3)))}, // 5π/6 | -√3/2
      {Rational(1), Integer(-1).clone()},                                       // π    | -1
  };
  auto [rhsShifted, isNegated] = phaseShiftCos(rhs);
  return findValue(trigTable, rhsShifted, isNegated);
}

std::tuple<Rational, bool> TrigExpression::phaseShiftSin(const Rational &rhs) {
  Rational rhsShifted = rhs;
  bool isNegated = false;

  if (rhsShifted < 0) {
    rhsShifted = -rhsShifted;
    isNegated = !isNegated;
  }

  if (rhsShifted.numerator() > rhsShifted.denominator()) {
    rhsShifted = Rational(rhsShifted.numerator() % rhsShifted.denominator(), rhsShifted.denominator());
    isNegated = !isNegated;
  }

  return {rhsShifted, isNegated};
}

std::tuple<Rational, bool> TrigExpression::phaseShiftCos(const Rational &rhs) {
  Rational rhsShifted = rhs;
  bool isNegated = false;

  if (rhsShifted < 0) {
    rhsShifted = -rhsShifted;
  }

  if (rhsShifted.numerator() > rhsShifted.denominator()) {
    rhsShifted = Rational(rhsShifted.numerator() % rhsShifted.denominator(), rhsShifted.denominator());
    isNegated = !isNegated;
  }

  return {rhsShifted, isNegated};
}

Rational TrigExpression::phaseShiftPeriod(const Rational &rhs) {
  return Rational(rhs.numerator() % (rhs.denominator() * 2), rhs.denominator());
}

std::shared_ptr<IFunction> TrigExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sin().toString(), std::make_shared<Asin>()},
      {Cos().toString(), std::make_shared<Acos>()},
      {Tan().toString(), std::make_shared<Atan>()},
      {Cot().toString(), std::make_shared<Acot>()},
  };
  return oppositeFunctions.at(function.toString());
}

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key, bool isNegated) {
  if (auto res = trigTable.find(key); res != trigTable.end()) {
    return isNegated ? negExpr(res->second) : res->second;
  }

  return {};
}

}
