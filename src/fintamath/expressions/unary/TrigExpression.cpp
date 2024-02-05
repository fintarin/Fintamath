#include "fintamath/expressions/unary/TrigExpression.hpp"

#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Acsc.hpp"
#include "fintamath/functions/trigonometry/Asec.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Csc.hpp"
#include "fintamath/functions/trigonometry/Sec.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

using SimplifyFunctionMap = std::unordered_map<std::string, std::function<ArgumentPtr(const ArgumentPtr &)>>;

using TrigonometryFunctionMap = std::unordered_map<std::string, std::function<ArgumentPtr(const Rational &)>>;

using TrigonometryTable = std::unordered_map<Rational, ArgumentPtr, boost::hash<Rational>>;

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key, bool isNegated);

TrigExpression::TrigExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

TrigExpression::SimplifyFunctionVector TrigExpression::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &TrigExpression::oppositeFunctionsSimplify,
      &TrigExpression::expandSimplify,
  };
  return simplifyFunctions;
}

TrigExpression::SimplifyFunctionVector TrigExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &TrigExpression::constSimplify,
      &TrigExpression::oppositeFunctionsSimplify,
      &TrigExpression::negSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr TrigExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (const auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

ArgumentPtr TrigExpression::expandSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const SimplifyFunctionMap expandFunctionMap = {
      {Tan{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(sinExpr(inRhs), cosExpr(inRhs));
       }},
      {Cot{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(cosExpr(inRhs), sinExpr(inRhs));
       }},
      {Sec{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), cosExpr(inRhs));
       }},
      {Csc{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), sinExpr(inRhs));
       }},
  };

  if (const auto iter = expandFunctionMap.find(func.toString()); iter != expandFunctionMap.end()) {
    return iter->second(rhs);
  }

  return {};
}

ArgumentPtr TrigExpression::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const SimplifyFunctionMap negFunctionsMap = {
      {Sin{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return negExpr(sinExpr(negExpr(inRhs)));
       }},
      {Cos{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return cosExpr(negExpr(inRhs));
       }},
  };

  if (isNegated(rhs)) {
    if (const auto iter = negFunctionsMap.find(func.toString()); iter != negFunctionsMap.end()) {
      return iter->second(rhs);
    }
  }

  return {};
}

ArgumentPtr TrigExpression::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (*rhs == Pi{}) {
    return trigTableSimplify(func, 1);
  }

  if (*rhs == *negExpr(Pi{})) {
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
  static const TrigonometryFunctionMap trigTable = {
      {Sin{}.toString(), &trigTableSinSimplify},
      {Cos{}.toString(), &trigTableCosSimplify},
  };

  if (const auto iter = trigTable.find(func.toString()); iter != trigTable.end()) {
    const Rational rhsShifted = phaseShiftPeriod(rhs);
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
  static const std::unordered_map<std::string, std::shared_ptr<IFunction>> oppositeFunctions = {
      {Sin{}.toString(), std::make_shared<Asin>()},
      {Cos{}.toString(), std::make_shared<Acos>()},
      {Tan{}.toString(), std::make_shared<Atan>()},
      {Cot{}.toString(), std::make_shared<Acot>()},
      {Sec{}.toString(), std::make_shared<Asec>()},
      {Csc{}.toString(), std::make_shared<Acsc>()},
  };
  return oppositeFunctions.at(function.toString());
}

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key, const bool isNegated) {
  if (const auto res = trigTable.find(key); res != trigTable.end()) {
    return isNegated ? negExpr(res->second) : res->second;
  }

  return {};
}
}
