#include "fintamath/expressions/unary/InvTrigExpression.hpp"

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

#include <boost/container_hash/hash.hpp>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Acsc.hpp"
#include "fintamath/functions/trigonometry/Asec.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

using TrigonometryFunctionMap = std::unordered_map<std::string, std::function<ArgumentPtr(const Rational &)>>;

using TrigonometryTable = std::unordered_map<Rational, ArgumentPtr, boost::hash<Rational>>;

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key);

InvTrigExpression::InvTrigExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

InvTrigExpression::SimplifyFunctionVector InvTrigExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &InvTrigExpression::constSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr InvTrigExpression::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto rat = convert<Rational>(*rhs)) {
    const Rational sqr = pow(*rat, 2) * rat->sign();
    return trigTableSimplify(func, sqr);
  }

  if (const auto expr = cast<IExpression>(rhs)) {
    if (is<Sqrt>(expr->getOutputFunction())) {
      if (const auto sqrtChildInt = cast<Integer>(expr->getChildren().front())) {
        const Rational sqr = (*sqrtChildInt);
        return trigTableSimplify(func, sqr);
      }
    }

    if (is<Mul>(expr->getOutputFunction())) {
      const auto childRat = convert<Rational>(*expr->getChildren().front());
      const auto childExpr = cast<IExpression>(expr->getChildren().back());

      if (childRat && childExpr &&
          is<Sqrt>(childExpr->getOutputFunction())) {

        if (const auto sqrtChildInt = cast<Integer>(childExpr->getChildren().front())) {
          const Rational sqr = pow(*childRat, 2) * (*sqrtChildInt) * childRat->sign();
          return trigTableSimplify(func, sqr);
        }
      }
    }
  }

  return {};
}

ArgumentPtr InvTrigExpression::trigTableSimplify(const IFunction &func, const Rational &rhs) {
  static const TrigonometryFunctionMap trigTable = {
      {Asin{}.toString(), &trigTableAsinSimplify},
      {Acos{}.toString(), &trigTableAcosSimplify},
      {Atan{}.toString(), &trigTableAtanSimplify},
      {Acot{}.toString(), &trigTableAcotSimplify},
      {Asec{}.toString(), &trigTableAsecSimplify},
      {Acsc{}.toString(), &trigTableAcscSimplify},
  };
  return trigTable.at(func.toString())(rhs);
}

