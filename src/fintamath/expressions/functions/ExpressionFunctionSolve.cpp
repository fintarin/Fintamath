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

ArgumentPtr getElementRate(const ArgumentPtr &elem, const shared_ptr<const Variable> &v);

ArgumentsPtrVector getPowerRates(const ArgumentPtr &rhs, const shared_ptr<const Variable> &v);

bool validatePowExpr(const shared_ptr<const IExpression> &powExpr);

bool validateMulExpr(const shared_ptr<const IExpression> &mulExpr);

bool validateAddExpr(const shared_ptr<const IExpression> &addExpr);

bool validateEquation(const CompExpression &expr);

ArgumentsPtrVector solveCubicEquation(const ArgumentsPtrVector &coeffAtPow);

ArgumentsPtrVector solveQuadraticEquation(const ArgumentsPtrVector &coeffAtPow);

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow);

Expression solve(const Expression &rhs) {
  if (auto compExpr = cast<CompExpression>(rhs.getChildren().front()->clone())) {
    // TODO: remove this if when inequalities will be implemented
    if (!is<Eqv>(compExpr->getFunction())) {
      if (!validateEquation(*compExpr)) {
        return rhs;
      }

      auto var = cast<Variable>(compExpr->getVariables().front());
      ArgumentsPtrVector coeffAtPow = getPowerRates(compExpr->getChildren().front(), var);

      if (coeffAtPow.size() == 2) {
        compExpr->markAsSolution();
        return *compExpr;
      }
    }
    if (is<Eqv>(compExpr->getFunction())) {
      if (!validateEquation(*compExpr)) {
        return rhs;
      }

      auto var = cast<Variable>(compExpr->getVariables().front());
      ArgumentsPtrVector powerRates = getPowerRates(compExpr->getChildren()[0], var);
      ArgumentsPtrVector roots;

      switch (powerRates.size()) {
      case 2:
        roots = solveLinearEquation(powerRates);
        break;
      case 3:
        roots = solveQuadraticEquation(powerRates);
        break;
      case 4:
        roots = solveCubicEquation(powerRates);
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

shared_ptr<const INumber> getPowOfElement(const ArgumentPtr &elem, const shared_ptr<const Variable> &v) {
  if (const auto var = cast<Variable>(elem); var && *var == *v) {
    return cast<INumber>(ONE.clone());
  }

  if (const auto expr = cast<IExpression>(elem)) {
    if (is<Neg>(expr->getFunction())) {
      return getPowOfElement(expr->getChildren().front(), v);
    }

    if (is<Mul>(expr->getFunction())) {
      return getPowOfMulElement(expr, v);
    }

    if (is<Pow>(expr->getFunction())) {
      if (const auto var = cast<Variable>(expr->getChildren().front()); var && *var == *v) {
        return cast<INumber>(expr->getChildren()[1]);
      }
    }
  }

  return cast<INumber>(ZERO.clone());
}

shared_ptr<const INumber> getPowOfMulElement(const shared_ptr<const IExpression> &elem,
                                             const shared_ptr<const Variable> &v) {
  for (const auto &child : elem->getChildren()) {
    if (auto powValue = getPowOfElement(child, v); *powValue != ZERO) {
      return powValue;
    }
  }
  return cast<INumber>(ZERO.clone());
}

ArgumentPtr getElementRate(const ArgumentPtr &elem, const shared_ptr<const Variable> &v) {
  if (const auto elemExpr = cast<IExpression>(elem)) {
    if (is<Neg>(elemExpr->getFunction())) {
      return makeFunctionExpression(Neg(), {getElementRate(elemExpr->getChildren().front(), v)});
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
        coeff.emplace_back(getElementRate(child, v));
      }
      return makeFunctionExpression(Mul(), coeff);
    }
  }

  if (const auto varElem = cast<Variable>(elem); varElem && *v == *varElem) {
    return ONE.clone();
  }
  return elem;
}

ArgumentsPtrVector getPowerRates(const ArgumentPtr &rhs, const shared_ptr<const Variable> &v) {
  ArgumentsPtrVector powerRates;
  ArgumentsPtrVector polynomVect;

  if (const auto exprVal = cast<IExpression>(rhs); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(rhs);
  }

  for (const auto &elem : polynomVect) {
    ArgumentPtr rate = getElementRate(elem, v);
    shared_ptr<const INumber> pow = getPowOfElement(elem, v);
    Integer intPow = cast<Integer>(*pow);

    if (powerRates.size() < intPow + 1) {
      while (powerRates.size() != intPow + 1) {
        powerRates.emplace_back(ZERO.clone());
      }
    }

    powerRates[intPow] = rate;
  }

  return powerRates;
}

bool validatePowExpr(const shared_ptr<const IExpression> &powExpr) {
  return is<Integer>(powExpr->getChildren()[1]);
}

bool validateMulExpr(const shared_ptr<const IExpression> &mulExpr) {
  for (const auto &child : mulExpr->getChildren()) {
    if (const auto childExpr = cast<IExpression>(child);
        childExpr && is<Pow>(childExpr->getFunction()) && !validatePowExpr(childExpr)) {
      return false;
    }
  }
  return true;
}

bool validateAddExpr(const shared_ptr<const IExpression> &addExpr) {
  for (const auto &child : addExpr->getChildren()) {
    if (const auto childExpr = cast<IExpression>(child)) {
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

  if (const auto lhsExpr = cast<IExpression>(lhsVal)) {
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

ArgumentsPtrVector solveCubicEquation(const ArgumentsPtrVector & /*coeffAtPow*/) {
  return {};
}

ArgumentsPtrVector solveQuadraticEquation(const ArgumentsPtrVector &coeffAtPow) {
  static const Variable a("a");
  static const Variable b("b");
  static const Variable c("c");

  static const Expression discriminant = sub(pow(b, 2), mul(4, a, c));
  static const Expression firstRoot = div(sum(neg(b), sqrt(discriminant)), mul(2, a));
  static const Expression secondRoot = div(sub(neg(b), sqrt(discriminant)), mul(2, a));

  Expression firstRootValue = firstRoot;
  firstRootValue.setValuesOfVariables({c, b, a}, coeffAtPow);

  Expression secondRootValue = secondRoot;
  secondRootValue.setValuesOfVariables({c, b, a}, coeffAtPow);

  return {firstRootValue.getChildren().front(), secondRootValue.getChildren().front()};
}

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {makeFunctionExpression(Neg(), {makeRawFunctionExpression(Div(), {coeffAtPow[0], coeffAtPow[1]})})};
}

}
