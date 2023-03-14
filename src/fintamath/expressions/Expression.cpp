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

Expression::Expression() : child(ZERO.clone()) {
}

Expression::Expression(const std::string &str) : Expression(Tokenizer::tokenize(str)) {
  validate();
  simplifyChild(child);
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

  if (!child) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }
}

Expression::Expression(const std::shared_ptr<IMathObject> &obj) {
  if (auto expr = cast<Expression>(obj)) {
    child = expr->child;
  }
  else {
    child = obj;
    simplifyChild(child);
  }
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(int64_t val) : child(std::make_shared<Integer>(val)) {
}

std::unique_ptr<IMathObject> Expression::toMinimalObject() const {
  return child->clone();
}

// void Expression::setPrecisionRec(uint8_t precision) {
//   setMathObjectPrecision(child, precision);
// }

std::string Expression::toString() const {
  return child->toString();
}

Expression Expression::precise(size_t precision) const {
  assert(precision <= FINTAMATH_ROUND_PRECISION);
  return *this;
}

bool Expression::parsePrefixOperator(const TokenVector &tokens) {
  if (std::shared_ptr<IOperator> oper = IOperator::parse(tokens.front(), IOperator::Priority::PrefixUnary)) {
    auto rhsExpr = std::shared_ptr<Expression>(new Expression(TokenVector(tokens.begin() + 1, tokens.end())));
    std::shared_ptr<IExpression> funcExpr = makeRawFunctionExpression(*oper, {rhsExpr});

    if (auto expr = cast<Expression>(funcExpr)) {
      *this = std::move(*expr);
    }
    else {
      child = funcExpr;
    }

    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TokenVector &tokens) {
  if (std::shared_ptr<IOperator> oper = IOperator::parse(tokens.back(), IOperator::Priority::PostfixUnary)) {
    int64_t order = 1;

    if (auto factor = cast<Factorial>(oper)) {
      for (; order < tokens.size(); order++) {
        if (tokens[tokens.size() - order - 1] != oper->toString()) {
          break;
        }
      }

      factor->setOrder(order);
    }

    auto rhsExpr = std::shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.end() - order)));
    std::shared_ptr<IExpression> funcExpr = makeRawFunctionExpression(*oper, {rhsExpr});

    if (auto expr = cast<Expression>(funcExpr)) {
      *this = std::move(*expr);
    }
    else {
      child = funcExpr;
    }

    return true;
  }

  return false;
}

bool Expression::parseBinaryOperator(const TokenVector &tokens) {
  std::map<size_t, std::shared_ptr<IMathObject>> operMap = findBinaryOperators(tokens);

  if (operMap.empty()) {
    return false;
  }

  auto foundOperIt = operMap.begin();
  size_t foundIndex = foundOperIt->first;
  IOperator::Priority foundPriority = cast<IOperator>(foundOperIt->second)->getOperatorPriority();

  auto it = operMap.begin();
  ++it;

  for (; it != operMap.end(); ++it) {
    size_t index = it->first;
    IOperator::Priority priority = cast<IOperator>(it->second)->getOperatorPriority();

    if (foundPriority < priority || (foundPriority == priority && foundIndex < index)) {
      foundPriority = priority;
      foundOperIt = it;
    }
  }

  auto operPos = int64_t(foundOperIt->first);
  if (operPos < 1 || operPos >= tokens.size()) {
    return false;
  }

  auto lhsExpr = std::shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.begin() + operPos)));
  auto rhsExpr = std::shared_ptr<Expression>(new Expression(TokenVector(tokens.begin() + operPos + 1, tokens.end())));
  std::shared_ptr<IExpression> funcExpr =
      makeRawFunctionExpression(*cast<IFunction>(foundOperIt->second), {lhsExpr, rhsExpr});

  if (auto expr = cast<Expression>(funcExpr)) {
    *this = std::move(*expr);
  }
  else {
    child = funcExpr;
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

  if (std::shared_ptr<IMathObject> parsed = ILiteral::parse(tokens.front())) {
    child = parsed;
    return true;
  }

  if (std::shared_ptr<IMathObject> parsed = INumber::parse(tokens.front())) {
    child = parsed;
    return true;
  }

  return false;
}

