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
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

using TrigonometryFunctionsTable = std::map<std::string, std::function<ArgumentPtr(Rational)>>;

using TrigonometryTable = std::map<Rational, ArgumentPtr>;

TrigExpression::TrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

TrigExpression::SimplifyFunctionsVector TrigExpression::getFunctionsForPreSimplify() const {
  static const TrigExpression::SimplifyFunctionsVector simplifyFunctions = {
      &TrigExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

TrigExpression::SimplifyFunctionsVector TrigExpression::getFunctionsForPostSimplify() const {
  static const TrigExpression::SimplifyFunctionsVector simplifyFunctions = {
      &TrigExpression::constantsSimplify,         //
      &TrigExpression::oppositeFunctionsSimplify, //
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

ArgumentPtr TrigExpression::constantsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
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

  const auto rhsChildRat = cast<Rational>(convert(Rational(), *rhsChildren.front()));
  if (!rhsChildRat) {
    return {};
  }

  Rational piCoeff = Rational(rhsChildRat->numerator() % (rhsChildRat->denominator() * 2), rhsChildRat->denominator());
  return trigTableSimplify(func, piCoeff);
}

ArgumentPtr TrigExpression::trigTableSimplify(const IFunction &func, const Rational &rhs) {
  static const TrigonometryFunctionsTable trigTable = {
      {Sin().toString(), &trigTableSinSimplify},
      {Cos().toString(), &trigTableCosSimplify},
      {Tan().toString(), &trigTableTanSimplify},
      {Cot().toString(), &trigTableCotSimplify},
  };
  return trigTable.at(func.toString())(rhs);
}

ArgumentPtr TrigExpression::trigTableSinSimplify(Rational rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(0).clone()},                                                   // 0    | 0
      {Rational(1, 6), Rational(1, 2).clone()},                                            // π/6  | 1/2
      {Rational(1, 4), makeExpr(Div(), makeExpr(Sqrt(), Integer(2)), Integer(2).clone())}, // π/4  | √2/2
      {Rational(1, 3), makeExpr(Div(), makeExpr(Sqrt(), Integer(3)), Integer(2).clone())}, // π/3  | √3/2
      {Rational(1, 2), Integer(1).clone()},                                                // π/2  | 1
      {Rational(2, 3), makeExpr(Div(), makeExpr(Sqrt(), Integer(3)), Integer(2).clone())}, // 2π/3 | √3/2
      {Rational(3, 4), makeExpr(Div(), makeExpr(Sqrt(), Integer(2)), Integer(2).clone())}, // 3π/4 | √2/2
      {Rational(5, 6), Rational(1, 2).clone()},                                            // 5π/6 | 1/2
      {Rational(1), Integer(0).clone()},                                                   // π    | 0
  };

  bool isResNegated = false;

  if (rhs < 0) {
    rhs = -rhs;
    isResNegated = !isResNegated;
  }

  if (rhs.numerator() > rhs.denominator()) {
    rhs = Rational(rhs.numerator() % rhs.denominator(), rhs.denominator());
    isResNegated = !isResNegated;
  }

  if (auto res = trigTable.find(rhs); res != trigTable.end()) {
    return isResNegated ? makeExpr(Neg(), res->second) : res->second;
  }

  return {};
}

ArgumentPtr TrigExpression::trigTableCosSimplify(Rational rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(0), Integer(1).clone()},                                                             // 0    | 1
      {Rational(1, 6), makeExpr(Div(), *makeExpr(Sqrt(), Integer(3)), Integer(2))},                  // π/6  | √3/2
      {Rational(1, 4), makeExpr(Div(), *makeExpr(Sqrt(), Integer(2)), Integer(2))},                  // π/4  | √2/2
      {Rational(1, 3), Rational(1, 2).clone()},                                                      // π/3  | 1/2
      {Rational(1, 2), Integer(0).clone()},                                                          // π/2  | 0
      {Rational(2, 3), Rational(-1, 2).clone()},                                                     // 2π/3 | -1/2
      {Rational(3, 4), makeExpr(Div(), *makeExpr(Neg(), makeExpr(Sqrt(), Integer(2))), Integer(2))}, // 3π/4 | -√2/2
      {Rational(5, 6), makeExpr(Div(), *makeExpr(Neg(), makeExpr(Sqrt(), Integer(3))), Integer(2))}, // 5π/6 | -√3/2
      {Rational(1), Integer(-1).clone()},                                                            // π    | -1
  };

  bool isResNegated = false;

  if (rhs < 0) {
    rhs = -rhs;
  }

  if (rhs.numerator() > rhs.denominator()) {
    rhs = Rational(rhs.numerator() % rhs.denominator(), rhs.denominator());
    isResNegated = !isResNegated;
  }

  if (auto res = trigTable.find(rhs); res != trigTable.end()) {
    return isResNegated ? makeExpr(Neg(), res->second) : res->second;
  }

  return {};
}

ArgumentPtr TrigExpression::trigTableTanSimplify(Rational /*rhs*/) {
  return {};
}

ArgumentPtr TrigExpression::trigTableCotSimplify(Rational /*rhs*/) {
  return {};
}

std::shared_ptr<IFunction> TrigExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sin().toString(), std::make_shared<Asin>()}, //
      {Cos().toString(), std::make_shared<Acos>()}, //
      {Tan().toString(), std::make_shared<Atan>()}, //
      {Cot().toString(), std::make_shared<Acot>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

}
