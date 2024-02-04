#include "fintamath/expressions/unary/HyperbExpression.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
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

using SimplifyFunctionMap = std::map<std::string, std::function<ArgumentPtr(const ArgumentPtr &)>, std::less<>>;

HyperbExpression::HyperbExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

HyperbExpression::SimplifyFunctionVector HyperbExpression::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify,
      &HyperbExpression::expandSimplify,
  };
  return simplifyFunctions;
}

HyperbExpression::SimplifyFunctionVector HyperbExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify,
      &HyperbExpression::negSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr HyperbExpression::oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (const auto expr = cast<IExpression>(rhs)) {
    if (const auto oppositeFunc = getOppositeFunction(func)) {
      if (*expr->getFunction() == *oppositeFunc) {
        return expr->getChildren().front();
      }
    }
  }

  return {};
}

ArgumentPtr HyperbExpression::expandSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const SimplifyFunctionMap expandFunctionMap = {
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

  if (const auto iter = expandFunctionMap.find(func.toString()); iter != expandFunctionMap.end()) {
    return iter->second(rhs);
  }

  return {};
}

ArgumentPtr HyperbExpression::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  static const SimplifyFunctionMap negFunctionsMap = {
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
    if (const auto iter = negFunctionsMap.find(func.toString()); iter != negFunctionsMap.end()) {
      return iter->second(rhs);
    }
  }

  return {};
}

std::shared_ptr<IFunction> HyperbExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Sinh{}.toString(), std::make_unique<Asinh>()},
      {Cosh{}.toString(), std::make_unique<Acosh>()},
      {Tanh{}.toString(), std::make_unique<Atanh>()},
      {Coth{}.toString(), std::make_unique<Acoth>()},
      {Sech{}.toString(), std::make_shared<Asech>()},
      {Csch{}.toString(), std::make_shared<Acsch>()},
  };
  return oppositeFunctions.at(function.toString());
}

}