ArgumentPtr InvTrigExpression::trigTableAsinSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), mulExpr(Rational(-1, 2), Pi{})},    // -1    | -π/2
      {Rational(-3, 4), mulExpr(Rational(-1, 3), Pi{})}, // -√3/2 | -π/3
      {Rational(-1, 2), mulExpr(Rational(-1, 4), Pi{})}, // -√2/2 | -π/4
      {Rational(-1, 4), mulExpr(Rational(-1, 6), Pi{})}, // -1/2  | -π/6
      {Rational(0), Integer(0).clone()},                 // 0     | 0
      {Rational(1, 4), mulExpr(Rational(1, 6), Pi{})},   // 1/2   | π/6
      {Rational(1, 2), mulExpr(Rational(1, 4), Pi{})},   // √2/2  | π/4
      {Rational(3, 4), mulExpr(Rational(1, 3), Pi{})},   // √3/2  | π/3
      {Rational(1), mulExpr(Rational(-1, 2), Pi{})},     // 1    | -π/2
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAcosSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), Pi{}.clone()},                     // -1    | π
      {Rational(-3, 4), mulExpr(Rational(5, 6), Pi{})}, // -√3/2 | 5π/6
      {Rational(-1, 2), mulExpr(Rational(3, 4), Pi{})}, // -√2/2 | 3π/4
      {Rational(-1, 4), mulExpr(Rational(2, 3), Pi{})}, // -1/2  | 2π/3
      {Rational(0), mulExpr(Rational(1, 2), Pi{})},     // 0     | π/2
      {Rational(1, 4), mulExpr(Rational(1, 3), Pi{})},  // 1/2   | π/3
      {Rational(1, 2), mulExpr(Rational(1, 4), Pi{})},  // √2/2  | π/4
      {Rational(3, 4), mulExpr(Rational(1, 6), Pi{})},  // √3/2  | π/6
      {Rational(1), Integer(0).clone()},                // 1     | 0
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAtanSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-3), mulExpr(Rational(-1, 3), Pi{})},    // -√3   | -π/3
      {Rational(-1), mulExpr(Rational(-1, 4), Pi{})},    // -1    | -π/4
      {Rational(-1, 3), mulExpr(Rational(-1, 6), Pi{})}, // -√3/3 | -π/6
      {Rational(0), Integer(0).clone()},                 // 0     | 0
      {Rational(1, 3), mulExpr(Rational(1, 6), Pi{})},   // √3/3  | π/6
      {Rational(1), mulExpr(Rational(1, 4), Pi{})},      // 1     | π/4
      {Rational(3), mulExpr(Rational(1, 3), Pi{})},      // √3    | π/3
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAcotSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-3), mulExpr(Rational(-1, 6), Pi{})},    // -√3   | -π/6
      {Rational(-1), mulExpr(Rational(-1, 4), Pi{})},    // -1    | -π/4
      {Rational(-1, 3), mulExpr(Rational(-1, 3), Pi{})}, // -√3/3 | -π/3
      {Rational(0), mulExpr(Rational(1, 2), Pi{})},      // 0     | π/2
      {Rational(1, 3), mulExpr(Rational(1, 3), Pi{})},   // √3/3  | π/3
      {Rational(1), mulExpr(Rational(1, 4), Pi{})},      // 1     | π/4
      {Rational(3), mulExpr(Rational(1, 6), Pi{})},      // √3    | π/6
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAsecSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), Pi{}.clone()},                     // -1    | π
      {Rational(-4, 3), mulExpr(Rational(5, 6), Pi{})}, // -2/√3 | 5π/6
      {Rational(-2), mulExpr(Rational(3, 4), Pi{})},    // -2/√2 | 3π/4
      {Rational(-4), mulExpr(Rational(2, 3), Pi{})},    // -2    | 2π/3
      {Rational(0), ComplexInf{}.clone()},              // 0     | ComplexInf
      {Rational(4), mulExpr(Rational(1, 3), Pi{})},     // 2     | π/3
      {Rational(2), mulExpr(Rational(1, 4), Pi{})},     // 2/√2  | π/4
      {Rational(4, 3), mulExpr(Rational(1, 6), Pi{})},  // 2/√3  | π/6
      {Rational(1), Integer(0).clone()},                // 1     | 0
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr InvTrigExpression::trigTableAcscSimplify(const Rational &rhs) {
  static const TrigonometryTable trigTable = {
      {Rational(-1), mulExpr(Rational(-1, 2), Pi{})},    // -1    | -π/2
      {Rational(-4, 3), mulExpr(Rational(-1, 3), Pi{})}, // -2/√3 | -π/3
      {Rational(-2), mulExpr(Rational(-1, 4), Pi{})},    // -2/√2 | -π/4
      {Rational(-4), mulExpr(Rational(-1, 6), Pi{})},    // -2    | -π/6
      {Rational(0), ComplexInf{}.clone()},               // 0     | ComplexInf
      {Rational(4), mulExpr(Rational(1, 6), Pi{})},      // 2     | π/6
      {Rational(2), mulExpr(Rational(1, 4), Pi{})},      // 2/√2  | π/4
      {Rational(4, 3), mulExpr(Rational(1, 3), Pi{})},   // 2/√3  | π/3
      {Rational(1), mulExpr(Rational(-1, 2), Pi{})},     // 1     | -π/2
  };
  return findValue(trigTable, rhs);
}

ArgumentPtr findValue(const TrigonometryTable &trigTable, const Rational &key) {
  if (const auto res = trigTable.find(key); res != trigTable.end()) {
    return res->second;
  }

  return {};
}

}
