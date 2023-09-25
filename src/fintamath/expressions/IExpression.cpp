#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Complex.hpp"
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

  std::ranges::sort(vars, std::less(), &Variable::toString);
  auto unique = std::ranges::unique(vars);
  vars.erase(unique.begin(), unique.end());

  return vars;
}

void IExpression::setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) {
  const ArgumentPtrVector &children = getChildren();
  ArgumentPtrVector newChildren;

  for (const auto &child : children) {
    if (std::shared_ptr<IExpression> exprChild = cast<IExpression>(child->clone())) {
      exprChild->setVariables(varsToVals);
      newChildren.emplace_back(exprChild);
      continue;
    }

    bool isAdded = false;

    if (const auto varChild = cast<Variable>(child)) {
      for (const auto &[var, val] : varsToVals) {
        if (*varChild == var) {
          newChildren.push_back(val);
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

ArgumentPtr IExpression::simplify() const {
  ArgumentPtr simpl = cast<IExpression>(clone());
  preSimplifyChild(simpl);
  postSimplifyChild(simpl);
  return simpl;
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

  constSimplifyChild(child);
}

void IExpression::postSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->postSimplify()) {
      child = simplObj;
    }
  }
}

void IExpression::preciseSimplifyChild(ArgumentPtr &child) {
  static const auto multiPrecise = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiPrecise;

    outMultiPrecise.add<Integer>([](const Integer &inRhs) {
      return Real(inRhs).clone();
    });

    outMultiPrecise.add<Rational>([](const Rational &inRhs) {
      return Real(inRhs).clone();
    });

    outMultiPrecise.add<Complex>([](const Complex &inRhs) {
      return Complex(
                 *convert<Real>(inRhs.real()),
                 *convert<Real>(inRhs.imag()))
          .clone();
    });

    return outMultiPrecise;
  }();

  if (const auto numChild = cast<INumber>(child)) {
    if (auto res = multiPrecise(*numChild)) {
      child = std::move(res);
    }
  }
  else if (const auto constChild = cast<IConstant>(child)) {
    child = (*constChild)();
  }
  else if (const auto exprChild = cast<IExpression>(child)) {
    child = exprChild->preciseSimplify();
  }
}

ArgumentPtr IExpression::callFunction(const IFunction &func, const ArgumentPtrVector &argPtrs) {
  if (!func.isNonExressionEvaluatable()) {
    return {};
  }

  ArgumentRefVector args;
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

ArgumentPtr IExpression::preciseSimplify() const {
  ArgumentPtrVector children = getChildren();

  for (auto &child : children) {
    preciseSimplifyChild(child);
  }

  auto res = cast<IExpression>(clone());
  res->setChildren(children);
  return res;
}

void IExpression::constSimplifyChild(ArgumentPtr &child) {
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
