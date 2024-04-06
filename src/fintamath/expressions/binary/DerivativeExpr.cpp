#include "fintamath/expressions/binary/DerivativeExpr.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
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
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqr.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Acsc.hpp"
#include "fintamath/functions/trigonometry/Asec.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Csc.hpp"
#include "fintamath/functions/trigonometry/Sec.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

using namespace detail;

using NameToSimplifyFunctionMap = std::unordered_map<
    std::string,
    std::function<ArgumentPtr(const ArgumentPtrVector &children,
                              const std::shared_ptr<const Variable> &var)>>;

DerivativeExpr::DerivativeExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Derivative{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

DerivativeExpr::SimplifyFunctionVector DerivativeExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &DerivativeExpr::derivativeSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr DerivativeExpr::derivativeSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto var = cast<Variable>(rhs);

  if (const auto lhsExpr = cast<IExpression>(lhs)) {
    return exprSimplify(lhsExpr, var);
  }

  if (is<Variable>(lhs)) {
    return (*lhs == *var) ? Integer(1).clone() : Integer(0).clone();
  }

  if (is<INumber>(lhs) || is<IConstant>(lhs)) {
    return Integer(0).clone();
  }

  return {};
}

ArgumentPtr DerivativeExpr::exprSimplify(const std::shared_ptr<const IExpression> &expr, const std::shared_ptr<const Variable> &var) {
  static const NameToSimplifyFunctionMap nameToSimplifyFunctionMap = [] {
    static const NameToSimplifyFunctionMap map = {
        {Add{}.toString(), &addSimplify},
        {Mul{}.toString(), &mulSimplify},
        {Div{}.toString(), &divSimplify},
        {Pow{}.toString(), &powSimplify},
        {Log{}.toString(), &logSimplify},
        {Sin{}.toString(), &sinSimplify},
        {Cos{}.toString(), &cosSimplify},
        {Tan{}.toString(), &tanSimplify},
        {Cot{}.toString(), &cotSimplify},
        {Sec{}.toString(), &secSimplify},
        {Csc{}.toString(), &cscSimplify},
        {Asin{}.toString(), &asinSimplify},
        {Acos{}.toString(), &acosSimplify},
        {Atan{}.toString(), &atanSimplify},
        {Acot{}.toString(), &acotSimplify},
        {Asec{}.toString(), &asecSimplify},
        {Acsc{}.toString(), &acscSimplify},
        {Sinh{}.toString(), &sinhSimplify},
        {Cosh{}.toString(), &coshSimplify},
        {Tanh{}.toString(), &tanhSimplify},
        {Coth{}.toString(), &cothSimplify},
        {Sech{}.toString(), &sechSimplify},
        {Csch{}.toString(), &cschSimplify},
        {Asinh{}.toString(), &asinhSimplify},
        {Acosh{}.toString(), &acoshSimplify},
        {Atanh{}.toString(), &atanhSimplify},
        {Acoth{}.toString(), &atanhSimplify},
        {Asech{}.toString(), &asechSimplify},
        {Acsch{}.toString(), &acschSimplify},
    };
    return map;
  }();

  if (const auto iter = nameToSimplifyFunctionMap.find(expr->getFunction()->toString());
      iter != nameToSimplifyFunctionMap.end()) {

    return iter->second(expr->getChildren(), var);
  }

  return {};
}

ArgumentPtr DerivativeExpr::addSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  ArgumentPtrVector newChildren = children;

  std::ranges::transform(newChildren, newChildren.begin(), [&var](const ArgumentPtr &child) {
    return derivativeExpr(child, var);
  });

  return addExpr(std::move(newChildren));
}

ArgumentPtr DerivativeExpr::mulSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const auto childrenSizeDiv2 = static_cast<ptrdiff_t>(children.size() / 2);

  auto lhsChildren = ArgumentPtrVector(children.begin(), children.begin() + childrenSizeDiv2);
  auto rhsChildren = ArgumentPtrVector(children.begin() + childrenSizeDiv2, children.end());

  const ArgumentPtr lhs = mulExpr(std::move(lhsChildren));
  const ArgumentPtr rhs = mulExpr(std::move(rhsChildren));

  return addExpr(
      mulExpr(derivativeExpr(lhs, var), rhs),
      mulExpr(derivativeExpr(rhs, var), lhs));
}

