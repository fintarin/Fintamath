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

Expression::Expression(const string &str) : Expression(Tokenizer::tokenize(str)) {
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

Expression::Expression(int64_t val) : child(make_shared<Integer>(val)) {
}

unique_ptr<IMathObject> Expression::toMinimalObject() const {
  ArgumentPtr childClone = child->clone();
  simplifyChild(childClone);
  return childClone->clone();
}

string Expression::toString() const {
  return child->toString();
}

Expression Expression::precise(uint8_t precision) const {
  assert(precision <= FINTAMATH_ROUND_PRECISION);
  return Expression(preciseRec(child, precision, true));
}

ArgumentPtr Expression::preciseRec(const ArgumentPtr &arg, uint8_t precision, bool shouldSimplify) {
  if (const auto num = cast<INumber>(arg)) {
    return make_shared<Real>(convert<Real>(*num).precise(precision));
  }

  if (shouldSimplify) {
    if (const auto constant = cast<IConstant>(arg)) {
      ArgumentPtr res = (*constant)();

      if (const auto num = cast<INumber>(res)) {
        return make_shared<Real>(convert<Real>(*num).precise(precision));
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

  ArgumentPtr res;

  if (shouldSimplify) {
    res = makeFunctionExpression(*expr->getFunction(), newChildren);
    res = preciseRec(res, precision, false);
  }
  else {
    res = makeRawFunctionExpression(*expr->getFunction(), newChildren);
  }

  if (is<IExpression>(res)) {
    copyPropertiesToChild(res, expr);
  }

  return res;
}

bool Expression::parsePrefixOperator(const TokenVector &tokens) {
  if (shared_ptr<IOperator> oper = IOperator::parse(tokens.front(), IOperator::Priority::PrefixUnary)) {
    auto rhsExpr = shared_ptr<Expression>(new Expression(TokenVector(tokens.begin() + 1, tokens.end())));
    shared_ptr<IExpression> funcExpr = makeRawFunctionExpression(*oper, {rhsExpr});

    if (auto expr = cast<Expression>(funcExpr)) {
      *this = move(*expr);
    }
    else {
      child = funcExpr;
    }

    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TokenVector &tokens) {
  if (shared_ptr<IOperator> oper = IOperator::parse(tokens.back(), IOperator::Priority::PostfixUnary)) {
    int64_t order = 1;

    if (auto factor = cast<Factorial>(oper)) {
      for (; order < tokens.size(); order++) {
        if (tokens[tokens.size() - order - 1] != oper->toString()) {
          break;
        }
      }

      factor->setOrder(order);
    }

    auto rhsExpr = shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.end() - order)));
    shared_ptr<IExpression> funcExpr = makeRawFunctionExpression(*oper, {rhsExpr});

    if (auto expr = cast<Expression>(funcExpr)) {
      *this = move(*expr);
    }
    else {
      child = funcExpr;
    }

    return true;
  }

  return false;
}

bool Expression::parseBinaryOperator(const TokenVector &tokens) {
  map<size_t, ArgumentPtr> operMap = findBinaryOperators(tokens);

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

  auto lhsExpr = shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.begin() + operPos)));
  auto rhsExpr = shared_ptr<Expression>(new Expression(TokenVector(tokens.begin() + operPos + 1, tokens.end())));
  shared_ptr<IExpression> funcExpr =
      makeRawFunctionExpression(*cast<IFunction>(foundOperIt->second), {lhsExpr, rhsExpr});

  if (auto expr = cast<Expression>(funcExpr)) {
    *this = move(*expr);
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

  if (ArgumentPtr parsed = ILiteral::parse(tokens.front())) {
    child = parsed;
    return true;
  }

  if (ArgumentPtr parsed = INumber::parse(tokens.front())) {
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
    child = make_shared<FunctionExpression>(*func, parseFunctionArgs(TokenVector(tokens.begin() + 1, tokens.end())));
    return true;
  }

  return false;
}

shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

ArgumentsPtrVector Expression::parseFunctionArgs(const TokenVector &tokens) {
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
        return parseFunctionArgs(cutBraces(tokens));
      }
      break;
    }

    if (tokens.at(pos) == ",") {
      if (pos == 0 || pos == tokens.size() - 1) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

      args.emplace_back(
          shared_ptr<Expression>(new Expression(TokenVector(tokens.begin(), tokens.begin() + int64_t(pos)))));

      ArgumentsPtrVector addArgs = parseFunctionArgs(TokenVector(tokens.begin() + int64_t(pos) + 1, tokens.end()));

      for (const auto &token : addArgs) {
        args.emplace_back(ArgumentPtr(token));
      }

      return args;
    }
  }

  args.emplace_back(shared_ptr<Expression>(new Expression(tokens)));

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

void Expression::validateChild(const ArgumentPtr &child) const {
  const auto childExpr = cast<IExpression>(child);

  if (!childExpr) {
    return;
  }

  const shared_ptr<IFunction> func = childExpr->getFunction();
  const ArgumentsPtrVector children = childExpr->getChildren();

  if (children.size() <= size_t(func->getFunctionType())) {
    validateFunctionArgs(func, children);
  }
  else {
    for (size_t i = 0; i < children.size() - 1; i++) {
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
    const ArgumentPtr &child = args[i];
    const std::type_info &type = childrenTypes[i];

    if (const auto childExpr = cast<IExpression>(child)) {
      const shared_ptr<IFunction> childFunc = childExpr->getFunction();
      const std::type_info &childType = childFunc->getReturnType();

      if (childType != typeid(Variable) && !InheritanceTable::isBaseOf(type, childType) &&
          !InheritanceTable::isBaseOf(childType, type)) {
        throw InvalidInputException(toString());
      }
    }
    else if (const auto childConst = cast<IConstant>(child)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }
    }
    else {
      const std::type_info &childType = typeid(*child);

      if (childType != typeid(Variable) && !InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }
    }
  }
}

unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args) {
  ArgumentsPtrVector argsPtrVect;
  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().toMinimalObject());
  }

  auto res = make_unique<Expression>();
  res->child = makeFunctionExpression(func, argsPtrVect);
  return res;
}

ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args) {
  Expression res(makeRawFunctionExpression(func, args));
  res.validateChild(res.child);
  Expression::simplifyChild(res.child);
  return res.child;
}

shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args) {
  if (shared_ptr<IExpression> expr = Parser::parse(Expression::expressionBuildersMap, func.toString(), args)) {
    return expr;
  }

  auto funcExpr = make_shared<Expression>();
  funcExpr->child = make_shared<FunctionExpression>(func, args);
  return funcExpr;
}

void Expression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != getChildren().size()) {
    return;
  }

  child = childVect.front();
}

}
