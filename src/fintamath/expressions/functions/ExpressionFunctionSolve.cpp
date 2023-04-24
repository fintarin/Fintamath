#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

shared_ptr<const INumber> getPowOfElement(const ArgumentPtr &elem, const shared_ptr<const Variable> &v);
shared_ptr<const INumber> getPowOfMulElement(const shared_ptr<const IExpression> &elem,
                                             const shared_ptr<const Variable> &v);

shared_ptr<const INumber> getPowOfElement(const ArgumentPtr &elem, const shared_ptr<const Variable> &v) {
  if (const auto &var = cast<Variable>(elem); var && *var == *v) {
    return cast<INumber>(ONE.clone());
  }
  if (const auto &expr = cast<IExpression>(elem)) {
    if (is<Neg>(expr->getFunction())) {
      return getPowOfElement(expr->getChildren().front(), v);
    }
    if (is<Mul>(expr->getFunction())) {
      return getPowOfMulElement(expr, v);
    }
    if (is<Pow>(expr->getFunction())) {
      if (const auto &var = cast<Variable>(expr->getChildren().front()); var && *var == *v) {
        return cast<INumber>(expr->getChildren()[1]);
      }
    }
  }
  return cast<INumber>(ZERO.clone());
}

shared_ptr<const INumber> getPowOfMulElement(const shared_ptr<const IExpression> &elem,
                                             const shared_ptr<const Variable> &v) {
  for (const auto &child : elem->getChildren()) {
    if (const auto &powValue = getPowOfElement(child, v); *powValue != ZERO) {
      return powValue;
    }
  }
  return cast<INumber>(ZERO.clone());
}

ArgumentPtr getCoefficientOfElement(const ArgumentPtr &elem, const shared_ptr<const Variable> &v) {
  if (const auto &elemExpr = cast<IExpression>(elem)) {
    if (is<Neg>(elemExpr->getFunction())) {
      return makeFunctionExpression(Neg(), {getCoefficientOfElement(elemExpr->getChildren().front(), v)});
    }
    if (is<Pow>(elemExpr->getFunction())) {
      if (hasVariable(elemExpr, v)) {
        return ONE.clone();
      }
      return elem;
    }
    if (is<Mul>(elemExpr->getFunction())) {
      ArgumentsPtrVector coeff{ONE.clone()};
      for (const auto &child : elemExpr->getChildren()) {
        coeff.emplace_back(getCoefficientOfElement(child, v));
      }
      return makeFunctionExpression(Mul(), coeff);
    }
  }

  if (const auto &varElem = cast<Variable>(elem); varElem && *v == *varElem) {
    return ONE.clone();
  }
  return elem;
}

ArgumentsPtrVector getCoefficientsAtPows(const ArgumentPtr &rhs, const shared_ptr<const Variable> &v) {
  ArgumentsPtrVector result;
  ArgumentsPtrVector polynomVect;

  if (const auto &exprVal = cast<IExpression>(rhs); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(rhs);
  }

  for (const auto &elem : polynomVect) {
    shared_ptr<const INumber> pow = getPowOfElement(elem, v);
    ArgumentPtr coefficient = getCoefficientOfElement(elem, v);

    Integer intPow = cast<Integer>(*pow);

    // TODO: add Integer to int conversion
    int powVal = 0;
    while (powVal < intPow) {
      powVal++;
    }

    if (result.size() < intPow + 1) {
      while (result.size() != intPow + 1) {
        result.emplace_back(ZERO.clone());
      }
    }

    result[powVal] = coefficient;
  }

  return result;
}

bool validatePowExpr(const shared_ptr<const IExpression> &powExpr) {
  return is<Integer>(powExpr->getChildren()[1]);
}

bool validateMulExpr(const shared_ptr<const IExpression> &mulExpr) {
  for (const auto &child : mulExpr->getChildren()) {
    if (const auto &childExpr = cast<IExpression>(child);
        childExpr && is<Pow>(childExpr->getFunction()) && !validatePowExpr(childExpr)) {
      return false;
    }
  }
  return true;
}

bool validateAddExpr(const shared_ptr<const IExpression> &addExpr) {
  for (const auto &child : addExpr->getChildren()) {
    if (const auto &childExpr = cast<IExpression>(child)) {
      shared_ptr<const IExpression> childExprNonNeg;
      if (is<Neg>(childExpr->getFunction())) {
        childExprNonNeg = cast<IExpression>(childExpr->getChildren()[0]);
      }
      else {
        childExprNonNeg = childExpr;
      }

      if (!childExprNonNeg) {
        return true;
      }

      if (is<Pow>(childExprNonNeg->getFunction()) && !validatePowExpr(childExprNonNeg)) {
        return false;
      }
      if (is<Mul>(childExprNonNeg->getFunction()) && !validateMulExpr(childExprNonNeg)) {
        return false;
      }
    }
  }
  return true;
}

