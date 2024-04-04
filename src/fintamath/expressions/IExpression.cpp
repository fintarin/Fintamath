#include "fintamath/expressions/IExpression.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

using namespace detail;

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IExpression)

std::vector<Variable> IExpression::getVariables() const {
  std::vector<Variable> vars;

  for (const auto &child : getChildren()) {
    if (auto var = cast<Variable>(child)) {
      vars.emplace_back(*var);
    }
    else if (const auto childExpr = cast<IExpression>(child)) {
      std::vector<Variable> childVars = childExpr->getVariables();
      vars.insert(vars.end(), childVars.begin(), childVars.end());
    }
  }

  stdr::sort(vars, std::less{}, &Variable::toString);
  auto unique = stdr::unique(vars);
  vars.erase(unique.begin(), unique.end());

  return vars;
}

void IExpression::setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) {
  const ArgumentPtrVector &children = getChildren();
  ArgumentPtrVector newChildren;

  for (const auto &child : children) {
    if (is<IExpression>(child)) {
      std::shared_ptr exprChild = cast<IExpression>(child->clone());
      exprChild->setVariables(varsToVals);
      newChildren.emplace_back(std::move(exprChild));
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

const std::shared_ptr<IFunction> &IExpression::getOutputFunction() const {
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
  else {
    if (const auto constChild = cast<IConstant>(child)) {
      const ArgumentPtr constVal = (*constChild)();

      if (const auto num = cast<INumber>(constVal); num && !num->isPrecise()) {
        child = constChild;
      }
      else {
        child = constVal;
      }
    }

    child = child->toMinimalObject();
  }
}

void IExpression::postSimplifyChild(ArgumentPtr &child) {
  if (const auto exprChild = cast<IExpression>(child)) {
    if (const auto simplObj = exprChild->postSimplify()) {
      child = simplObj;
    }
  }
}

void IExpression::approximateChild(ArgumentPtr &child) {
  if (const auto constChild = cast<IConstant>(child)) {
    child = (*constChild)();
  }
  else if (const auto exprChild = cast<IExpression>(child)) {
    child = exprChild->approximate();
  }
}

void IExpression::setPrecisionChild(ArgumentPtr &child, const unsigned precision, const Integer &maxInt) {
  if (const auto numChild = cast<INumber>(child)) {
    if (auto res = convertToApproximated(*numChild, precision, maxInt)) {
      child = std::move(res);
    }
  }
  else if (const auto exprChild = cast<IExpression>(child)) {
    child = exprChild->setPrecision(precision, maxInt);
  }
}

std::unique_ptr<INumber> IExpression::convertToApproximated(const INumber &num) {
  static const auto multiApproximate = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiApproximate;

    outMultiApproximate.add<Integer>([](const Integer &inRhs) {
      return Real(inRhs).clone();
    });

    outMultiApproximate.add<Rational>([](const Rational &inRhs) {
      return Real(inRhs).clone();
    });

    outMultiApproximate.add<Complex>([](const Complex &inRhs) {
      return Complex(
                 *convert<Real>(inRhs.real()),
                 *convert<Real>(inRhs.imag()))
          .clone();
    });

    return outMultiApproximate;
  }();

  return cast<INumber>(multiApproximate(num));
}

std::unique_ptr<INumber> IExpression::convertToApproximated(const INumber &num,
                                                            const unsigned precision,
                                                            const Integer &maxInt) {

  static const auto multiSetPrecision = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &,
                                                    const Integer &,
                                                    const Integer &)>
        outMultiSetPrecision;

    outMultiSetPrecision.add<Integer, Integer, Integer>([](const Integer &inRhs,
                                                           const Integer & /*inPrecision*/,
                                                           const Integer &inMaxInt) {
      if (inRhs >= inMaxInt) {
        return Real(inRhs).clone();
      }

      return std::unique_ptr<IMathObject>{};
    });

    outMultiSetPrecision.add<Rational, Integer, Integer>([](const Rational &inRhs,
                                                            const Integer & /*inPrecision*/,
                                                            const Integer & /*inMaxInt*/) {
      return Real(inRhs).clone();
    });

    outMultiSetPrecision.add<Real, Integer, Integer>([](const Real &inRhs,
                                                        const Integer & /*inPrecision*/,
                                                        const Integer & /*inMaxInt*/) {
      auto res = cast<Real>(inRhs.clone());
      res->setOutputPrecision(Real::getPrecision());
      return res;
    });

    outMultiSetPrecision.add<Complex, Integer, Integer>([](const Complex &inRhs,
                                                           const Integer &inPrecision,
                                                           const Integer &inMaxInt) {
      const auto approxReal = convertToApproximated(inRhs.real(), static_cast<unsigned>(inPrecision), inMaxInt);
      const auto approxImag = convertToApproximated(inRhs.imag(), static_cast<unsigned>(inPrecision), inMaxInt);

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

    return outMultiSetPrecision;
  }();

  return cast<INumber>(multiSetPrecision(num, Integer(precision), maxInt));
}

ArgumentPtrVector IExpression::convertToApproximatedNumbers(const ArgumentPtrVector &args) {
  ArgumentPtrVector approxArgs = args;

  for (auto &arg : approxArgs) {
    if (const auto argNum = cast<INumber>(arg); argNum) {
      if (auto argConv = convertToApproximated(*argNum)) {
        arg = std::move(argConv);
      }
    }
  }

  return approxArgs;
}

ArgumentPtr IExpression::callFunction(const IFunction &func, const ArgumentPtrVector &argPtrs) {
  if (!func.isEvaluatable()) {
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

ArgumentPtr IExpression::approximate() const {
  ArgumentPtr simpl = simplify();

  if (!is<IExpression>(simpl)) {
    approximateChild(simpl);
    return simpl;
  }

  const auto simplExpr = cast<IExpression>(simpl);
  ArgumentPtrVector approxChildren = simplExpr->getChildren();

  bool areNumberChilrenPrecise = true;
  size_t numberChildrenCount = 0;

  for (auto &child : approxChildren) {
    approximateChild(child);

    if (const auto childNum = cast<INumber>(child)) {
      numberChildrenCount++;

      if (!childNum->isPrecise()) {
        areNumberChilrenPrecise = false;
      }
    }
  }

  auto approxExpr = cast<IExpression>(simplExpr->clone());
  approxExpr->setChildren(approxChildren);

  const bool containsVar = containsVariable(simplExpr);

  if (containsVar &&
      (numberChildrenCount < 2 ||
       approxChildren.size() == getFunction()->getArgumentClasses().size())) {

    return approxExpr;
  }

  ArgumentPtr approxSimpl = approxExpr->simplify();
  const auto approxSimplExpr = cast<IExpression>(approxSimpl);

  if (!approxSimplExpr || *approxSimplExpr != *approxExpr) {
    return approxSimpl;
  }

  if (!containsVar && areNumberChilrenPrecise) {
    if (auto res = callFunction(*approxSimplExpr->getFunction(),
                                convertToApproximatedNumbers(approxSimplExpr->getChildren()));
        is<INumber>(res)) {

      return res;
    }
  }

  return approxSimpl;
}

ArgumentPtr IExpression::setPrecision(const unsigned precision, const Integer &maxInt) const {
  ArgumentPtrVector newChildren = getChildren();

  for (auto &child : newChildren) {
    setPrecisionChild(child, precision, maxInt);
  }

  auto newExprArg = cast<IExpression>(clone());
  newExprArg->setChildren(newChildren);
  return newExprArg;
}

}
