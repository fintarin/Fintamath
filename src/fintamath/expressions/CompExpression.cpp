#include "fintamath/expressions/CompExpression.hpp"

#include <algorithm>
#include <cstdint>
#include <ios>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/NegExpression.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

CompExpression::CompExpression(const IMathObject &oper, MathObjectPtr &&lhs, MathObjectPtr &&rhs) {
  if (is<CompExpression>(lhs) || is<CompExpression>(rhs)) {
    throw UndefinedBinaryOpearatorException(oper.toString(), lhs->toString(), rhs->toString());
  }

  this->oper = cast<IOperator>(oper.clone());
  leftExpr = std::move(lhs);
  rightExpr = std::move(rhs);
}

CompExpression::CompExpression(const CompExpression &rhs)
    : leftExpr(rhs.leftExpr->clone()),
      rightExpr(rhs.rightExpr->clone()),
      oper(cast<IOperator>(rhs.oper->clone())) {
}

CompExpression::CompExpression(CompExpression &&rhs) noexcept
    : leftExpr(std::move(rhs.leftExpr)),
      rightExpr(std::move(rhs.rightExpr)),
      oper(std::move(rhs.oper)) {
}

CompExpression &CompExpression::operator=(const CompExpression &rhs) {
  if (&rhs != this) {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = cast<IOperator>(rhs.oper->clone());
  }

  return *this;
}

CompExpression &CompExpression::operator=(CompExpression &&rhs) noexcept {
  if (&rhs != this) {
    std::swap(leftExpr, rhs.leftExpr);
    std::swap(rightExpr, rhs.rightExpr);
    std::swap(oper, rhs.oper);
  }

  return *this;
}

std::string CompExpression::toString() const {
  return leftExpr->toString() + ' ' + oper->toString() + ' ' + rightExpr->toString();
}

MathObjectPtr CompExpression::toMinimalObject() const {
  return simplify(true);
}

MathObjectPtr CompExpression::simplify(bool isPrecise) const {
  SumExpression addExpr(*leftExpr->clone());
  addExpr.addElement(NegExpression(*rightExpr).toMinimalObject());

  MathObjectPtr simplExpr = addExpr.simplify(isPrecise);

  if (is<IComparable>(simplExpr)) {
    return (*oper)(*simplExpr, ZERO);
  }

  auto res = std::make_unique<CompExpression>(*this);
  res->leftExpr = std::move(simplExpr);
  res->rightExpr = ZERO.clone();
  return res;
}

void CompExpression::compress() {
  if (auto *childExpr = cast<Expression>(leftExpr.get()); childExpr && childExpr->getChildren().empty()) {
    leftExpr = std::move(childExpr->getInfo());
  }
  if (auto *childExpr = cast<Expression>(rightExpr.get()); childExpr && childExpr->getChildren().empty()) {
    rightExpr = std::move(childExpr->getInfo());
  }
}

void CompExpression::validate() const {
  if (const auto *childExpr = cast<IExpression>(leftExpr.get())) {
    childExpr->validate();
  }
  if (const auto *childExpr = cast<IExpression>(rightExpr.get())) {
    childExpr->validate();
  }

  this->validateArgs(*getFunction(), {*leftExpr, *rightExpr});
}

void CompExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(leftExpr.get())) {
    expr->setPrecision(precision);
  }
}

std::string CompExpression::solve() const {
  return "Remove this"; // TODO: remove this
  Variable x("x");
  auto expr = simplify(false);
  if (!is<CompExpression>(expr)) {
    return expr->toString();
  }
  auto copyExpr = cast<CompExpression>(*expr);
  if (!is<Eqv>(copyExpr.oper)) {
    return expr->toString();
  }
  if (!copyExpr.detectOneVariable(x)) {
    return toString();
  }

  auto results = copyExpr.solvePowEquation(x);
  if (results.empty()) {
    return toString();
  }
  results = sortResult(results);
  std::string resultStr = x.toString() + " in {";
  for (const auto &res : results) {
    resultStr += res->toString();
    resultStr += ",";
  }
  resultStr.pop_back();
  resultStr += "}";
  return resultStr;
}

