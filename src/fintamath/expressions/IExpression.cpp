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

ArgumentsPtrVector IExpression::getVariablesUnsorted() const {
  ArgumentsPtrVector vars;

  for (auto child : getChildren()) {
    if (is<Variable>(child)) {
      vars.emplace_back(child);
    }
    else if (auto childExpr = cast<IExpression>(child)) {
      ArgumentsPtrVector childVars = childExpr->getVariablesUnsorted();

      for (auto childVar : childVars) {
        vars.emplace_back(childVar);
      }
    }
  }

  return vars;
}

ArgumentsPtrVector IExpression::getVariables() const {
  ArgumentsPtrVector vars = getVariablesUnsorted();

  vars.erase(std::unique(vars.begin(), vars.end(),
                         [](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
                           return *lhs == *rhs;
                         }),
             vars.end());

  std::sort(vars.begin(), vars.end(), [](const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
    return lhs->toString() < rhs->toString();
  });

  return vars;
}

shared_ptr<const IExpression> IExpression::setValuesOfVariables(const ArgumentsPtrVector &vars,
                                                                const ArgumentsPtrVector &vals) const {
  auto valExpr = cast<IExpression>(clone());
  auto children = valExpr->getChildren();

  ArgumentsPtrVector newChildren;

  for (auto &child : children) {
    if (const auto &exprChild = cast<IExpression>(child)) {
      newChildren.emplace_back(exprChild->setValuesOfVariables(vars, vals));
      continue;
    }

    bool isAdded = false;
    for (size_t i = 0; i < vars.size(); i++) {
      if (const auto &varChild = cast<Variable>(child); varChild && *varChild == *cast<Variable>(vars[i])) {
        newChildren.push_back(vals[i]->clone());
        isAdded = true;
        break;
      }
    }
    if (!isAdded) {
      newChildren.emplace_back(child);
    }
  }
  valExpr->setChildren(newChildren);
  return valExpr;
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

void IExpression::copyPropertiesToChild(ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto lhsExpr = cast<IExpression>(lhs)) {
    lhs = lhsExpr->copyPropertiesAbstract(rhs);
  }
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
