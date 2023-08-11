#include "fintamath/expressions/unary/TrigExpression.hpp"

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

using TrigonometryFunctionsTable = std::map<std::string, std::function<ArgumentPtr(const Rational &)>>;

using TrigonometryTable = std::map<Rational, ArgumentPtr>;

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key, bool isNegated);

TrigExpression::TrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

TrigExpression::SimplifyFunctionsVector TrigExpression::getFunctionsForPreSimplify() const {
  static const TrigExpression::SimplifyFunctionsVector simplifyFunctions = {
      &TrigExpression::oppositeFunctionsSimplify,
  };
  return simplifyFunctions;
}

TrigExpression::SimplifyFunctionsVector TrigExpression::getFunctionsForPostSimplify() const {
  static const TrigExpression::SimplifyFunctionsVector simplifyFunctions = {
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

ArgumentPtr TrigExpression::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (*rhs == Pi()) {
    return trigTableSimplify(func, 1);
  }

  if (*rhs == *makeExpr(Neg(), Pi())) {
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
  static const TrigonometryFunctionsTable trigTable = {
      {Sin().toString(), &trigTableSinSimplify},
      {Cos().toString(), &trigTableCosSimplify},
      {Tan().toString(), &trigTableTanSimplify},
      {Cot().toString(), &trigTableCotSimplify},
  };
  Rational rhsShifted = phaseShiftPeriod(rhs);
  return trigTable.at(func.toString())(rhsShifted);
}

ArgumentPtr TrigExpression::trigTableSinSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(0).clone()},                                                       // 0    | 0
      {Rational(1, 6), Rational(1, 2).clone()},                                                // π/6  | 1/2
      {Rational(1, 4), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(2)))}, // π/4  | √2/2
      {Rational(1, 3), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(3)))}, // π/3  | √3/2
      {Rational(1, 2), Integer(1).clone()},                                                    // π/2  | 1
      {Rational(2, 3), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(3)))}, // 2π/3 | √3/2
      {Rational(3, 4), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(2)))}, // 3π/4 | √2/2
      {Rational(5, 6), Rational(1, 2).clone()},                                                // 5π/6 | 1/2
      {Rational(1), Integer(0).clone()},                                                       // π    | 0
  };
  auto [rhsShifted, isNegated] = phaseShiftSin(rhs);
  return findValue(trigTable, rhsShifted, isNegated);
}

ArgumentPtr TrigExpression::trigTableCosSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(1).clone()},                                                        // 0    | 1
      {Rational(1, 6), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(3)))},  // π/6  | √3/2
      {Rational(1, 4), makeExpr(Mul(), Rational(1, 2).clone(), makeExpr(Sqrt(), Integer(2)))},  // π/4  | √2/2
      {Rational(1, 3), Rational(1, 2).clone()},                                                 // π/3  | 1/2
      {Rational(1, 2), Integer(0).clone()},                                                     // π/2  | 0
      {Rational(2, 3), Rational(-1, 2).clone()},                                                // 2π/3 | -1/2
      {Rational(3, 4), makeExpr(Mul(), Rational(-1, 2).clone(), makeExpr(Sqrt(), Integer(2)))}, // 3π/4 | -√2/2
      {Rational(5, 6), makeExpr(Mul(), Rational(-1, 2).clone(), makeExpr(Sqrt(), Integer(3)))}, // 5π/6 | -√3/2
      {Rational(1), Integer(-1).clone()},                                                       // π    | -1
  };
  auto [rhsShifted, isNegated] = phaseShiftCos(rhs);
  return findValue(trigTable, rhsShifted, isNegated);
}

ArgumentPtr TrigExpression::trigTableTanSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(0).clone()},                                                        // 0    | 0
      {Rational(1, 6), makeExpr(Mul(), Rational(1, 3).clone(), makeExpr(Sqrt(), Integer(3)))},  // π/6  | √3/3
      {Rational(1, 4), Integer(1).clone()},                                                     // π/4  | 1
      {Rational(1, 3), makeExpr(Sqrt(), Integer(3))},                                           // π/3  | √3
      {Rational(1, 2), ComplexInf().clone()},                                                   // π/2  | ComplexInf
      {Rational(2, 3), makeExpr(Neg(), makeExpr(Sqrt(), Integer(3)))},                          // 2π/3 | -√3
      {Rational(3, 4), Integer(-1).clone()},                                                    // 3π/4 | -1
      {Rational(5, 6), makeExpr(Mul(), Rational(-1, 3).clone(), makeExpr(Sqrt(), Integer(3)))}, // 5π/6 | -√3/3
      {Rational(1), Integer(0).clone()},                                                        // π    | 0
  };
  auto [rhsShifted, isNegated] = phaseShiftTan(rhs);
  return findValue(trigTable, rhsShifted, isNegated);
}

ArgumentPtr TrigExpression::trigTableCotSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), ComplexInf().clone()},                                                      // 0    | ComplexInf
      {Rational(1, 6), makeExpr(Sqrt(), Integer(3))},                                           // π/6  | √3
      {Rational(1, 4), Integer(1).clone()},                                                     // π/4  | 1
      {Rational(1, 3), makeExpr(Mul(), Rational(1, 3).clone(), makeExpr(Sqrt(), Integer(3)))},  // π/3  | √3/3
      {Rational(1, 2), Integer(0).clone()},                                                     // π/2  | 0
      {Rational(2, 3), makeExpr(Mul(), Rational(-1, 3).clone(), makeExpr(Sqrt(), Integer(3)))}, // 2π/3 | -√3/3
      {Rational(3, 4), Integer(-1).clone()},                                                    // 3π/4 | -1
      {Rational(5, 6), makeExpr(Neg(), makeExpr(Sqrt(), Integer(3)))},                          // 5π/6 | -√3
      {Rational(1), ComplexInf().clone()},                                                      // π    | ComplexInf
  };
  auto [rhsShifted, isNegated] = phaseShiftCot(rhs);
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

std::tuple<Rational, bool> TrigExpression::phaseShiftTan(const Rational &rhs) {
  Rational rhsShifted = rhs;
  bool isNegated = false;

  if (rhsShifted < 0) {
    rhsShifted = -rhsShifted;
    isNegated = !isNegated;
  }

  if (rhsShifted.numerator() > rhsShifted.denominator()) {
    rhsShifted = Rational(rhsShifted.numerator() % rhsShifted.denominator(), rhsShifted.denominator());
  }

  return {rhsShifted, isNegated};
}

std::tuple<Rational, bool> TrigExpression::phaseShiftCot(const Rational &rhs) {
  return phaseShiftTan(rhs);
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
    return isNegated ? makeExpr(Neg(), res->second) : res->second;
  }

  return {};
}

}
