#include "fintamath/expressions/unary/HyperbExpression.hpp"

#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"

namespace fintamath {

HyperbExpression::HyperbExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

HyperbExpression::SimplifyFunctionsVector HyperbExpression::getFunctionsForPreSimplify() const {
  static const HyperbExpression::SimplifyFunctionsVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

HyperbExpression::SimplifyFunctionsVector HyperbExpression::getFunctionsForPostSimplify() const {
  static const HyperbExpression::SimplifyFunctionsVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr HyperbExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

std::shared_ptr<IFunction> HyperbExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sinh().toString(), std::make_unique<Asinh>()}, //
      {Cosh().toString(), std::make_unique<Acosh>()}, //
      {Tanh().toString(), std::make_unique<Atanh>()}, //
      {Coth().toString(), std::make_unique<Acoth>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

}
