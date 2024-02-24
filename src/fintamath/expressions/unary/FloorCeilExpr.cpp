#include "fintamath/expressions/unary/FloorCeilExpr.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

using namespace detail;

FloorCeilExpr::FloorCeilExpr(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

FloorCeilExpr::SimplifyFunctionVector FloorCeilExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &FloorCeilExpr::negSimplify,
      &FloorCeilExpr::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr FloorCeilExpr::intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  if (auto res = cast<INumber>(callFunction(func, {approx}))) {
    return res;
  }

  return {};
}

ArgumentPtr FloorCeilExpr::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(makeExpr(*getOppositeFunction(func), negExpr(rhs)));
  }

  return {};
}

std::shared_ptr<IFunction> FloorCeilExpr::getOppositeFunction(const IFunction &function) {
  static const std::unordered_map<std::string, std::shared_ptr<IFunction>> nameToOppositeFuncMap = {
      {Floor{}.toString(), std::make_shared<Ceil>()},
      {Ceil{}.toString(), std::make_shared<Floor>()},
  };
  return nameToOppositeFuncMap.at(function.toString());
}

}
