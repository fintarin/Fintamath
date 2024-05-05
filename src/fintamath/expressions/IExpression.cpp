#include "fintamath/expressions/IExpression.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "fintamath/core/Cache.hpp"
#include "fintamath/core/Converter.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/expressions/ExpressionComparator.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IExpression)

using namespace detail;

const IExpression::VariableSet &IExpression::getVariables() const {
  if (!variablesCached) {
    variablesCached = VariableSet{};

    for (const auto &child : getChildren()) {
      if (auto var = cast<Variable>(child)) {
        variablesCached->emplace(*var);
      }
      else if (const auto childExpr = cast<IExpression>(child)) {
        VariableSet childVars = childExpr->getVariables();
        variablesCached->insert(childVars.begin(), childVars.end());
      }
    }
  }

  return *variablesCached;
}

std::unique_ptr<IMathObject> IExpression::toMinimalObject() const {
  if (const auto res = simplify()) {
    return res->clone();
  }

  return clone();
}

const std::shared_ptr<IFunction> &IExpression::getOutputFunction() const {
  return getFunction();
}

std::string IExpression::toString() const {
  return functionToString(*getFunction(), getChildren());
}

IExpression::State IExpression::getState() const {
  return state;
}

ArgumentPtr IExpression::callFunction() const {
  const IFunction &func = *getFunction();
  const ArgumentPtrVector &children = getChildren();

  if (!func.isEvaluatable()) {
    return {};
  }

  if (callFunctionCached && callFunctionCached->precision && callFunctionCached->precision < Real::getPrecisionStatic()) {
    callFunctionCached = {};
  }

  if (!callFunctionCached) {
    callFunctionCached = CallFunctionCached();

    ArgumentRefVector funcArgs;

    for (const auto &child : children) {
      funcArgs.emplace_back(*child);

      if (const auto num = cast<INumber>(child); num && num->getPrecision()) {
        callFunctionCached->areArgsPrecise = false;
      }
    }

    if (func.doArgsMatch(funcArgs)) {
      callFunctionCached->value = func(funcArgs);
      tranformChild(callFunctionCached->value, State::Simplify, false);

      if (auto callFunctionNum = cast<INumber>(callFunctionCached->value)) {
        callFunctionCached->precision = callFunctionNum->getPrecision();
      }
    }
  }

  if (callFunctionCached->areArgsPrecise) {
    if (const auto num = cast<INumber>(callFunctionCached->value); num && num->getPrecision()) {
      return {};
    }
  }

  return callFunctionCached->value;
}

ArgumentPtr IExpression::preSimplify(const bool isTranformOverriden) const {
  if (state >= State::PreSimplify) {
    return {};
  }

  if (auto res = simplifyUndefined()) {
    return res;
  }

  ArgumentPtrVector children = getChildren();
  const IFunction &func = *getFunction();

  for (auto &child : children) {
    preSimplifyChild(child);
  }

  ArgumentPtr res = makeExpr(func, children);
  callFunctionChild(res);
  tranformChild(res, State::PreSimplify, isTranformOverriden);

  auto resExpr = cast<IExpression>(res);
  bool isResTranformOverriden = resExpr && resExpr->state < State::PreSimplify && *resExpr != *this;
  preSimplifyChild(res, isResTranformOverriden);

  return res;
}

ArgumentPtr IExpression::simplify(const bool isTranformOverriden) const {
  if (state >= State::Simplify) {
    return {};
  }

  ArgumentPtr preSimpl = preSimplify(isTranformOverriden);
  const auto *preSimplExpr = cast<IExpression>(preSimpl.get());

  if (!preSimplExpr) {
    if (preSimpl) {
      return preSimpl;
    }

    preSimplExpr = this;
  }

  ArgumentPtrVector children = preSimplExpr->getChildren();
  const IFunction &func = *preSimplExpr->getFunction();

  for (auto &child : children) {
    simplifyChild(child);
  }

  ArgumentPtr res = makeExpr(func, children);
  tranformChild(res, State::Simplify, isTranformOverriden);

  auto resExpr = cast<IExpression>(res);
  bool isResTranformOverriden = resExpr && resExpr->state < State::Simplify && *resExpr != *this;
  simplifyChild(res, isResTranformOverriden);

  return res;
}

