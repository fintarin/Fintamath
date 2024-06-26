#include "fintamath/expressions/ExpressionFunctions.hpp"

#include <cstddef>
#include <memory>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/binary/CompExpr.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

using namespace detail;

namespace {

constexpr size_t maxPower = 4;

ArgumentPtrVector getPolynomCoefficients(const ArgumentPtr &elem, const Variable &var);

ArgumentPtrVector solveCubicEquation(const ArgumentPtrVector &coeffAtPow);

ArgumentPtrVector solveQuadraticEquation(const ArgumentPtrVector &coeffAtPow);

ArgumentPtrVector solveLinearEquation(const ArgumentPtrVector &coeffAtPow);

}

Expression solve(const Expression &rhs) {
  const auto compExpr = cast<CompExpr>(rhs.getChildren().front()->clone());

  if (!compExpr || compExpr->getVariables().size() != 1) {
    return rhs;
  }

  // TODO: remove this if when inequalities will be implemented
  if (!is<Eqv>(compExpr->getFunction())) {
    const auto var = cast<Variable>(*compExpr->getVariables().begin());
    const ArgumentPtrVector powerRate = getPolynomCoefficients(compExpr->getChildren().front(), var);

    if (powerRate.size() == 2) {
      compExpr->markAsSolution();
      return *compExpr;
    }

    return rhs;
  }

  const auto var = cast<Variable>(*compExpr->getVariables().begin());
  const ArgumentPtrVector powerRates = getPolynomCoefficients(compExpr->getChildren().front(), var);
  ArgumentPtrVector roots;

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
      break;
  }

  if (roots.empty()) {
    return *compExpr;
  }

  ArgumentPtrVector answers;

  for (auto &root : roots) {
    auto rootAnswer = std::make_shared<CompExpr>(Eqv{}, var.clone(), root);
    rootAnswer->markAsSolution();
    answers.emplace_back(rootAnswer);
  }

  if (answers.size() == 1) {
    return Expression(answers.front());
  }

  return Expression(orExpr(std::move(answers)));
}

namespace {

ArgumentPtrVector getPolynomCoefficients(const ArgumentPtr &elem, const Variable &var) {
  ArgumentPtrVector powers;
  ArgumentPtrVector polynomVect;

  if (const auto exprVal = cast<IExpression>(elem); exprVal && is<Add>(exprVal->getFunction())) {
    polynomVect = exprVal->getChildren();
  }
  else {
    polynomVect.emplace_back(elem);
  }

  for (const auto &polynomChild : polynomVect) {
    if (!containsVariable(polynomChild, var)) {
      powers[0] = polynomChild;
      continue;
    }

    auto [mulRate, mulValue] = splitMulExpr(polynomChild);
    auto [powBase, powValue] = splitPowExpr(mulValue);
    auto intPower = cast<Integer>(powValue);

    if (!intPower || *intPower > maxPower || *powBase != var) {
      return {};
    }

    while (powers.size() < *intPower + 1) {
      powers.emplace_back(Integer(0).clone());
    }

    powers[static_cast<size_t>(*intPower)] = mulRate;
  }

  return powers;
}

ArgumentPtrVector solveQuadraticEquation(const ArgumentPtrVector &coeffAtPow) {
  const Expression a(coeffAtPow[2]);
  const Expression b(coeffAtPow[1]);
  const Expression c(coeffAtPow[0]);

  const ArgumentPtr discriminantArg = (pow(b, 2) - (4 * a * c)).toMinimalObject();
  const Expression discriminant(discriminantArg);

  const Expression firstRoot = (-b + sqrt(discriminant)) / 2 * a;
  const Expression secondRoot = (-b - sqrt(discriminant)) / (2 * a);

  return {firstRoot.getChildren().front(), secondRoot.getChildren().front()};
}

ArgumentPtrVector solveCubicEquation(const ArgumentPtrVector & /*coeffAtPow*/) {
  return {};
}

ArgumentPtrVector solveLinearEquation(const ArgumentPtrVector &coeffAtPow) {
  return {negExpr(divExpr(coeffAtPow[0], coeffAtPow[1]))->toMinimalObject()};
}

}

}
