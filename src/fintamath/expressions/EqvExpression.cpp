#include "fintamath/expressions/EqvExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include <algorithm>
#include <cstdint>
#include <ios>

namespace fintamath {

EqvExpression::EqvExpression(const TokenVector &tokens) {
  parse(tokens);
}

EqvExpression::EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs) {
  if (!oper.instanceOf<IOperator>() || oper.to<IOperator>().getOperatorPriority() != IOperator::Priority::Comparison) {
    throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
  }
  if (lhs.is<EqvExpression>() || rhs.is<EqvExpression>()) {
    throw UndefinedBinaryOpearatorException(oper.toString(), lhs.toString(), rhs.toString());
  }

  this->oper = oper.clone();
  leftExpr = lhs.clone();
  rightExpr = rhs.clone();
}

EqvExpression::EqvExpression(const EqvExpression &rhs) noexcept {
  leftExpr = rhs.leftExpr->clone();
  rightExpr = rhs.rightExpr->clone();
  oper = rhs.oper->clone();
}

EqvExpression::EqvExpression(EqvExpression &&rhs) noexcept {
  leftExpr = rhs.leftExpr->clone();
  rightExpr = rhs.rightExpr->clone();
  oper = rhs.oper->clone();
}

EqvExpression &EqvExpression::operator=(const EqvExpression &rhs) noexcept {
  if (&rhs != this) {
    leftExpr = rhs.leftExpr->clone();
    rightExpr = rhs.rightExpr->clone();
    oper = rhs.oper->clone();
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
  return leftExpr->toString() + oper->toString() + rightExpr->toString();
}

MathObjectPtr EqvExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr EqvExpression::simplify(bool isPrecise) const {
  auto cloneExpr = *this;
  AddExpression addExpr;
  addExpr.addElement(AddExpression::Element(cloneExpr.leftExpr->clone()));
  addExpr.addElement(AddExpression::Element(cloneExpr.rightExpr->clone(), true));
  cloneExpr.leftExpr = addExpr.simplify(isPrecise);
  cloneExpr.rightExpr = Integer(0).clone();

  if (cloneExpr.leftExpr->instanceOf<IComparable>()) {
    auto b = Expression(oper->to<IOperator>()(*cloneExpr.leftExpr, *cloneExpr.rightExpr));
    return b.simplify(isPrecise);
  }
  return cloneExpr.clone();
}

uint16_t EqvExpression::getInfoPriority() {
  return (uint16_t)IOperator::Priority::Comparison;
}

void EqvExpression::parse(const TokenVector &tokens) {
  bool eqvOpers = false;
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i] == "<" || tokens[i] == "<=" || tokens[i] == "=" || tokens[i] == ">=" || tokens[i] == ">") {
      if (eqvOpers) {
        throw InvalidInputException(" number of comparison operators exceeded");
      }
      eqvOpers = true;
    }
  }

  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i] == "(" && !skipBrackets(tokens, i)) {
      throw InvalidInputException(" braces must be closed");
    }
    if (i == tokens.size()) {
      break;
    }
    if (tokens[i] != "<" && tokens[i] != "<=" && tokens[i] != "=" && tokens[i] != ">=" && tokens[i] != ">") {
      continue;
    }
    if (i == tokens.size() - 1) {
      throw InvalidInputException(" unexpected sign");
    }

    leftExpr = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i));
    rightExpr = IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end()));
    oper = IOperator::parse(tokens[i]);

    if (!leftExpr || !rightExpr || !oper) {
      throw InvalidInputException(tokensToString(tokens));
    }
    return;
  }
  throw InvalidInputException(" not an EqvExpression");
}

void EqvExpression::setPrecision(uint8_t precision) {
  if (leftExpr->instanceOf<IExpression>()) {
    auto copyExpr = helpers::cast<IExpression>(leftExpr);
    copyExpr->setPrecision(precision);
    leftExpr = copyExpr->clone();
  }
}

