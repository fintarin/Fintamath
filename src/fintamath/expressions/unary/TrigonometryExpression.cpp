#include "fintamath/expressions/unary/TrigonometryExpression.hpp"

#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"

namespace fintamath {

TrigonometryExpression::TrigonometryExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

TrigonometryExpression::SimplifyFunctionsVector TrigonometryExpression::getFunctionsForPreSimplify() const {
  static const TrigonometryExpression::SimplifyFunctionsVector simplifyFunctions = {
      &TrigonometryExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

TrigonometryExpression::SimplifyFunctionsVector TrigonometryExpression::getFunctionsForPostSimplify() const {
  static const TrigonometryExpression::SimplifyFunctionsVector simplifyFunctions = {
      &TrigonometryExpression::constantsSimplify,         //
      &TrigonometryExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr TrigonometryExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

ArgumentPtr TrigonometryExpression::constantsSimplify(const IFunction & /*func*/, const ArgumentPtr & /*rhs*/) {
  // TODO! implement
  return {};
}

std::shared_ptr<IFunction> TrigonometryExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sin().toString(), std::make_shared<Asin>()}, //
      {Cos().toString(), std::make_shared<Acos>()}, //
      {Tan().toString(), std::make_shared<Atan>()}, //
      {Cot().toString(), std::make_shared<Acot>()}, //
  };

  if (auto res = oppositeFunctions.find(function.toString()); res != oppositeFunctions.end()) {
    return res->second;
  }

  return {};
}
}