ArgumentPtr IExpression::approximate(const bool isTranformOverriden) const {
  if (state >= State::Approximate) {
    return {};
  }

  if (auto res = callFunction()) {
    return res;
  }

  ArgumentPtr simpl = simplify(isTranformOverriden); // TODO! solve
  const auto *simplExpr = cast<IExpression>(simpl.get());

  if (!simplExpr) {
    if (simpl) {
      return simpl;
    }

    simplExpr = this;
  }

  ArgumentPtrVector children = simplExpr->getChildren();
  const auto &func = *simplExpr->getFunction();

  for (auto &child : children) {
    approximateChild(child);
  }

  ArgumentPtr res = makeExpr(func, children);
  tranformChild(res, State::Approximate, isTranformOverriden);

  auto resExpr = cast<IExpression>(res);
  bool isResTranformOverriden = resExpr && resExpr->state < State::Approximate && *resExpr != *this;
  approximateChild(res, isResTranformOverriden); // TODO! solve child

  return res;
}

ArgumentPtr IExpression::tranform(const State newState) const {
  state = std::max(state, newState);
  return {};
}

void IExpression::callFunctionChild(ArgumentPtr &child) {
  if (const auto childExpr = cast<IExpression>(child)) {
    if (auto res = childExpr->callFunction()) {
      child = res;
    }
  }
}

void IExpression::preSimplifyChild(ArgumentPtr &child, const bool isTranformOverriden) {
  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto res = childExpr->preSimplify(isTranformOverriden)) {
      child = res;
    }
  }
  else if (const auto childConst = cast<IConstant>(child)) {
    const ArgumentPtr childConstVal = (*childConst)();

    if (const auto num = cast<INumber>(childConstVal); num && num->getPrecision()) {
      child = childConst;
    }
    else {
      child = childConstVal;
    }
  }
  else if (child) {
    child = child->toMinimalObject();
  }
}

void IExpression::simplifyChild(ArgumentPtr &child, const bool isTranformOverriden) {
  if (const auto childExpr = cast<IExpression>(child)) {
    if (auto res = childExpr->simplify(isTranformOverriden)) {
      child = res;
    }
  }
}

void IExpression::approximateChild(ArgumentPtr &child, const bool isTranformOverriden) {
  if (const auto childExpr = cast<IExpression>(child)) {
    if (auto res = childExpr->approximate(isTranformOverriden)) {
      child = res;
    }
  }
  else if (const auto childNum = cast<INumber>(child)) {
    if (auto res = convertToApproximated(*childNum)) {
      child = std::move(res);
    }
  }
  else if (const auto childConst = cast<IConstant>(child)) {
    child = (*childConst)();
  }
}

void IExpression::tranformChild(ArgumentPtr &child, const State newState, const bool isOverriden) {
  if (const auto childExpr = cast<IExpression>(child)) {
    if (childExpr->state < newState) {
      if (auto res = isOverriden ? childExpr->tranform(newState) : childExpr->IExpression::tranform(newState)) {
        child = res;
      }
    }
  }
}

ArgumentPtr IExpression::simplifyUndefined() const {
  static const MathObjectClass undefinedClass = Undefined{}.getReturnClass();
  const MathObjectClass funcReturnClass = getOutputFunction()->getReturnClass();

  if (!is(undefinedClass, funcReturnClass) &&
      !is(funcReturnClass, undefinedClass)) {

    return {};
  }

  for (const auto &child : getChildren()) {
    if ((is<Undefined>(child))) {
      return Undefined().clone();
    }
  }

  return {};
}

std::unique_ptr<INumber> IExpression::convertToApproximated(const INumber &num) {
  static const auto multiConvert = [] {
    static Cache<unsigned, Integer> maxIntCache([](const unsigned inPrecision) {
      static const Integer powBase = 10;
      return pow(powBase, inPrecision);
    });

    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiConvert;

    outMultiConvert.add<Integer>([](const Integer &inRhs) {
      if (inRhs >= maxIntCache[Real::getPrecisionStatic()]) {
        return Real(inRhs).clone();
      }

      return std::unique_ptr<IMathObject>{};
    });

    outMultiConvert.add<Rational>([](const Rational &inRhs) {
      return Real(inRhs).clone();
    });

    outMultiConvert.add<Real>([](const Real &inRhs) {
      auto res = cast<Real>(inRhs.clone());
      res->setPrecision(Real::getPrecisionStatic());
      return res;
    });

    outMultiConvert.add<Complex>([](const Complex &inRhs) {
      const auto approxReal = convertToApproximated(inRhs.real());
      const auto approxImag = convertToApproximated(inRhs.imag());

      if (!approxReal && !approxImag) {
        return std::unique_ptr<IMathObject>{};
      }

      if (!approxReal) {
        return Complex(inRhs.real(), *approxImag).clone();
      }

      if (!approxImag) {
        return Complex(*approxReal, inRhs.imag()).clone();
      }

      return Complex(*approxReal, *approxImag).clone();
    });

    return outMultiConvert;
  }();

  return cast<INumber>(multiConvert(num));
}

}
