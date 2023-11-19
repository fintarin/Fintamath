#include "fintamath/expressions/unary/HyperbExpression.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Acsch.hpp"
#include "fintamath/functions/hyperbolic/Asech.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Csch.hpp"
#include "fintamath/functions/hyperbolic/Sech.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"

namespace fintamath {

using ExpandFunctionMap = std::map<std::string, std::function<ArgumentPtr(const ArgumentPtr &)>, std::less<>>;

HyperbExpression::HyperbExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

HyperbExpression::SimplifyFunctionVector HyperbExpression::getFunctionsForPreSimplify() const {
  static const HyperbExpression::SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify,
      &HyperbExpression::expandSimplify,
  };
  return simplifyFunctions;
}

HyperbExpression::SimplifyFunctionVector HyperbExpression::getFunctionsForPostSimplify() const {
  static const HyperbExpression::SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify,
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

ArgumentPtr HyperbExpression::expandSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const ExpandFunctionMap expandFunctionsMap = {
      {Tanh().toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(sinhExpr(inRhs), coshExpr(inRhs));
       }},
      {Coth().toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(coshExpr(inRhs), sinhExpr(inRhs));
       }},
      {Sech().toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), coshExpr(inRhs));
       }},
      {Csch().toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), sinhExpr(inRhs));
       }},
  };

  if (const auto expandFunc = expandFunctionsMap.find(func.toString()); expandFunc != expandFunctionsMap.end()) {
    return expandFunc->second(rhs);
  }

  return {};
}

std::shared_ptr<IFunction> HyperbExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sinh().toString(), std::make_unique<Asinh>()},
      {Cosh().toString(), std::make_unique<Acosh>()},
      {Tanh().toString(), std::make_unique<Atanh>()},
      {Coth().toString(), std::make_unique<Acoth>()},
      {Sech().toString(), std::make_shared<Asech>()},
      {Csch().toString(), std::make_shared<Acsch>()},
  };
  return oppositeFunctions.at(function.toString());
}

}