std::string CompExpression::solve(uint8_t precision) const {
  return "Remove this"; // TODO: remove this
  Variable x("x");
  auto expr = simplify(false);
  if (!is<CompExpression>(expr)) {
    return expr->toString();
  }
  auto copyExpr = cast<CompExpression>(*expr);
  if (!is<Eqv>(copyExpr.oper)) {
    return expr->toString();
  }
  if (!copyExpr.detectOneVariable(x)) {
    auto e = *this;
    e.setPrecision(precision);
    return e.toString();
  }

  auto results = copyExpr.solvePowEquation(x);
  if (results.empty()) {
    auto e = *this;
    e.setPrecision(precision);
    return e.toString();
  }
  results = sortResult(results);
  std::string resultStr = x.toString() + " in {";
  for (const auto &res : results) {
    resultStr += Expression(*res).toString(precision);
    resultStr += ",";
  }
  resultStr.pop_back();
  resultStr += "}";
  return resultStr;
}

const IFunction *CompExpression::getFunction() const {
  return oper.get();
}

std::vector<MathObjectPtr> CompExpression::solvePowEquation(const Variable &x) const {
  auto results = solveQuadraticEquation(x.clone());
  return results;
}

// TODO: v is unused here
std::vector<MathObjectPtr> CompExpression::solveQuadraticEquation(const MathObjectPtr &v) const {
  auto copyExpr = *this;
  SumExpression polynom;
  polynom.addElement({leftExpr->clone()});

  auto maxPowObj = polynom.getPow();
  if (!maxPowObj) {
    return {};
  }

  const auto *maxPow = cast<Integer>(maxPowObj.get());
  if (*maxPow > TWO) {
    return {};
  }

  std::vector<MathObjectPtr> coefficients;
  for (int i = 0; i <= *maxPow; i++) {
    coefficients.emplace_back(polynom.getPowCoefficient(Integer(i).clone()));
  }

  std::vector<MathObjectPtr> results;
  if (coefficients.size() == 2) {
    results.emplace_back(Neg()(*div(*coefficients.at(0), *coefficients.at(1)).simplify(false)));
    return results;
  }
  if (coefficients.size() == 3) {
    auto discr = (fintamath::pow(*coefficients.at(1), TWO) - mul(Integer(4), *coefficients.at(0), *coefficients.at(2)))
                     .simplify(false);

    if (const auto *discrPtr = cast<Integer>(discr.get()); discrPtr && *discrPtr < ZERO) {
      return {};
    }

    auto sqrt_D = sqrt(*discr);
    auto minus_B = Neg()(*coefficients.at(1));
    auto two_A = mul(*coefficients.at(2), TWO);

    auto x1 = div(sub(*minus_B, sqrt_D), two_A).simplify(false);
    auto x2 = div(sum(*minus_B, sqrt_D), two_A).simplify(false);

    results.emplace_back(std::move(x1));
    results.emplace_back(std::move(x2));

    return results;
  }
  return results;
}

bool CompExpression::detectOneVariable(Variable &v) const {
  if (const auto *var = cast<Variable>(leftExpr.get())) {
    v = *var;
    return true;
  }
  if (const auto *expr = cast<IExpression>(leftExpr.get())) {
    auto variables = expr->getVariables();
    if (variables.empty()) {
      return false;
    }
    v = cast<Variable>(*variables.at(0).get());
    for (const auto &var : variables) {
      if (var->toString() != v.toString()) {
        return false;
      }
    }
    return true;
  }
}

bool CompExpression::sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs) {
  if (const auto *lhsComp = cast<IComparable>(lhs.get())) {
    if (const auto *rhsComp = cast<IComparable>(rhs.get())) {
      return *lhsComp < *rhsComp;
    }
  }

  return false;
}

std::vector<MathObjectPtr> CompExpression::sortResult(std::vector<MathObjectPtr> &result) {
  std::sort(result.begin(), result.end(), sortFunc);
  std::vector<MathObjectPtr> resultWithoutRepeat;
  for (auto &val : result) {
    if (resultWithoutRepeat.empty()) {
      resultWithoutRepeat.emplace_back(std::move(val));
      continue;
    }
    if (*val == *resultWithoutRepeat.at(resultWithoutRepeat.size() - 1)) {
      continue;
    }
    resultWithoutRepeat.emplace_back(std::move(val));
  }
  return resultWithoutRepeat;
}

}