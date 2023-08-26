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

const Variable a("a");
const Variable b("b");
const Variable c("c");

std::shared_ptr<const INumber> getElementPower(const ArgumentPtr &elem, const Variable &var);

std::shared_ptr<const INumber> getMulElementPower(const std::shared_ptr<const IExpression> &elem, const Variable &var);

ArgumentPtr getElementRate(const ArgumentPtr &elem, const Variable &var);

ArgumentsPtrVector getVariableIntPowerRates(const ArgumentPtr &elem, const Variable &var);

ArgumentsPtrVector solveCubicEquation(const ArgumentsPtrVector &coeffAtPow);

ArgumentsPtrVector solveQuadraticEquation(const ArgumentsPtrVector &coeffAtPow);

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow);

Expression solve(const Expression &rhs) {
  if (auto compExpr = cast<CompExpression>(rhs.getChildren().front()->clone())) {
    if (compExpr->getVariables().size() != 1) {
      return rhs;
    }

    // TODO: remove this if when inequalities will be implemented
    if (!is<Eqv>(compExpr->getFunction())) {
      auto var = cast<Variable>(compExpr->getVariables().front());
      ArgumentsPtrVector powerRate = getVariableIntPowerRates(compExpr->getChildren().front(), var);

      if (powerRate.size() == 2) {
        compExpr->markAsSolution();
        return *compExpr;
      }
    }
    if (is<Eqv>(compExpr->getFunction())) {
      auto var = cast<Variable>(compExpr->getVariables().front());
      ArgumentsPtrVector powerRates = getVariableIntPowerRates(compExpr->getChildren().front(), var);
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
        auto rootAnswer = std::make_shared<CompExpression>(Eqv(), var.clone(), root);
        rootAnswer->markAsSolution();
        answers.emplace_back(rootAnswer);
      }

      if (answers.size() == 1) {
        return Expression(answers.front());
      }

      return Expression(orExpr(answers));
    }
  }

  return rhs;
}

std::shared_ptr<const INumber> getElementPower(const ArgumentPtr &elem, const Variable &var) {
  if (const auto elemVar = cast<Variable>(elem); elemVar && *elemVar == var) {
    return cast<INumber>(std::make_shared<Integer>(1));
  }

  if (const auto expr = cast<IExpression>(elem)) {
    if (is<Mul>(expr->getFunction())) {
      return getMulElementPower(expr, var);
    }

    if (is<Pow>(expr->getFunction())) {
      if (const auto elemVar = cast<Variable>(expr->getChildren().front()); elemVar && *elemVar == var) {
        return cast<INumber>(expr->getChildren().back());
      }
    }
  }

  return cast<INumber>(std::make_shared<Integer>(0));
}

std::shared_ptr<const INumber> getMulElementPower(const std::shared_ptr<const IExpression> &elem, const Variable &var) {
  for (const auto &child : elem->getChildren()) {
    if (auto powValue = getElementPower(child, var); *powValue != Integer(0)) {
      return powValue;
    }
  }

  return std::make_shared<Integer>(0);
}

ArgumentPtr getElementRate(const ArgumentPtr &elem, const Variable &var) {
  if (const auto elemExpr = cast<IExpression>(elem)) {
    if (is<Pow>(elemExpr->getFunction())) {
      if (hasVariable(elemExpr, var)) {
        return std::make_shared<Integer>(1);
      }

      return elem;
    }

    if (is<Mul>(elemExpr->getFunction())) {
      ArgumentsPtrVector coeff{std::make_shared<Integer>(1)};

      for (const auto &child : elemExpr->getChildren()) {
        coeff.emplace_back(getElementRate(child, var));
      }

      return mulExpr(coeff)->toMinimalObject();
    }
  }

  if (const auto elemVar = cast<Variable>(elem); elemVar && var == *elemVar) {
    return std::make_shared<Integer>(1);
  }

  return elem;
}

ArgumentsPtrVector getVariableIntPowerRates(const ArgumentPtr &elem, const Variable &var) {
  ArgumentsPtrVector powerRates;
  ArgumentsPtrVector polynomVect;

  if (const auto exprVal = cast<IExpression>(elem); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(elem);
  }

  for (const auto &polynomChild : polynomVect) {
    ArgumentPtr rate = getElementRate(polynomChild, var);
    std::shared_ptr<const INumber> power = getElementPower(polynomChild, var);

    if (auto intPow = cast<Integer>(power)) {
      if (int64_t(powerRates.size()) < *intPow + 1) {
        while (int64_t(powerRates.size()) != *intPow + 1) {
          powerRates.emplace_back(std::make_shared<Integer>(0));
        }
      }

      powerRates[size_t(*intPow)] = rate;
    }
    else {
      return {};
    }
  }

  return powerRates;
}

ArgumentsPtrVector solveCubicEquation(const ArgumentsPtrVector & /*coeffAtPow*/) {
  return {};
}

ArgumentsPtrVector solveQuadraticEquation(const ArgumentsPtrVector &coeffAtPow) {
  static const Expression discriminant = sub(pow(b, 2), mul(4, a, c));
  static const Expression firstRoot = div(add(neg(b), sqrt(discriminant)), mul(2, a));
  static const Expression secondRoot = div(sub(neg(b), sqrt(discriminant)), mul(2, a));

  Expression firstRootValue = firstRoot;
  firstRootValue.setVariables({
      {c, coeffAtPow[0]},
      {b, coeffAtPow[1]},
      {a, coeffAtPow[2]},
  });

  Expression secondRootValue = secondRoot;
  secondRootValue.setVariables({
      {c, coeffAtPow[0]},
      {b, coeffAtPow[1]},
      {a, coeffAtPow[2]},
  });

  return {firstRootValue.getChildren().front(), secondRootValue.getChildren().front()};
}

ArgumentsPtrVector solveLinearEquation(const ArgumentsPtrVector &coeffAtPow) {
  return {negExpr(divExpr(coeffAtPow[0], coeffAtPow[1]))->toMinimalObject()};
}

}