bool validateEquation(const CompExpression &expr) {
  ArgumentsPtrVector vars = expr.getVariables();
  // TODO: remove for equation systems
  if (vars.size() != 1) {
    return false;
  }

  ArgumentPtr lhsVal = expr.getChildren().front();
  if (const auto &lhsExpr = cast<IExpression>(lhsVal)) {
    shared_ptr<const IExpression> lhsExprNonNeg;
    if (is<Neg>(lhsExpr->getFunction())) {
      lhsExprNonNeg = cast<IExpression>(lhsExpr->getChildren()[0]);
    }
    else {
      lhsExprNonNeg = lhsExpr;
    }

    if (!lhsExprNonNeg) {
      return true;
    }

    if (is<Add>(lhsExprNonNeg->getFunction())) {
      return validateAddExpr(lhsExprNonNeg);
    }
    if (is<Mul>(lhsExprNonNeg->getFunction())) {
      return validateMulExpr(lhsExprNonNeg);
    }
    if (is<Pow>(lhsExprNonNeg->getFunction())) {
      return validatePowExpr(lhsExprNonNeg);
    }
    return false;
  }
  return true;
}

ArgumentsPtrVector solveCubicEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {};
}

ArgumentsPtrVector solveQuadraticEquation(const ArgumentsPtrVector &coeffAtPow) {
  static const ArgumentPtr a = make_shared<Variable>("a");
  static const ArgumentPtr b = make_shared<Variable>("b");
  static const ArgumentPtr c = make_shared<Variable>("c");

  static const Expression discr = sub(pow(*b, 2), mul(4, *a, *c));
  static const Expression firstRoot = div(sum(neg(*b), sqrt(discr)), mul(2, *a));
  static const Expression secondRoot = div(sub(neg(*b), sqrt(discr)), mul(2, *a));

  ArgumentPtr discrValue = discr.setValuesOfVariables({c, b, a}, coeffAtPow);
  if (const auto &number = cast<INumber>(discrValue)) {
    if (*number < ZERO) {
      return {};
    }
    if (*number == ZERO) {
      return {firstRoot.setValuesOfVariables({c, b, a}, coeffAtPow)};
    }
  }
  return {firstRoot.setValuesOfVariables({c, b, a}, coeffAtPow),
          secondRoot.setValuesOfVariables({c, b, a}, coeffAtPow)};
}

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {makeFunctionExpression(Neg(), {makeFunctionExpression(Div(), {coeffAtPow[0], coeffAtPow[1]})})};
}

Expression solve(const Expression &rhs) {
  if (auto compExpr = cast<CompExpression>(rhs.getChildren().front()->clone())) {
    // TODO: remove this if when inequalities will be implemented
    if (!is<Eqv>(compExpr->getFunction())) {
      if (!validateEquation(*compExpr)) {
        return rhs;
      }

      ArgumentsPtrVector variables = compExpr->getVariables();

      shared_ptr<const Variable> var = cast<Variable>(variables.front());

      ArgumentsPtrVector coeffAtPow = getCoefficientsAtPows(compExpr->getChildren()[0], var);

      if (coeffAtPow.size() == 2) {
        compExpr->markAsSolution();
        return *compExpr;
      }
    }
    if (is<Eqv>(compExpr->getFunction())) {
      if (!validateEquation(*compExpr)) {
        return rhs;
      }

      ArgumentsPtrVector variables = compExpr->getVariables();

      shared_ptr<const Variable> var = cast<Variable>(variables.front());

      ArgumentsPtrVector coeffAtPow = getCoefficientsAtPows(compExpr->getChildren()[0], var);

      ArgumentsPtrVector roots;

      switch (coeffAtPow.size()) {
      case 2:
        roots = solveLinearEquation(coeffAtPow);
        break;
      case 3:
        roots = solveQuadraticEquation(coeffAtPow);
        break;
      case 4:
        roots = solveCubicEquation(coeffAtPow);
        break;
      default:
        roots = {};
      }

      if (roots.empty()) {
        return *compExpr;
      }

      ArgumentsPtrVector answer;

      for (auto &root : roots) {
        auto rootAnswer = make_shared<CompExpression>(Eqv(), var->clone(), root);
        rootAnswer->markAsSolution();
        answer.emplace_back(rootAnswer);
      }

      if (answer.size() == 1) {
        return Expression(answer.front());
      }

      return Expression(makeFunctionExpression(Or(), answer));
    }

    return *compExpr;
  }

  return rhs;
}

}
