#include "fintamath/expressions/EqvExpression.hpp"

#include <algorithm>
#include <cstdint>
#include <ios>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

EqvExpression::EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs) {
  if (const auto *operPtr = cast<IOperator>(&oper);
      !operPtr || operPtr->getOperatorPriority() != IOperator::Priority::Comparison) {
    throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
  }

  if (is<EqvExpression>(lhs) || is<EqvExpression>(rhs)) {
    throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
  }

  this->oper = cast<IOperator>(oper.clone());
  leftExpr = lhs.clone();
  rightExpr = rhs.clone();
}

EqvExpression::EqvExpression(const EqvExpression &rhs) noexcept {
  leftExpr = rhs.leftExpr->clone();
  rightExpr = rhs.rightExpr->clone();
  oper = cast<IOperator>(rhs.oper->clone());
}

EqvExpression::EqvExpression(EqvExpression &&rhs) noexcept {
  leftExpr = rhs.leftExpr->clone();
  rightExpr = rhs.rightExpr->clone();
  oper = cast<IOperator>(rhs.oper->clone());
}

EqvExpression &EqvExpression::operator=(const EqvExpression &rhs) noexcept {
  if (&rhs != this) {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = cast<IOperator>(rhs.oper->clone());
  }
  return *this;
}

EqvExpression &EqvExpression::operator=(EqvExpression &&rhs) noexcept {
  if (&rhs != this) {
    std::swap(leftExpr, rhs.leftExpr);
    std::swap(rightExpr, rhs.rightExpr);
    std::swap(oper, rhs.oper);
  }
  return *this;
}

std::string EqvExpression::toString() const {
  return leftExpr->toString() + ' ' + oper->toString() + ' ' + rightExpr->toString();
}

MathObjectPtr EqvExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr EqvExpression::simplify(bool isPrecise) const {
  auto cloneExpr = *this;
  SumExpression addExpr;
  addExpr.addElement({cloneExpr.leftExpr->clone()});
  addExpr.addElement({cloneExpr.rightExpr->clone(), true});
  cloneExpr.leftExpr = addExpr.simplify(isPrecise);
  cloneExpr.rightExpr = ZERO.clone();

  if (cast<IComparable>(cloneExpr.leftExpr.get())) {
    auto res = Expression(cast<IOperator>(*oper)(*cloneExpr.leftExpr, *cloneExpr.rightExpr));
    return res.simplify(isPrecise);
  }

  return cloneExpr.clone();
}

void EqvExpression::setPrecision(uint8_t precision) {
  if (is<IExpression>(leftExpr)) {
    auto copyExpr = cast<IExpression>(std::move(leftExpr));
    copyExpr->setPrecision(precision);
    leftExpr = copyExpr->clone();
  }
}

std::string EqvExpression::solve() const {
  Variable x("x");
  auto expr = simplify(false);
  if (!is<EqvExpression>(expr)) {
    return expr->toString();
  }
  auto copyExpr = cast<EqvExpression>(*expr);
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

std::string EqvExpression::solve(uint8_t precision) const {
  Variable x("x");
  auto expr = simplify(false);
  if (!is<EqvExpression>(expr)) {
    return expr->toString();
  }
  auto copyExpr = cast<EqvExpression>(*expr);
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

const IFunction *EqvExpression::getFunction() const {
  return oper.get();
}

std::vector<MathObjectPtr> EqvExpression::solvePowEquation(const Variable &x) const {
  auto results = solveQuadraticEquation(x.clone());
  return results;
}

std::vector<MathObjectPtr> EqvExpression::solveQuadraticEquation(const MathObjectPtr &v) const {
  auto copyExpr = *this;
  SumExpression polynom(*leftExpr);

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

bool EqvExpression::detectOneVariable(Variable &v) const {
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

bool EqvExpression::sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs) {
  if (const auto *lhsComp = cast<IComparable>(lhs.get())) {
    if (const auto *rhsComp = cast<IComparable>(rhs.get())) {
      return *lhsComp < *rhsComp;
    }
  }

  return false;
}

std::vector<MathObjectPtr> EqvExpression::sortResult(std::vector<MathObjectPtr> &result) {
  std::sort(result.begin(), result.end(), sortFunc);
  std::vector<MathObjectPtr> resultWithoutRepeat;
  for (const auto &val : result) {
    if (resultWithoutRepeat.empty()) {
      resultWithoutRepeat.emplace_back(val->clone());
      continue;
    }
    if (*val == *resultWithoutRepeat.at(resultWithoutRepeat.size() - 1)) {
      continue;
    }
    resultWithoutRepeat.emplace_back(val->clone());
  }
  return resultWithoutRepeat;
}

}