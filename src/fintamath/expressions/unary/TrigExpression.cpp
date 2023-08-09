#include "fintamath/expressions/unary/TrigExpression.hpp"

#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"

namespace fintamath {

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

ArgumentPtr TrigExpression::constantsSimplify(const IFunction & /*func*/, const ArgumentPtr & /*rhs*/) {
  // TODO! implement
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