bool Expression::parseFunction(const TokenVector &tokens) {
  if (tokens.size() <= 1) {
    return false;
  }

  if (auto func = IFunction::parse(tokens.front()); func && !is<IOperator>(func)) {
    child = std::make_shared<FunctionExpression>(*func, getFunctionArgs(TokenVector(tokens.begin() + 1, tokens.end())));
    return true;
  }

  return false;
}

std::unique_ptr<IMathObject> Expression::makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args) {
  ArgumentsPtrVector argsPtrVect;
  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().toMinimalObject());
  }

  auto res = std::make_unique<Expression>();
  res->child = makeFunctionExpression(func, argsPtrVect);
  return res;
}

std::shared_ptr<IMathObject> Expression::makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args) {
  auto res = std::make_shared<Expression>(makeRawFunctionExpression(func, args));
  res->validate();
  simplifyChild(res->child);
  return res;
}

std::shared_ptr<IExpression> Expression::makeRawFunctionExpression(const IFunction &func,
                                                                   const ArgumentsPtrVector &args) {

  if (std::shared_ptr<IExpression> expr = Parser::parse(expressionBuildersMap, func.toString(), args)) {
    return expr;
  }

  auto funcExpr = std::make_shared<Expression>();
  funcExpr->child = std::make_shared<FunctionExpression>(func, args);
  return funcExpr;
}

std::shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

ArgumentsPtrVector Expression::getFunctionArgs(const TokenVector &tokens) {
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
        return getFunctionArgs(cutBraces(tokens));
      }
      break;
    }

    if (tokens.at(pos) == ",") {
      if (pos == 0 || pos == tokens.size() - 1) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

      args.emplace_back(
          std::shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.begin() + int64_t(pos)))));

      ArgumentsPtrVector addArgs = getFunctionArgs(TokenVector(tokens.begin() + int64_t(pos) + 1, tokens.end()));

      for (auto &token : addArgs) {
        args.emplace_back(std::shared_ptr<IMathObject>(token));
      }

      return args;
    }
  }

  args.emplace_back(std::shared_ptr<Expression>(new Expression(tokens)));

  return args;
}

Expression &Expression::add(const Expression &rhs) {
  child = makeFunctionExpression(Add(), {child, rhs.child});
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  child = makeFunctionExpression(Sub(), {child, rhs.child});
  return *this;
}

Expression &Expression::multiply(const Expression &rhs) {
  child = makeFunctionExpression(Mul(), {child, rhs.child});
  return *this;
}

Expression &Expression::divide(const Expression &rhs) {
  child = makeFunctionExpression(Div(), {child, rhs.child});
  return *this;
}

Expression &Expression::negate() {
  child = makeFunctionExpression(Neg(), {child});
  return *this;
}

void Expression::validate() const {
  if (const auto expr = cast<IExpression>(child)) {
    expr->validate();
  }
}

// void Expression::setPrecision(uint8_t precision) {
//   setPrecisionRec(precision);
// }

// std::unique_ptr<IMathObject> Expression::simplify(bool isPrecise) const {
// simplifyValue(isPrecise, expr.info);
// return child->clone();
// }

ArgumentsPtrVector Expression::getChildren() const {
  return {child};
}

ArgumentsPtrVector Expression::getVariables() const {
  if (is<Variable>(child)) {
    return {child};
  }

  if (const auto expr = cast<IExpression>(child)) {
    return expr->getVariables();
  }

  return {};
}

std::shared_ptr<IMathObject> Expression::simplify() {
  simplifyChild(child);
  // callPowSimplify()
  return child;
}

// void Expression::callPowSimplify() {
//   if (auto powExpr = cast<PowExpression>(child)) {
//     child = powExpr->polynomSimplify();
//   }
// }

}
