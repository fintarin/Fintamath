#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <regex>

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

Expression::Expression() : child(ZERO.clone()) {
}

Expression::Expression(const std::string &str) : Expression(Tokenizer::tokenize(str)) {
  validateChild(child);
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

Expression::Expression(const ArgumentPtr &obj) {
  if (auto expr = cast<Expression>(obj)) {
    child = expr->child;
  }
  else {
    child = obj;
    simplifyChild(child);
  }
}

Expression::Expression(const IMathObject &obj) : Expression(obj.toMinimalObject()) {
}

Expression::Expression(int64_t val) : child(std::make_shared<Integer>(val)) {
}

std::string Expression::toString() const {
  return child->toString();
}

Expression Expression::precise(uint8_t precision) const {
  assert(precision <= FINTAMATH_ROUND_PRECISION);
  return Expression(preciseRec(child, precision, true));
}

ArgumentPtr Expression::preciseRec(const ArgumentPtr &arg, uint8_t precision, bool shouldSimplify) {
  if (const auto num = cast<INumber>(arg)) {
    return std::make_shared<Real>(convert<Real>(*num).precise(precision));
  }

  if (shouldSimplify) {
    if (const auto constant = cast<IConstant>(arg)) {
      ArgumentPtr res = (*constant)();

      if (const auto num = cast<INumber>(res)) {
        return std::make_shared<Real>(convert<Real>(*num).precise(precision));
      }

      return res;
    }
  }

  if (const auto expr = cast<IExpression>(arg)) {
    return preciseExpressionRec(expr, precision, shouldSimplify);
  }

  return arg;
}

ArgumentPtr Expression::preciseExpressionRec(const std::shared_ptr<const IExpression> &expr, uint8_t precision,
                                             bool shouldSimplify) {
  ArgumentsPtrVector newChildren;

  for (const auto &child : expr->getChildren()) {
    newChildren.emplace_back(preciseRec(child, precision, shouldSimplify));
  }

  std::shared_ptr<IExpression> res = cast<IExpression>(expr->clone());
  res->setChildren(newChildren);

  if (shouldSimplify) {
    auto resSimpl = std::dynamic_pointer_cast<const IMathObject>(res);
    simplifyChild(resSimpl);
    return preciseRec(resSimpl, precision, false);
  }

  return res;
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
    size_t order = 1;

    if (auto factor = cast<Factorial>(oper)) {
      for (; order < tokens.size(); order++) {
        if (tokens[tokens.size() - order - 1] != oper->toString()) {
          break;
        }
      }

      factor->setOrder(order);
    }

    auto rhsExpr = std::shared_ptr<Expression>(
        new Expression(TokenVector(tokens.begin(), tokens.end() - TokenVector::iterator::difference_type(order))));
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
  std::map<size_t, ArgumentPtr> operMap = findBinaryOperators(tokens);

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

  auto operPos = foundOperIt->first;
  if (operPos < 1 || operPos >= tokens.size()) {
    return false;
  }

  auto lhsExpr = std::shared_ptr<Expression>(new Expression(
      TokenVector(tokens.begin(), tokens.begin() + ArgumentsPtrVector::iterator::difference_type(operPos))));
  auto rhsExpr = std::shared_ptr<Expression>(new Expression(
      TokenVector(tokens.begin() + ArgumentsPtrVector::iterator::difference_type(operPos) + 1, tokens.end())));
  std::shared_ptr<IExpression> funcExpr = makeRawFunctionExpression(
      *cast<IFunction>(foundOperIt->second), {lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});

  if (auto expr = cast<Expression>(funcExpr)) {
    *this = std::move(*expr);
  }
  else {
    child = funcExpr;
  }

  return true;
}

bool Expression::parseFiniteTerm(const TokenVector &tokens) {
  bool res = false;

  if (tokens.size() > 1) {
    if (tokens.front() == "(" && tokens[tokens.size() - 1] == ")") {
      *this = Expression(cutBrackets(tokens));
      res = true;
    }
  }
  else if (ArgumentPtr literal = ILiteral::parse(tokens.front())) {
    child = literal;
    res = true;
  }
  else if (ArgumentPtr number = INumber::parse(tokens.front())) {
    child = number;
    res = true;
  }

  return res;
}

bool Expression::parseFunction(const TokenVector &tokens) {
  if (tokens.size() <= 1) {
    return false;
  }

  if (auto func = IFunction::parse(tokens.front()); func && !is<IOperator>(func)) {
    ArgumentsPtrVector args = parseFunctionArgs(TokenVector(tokens.begin() + 1, tokens.end()));
    child = makeRawFunctionExpression(*func, args);
    return true;
  }

  return false;
}

std::shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

ArgumentsPtrVector Expression::parseFunctionArgs(const TokenVector &tokens) {
  ArgumentsPtrVector args;

  for (size_t pos = 0; pos < tokens.size(); pos++) {
    bool isBracketsSkip = false;
    if (tokens[pos] == "(") {
      if (pos == 0) {
        isBracketsSkip = true;
      }

      skipBrackets(tokens, pos);
    }

    if (pos == tokens.size()) {
      if (isBracketsSkip) {
        return parseFunctionArgs(cutBrackets(tokens));
      }
      break;
    }

    if (tokens[pos] == ",") {
      if (pos == 0 || pos + 1 == tokens.size()) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

      args.emplace_back(std::shared_ptr<Expression>(new Expression(
          TokenVector(tokens.begin(), tokens.begin() + ArgumentsPtrVector::iterator::difference_type(pos)))));

      ArgumentsPtrVector addArgs = parseFunctionArgs(
          TokenVector(tokens.begin() + ArgumentsPtrVector::iterator::difference_type(pos) + 1, tokens.end()));

      for (const auto &token : addArgs) {
        args.emplace_back(ArgumentPtr(token));
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

ArgumentsPtrVector Expression::getChildren() const {
  return {child};
}

ArgumentPtr Expression::simplify() const {
  return child;
}

void Expression::validateChild(const ArgumentPtr &inChild) const {
  const auto childExpr = cast<IExpression>(inChild);

  if (!childExpr) {
    return;
  }

  const std::shared_ptr<IFunction> func = childExpr->getFunction();
  const ArgumentsPtrVector children = childExpr->getChildren();

  if (children.size() <= size_t(func->getFunctionType())) {
    validateFunctionArgs(func, children);
  }
  else {
    for (size_t i = 0; i + 1 < children.size(); i++) {
      for (size_t j = i + 1; j < children.size(); j++) {
        validateFunctionArgs(func, {children[i], children[j]});
      }
    }
  }

  for (const auto &arg : children) {
    validateChild(arg);
  }
}

void Expression::validateFunctionArgs(const std::shared_ptr<IFunction> &func, const ArgumentsPtrVector &args) const {
  const ArgumentsTypesVector childrenTypes = func->getArgsTypes();

  if (childrenTypes.size() != args.size()) {
    throw InvalidInputException(toString());
  }

  for (size_t i = 0; i < args.size(); i++) {
    const ArgumentPtr &arg = args[i];
    const std::type_info &type = childrenTypes[i];

    if (const auto childExpr = cast<IExpression>(arg)) {
      const std::shared_ptr<IFunction> childFunc = childExpr->getFunction();
      const std::type_info &childType = childFunc->getReturnType();

      if (childType != typeid(Variable) && !InheritanceTable::isBaseOf(type, childType) &&
          !InheritanceTable::isBaseOf(childType, type)) {
        throw InvalidInputException(toString());
      }
    }
    else if (const auto childConst = cast<IConstant>(arg)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }
    }
    else {
      const auto &argRef = *arg;
      const std::type_info &childType = typeid(argRef);

      if (childType != typeid(Variable) && !InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }
    }
  }
}

std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args) {
  ArgumentsPtrVector argsPtrVect;
  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().toMinimalObject());
  }

  auto res = std::make_unique<Expression>();
  res->child = makeFunctionExpression(func, argsPtrVect);
  return res;
}

ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args) {
  Expression res(makeRawFunctionExpression(func, args));
  return res.child;
}

