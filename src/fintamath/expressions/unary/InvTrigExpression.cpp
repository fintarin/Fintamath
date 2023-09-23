#include "fintamath/expressions/unary/InvTrigExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

using TrigonometryFunctionTable = std::map<std::string, std::function<ArgumentPtr(const Rational &)>, std::less<>>;

using TrigonometryTable = std::map<Rational, ArgumentPtr>;

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key);

InvTrigExpression::InvTrigExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

InvTrigExpression::SimplifyFunctionVector InvTrigExpression::getFunctionsForPostSimplify() const {
  static const InvTrigExpression::SimplifyFunctionVector simplifyFunctions = {
      &InvTrigExpression::constSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr InvTrigExpression::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto rat = cast<Rational>(rhs)) {
    Rational sqr = pow(*rat, 2) * rat->sign();
    return trigTableSimplify(func, sqr);
  }

  if (auto expr = cast<IExpression>(rhs)) {
    if (is<Sqrt>(expr->getOutputFunction())) {
      if (const auto sqrtChildInt = cast<Integer>(expr->getChildren().front())) {
        Rational sqr = (*sqrtChildInt);
        return trigTableSimplify(func, sqr);
      }
    }

    if (is<Mul>(expr->getOutputFunction())) {
      const auto childRat = convert<Rational>(*expr->getChildren().front());
      const auto childExpr = cast<IExpression>(expr->getChildren().back());

      if (childRat && childExpr &&
          is<Sqrt>(childExpr->getOutputFunction())) {

        if (const auto sqrtChildInt = cast<Integer>(childExpr->getChildren().front())) {
          Rational sqr = pow(*childRat, 2) * (*sqrtChildInt) * childRat->sign();
          return trigTableSimplify(func, sqr);
        }
      }
    }
  }

  return {};
}

ArgumentPtr InvTrigExpression::trigTableSimplify(const IFunction &func, const Rational &rhs) {
  static const TrigonometryFunctionTable trigTable = {
      {Asin().toString(), &trigTableAsinSimplify},
      {Acos().toString(), &trigTableAcosSimplify},
      {Atan().toString(), &trigTableAtanSimplify},
      {Acot().toString(), &trigTableAcotSimplify},
  };
  return trigTable.at(func.toString())(rhs);
}

ArgumentPtr InvTrigExpression::trigTableAsinSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), mulExpr(Rational(-1, 2), Pi())},    // -1    | -π/2
      {Rational(-3, 4), mulExpr(Rational(-1, 3), Pi())}, // -√3/2 | -π/3
      {Rational(-1, 2), mulExpr(Rational(-1, 4), Pi())}, // -√2/2 | -π/4
      {Rational(-1, 4), mulExpr(Rational(-1, 6), Pi())}, // -1/2  | -π/6
      {Rational(0), Integer(0).clone()},                 // 0     | 0
      {Rational(1, 4), mulExpr(Rational(1, 6), Pi())},   // 1/2   | π/6
      {Rational(1, 2), mulExpr(Rational(1, 4), Pi())},   // √2/2  | π/4
      {Rational(3, 4), mulExpr(Rational(1, 3), Pi())},   // √3/2  | π/3
      {Rational(1), mulExpr(Rational(-1, 2), Pi())},     // 1    | -π/2
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAcosSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), Pi().clone()},                     // -1    | π
      {Rational(-3, 4), mulExpr(Rational(5, 6), Pi())}, // -√3/2 | 5π/6
      {Rational(-1, 2), mulExpr(Rational(3, 4), Pi())}, // -√2/2 | 3π/4
      {Rational(-1, 4), mulExpr(Rational(2, 3), Pi())}, // -1/2  | 2π/3
      {Rational(0), mulExpr(Rational(1, 2), Pi())},     // 0     | π/2
      {Rational(1, 4), mulExpr(Rational(1, 3), Pi())},  // 1/2   | π/3
      {Rational(1, 2), mulExpr(Rational(1, 4), Pi())},  // √2/2  | π/4
      {Rational(3, 4), mulExpr(Rational(1, 6), Pi())},  // √3/2  | π/6
      {Rational(1), Integer(0).clone()},                // 1     | 0
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAtanSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-3), mulExpr(Rational(-1, 3), Pi())},    // -√3   | -π/3
      {Rational(-1), mulExpr(Rational(-1, 4), Pi())},    // -1    | -π/4
      {Rational(-1, 3), mulExpr(Rational(-1, 6), Pi())}, // -√3/3 | -π/6
      {Rational(0), Integer(0).clone()},                 // 0     | 0
      {Rational(1, 3), mulExpr(Rational(1, 6), Pi())},   // √3/3  | π/6
      {Rational(1), mulExpr(Rational(1, 4), Pi())},      // 1     | π/4
      {Rational(3), mulExpr(Rational(1, 3), Pi())},      // √3    | π/3
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAcotSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-3), mulExpr(Rational(-1, 6), Pi())},    // -√3   | -π/6
      {Rational(-1), mulExpr(Rational(-1, 4), Pi())},    // -1    | -π/4
      {Rational(-1, 3), mulExpr(Rational(-1, 3), Pi())}, // -√3/3 | -π/3
      {Rational(0), mulExpr(Rational(1, 2), Pi())},      // 0     | π/2
      {Rational(1, 3), mulExpr(Rational(1, 3), Pi())},   // √3/3  | π/3
      {Rational(1), mulExpr(Rational(1, 4), Pi())},      // 1     | π/4
      {Rational(3), mulExpr(Rational(1, 6), Pi())},      // √3    | π/6
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key) {
  if (auto res = trigTable.find(key); res != trigTable.end()) {
    return res->second;
  }

  return {};
}

}
