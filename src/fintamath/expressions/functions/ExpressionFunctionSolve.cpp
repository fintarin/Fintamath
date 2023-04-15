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

shared_ptr<const INumber> getPowOfElement(const ArgumentPtr &elem) {
  shared_ptr<const IExpression> powExpr;

  if (const auto &expr = cast<IExpression>(elem)) {
    if (is<Neg>(expr->getFunction())) {
      if (is<Variable>(expr->getChildren()[0])) {
        return cast<INumber>(ONE.clone());
      }
      powExpr = expr;
    }

    if (is<Mul>(expr->getFunction())) {
      for (const auto &child : expr->getChildren()) {
        if (is<Variable>(child)) {
          return cast<INumber>(ONE.clone());
        }

        if (const auto &childExpr = cast<IExpression>(child); childExpr && is<Pow>(childExpr->getFunction())) {
          powExpr = childExpr;
          break;
        }
      }
    }
    else {
      powExpr = expr;
    }

    if (powExpr) {
      if (is<Pow>(powExpr->getFunction())) {
        return cast<INumber>(powExpr->getChildren()[1]);
      }
      return cast<INumber>(ZERO.clone());
    }
  }
  if (is<Variable>(elem)) {
    return cast<INumber>(ONE.clone());
  }
  return cast<INumber>(ZERO.clone());
}

ArgumentPtr getCoefficientOfElement(const ArgumentPtr &elem) {
  if (const auto &elemExpr = cast<IExpression>(elem)) {
    if (is<Neg>(elemExpr->getFunction())) {
      return cast<INumber>(NEG_ONE.clone());
    }
    if (is<Mul>(elemExpr->getFunction())) {
      return cast<INumber>(elemExpr->getChildren().front());
    }
    return cast<INumber>(ONE.clone());
  }
  if (is<Variable>(elem)) {
    return cast<INumber>(ONE.clone());
  }

  return elem;
}

ArgumentsPtrVector getCoefficientsAtPows(const ArgumentPtr &rhs) {
  ArgumentsPtrVector result;
  ArgumentsPtrVector polynomVect;

  if (const auto &exprVal = cast<IExpression>(rhs); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(rhs);
  }

  for (const auto &elem : polynomVect) {
    shared_ptr<const INumber> pow = getPowOfElement(elem);
    ArgumentPtr coefficient = getCoefficientOfElement(elem);

    Integer intPow = cast<Integer>(*pow);

    // TODO: add Integer to int conversion
    int powVal = 0;
    while (powVal < intPow) {
      powVal++;
    }

    if (result.size() - 1 < intPow) {
      while (result.size() - 1 != intPow) {
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
  if (mulExpr->getChildren().size() > 2) {
    return false;
  }
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

  ArgumentPtr discrValue = discr.setValueOfVariable({c, b, a}, coeffAtPow)->toMinimalObject();
  if (const auto &number = cast<INumber>(discrValue)) {
    if (*number < ZERO) {
      return {};
    }
    if (*number == ZERO) {
      return {firstRoot.setValueOfVariable({c, b, a}, coeffAtPow)->toMinimalObject()};
    }
  }
  return {firstRoot.setValueOfVariable({c, b, a}, coeffAtPow)->toMinimalObject(),
          secondRoot.setValueOfVariable({c, b, a}, coeffAtPow)->toMinimalObject()};
}

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {makeFunctionExpression(Div(), {coeffAtPow[1], coeffAtPow[0]})};
}

Expression solve(const Expression &rhs) {
  if (auto compExpr = cast<CompExpression>(rhs.getChildren().front()->clone());
      compExpr && is<Eqv>(compExpr->getFunction())) {
    if (!validateEquation(*compExpr)) {
      return rhs;
    }

    ArgumentsPtrVector coeffAtPow = getCoefficientsAtPows(compExpr->getChildren()[0]);

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
    ArgumentPtr var = compExpr->getVariables()[0];

    for (auto &root : roots) {
      auto rootAnswer = make_shared<CompExpression>(Eqv(), var->clone(), root);
      rootAnswer->markAsSolution();
      answer.emplace_back(rootAnswer);
    }

    return Expression(makeFunctionExpression(Or(), answer));
  }

  return rhs;
}

}
