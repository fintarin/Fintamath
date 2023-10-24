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
#include "fintamath/functions/trigonometry/Csc.hpp"
#include "fintamath/functions/trigonometry/Sec.hpp"

namespace fintamath {

HyperbExpression::HyperbExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

HyperbExpression::SimplifyFunctionVector HyperbExpression::getFunctionsForPreSimplify() const {
  static const HyperbExpression::SimplifyFunctionVector simplifyFunctions = {
      &HyperbExpression::oppositeFunctionsSimplify,
      &HyperbExpression::tanhSimplify,
      &HyperbExpression::cothSimplify,
      &HyperbExpression::sechSimplify,
      &HyperbExpression::cschSimplify,
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

ArgumentPtr HyperbExpression::tanhSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Tanh>(func)) {
    return divExpr(sinhExpr(rhs), coshExpr(rhs));
  }

  return {};
}

ArgumentPtr HyperbExpression::cothSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Coth>(func)) {
    return divExpr(coshExpr(rhs), sinhExpr(rhs));
  }

  return {};
}

ArgumentPtr HyperbExpression::sechSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Sech>(func)) {
    return divExpr(Integer(1).clone(), coshExpr(rhs));
  }

  return {};
}

ArgumentPtr HyperbExpression::cschSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (is<Csch>(func)) {
    return divExpr(Integer(1).clone(), sinhExpr(rhs));
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