std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args) {
  if (std::shared_ptr<IExpression> expr = Parser::parse(Expression::getExpressionMakers(), func.toString(), args)) {
    return expr;
  }

  return std::make_shared<FunctionExpression>(func, args);
}

void Expression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 1) {
    return;
  }

  child = childVect.front();
}

void Expression::setValuesOfVariables(const std::vector<Variable> &vars, const ArgumentsPtrVector &vals) {
  IExpression::setValuesOfVariables(vars, vals);
  simplifyChild(child);
}

Expression operator+(const Variable &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Add(), {lhs.clone(), rhs.clone()}));
}

Expression operator+(const Expression &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Add(), {lhs.getChildren().front(), rhs.clone()}));
}

Expression operator+(const Variable &lhs, const Expression &rhs) {
  return Expression(makeFunctionExpression(Add(), {lhs.clone(), rhs.getChildren().front()}));
}

Expression operator-(const Variable &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Sub(), {lhs.clone(), rhs.clone()}));
}

Expression operator-(const Expression &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Sub(), {lhs.getChildren().front(), rhs.clone()}));
}

Expression operator-(const Variable &lhs, const Expression &rhs) {
  return Expression(makeFunctionExpression(Sub(), {lhs.clone(), rhs.getChildren().front()}));
}

Expression operator*(const Variable &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Mul(), {lhs.clone(), rhs.clone()}));
}

Expression operator*(const Expression &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Mul(), {lhs.getChildren().front(), rhs.clone()}));
}

Expression operator*(const Variable &lhs, const Expression &rhs) {
  return Expression(makeFunctionExpression(Mul(), {lhs.clone(), rhs.getChildren().front()}));
}

Expression operator/(const Variable &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Div(), {lhs.clone(), rhs.clone()}));
}

Expression operator/(const Expression &lhs, const Variable &rhs) {
  return Expression(makeFunctionExpression(Div(), {lhs.getChildren().front(), rhs.clone()}));
}

Expression operator/(const Variable &lhs, const Expression &rhs) {
  return Expression(makeFunctionExpression(Div(), {lhs.clone(), rhs.getChildren().front()}));
}

}
