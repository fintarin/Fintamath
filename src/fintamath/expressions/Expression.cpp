#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <memory>
#include <regex>
#include <stdexcept>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

Expression::Expression(const Expression &rhs) {
  if (rhs.info) {
    info = rhs.info->clone();
  }
}

Expression::Expression() : info(ZERO.clone()) {
}

Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)) {
}

Expression &Expression::operator=(const Expression &rhs) {
  if (&rhs != this) {
    if (rhs.info) {
      info = rhs.info->clone();
    } else {
      info = nullptr;
    }
  }

  return *this;
}

Expression &Expression::operator=(Expression &&rhs) noexcept {
  if (&rhs != this) {
    std::swap(info, rhs.info);
  }

  return *this;
}

Expression::Expression(const std::string &str) : Expression(Tokenizer::tokenize(str)) {
  compress();
  validate();
  info = MathObjectPtr(simplify());
}

Expression::Expression(const TokenVector &tokens) {
  if (tokens.empty()) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }

  if (parseBinaryOperator(tokens) ||  //
      parsePrefixOperator(tokens) ||  //
      parsePostfixOperator(tokens) || //
      parseFunction(tokens) ||        //
      parseFiniteTerm(tokens)) {
    return;
  }

  if (!info) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(MathObjectPtr &&obj) {
  if (auto *expr = cast<Expression>(obj.get())) {
    *this = std::move(*expr);
  } else {
    info = std::move(obj);
  }
}

Expression::Expression(int64_t val) : info(std::make_unique<Integer>(val)) {
}

void Expression::compress() {
  if (auto *childExpr = cast<IExpression>(info.get())) {
    childExpr->compress();
  }

  while (auto *childExpr = cast<Expression>(info.get())) {
    *this = std::move(*childExpr);
  }
}

void Expression::setPrecisionRec(uint8_t precision) {
  setMathObjectPrecision(info, precision);
}

MathObjectPtr &Expression::getChild() {
  return info;
}

const MathObjectPtr &Expression::getInfo() const {
  return info;
}

std::string Expression::toString() const {
  return info ? info->toString() : "";
}

std::string Expression::toString(uint8_t precision) const {
  auto expr = Expression(*simplify(false));
  expr.setPrecision(precision);
  return expr.toString();
}

bool Expression::parsePrefixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.front(), IOperator::Priority::PrefixUnary)) {
    auto rhsExpr = ExpressionPtr(new Expression(TokenVector(tokens.begin() + 1, tokens.end())));
    auto funcExpr = makeRawFunctionExpression(*oper, makeArgumentsPtrVector(std::move(rhsExpr)));

    if (auto *expr = cast<Expression>(funcExpr.get())) {
      *this = std::move(*expr);
    } else {
      info = std::move(funcExpr);
    }

    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.back(), IOperator::Priority::PostfixUnary)) {
    int64_t order = 1;

    if (auto *factor = cast<Factorial>(oper.get())) {
      for (; order < tokens.size(); order++) {
        if (tokens[tokens.size() - order - 1] != oper->toString()) {
          break;
        }
      }

      factor->setOrder(order);
    }

    auto rhsExpr = ExpressionPtr(new Expression(TokenVector(tokens.begin(), tokens.end() - order)));
    auto funcExpr = makeRawFunctionExpression(*oper, makeArgumentsPtrVector(std::move(rhsExpr)));

    if (auto *expr = cast<Expression>(funcExpr.get())) {
      *this = std::move(*expr);
    } else {
      info = std::move(funcExpr);
    }

    return true;
  }

  return false;
}

bool Expression::parseBinaryOperator(const TokenVector &tokens) {
  auto operMap = findBinaryOperators(tokens);

  if (operMap.empty()) {
    return false;
  }

  auto foundOperIt = operMap.begin();
  auto foundIndex = foundOperIt->first;
  auto foundPriority = cast<IOperator>(foundOperIt->second.get())->getOperatorPriority();

  auto it = operMap.begin();
  ++it;

  for (; it != operMap.end(); ++it) {
    auto index = it->first;
    auto priority = cast<IOperator>(it->second.get())->getOperatorPriority();

    if (foundPriority < priority || (foundPriority == priority && foundIndex < index)) {
      foundPriority = priority;
      foundOperIt = it;
    }
  }

  auto operPos = int64_t(foundOperIt->first);
  if (operPos < 1 || operPos >= tokens.size()) {
    return false;
  }

  auto lhsExpr = ExpressionPtr(new Expression(TokenVector(tokens.begin(), tokens.begin() + operPos)));
  auto rhsExpr = ExpressionPtr(new Expression(TokenVector(tokens.begin() + operPos + 1, tokens.end())));
  auto funcExpr = makeRawFunctionExpression(cast<IFunction>(*foundOperIt->second),
                                            makeArgumentsPtrVector(std::move(lhsExpr), std::move(rhsExpr)));

  if (auto *expr = cast<Expression>(funcExpr.get())) {
    *this = std::move(*expr);
  } else {
    info = std::move(funcExpr);
  }

  return true;
}

bool Expression::parseFiniteTerm(const TokenVector &tokens) {
  if (tokens.front() == "(" && tokens.at(tokens.size() - 1) == ")") {
    *this = Expression(cutBraces(tokens));
    return true;
  }

  if (tokens.size() > 1) {
    return false;
  }

  if (auto ptr = ILiteral::parse(tokens.front())) {
    info = std::unique_ptr<ILiteral>(ptr.release());
    return true;
  }

  if (auto ptr = INumber::parse(tokens.front())) {
    info = std::unique_ptr<INumber>(ptr.release());
    return true;
  }

  return false;
}