std::string EqvExpression::solve() const {
  Variable x("x");
  auto expr = simplify(false);
  if (!expr->is<EqvExpression>()) {
    return expr->toString();
  }
  auto copyExpr = expr->to<EqvExpression>();
  if (!copyExpr.oper->is<Eqv>()) {
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
  if (!expr->is<EqvExpression>()) {
    return expr->toString();
  }
  auto copyExpr = expr->to<EqvExpression>();
  if (!copyExpr.oper->is<Eqv>()) {
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

std::vector<MathObjectPtr> EqvExpression::solvePowEquation(const Variable &x) const {
  auto results = solveQuadraticEquation(x.clone());
  return results;
}

std::vector<MathObjectPtr> EqvExpression::solveQuadraticEquation(const MathObjectPtr &v) const {
  auto copyExpr = *this;

  AddExpression polynom(*leftExpr);
  auto maxPow = polynom.getPow();

  if (!maxPow->is<Integer>() || maxPow->to<Integer>() > Integer(2)) {
    return {};
  }

  std::vector<MathObjectPtr> coefficients;

  for (int i = 0; i <= maxPow->to<Integer>(); i++) {
    coefficients.emplace_back(polynom.getPowCoefficient(Integer(i).clone()));
  }

  std::vector<MathObjectPtr> results;
  if (coefficients.size() == 2) {
    results.emplace_back(Neg()(*div(*coefficients.at(0), *coefficients.at(1)).simplify(false)));
    return results;
  }
  if (coefficients.size() == 3) {
    auto discr =
        (fintamath::pow(*coefficients.at(1), Integer(2)) - mul(Integer(4), *coefficients.at(0), *coefficients.at(2)))
            .simplify(false);

    if (discr->instanceOf<IComparable>() && discr->to<IComparable>() < Integer(0)) {
      return {};
    }

    auto sqrt_D = sqrt(*discr);
    auto minus_B = Neg()(*coefficients.at(1));
    auto two_A = mul(*coefficients.at(2), Integer(2));

    auto x1 = div(sub(*minus_B, sqrt_D), two_A).simplify(false);
    auto x2 = div(add(*minus_B, sqrt_D), two_A).simplify(false);

    results.emplace_back(std::move(x1));
    results.emplace_back(std::move(x2));

    return results;
  }
  return results;
}

bool EqvExpression::detectOneVariable(Variable &v) const {
  if (leftExpr->is<Variable>()) {
    v = leftExpr->to<Variable>();
    return true;
  }
  if (leftExpr->instanceOf<IExpression>()) {
    auto variables = leftExpr->to<IExpression>().getVariables();
    if (variables.empty()) {
      return false;
    }
    v = variables.at(0)->to<Variable>();
    for (const auto &var : variables) {
      if (var->toString() != v.toString()) {
        return false;
      }
    }
    return true;
  }
}

bool EqvExpression::sortPredicat(const MathObjectPtr &lhs, const MathObjectPtr &rhs) {
  if (!lhs->instanceOf<IComparable>() || !rhs->instanceOf<IComparable>()) {
    return false;
  }
  return lhs->to<IComparable>() < rhs->to<IComparable>();
}

std::vector<MathObjectPtr> EqvExpression::sortResult(std::vector<MathObjectPtr> &result) {
  std::sort(result.begin(), result.end(), sortPredicat);
  std::vector<MathObjectPtr> resultWithoutRepeat;
  for (const auto &val : result) {
    if (resultWithoutRepeat.empty()) {
      resultWithoutRepeat.emplace_back(val->clone());
      continue;
    }
    if (val->to<IComparable>() == resultWithoutRepeat.at(resultWithoutRepeat.size() - 1)->to<IComparable>()) {
      continue;
    }
    resultWithoutRepeat.emplace_back(val->clone());
  }
  return resultWithoutRepeat;
}

}