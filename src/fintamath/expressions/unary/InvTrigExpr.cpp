#include "fintamath/expressions/unary/InvTrigExpr.hpp"

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

using NameToSimplifyFunctionMap = std::unordered_map<std::string, std::function<ArgumentPtr(const Rational &)>>;

using TrigTable = std::unordered_map<Rational, ArgumentPtr, boost::hash<Rational>>;

ArgumentPtr findValue(const TrigTable &trigTable, const Rational &key);

InvTrigExpr::InvTrigExpr(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

InvTrigExpr::SimplifyFunctionVector InvTrigExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &InvTrigExpr::constSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr InvTrigExpr::constSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto rat = convert<Rational>(*rhs)) {
    const Rational sqr = pow(*rat, 2) * rat->sign();
    return TrigTableSimplify(func, sqr);
  }

  if (const auto expr = cast<IExpression>(rhs)) {
    if (is<Sqrt>(expr->getOutputFunction())) {
      if (const auto sqrtChildInt = cast<Integer>(expr->getChildren().front())) {
        const Rational sqr = (*sqrtChildInt);
        return TrigTableSimplify(func, sqr);
      }
    }

    if (is<Mul>(expr->getOutputFunction())) {
      const auto childRat = convert<Rational>(*expr->getChildren().front());
      const auto childExpr = cast<IExpression>(expr->getChildren().back());

      if (childRat && childExpr &&
          is<Sqrt>(childExpr->getOutputFunction())) {

        if (const auto sqrtChildInt = cast<Integer>(childExpr->getChildren().front())) {
          const Rational sqr = pow(*childRat, 2) * (*sqrtChildInt) * childRat->sign();
          return TrigTableSimplify(func, sqr);
        }
      }
    }
  }

  return {};
}

ArgumentPtr InvTrigExpr::TrigTableSimplify(const IFunction &func, const Rational &rhs) {
  static const NameToSimplifyFunctionMap nameToSimplifyFunctionMap = {
      {Asin{}.toString(), &TrigTableAsinSimplify},
      {Acos{}.toString(), &TrigTableAcosSimplify},
      {Atan{}.toString(), &TrigTableAtanSimplify},
      {Acot{}.toString(), &TrigTableAcotSimplify},
      {Asec{}.toString(), &TrigTableAsecSimplify},
      {Acsc{}.toString(), &TrigTableAcscSimplify},
  };
  return nameToSimplifyFunctionMap.at(func.toString())(rhs);
}

ArgumentPtr InvTrigExpr::TrigTableAsinSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr InvTrigExpr::TrigTableAcosSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr InvTrigExpr::TrigTableAtanSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr InvTrigExpr::TrigTableAcotSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr InvTrigExpr::TrigTableAsecSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr InvTrigExpr::TrigTableAcscSimplify(const Rational &rhs) {
  static const TrigTable trigTable = {
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

ArgumentPtr findValue(const TrigTable &trigTable, const Rational &key) {
  if (const auto res = trigTable.find(key); res != trigTable.end()) {
    return res->second;
  }

  return {};
}

}