bool Expression::parseFunction(const TokenVector &tokens) {
  if (tokens.size() <= 1) {
    return false;
  }

  if (auto ptr = IFunction::parse(tokens.front()); ptr && !is<IOperator>(ptr)) {
    info = std::make_unique<FunctionExpression>(*ptr, getArgs(TokenVector(tokens.begin() + 1, tokens.end())));
    return true;
  }

  return false;
}

MathObjectPtr Expression::makeFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args) {
  auto expr = cast<IMathObject>(makeRawFunctionExpression(func, std::move(args)));
  simplifyExpr(expr);
  return expr;
}

ExpressionPtr Expression::makeRawFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args) {
  if (auto expr = Parser::parse(expressionBuildersMap, func.toString(), std::move(args))) {
    return expr;
  }

  auto funcExpr = std::make_unique<Expression>();
  funcExpr->info = std::make_unique<FunctionExpression>(func, std::move(args));
  return funcExpr;
}

const IFunction *Expression::getFunction() const {
  if (const auto *funcExpr = cast<IExpression>(info.get())) {
    return funcExpr->getFunction();
  }

  return nullptr;
}

ArgumentsPtrVector Expression::getArgs(const TokenVector &tokens) {
  ArgumentsPtrVector args;

  for (size_t pos = 0; pos < tokens.size(); pos++) {
    bool isBracketsSkip = false;
    if (tokens.at(pos) == "(") {
      if (pos == 0) {
        isBracketsSkip = true;
      }

      skipBrackets(tokens, pos);
    }

    if (pos == tokens.size()) {
      if (isBracketsSkip) {
        return getArgs(cutBraces(tokens));
      }
      break;
    }

    if (tokens.at(pos) == ",") {
      if (pos == 0 || pos == tokens.size() - 1) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

      args.emplace_back(
          std::unique_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.begin() + int64_t(pos)))));
      auto addArgs = getArgs(TokenVector(tokens.begin() + int64_t(pos) + 1, tokens.end()));

      for (auto &token : addArgs) {
        args.push_back(MathObjectPtr(token.release()));
      }

      return args;
    }
  }

  args.emplace_back(std::unique_ptr<Expression>(new Expression(tokens)));

  return args;
}

Expression &Expression::add(const Expression &rhs) {
  MathObjectPtr expr = makeFunctionExpression(
      Add(), makeArgumentsPtrVector(std::make_unique<Expression>(std::move(*this)), rhs.clone()));
  return *this = Expression(std::move(expr));
}

Expression &Expression::substract(const Expression &rhs) {
  MathObjectPtr expr = makeFunctionExpression(
      Sub(), makeArgumentsPtrVector(std::make_unique<Expression>(std::move(*this)), rhs.clone()));
  return *this = Expression(std::move(expr));
}

Expression &Expression::multiply(const Expression &rhs) {
  MathObjectPtr expr = makeFunctionExpression(
      Mul(), makeArgumentsPtrVector(std::make_unique<Expression>(std::move(*this)), rhs.clone()));
  return *this = Expression(std::move(expr));
}

Expression &Expression::divide(const Expression &rhs) {
  MathObjectPtr expr = makeFunctionExpression(
      Div(), makeArgumentsPtrVector(std::make_unique<Expression>(std::move(*this)), rhs.clone()));
  return *this = Expression(std::move(expr));
}

Expression &Expression::negate() {
  MathObjectPtr expr = makeFunctionExpression(Neg(), makeArgumentsPtrVector(std::make_unique<Expression>(*this)));
  return *this = Expression(std::move(expr));
}

void Expression::validate() const {
  if (const auto *expr = cast<IExpression>(info.get())) {
    expr->validate();
  }
}

void Expression::setPrecision(uint8_t precision) {
  setPrecisionRec(precision);
}

MathObjectPtr Expression::simplify(bool isPrecise) const {
  Expression expr = *this;

  // simplifyValue(isPrecise, expr.info);
  return std::move(expr.info);
}

std::string Expression::solve(uint8_t precision) const {
  if (const auto *expr = cast<CompExpression>(info.get())) {
    return expr->solve(precision);
  }

  return toString(precision);
}

std::string Expression::solve() const {
  if (const auto *expr = cast<CompExpression>(info.get())) {
    return expr->solve();
  }

  return toString();
}

std::vector<MathObjectPtr> Expression::getVariables() const {
  std::vector<MathObjectPtr> result;

  if (is<Variable>(info)) {
    result.emplace_back(info->clone());
    return result;
  }

  if (const auto *expr = cast<IExpression>(info.get())) {
    auto addResult = expr->getVariables();
    for (const auto &add : addResult) {
      result.emplace_back(add->clone());
    }
    return result;
  }

  return result;
}

IMathObject *Expression::simplify() {
  simplifyExpr(info);
  callPowSimplify();
  return info.release();
}

void Expression::callPowSimplify() {
  if (is<PowExpression>(info)) {
    auto *powExpr = cast<PowExpression>(info.release());
    info = MathObjectPtr(powExpr->mulSimplify());
  }
  if (is<PowExpression>(info)) {
    auto *powExpr = cast<PowExpression>(info.release());
    info = MathObjectPtr(powExpr->sumSimplify());
  }
}

}
