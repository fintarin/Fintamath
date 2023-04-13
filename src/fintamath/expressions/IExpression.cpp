#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

ArgumentsPtrVector IExpression::getVariables() const {
  ArgumentsPtrVector vars;

  for (auto child : getChildren()) {
    if (is<Variable>(child)){
      vars.emplace_back(child);
    }
    else if (auto childExpr = cast<IExpression>(child)){
      ArgumentsPtrVector childVars = childExpr->getVariables();

      for (auto childVar : childVars) {
        vars.emplace_back(childVar);
      }
    }
  }

  return vars;
}

void IExpression::compressChild(ArgumentPtr &child) {
  for (;;) {
    if (const auto expr = cast<IExpression>(child); expr && !expr->getFunction()) {
      child = expr->getChildren().front();
    }
    else {
      break;
    }
  }
}

void IExpression::simplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->simplify()) {
      child = simplObj;
    }
  }
}

void IExpression::preSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->preSimplify()) {
      child = simplObj;
    }
  }

  simplifyConstant(child);
}

void IExpression::postSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->postSimplify()) {
      child = simplObj;
    }
  }

  simplifyConstant(child);
}

ArgumentPtr IExpression::callFunction(const IFunction &func, const ArgumentsPtrVector &argPtrs) {
  ArgumentsRefVector args;
  bool areArgumentsPrecise = true;

  for (const auto &argPtr : argPtrs) {
    args.emplace_back(*argPtr);

    if (const auto num = cast<INumber>(argPtr); num && !num->isPrecise()) {
      areArgumentsPrecise = false;
    }
  }

  if (!func.isNonExressionEvaluatable() || !func.doArgsMatch(args)) {
    return {};
  }

  ArgumentPtr res = func(args);

  if (areArgumentsPrecise) {
    if (const auto num = cast<INumber>(res); num && !num->isPrecise()) {
      return {};
    }
  }

  return res;
}

ArgumentPtr IExpression::postSimplify() const {
  return nullptr;
}

ArgumentPtr IExpression::preSimplify() const {
  return nullptr;
}

void IExpression::simplifyConstant(ArgumentPtr &child) {
  if (const auto constChild = cast<IConstant>(child)) {
    ArgumentPtr constVal = (*constChild)();

    if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise()) {
      child = constChild;
    }
    else {
      child = constVal;
    }
  }
}

}
