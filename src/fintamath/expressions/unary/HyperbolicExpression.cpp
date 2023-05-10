#include "fintamath/expressions/unary/HyperbolicExpression.hpp"

#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"

namespace fintamath {

HyperbolicExpression::HyperbolicExpression(const IFunction &inFunc, const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(inFunc, inChild) {
}

HyperbolicExpression::SimplifyFunctionsVector HyperbolicExpression::getFunctionsForSimplify() const {
  static const HyperbolicExpression::SimplifyFunctionsVector simplifyFunctions = {
      &HyperbolicExpression::oppositeFunctionsSimplify, //
  };
  return simplifyFunctions;
}

HyperbolicExpression::SimplifyFunctionsVector HyperbolicExpression::getFunctionsForPostSimplify() const {
  static const HyperbolicExpression::SimplifyFunctionsVector simplifyFunctions = {
      &HyperbolicExpression::constantsSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr HyperbolicExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<HyperbolicExpression>(rhs)) {
    if (auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->child;
      }
    }
  }

  return {};
}

ArgumentPtr HyperbolicExpression::constantsSimplify(const IFunction & /*func*/, const ArgumentPtr & /*rhs*/) {
  // TODO! implement
  return {};
}

std::shared_ptr<IFunction> HyperbolicExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>> oppositeFunctions = {
      {Sinh().toString(), std::make_unique<Asinh>()}, //
      {Cosh().toString(), std::make_unique<Acosh>()}, //
      {Tanh().toString(), std::make_unique<Atanh>()}, //
      {Coth().toString(), std::make_unique<Acoth>()}, //
  };

  if (auto res = oppositeFunctions.find(function.toString()); res != oppositeFunctions.end()) {
    return res->second;
  }

  return {};
}

}
