#include "fintamath/expressions/binary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
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

using DerivativeSimplifyMap = std::unordered_map<
    std::string,
    std::function<ArgumentPtr(const ArgumentPtrVector &children,
                              const std::shared_ptr<const Variable> &var)>>;

DerivativeExpression::DerivativeExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Derivative(), std::move(inLhsChild), std::move(inRhsChild)) {
}

DerivativeExpression::SimplifyFunctionVector DerivativeExpression::getFunctionsForPostSimplify() const {
  static const DerivativeExpression::SimplifyFunctionVector simplifyFunctions = {
      &DerivativeExpression::derivativeSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr DerivativeExpression::derivativeSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto var = cast<Variable>(rhs);

  if (auto lhsExpr = cast<IExpression>(lhs)) {
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

ArgumentPtr DerivativeExpression::exprSimplify(const std::shared_ptr<const IExpression> &expr, const std::shared_ptr<const Variable> &var) {
  static const DerivativeSimplifyMap derivativeSimplifyMap = [] {
    static const DerivativeSimplifyMap map = {
        {Add().toString(), &addSimplify},
        {Mul().toString(), &mulSimplify},
        {Div().toString(), &divSimplify},
        {Pow().toString(), &powSimplify},
        {Log().toString(), &logSimplify},
        {Sin().toString(), &sinSimplify},
        {Cos().toString(), &cosSimplify},
        {Tan().toString(), &tanSimplify},
        {Cot().toString(), &cotSimplify},
        {Sec().toString(), &secSimplify},
        {Csc().toString(), &cscSimplify},
        {Asin().toString(), &asinSimplify},
        {Acos().toString(), &acosSimplify},
        {Atan().toString(), &atanSimplify},
        {Acot().toString(), &acotSimplify},
        {Asec().toString(), &asecSimplify},
        {Acsc().toString(), &acscSimplify},
        {Sinh().toString(), &sinhSimplify},
        {Cosh().toString(), &coshSimplify},
        {Tanh().toString(), &tanhSimplify},
        {Coth().toString(), &cothSimplify},
        {Sech().toString(), &sechSimplify},
        {Csch().toString(), &cschSimplify},
        {Asinh().toString(), &asinhSimplify},
        {Acosh().toString(), &acoshSimplify},
        {Atanh().toString(), &atanhSimplify},
        {Acoth().toString(), &atanhSimplify},
        {Asech().toString(), &asechSimplify},
        {Acsch().toString(), &acschSimplify},
    };
    return map;
  }();

  if (auto iter = derivativeSimplifyMap.find(expr->getFunction()->toString());
      iter != derivativeSimplifyMap.end()) {

    return iter->second(expr->getChildren(), var);
  }

  return {};
}

ArgumentPtr DerivativeExpression::addSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  ArgumentPtrVector newChildren = children;

  std::ranges::transform(newChildren, newChildren.begin(), [&var](const ArgumentPtr &child) {
    return derivativeExpr(child, var);
  });

  return addExpr(std::move(newChildren));
}

ArgumentPtr DerivativeExpression::mulSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  auto childrenSizeDiv2 = ptrdiff_t(children.size() / 2);

  ArgumentPtrVector lhsChildren = ArgumentPtrVector(children.begin(), children.begin() + childrenSizeDiv2);
  ArgumentPtrVector rhsChildren = ArgumentPtrVector(children.begin() + childrenSizeDiv2, children.end());

  ArgumentPtr lhs = makePolynom(Mul(), std::move(lhsChildren));
  ArgumentPtr rhs = makePolynom(Mul(), std::move(rhsChildren));

  return addExpr(
      mulExpr(derivativeExpr(lhs, var), rhs),
      mulExpr(derivativeExpr(rhs, var), lhs));
}

ArgumentPtr DerivativeExpression::divSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr numerator = subExpr(
      mulExpr(derivativeExpr(lhs, var), rhs),
      mulExpr(derivativeExpr(rhs, var), lhs));

  ArgumentPtr denominator = sqrExpr(rhs);

  return divExpr(numerator, denominator);
}

