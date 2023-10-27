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
  else {
    if (const auto constChild = cast<IConstant>(child)) {
      ArgumentPtr constVal = (*constChild)();

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

void IExpression::approximateSimplifyChild(ArgumentPtr &child) {
  if (const auto constChild = cast<IConstant>(child)) {
    child = (*constChild)();
  }
  else if (const auto exprChild = cast<IExpression>(child)) {
    child = exprChild->approximateSimplify();
  }
}

void IExpression::setPrecisionChild(ArgumentPtr &child, uint8_t precision, const Integer &maxInt) {
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
                                                            uint8_t precision,
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

      return std::unique_ptr<IMathObject>();
    });

    outMultiSetPrecision.add<Rational, Integer, Integer>([](const Rational &inRhs,
                                                            const Integer & /*inPrecision*/,
                                                            const Integer & /*inMaxInt*/) {
      return Real(inRhs).clone();
    });

    outMultiSetPrecision.add<Real, Integer, Integer>([](const Real &inRhs,
                                                        const Integer & /*inPrecision*/,
                                                        const Integer & /*inMaxInt*/) {
      return inRhs.clone();
    });

    outMultiSetPrecision.add<Complex, Integer, Integer>([](const Complex &inRhs,
                                                           const Integer &inPrecision,
                                                           const Integer &inMaxInt) {
      auto approxReal = convertToApproximated(inRhs.real(), uint8_t(inPrecision), inMaxInt);
      auto approxImag = convertToApproximated(inRhs.imag(), uint8_t(inPrecision), inMaxInt);

      if (!approxReal && !approxImag) {
        return std::unique_ptr<IMathObject>();
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

  auto res = cast<INumber>(multiSetPrecision(num, Integer(precision), maxInt));

  if (is<Real>(res)) {
    cast<Real>(*res).setPrecision(precision);
  }

  return res;
}

ArgumentPtrVector fintamath::IExpression::convertToApproximatedNumbers(const ArgumentPtrVector &args) {
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

ArgumentPtr IExpression::approximateSimplify() const {
  ArgumentPtr simpl = simplify();

  if (!is<IExpression>(simpl)) {
    approximateSimplifyChild(simpl);
    return simpl;
  }

  auto simplExpr = cast<IExpression>(simpl);
  ArgumentPtrVector approxChildren = simplExpr->getChildren();

  bool areNumberChilrenPrecise = true;
  size_t numberChildrenCount = 0;

  for (auto &child : approxChildren) {
    approximateSimplifyChild(child);

    if (const auto childNum = cast<INumber>(child)) {
      numberChildrenCount++;

      if (!childNum->isPrecise()) {
        areNumberChilrenPrecise = false;
      }
    }
  }

  auto approxExpr = cast<IExpression>(simplExpr->clone());
  approxExpr->setChildren(approxChildren);

  bool containsVar = containsVariable(simplExpr);

  if (containsVar &&
      (numberChildrenCount < 2 ||
       IFunction::Type(approxChildren.size()) == getFunction()->getFunctionType())) {

    return approxExpr;
  }

  ArgumentPtr approxSimpl = approxExpr->simplify();
  auto approxSimplExpr = cast<IExpression>(approxSimpl);

  if (!approxSimplExpr || *approxSimplExpr != *approxExpr) {
    return approxSimpl;
  }

  if (!containsVar && areNumberChilrenPrecise) {
    auto res = callFunction(*approxSimplExpr->getFunction(),
                            convertToApproximatedNumbers(approxSimplExpr->getChildren()));

    if (is<INumber>(res)) {
      return res;
    }
  }

  return approxSimpl;
}

ArgumentPtr IExpression::setPrecision(uint8_t precision, const Integer &maxInt) const {
  ArgumentPtrVector newChildren = getChildren();

  for (auto &child : newChildren) {
    setPrecisionChild(child, precision, maxInt);
  }

  auto newExprArg = cast<IExpression>(clone());
  newExprArg->setChildren(newChildren);
  return newExprArg;
}

}
