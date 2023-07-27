#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Indeterminate.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

std::vector<Variable> IExpression::getVariables() const {
  std::vector<Variable> vars;

  for (const auto &child : getChildren()) {
    if (auto var = cast<Variable>(child)) {
      vars.emplace_back(*var);
    }
    else if (auto childExpr = cast<IExpression>(child)) {
      std::vector<Variable> childVars = childExpr->getVariables();
      vars.insert(vars.end(), childVars.begin(), childVars.end());
    }
  }

  vars.erase(std::unique(vars.begin(), vars.end(),
                         [](const Variable &lhs, const Variable &rhs) {
                           return lhs == rhs;
                         }),
             vars.end());

  return vars;
}

void IExpression::setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) {
  auto children = getChildren();

  ArgumentsPtrVector newChildren;

  for (auto &child : children) {
    if (std::shared_ptr<IExpression> exprChild = cast<IExpression>(child->clone())) {
      exprChild->setVariables(varsToVals);
      newChildren.emplace_back(exprChild);
      continue;
    }

    bool isAdded = false;

    if (const auto varChild = cast<Variable>(child)) {
      for (const auto &varsToVal : varsToVals) {
        if (*varChild == varsToVal.first) {
          newChildren.push_back(varsToVal.second);
          isAdded = true;
          break;
        }
      }
    }

    if (!isAdded) {
      newChildren.emplace_back(child);
    }
  }

  setChildren(newChildren);
}

std::unique_ptr<IMathObject> IExpression::toMinimalObject() const {
  return simplify()->clone();
}

std::shared_ptr<IFunction> IExpression::getOutputFunction() const {
  return getFunction();
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

  simplifyConstant(child);
}

void IExpression::preSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->preSimplify()) {
      child = simplObj;
    }
  }
}

void IExpression::postSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->postSimplify()) {
      child = simplObj;
    }
  }
}

void IExpression::preciseSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    child = exprChild->preciseSimplify();
  }
  else if (const auto numChild = cast<INumber>(child)) {
    child = std::make_shared<Real>(convert<Real>(*numChild));
  }
  else if (const auto constChild = cast<IConstant>(child)) {
    child = (*constChild)();
  }
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

ArgumentPtr IExpression::preSimplify() const {
  return {};
}

ArgumentPtr IExpression::postSimplify() const {
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

}
