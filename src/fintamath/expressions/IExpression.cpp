#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

std::vector<Variable> IExpression::getVariablesUnsorted() const {
  std::vector<Variable> vars;

  for (const auto &child : getChildren()) {
    if (auto var = cast<Variable>(child); var && isVariableUnique(vars, *var)) {
      vars.emplace_back(*var);
    }
    else if (auto childExpr = cast<IExpression>(child)) {
      std::vector<Variable> childVars = childExpr->getVariablesUnsorted();

      for (const auto &childVar : childVars) {
        if (isVariableUnique(vars, childVar)) {
          vars.emplace_back(childVar);
        }
      }
    }
  }

  return vars;
}

std::vector<Variable> IExpression::getVariables() const {
  std::vector<Variable> vars = getVariablesUnsorted();

  vars.erase(std::unique(vars.begin(), vars.end(),
                         [](const Variable &lhs, const Variable &rhs) {
                           return lhs == rhs;
                         }),
             vars.end());

  std::sort(vars.begin(), vars.end(), [](const Variable &lhs, const Variable &rhs) {
    return lhs.toString() < rhs.toString();
  });

  return vars;
}

void IExpression::setValuesOfVariables(const std::vector<Variable> &vars, const ArgumentsPtrVector &vals) {
  auto children = getChildren();

  ArgumentsPtrVector newChildren;

  for (auto &child : children) {
    if (std::shared_ptr<IExpression> exprChild = cast<IExpression>(child->clone())) {
      exprChild->setValuesOfVariables(vars, vals);
      newChildren.emplace_back(exprChild);
      continue;
    }

    bool isAdded = false;

    for (size_t i = 0; i < vars.size(); i++) {
      if (const auto varChild = cast<Variable>(child); varChild && *varChild == vars[i]) {
        newChildren.push_back(vals[i]->clone());
        isAdded = true;
        break;
      }
    }

    if (!isAdded) {
      newChildren.emplace_back(child);
    }
  }

  setChildren(newChildren);
}

std::unique_ptr<IMathObject> IExpression::toMinimalObject() const {
  if (getFunction() == nullptr) {
    return getChildren().front()->toMinimalObject();
  }

  ArgumentPtr cloneExpr = clone();
  simplifyChild(cloneExpr);
  return cloneExpr->clone();
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
  if (!func.isNonExressionEvaluatable()) {
    return {};
  }

  ArgumentsRefVector args;
  bool areArgumentsPrecise = true;

  for (const auto &argPtr : argPtrs) {
    args.emplace_back(*argPtr);

    if (const auto num = cast<INumber>(argPtr); num && !num->isPrecise()) {
      areArgumentsPrecise = false;
    }
  }

  if (!func.doArgsMatch(args)) {
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
  return {};
}

ArgumentPtr IExpression::preSimplify() const {
  return {};
}

void IExpression::simplifyConstant(ArgumentPtr &child) {
  if (const auto constChild = cast<IConstant>(child)) {
    ArgumentPtr constVal = (*constChild)();

    if (const auto num = cast<INumber>(constVal); num && !num->isPrecise()) {
      child = constChild;
    }
    else {
      child = constVal;
    }
  }
}

bool IExpression::isVariableUnique(const std::vector<Variable> &vars, const Variable &var) {
  return std::find(vars.begin(), vars.end(), var) == vars.end();
}

}