ArgumentPtr DerivativeExpression::powSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr mulFirst = powExpr(lhs, subExpr(rhs, Integer(1).clone()));

  ArgumentPtr mulSecond = addExpr(
      mulExpr(rhs, derivativeExpr(lhs, var)),
      mulExpr(lhs, lnExpr(lhs), derivativeExpr(rhs, var)));

  return mulExpr(mulFirst, mulSecond);
}

ArgumentPtr DerivativeExpression::logSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &lhs = children.front();
  const ArgumentPtr &rhs = children.back();

  ArgumentPtr subLhs = divExpr(
      derivativeExpr(rhs, var),
      mulExpr(rhs, lnExpr(lhs)));

  ArgumentPtr subRhs = divExpr(
      mulExpr(derivativeExpr(lhs, var), lnExpr(rhs)),
      mulExpr(lhs, sqrExpr(lnExpr(lhs))));

  return subExpr(subLhs, subRhs);
}

ArgumentPtr DerivativeExpression::sinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(cosExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::cosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(negExpr(sinExpr(rhs)), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::tanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrExpr(cosExpr(rhs));

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::cotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrExpr(sinExpr(rhs));

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::secSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(tanExpr(rhs), secExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::cscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(negExpr(cotExpr(rhs)), cscExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::asinSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(subExpr(Integer(1).clone(), sqrExpr(rhs)));

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::acosSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(subExpr(Integer(1).clone(), sqrExpr(rhs)));

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::atanSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = addExpr(sqrExpr(rhs), Integer(1).clone());

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::acotSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = addExpr(sqrExpr(rhs), Integer(1).clone());

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::asecSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(Integer(1).clone(),
              divExpr(Integer(1).clone(), sqrExpr(rhs))));

  ArgumentPtr denominatorMulSecond = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(denominatorMulFirst, denominatorMulSecond);

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::acscSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(Integer(1).clone(),
              divExpr(Integer(1).clone(), sqrExpr(rhs))));

  ArgumentPtr denominatorMulRhs = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(denominatorMulFirst, denominatorMulRhs);

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::sinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(coshExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::coshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(sinhExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::tanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = powExpr(coshExpr(rhs), Integer(2).clone());

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::cothSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = powExpr(sinhExpr(rhs), Integer(2).clone());

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::sechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(negExpr(tanhExpr(rhs)), sechExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::cschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  return mulExpr(negExpr(cothExpr(rhs)), cschExpr(rhs), derivativeExpr(rhs, var));
}

ArgumentPtr DerivativeExpression::asinhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = sqrtExpr(addExpr(sqrExpr(rhs), Integer(1).clone()));

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::acoshSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = mulExpr(
      sqrtExpr(subExpr(rhs, Integer(1).clone())),
      sqrtExpr(addExpr(rhs, Integer(1).clone())));

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::atanhSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominator = subExpr(Integer(1).clone(), sqrExpr(rhs));

  return divExpr(derivativeExpr(rhs, var), denominator);
}

ArgumentPtr DerivativeExpression::asechSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      subExpr(divExpr(Integer(1).clone(), rhs),
              Integer(1).clone()));

  ArgumentPtr denominatorMulSecond = sqrtExpr(
      addExpr(divExpr(Integer(1).clone(), rhs),
              Integer(1).clone()));

  ArgumentPtr denominatorMulThird = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(denominatorMulFirst, denominatorMulSecond, denominatorMulThird);

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

ArgumentPtr DerivativeExpression::acschSimplify(const ArgumentPtrVector &children, const std::shared_ptr<const Variable> &var) {
  const ArgumentPtr &rhs = children.front();

  ArgumentPtr denominatorMulFirst = sqrtExpr(
      addExpr(divExpr(Integer(1).clone(), sqrExpr(rhs)),
              Integer(1).clone()));

  ArgumentPtr denominatorMulSecond = sqrExpr(rhs);

  ArgumentPtr denominator = mulExpr(denominatorMulFirst, denominatorMulSecond);

  return divExpr(negExpr(derivativeExpr(rhs, var)), denominator);
}

}
