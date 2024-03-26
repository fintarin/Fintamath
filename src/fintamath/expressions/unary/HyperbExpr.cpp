#include "fintamath/expressions/unary/HyperbExpr.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
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

using namespace detail;

using NameToSimplifyFunctionMap = std::unordered_map<std::string, std::function<ArgumentPtr(const ArgumentPtr &)>>;

HyperbExpr::HyperbExpr(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

HyperbExpr::SimplifyFunctionVector HyperbExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpr::oppositeFunctionsSimplify,
      &HyperbExpr::expandSimplify,
  };
  return simplifyFunctions;
}

HyperbExpr::SimplifyFunctionVector HyperbExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpr::oppositeFunctionsSimplify,
      &HyperbExpr::negSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr HyperbExpr::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (const auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

ArgumentPtr HyperbExpr::expandSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const NameToSimplifyFunctionMap nameToExpandFunctionMap = {
      {Tanh{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(sinhExpr(inRhs), coshExpr(inRhs));
       }},
      {Coth{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(coshExpr(inRhs), sinhExpr(inRhs));
       }},
      {Sech{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), coshExpr(inRhs));
       }},
      {Csch{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return divExpr(Integer(1).clone(), sinhExpr(inRhs));
       }},
  };

  if (const auto iter = nameToExpandFunctionMap.find(func.toString()); iter != nameToExpandFunctionMap.end()) {
    return iter->second(rhs);
  }

  return {};
}

ArgumentPtr HyperbExpr::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const NameToSimplifyFunctionMap nameToNegFunctionsMap = {
      {Sinh{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return negExpr(sinhExpr(negExpr(inRhs)));
       }},
      {Cosh{}.toString(),
       [](const ArgumentPtr &inRhs) {
         return coshExpr(negExpr(inRhs));
       }},
  };

  if (isNegated(rhs)) {
    if (const auto iter = nameToNegFunctionsMap.find(func.toString()); iter != nameToNegFunctionsMap.end()) {
      return iter->second(rhs);
    }
  }

  return {};
}

std::shared_ptr<IFunction> HyperbExpr::getOppositeFunction(const IFunction &function) {
  static const std::unordered_map<std::string, std::shared_ptr<IFunction>> nameToOppositeFunctionMap = {
      {Sinh{}.toString(), std::make_unique<Asinh>()},
      {Cosh{}.toString(), std::make_unique<Acosh>()},
      {Tanh{}.toString(), std::make_unique<Atanh>()},
      {Coth{}.toString(), std::make_unique<Acoth>()},
      {Sech{}.toString(), std::make_shared<Asech>()},
      {Csch{}.toString(), std::make_shared<Acsch>()},
  };
  return nameToOppositeFunctionMap.at(function.toString());
}

}