ArgumentPtr DerivativeExpr::divSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr numerator = subExpr(
      mulExpr(derivativeExpr(lhs, var), rhs),
      mulExpr(derivativeExpr(rhs, var), lhs));

  ArgumentPtr denominator = sqrExpr(rhs);

  return divExpr(std::move(numerator), std::move(denominator));
}

ArgumentPtr DerivativeExpr::powSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr mulFirst = powExpr(lhs, subExpr(rhs, Integer(1).clone()));

  ArgumentPtr mulSecond = addExpr(
      mulExpr(rhs, derivativeExpr(lhs, var)),
      mulExpr(lhs, lnExpr(lhs), derivativeExpr(rhs, var)));

  return mulExpr(std::move(mulFirst), std::move(mulSecond));
}

ArgumentPtr DerivativeExpr::logSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr subLhs = divExpr(
      derivativeExpr(rhs, var),
      mulExpr(rhs, lnExpr(lhs)));

  ArgumentPtr subRhs = divExpr(
      mulExpr(derivativeExpr(lhs, var), lnExpr(rhs)),
      mulExpr(lhs, sqrExpr(lnExpr(lhs))));

  return subExpr(std::move(subLhs), std::move(subRhs));
}

ArgumentPtr DerivativeExpr::sinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(cosExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpr::cosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(negExpr(sinExpr(rhs)), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpr::tanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrExpr(cosExpr(rhs));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::cotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrExpr(sinExpr(rhs));

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::secSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(
      sqrExpr(secExpr(rhs)),
      sinExpr(rhs),
      derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpr::cscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return negExpr(mulExpr(
      sqrExpr(cscExpr(rhs)),
      cosExpr(rhs),
      derivativeExpr(rhs, var)));
}

ArgumentPtr DerivativeExpr::asinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(subExpr(Integer(1).clone(), sqrExpr(rhs)));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::acosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(subExpr(Integer(1).clone(), sqrExpr(rhs)));

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::atanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = addExpr(sqrExpr(rhs), Integer(1).clone());

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::acotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = addExpr(sqrExpr(rhs), Integer(1).clone());

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::asecSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(Integer(1).clone(),
              divExpr(Integer(1).clone(), sqrExpr(rhs))));

  ArgumentPtr denominatorMulSecond = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(std::move(denominatorMulFirst), std::move(denominatorMulSecond));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::acscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(Integer(1).clone(),
              divExpr(Integer(1).clone(), sqrExpr(rhs))));

  ArgumentPtr denominatorMulRhs = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(std::move(denominatorMulFirst), std::move(denominatorMulRhs));

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::sinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(coshExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpr::coshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(sinhExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpr::tanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = powExpr(coshExpr(rhs), Integer(2).clone());

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::cothSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = powExpr(sinhExpr(rhs), Integer(2).clone());

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::sechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return negExpr(mulExpr(
      sqrExpr(sechExpr(rhs)),
      sinhExpr(rhs),
      derivativeExpr(rhs, var)));
}

ArgumentPtr DerivativeExpr::cschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return negExpr(mulExpr(
      sqrExpr(cschExpr(rhs)),
      coshExpr(rhs),
      derivativeExpr(rhs, var)));
}

ArgumentPtr DerivativeExpr::asinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(addExpr(sqrExpr(rhs), Integer(1).clone()));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::acoshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = mulExpr(
      sqrtExpr(subExpr(rhs, Integer(1).clone())),
      sqrtExpr(addExpr(rhs, Integer(1).clone())));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::atanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = subExpr(Integer(1).clone(), sqrExpr(rhs));

  return divExpr(derivativeExpr(rhs, var), std::move(denominator));
}

ArgumentPtr DerivativeExpr::asechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(divExpr(Integer(1).clone(), rhs),
              Integer(1).clone()));

  ArgumentPtr denominatorMulSecond = sqrtExpr(
      addExpr(divExpr(Integer(1).clone(), rhs),
              Integer(1).clone()));

  ArgumentPtr denominatorMulThird = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(std::move(denominatorMulFirst),
                                    std::move(denominatorMulSecond),
                                    std::move(denominatorMulThird));

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

ArgumentPtr DerivativeExpr::acschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      addExpr(divExpr(Integer(1).clone(), sqrExpr(rhs)),
              Integer(1).clone()));

  ArgumentPtr denominatorMulSecond = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(std::move(denominatorMulFirst), std::move(denominatorMulSecond));

  return divExpr(negExpr(derivativeExpr(rhs, var)), std::move(denominator));
}

}
