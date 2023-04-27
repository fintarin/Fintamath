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

shared_ptr<const INumber> getElementPower(const ArgumentPtr &elem, const shared_ptr<const Variable> &var);

shared_ptr<const INumber> getMulElementPower(const shared_ptr<const IExpression> &elem,
                                             const shared_ptr<const Variable> &var);

ArgumentPtr getElementRate(const ArgumentPtr &elem, const shared_ptr<const Variable> &var);

ArgumentsPtrVector getVariablePowerRates(const ArgumentPtr &elem, const shared_ptr<const Variable> &varar);

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
      ArgumentsPtrVector powerRate = getVariablePowerRates(compExpr->getChildren().front(), var);

      if (powerRate.size() == 2) {
        compExpr->markAsSolution();
        return *compExpr;
      }
    }
    if (is<Eqv>(compExpr->getFunction())) {
      if (!validateEquation(*compExpr)) {
        return rhs;
      }

      auto var = cast<Variable>(compExpr->getVariables().front());
      ArgumentsPtrVector powerRates = getVariablePowerRates(compExpr->getChildren()[0], var);
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

      ArgumentsPtrVector answers;

      for (auto &root : roots) {
        auto rootAnswer = make_shared<CompExpression>(Eqv(), var->clone(), root);
        rootAnswer->markAsSolution();
        answers.emplace_back(rootAnswer);
      }

      if (answers.size() == 1) {
        return Expression(answers.front());
      }

      return Expression(makeFunctionExpression(Or(), answers));
    }

    return *compExpr;
  }

  return rhs;
}

shared_ptr<const INumber> getElementPower(const ArgumentPtr &elem, const shared_ptr<const Variable> &var) {
  if (const auto elemVar = cast<Variable>(elem); elemVar && *elemVar == *var) {
    return cast<INumber>(ONE.clone());
  }

  if (const auto expr = cast<IExpression>(elem)) {
    if (is<Neg>(expr->getFunction())) {
      return getElementPower(expr->getChildren().front(), var);
    }

    if (is<Mul>(expr->getFunction())) {
      return getMulElementPower(expr, var);
    }

    if (is<Pow>(expr->getFunction())) {
      if (const auto elemVar = cast<Variable>(expr->getChildren().front()); elemVar && *elemVar == *var) {
        return cast<INumber>(expr->getChildren()[1]);
      }
    }
  }

  return cast<INumber>(ZERO.clone());
}

shared_ptr<const INumber> getMulElementPower(const shared_ptr<const IExpression> &elem,
                                             const shared_ptr<const Variable> &var) {
  for (const auto &child : elem->getChildren()) {
    if (auto powValue = getElementPower(child, var); *powValue != ZERO) {
      return powValue;
    }
  }

  return cast<INumber>(ZERO.clone());
}

ArgumentPtr getElementRate(const ArgumentPtr &elem, const shared_ptr<const Variable> &var) {
  if (const auto elemExpr = cast<IExpression>(elem)) {
    if (is<Neg>(elemExpr->getFunction())) {
      return makeFunctionExpression(Neg(), {getElementRate(elemExpr->getChildren().front(), var)});
    }

    if (is<Pow>(elemExpr->getFunction())) {
      if (hasVariable(elemExpr, var)) {
        return ONE.clone();
      }

      return elem;
    }

    if (is<Mul>(elemExpr->getFunction())) {
      ArgumentsPtrVector coeff{ONE.clone()};

      for (const auto &child : elemExpr->getChildren()) {
        coeff.emplace_back(getElementRate(child, var));
      }

      return makeFunctionExpression(Mul(), coeff);
    }
  }

  if (const auto elemVar = cast<Variable>(elem); elemVar && *var == *elemVar) {
    return ONE.clone();
  }

  return elem;
}

ArgumentsPtrVector getVariablePowerRates(const ArgumentPtr &elem, const shared_ptr<const Variable> &var) {
  ArgumentsPtrVector powerRates;
  ArgumentsPtrVector polynomVect;

  if (const auto exprVal = cast<IExpression>(elem); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(elem);
  }

  for (const auto &elem : polynomVect) {
    ArgumentPtr rate = getElementRate(elem, var);
    shared_ptr<const INumber> power = getElementPower(elem, var);
    Integer intPow = cast<Integer>(*power);

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
    if (auto childExpr = cast<IExpression>(child)) {
      if (is<Neg>(childExpr->getFunction())) {
        childExpr = cast<IExpression>(childExpr->getChildren()[0]);
      }

      if (!childExpr) {
        return true;
      }

      if (is<Pow>(childExpr->getFunction()) && !validatePowExpr(childExpr)) {
        return false;
      }

      if (is<Mul>(childExpr->getFunction()) && !validateMulExpr(childExpr)) {
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

  ArgumentPtr firstChild = expr.getChildren().front();

  if (auto firstChildExpr = cast<IExpression>(firstChild)) {
    if (is<Neg>(firstChildExpr->getFunction())) {
      firstChildExpr = cast<IExpression>(firstChildExpr->getChildren()[0]);
    }

    if (!firstChildExpr) {
      return true;
    }

    if (is<Add>(firstChildExpr->getFunction())) {
      return validateAddExpr(firstChildExpr);
    }

    if (is<Mul>(firstChildExpr->getFunction())) {
      return validateMulExpr(firstChildExpr);
    }

    if (is<Pow>(firstChildExpr->getFunction())) {
      return validatePowExpr(firstChildExpr);
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

  // TODO: remove this try/catch when complex numbers will be implemented
  try {
    Expression firstRootValue = firstRoot;
    firstRootValue.setValuesOfVariables({c, b, a}, coeffAtPow);

    Expression secondRootValue = secondRoot;
    secondRootValue.setValuesOfVariables({c, b, a}, coeffAtPow);

    return {firstRootValue.getChildren().front(), secondRootValue.getChildren().front()};
  }
  catch (const UndefinedException &) {
    return {};
  }
}

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {makeFunctionExpression(Neg(), {makeRawFunctionExpression(Div(), {coeffAtPow[0], coeffAtPow[1]})})};
}

}
