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

ArgumentPtr TrigExpression::trigTableSinSimplify(Rational /*rhs*/) {
  return {};
}

ArgumentPtr TrigExpression::trigTableCosSimplify(Rational /*rhs*/) {
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
