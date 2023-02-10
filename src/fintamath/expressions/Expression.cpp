#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <memory>
#include <regex>
#include <stdexcept>

#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp" // TODO: remove this include after LogicException is implemented
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/IndexExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/logic/And.hpp"    // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/logic/Equiv.hpp"  // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/logic/Impl.hpp"   // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/logic/Nequiv.hpp" // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/logic/Not.hpp"    // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/logic/Or.hpp"     // TODO: remove this include after LogicException is implemented
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/other/Index.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression::Expression(const Expression &rhs) {
  if (rhs.info) {
    info = rhs.info->clone();
    children = copy(rhs.children);
  }
}

Expression::Expression() : info(ZERO.clone()) {
}

Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)), children(std::move(rhs.children)) {
}

Expression &Expression::operator=(const Expression &rhs) {
  if (&rhs != this) {
    if (rhs.info) {
      info = rhs.info->clone();
      children = copy(rhs.children);
    } else {
      info = nullptr;
    }
  }

  return *this;
}

Expression &Expression::operator=(Expression &&rhs) noexcept {
  if (&rhs != this) {
    std::swap(info, rhs.info);
    std::swap(children, rhs.children);
  }

  return *this;
}

Expression::Expression(const std::string &str) : Expression(Tokenizer::tokenize(str)) {
  compress();
  validate();
  // TODO: implement void simplify() and use it here
  *this = Expression(simplify());
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

Expression::Expression(const MathObjectPtr &obj) : Expression(obj->clone()) {
}

Expression::Expression(MathObjectPtr &&obj) {
  if (auto *expr = cast<Expression>(obj.get())) {
    *this = std::move(*expr);
  } else if (is<IExpression>(obj)) {
    info = std::move(obj);
    children.clear();
  } else {
    info = obj->simplify();
    children.clear();
  }

  obj = nullptr;
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

  for (auto &child : children) {
    if (auto *childExpr = cast<IExpression>(child.get())) {
      childExpr->compress();
    }

    if (auto *childExpr = cast<Expression>(child.get())) {
      if (childExpr->children.empty()) {
        child = std::move(childExpr->info);
      }
    }
  }
}

std::string putInBrackets(const std::string &str) {
  return "(" + str + ")";
}

std::string Expression::binaryOperatorToString() const {
  std::string result;

  const auto *parentOper = cast<IOperator>(info.get());
  std::string parentOperStr = info->toString();
  IOperator::Priority parentOperPriority = parentOper->getOperatorPriority();
  bool parentOperIsAssociative = parentOper->isAssociative();

  if (parentOperPriority != IOperator::Priority::Multiplication &&
      parentOperPriority != IOperator::Priority::Exponentiation) {
    parentOperStr = ' ' + parentOperStr + ' ';
  }

  for (size_t i = 0; i < children.size(); i++) {
    const auto &child = children[i];

    bool shouldPutInBrackets = false;

    if (const auto *childExpr = cast<IExpression>(child.get())) {
      if (const auto *oper = cast<IOperator>(childExpr->getFunction())) {
        if (auto priority = oper->getOperatorPriority();
            priority > parentOperPriority || (priority == parentOperPriority && !parentOperIsAssociative && i > 0)) {
          shouldPutInBrackets = true;
        }
      }
    }

    if (shouldPutInBrackets) {
      result += putInBrackets(child->toString());
    } else {
      result += child->toString();
    }

    result += parentOperStr;
  }

  result = result.substr(0, result.length() - parentOperStr.length());

  return result;
}

std::string Expression::prefixUnaryOperatorToString() const {
  std::string result = info->toString();

  if (const auto *child = cast<IExpression>(children.front().get())) {
    if (const auto *oper = cast<IOperator>(child->getFunction())) {
      if (auto priority = oper->getOperatorPriority(); priority != IOperator::Priority::PrefixUnary) {
        if (is<MulExpression>(child)) {
          return result + children.front()->toString();
        }

        if (const auto *childExpr = cast<Expression>(child)) {
          if (is<Pow>(childExpr->info)) {
            return result + children.front()->toString();
          }
        }

        return result + putInBrackets(children.front()->toString());
      }
    }
  }

  return result + children.front()->toString();
}

std::string Expression::postfixUnaryOperatorToString() const {
  std::string result = children.front()->toString();

  if (const auto *child = cast<IExpression>(children.front().get())) {
    if (const auto *oper = cast<IOperator>(child->getFunction())) {
      if (auto priority = oper->getOperatorPriority(); priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + info->toString();
      }
    }
  }

  if (const auto *comp = cast<IComparable>(children.front().get()); comp && *comp < ZERO) {
    return putInBrackets(result) + info->toString();
  }

  return result + info->toString();
}

std::string Expression::functionToString() const {
  static const std::string delimiter = ", ";

  std::string result = info->toString() + "(";

  for (const auto &child : children) {
    result += child->toString() + delimiter;
  }

  result = result.substr(0, result.length() - delimiter.length()) + ")";

  return result;
}

void Expression::setPrecisionRec(uint8_t precision) {
  if (children.empty()) {
    if (is<INumber>(info)) {
      info = convert<Real>(*info).precise(precision).clone();
      return;
    }
    if (is<IExpression>(info)) {
      auto copyExpr = cast<IExpression>(std::move(info));
      copyExpr->setPrecision(precision);
      info = std::move(copyExpr);
    }
  }

  for (auto &child : children) {
    if (is<IExpression>(child)) {
      auto copyExpr = cast<IExpression>(std::move(child));
      copyExpr->setPrecision(precision);
      child = copyExpr->simplify(false);
      continue;
    }
    if (is<INumber>(child)) {
      child = convert<Real>(*child).precise(precision).clone();
      continue;
    }
  }

  if (const auto *func = cast<IFunction>(info.get())) {
    ArgumentsVector args;

    for (const auto &child : children) {
      args.emplace_back(*child);
    }

    auto countResult = (*func)(args);
    if (is<INumber>(countResult)) {
      info = convert<Real>(*countResult).precise(precision).clone();
      children.clear();
    }
  }
}

MathObjectPtr &Expression::getInfo() {
  return info;
}

const MathObjectPtr &Expression::getInfo() const {
  return info;
}

Expression::ChildrenVector &Expression::getChildren() {
  return children;
}

const Expression::ChildrenVector &Expression::getChildren() const {
  return children;
}

std::string Expression::toString() const {
  if (children.empty()) {
    return info ? info->toString() : "";
  }

  std::string result;

  if (const auto *oper = cast<IOperator>(info.get())) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixUnaryOperatorToString();
    case IOperator::Priority::PrefixUnary:
      return prefixUnaryOperatorToString();
    default:
      return binaryOperatorToString();
    }
  }

  if (info && is<IFunction>(info)) {
    return functionToString();
  }

  return result;
}

std::string Expression::toString(uint8_t precision) const {
  auto expr = Expression(*simplify(false));
  expr.setPrecision(precision);
  return expr.toString();
}

bool Expression::parsePrefixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.front(), IOperator::Priority::PrefixUnary)) {
    auto rhsExpr = Expression(TokenVector(tokens.begin() + 1, tokens.end()));
    auto funcExpr = buildRawFunctionExpression(*oper, {rhsExpr});

    if (auto *expr = cast<Expression>(funcExpr.get())) {
      *this = std::move(*expr);
    } else {
      info = std::move(funcExpr);
      children.clear();
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

    auto rhsExpr = Expression(TokenVector(tokens.begin(), tokens.end() - order));
    auto funcExpr = buildRawFunctionExpression(*oper, {rhsExpr});

    if (auto *expr = cast<Expression>(funcExpr.get())) {
      *this = std::move(*expr);
    } else {
      info = std::move(funcExpr);
      children.clear();
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

  auto lhsExpr = Expression(TokenVector(tokens.begin(), tokens.begin() + operPos));
  auto rhsExpr = Expression(TokenVector(tokens.begin() + operPos + 1, tokens.end()));
  auto funcExpr = buildRawFunctionExpression(cast<IFunction>(*foundOperIt->second), {lhsExpr, rhsExpr});

  if (auto *expr = cast<Expression>(funcExpr.get())) {
    *this = std::move(*expr);
  } else {
    info = std::move(funcExpr);
    children.clear();
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
    info = std::unique_ptr<IFunction>(ptr.release());
    children = getArgs(TokenVector(tokens.begin() + 1, tokens.end()));
    return true;
  }

  return false;
}

std::map<size_t, MathObjectPtr> Expression::findBinaryOperators(const TokenVector &tokens) {
  std::map<size_t, MathObjectPtr> operators;

  bool isPrevTokenOper = false;

  for (size_t i = 0; i < tokens.size(); i++) {
    if (skipBrackets(tokens, i)) {
      isPrevTokenOper = false;
      i--;
      continue;
    }

    if (auto oper = IOperator::parse(tokens.at(i)); oper && oper->getFunctionType() == IFunction::Type::Binary) {
      if (!isPrevTokenOper) {
        operators.insert({i, std::move(oper)});
        isPrevTokenOper = true;
      }
    } else {
      isPrevTokenOper = false;
    }
  }

  return operators;
}

MathObjectPtr Expression::buildFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  return buildRawFunctionExpression(func, args)->simplify();
}

ExpressionPtr Expression::buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  if (is<Add>(func) || is<Sub>(func)) {
    return buildAddExpression(func, args);
  }

  if (is<Mul>(func) || is<Div>(func)) {
    return buildMulExpression(func, args);
  }

  if (const auto *oper = cast<IOperator>(&func);
      oper && oper->getOperatorPriority() == IOperator::Priority::Comparison) {
    return buildEqvExpression(func, args);
  }

  if (is<Derivative>(func)) {
    return buildDerivateExpression(args);
  }

  if (is<Index>(func)) {
    return buildIndexExpression(args);
  }

  auto funcExpr = std::make_unique<Expression>();
  funcExpr->info = func.clone();

  for (const auto &arg : args) {
    funcExpr->children.push_back(arg.get().clone());
  }

  return funcExpr;
}

const IFunction *Expression::getFunction() const {
  if (const auto *func = cast<IFunction>(info.get())) {
    return func;
  }

  return nullptr;
}

ExpressionPtr Expression::buildAddExpression(const IFunction &func, const ArgumentsVector &args) {
  auto addExpr = std::make_unique<SumExpression>();
  addExpr->addElement({args.front().get().clone()});
  addExpr->addElement({args.back().get().clone(), is<Sub>(func)});
  return addExpr;
}

ExpressionPtr Expression::buildMulExpression(const IFunction &func, const ArgumentsVector &args) {
  auto mulExpr = std::make_unique<MulExpression>();
  mulExpr->addElement({args.front().get().clone()});
  mulExpr->addElement({args.back().get().clone(), is<Div>(func)});
  return mulExpr;
}

ExpressionPtr Expression::buildEqvExpression(const IFunction &func, const ArgumentsVector &args) {
  return std::make_unique<EqvExpression>(func, args.front().get(), args.back().get());
}

ExpressionPtr Expression::buildDerivateExpression(const ArgumentsVector &args) {
  return std::make_unique<DerivativeExpression>(args.front().get());
}

ExpressionPtr Expression::buildIndexExpression(const ArgumentsVector &args) {
  return std::make_unique<IndexExpression>(args.front().get(), args.back().get());
}

Expression::ChildrenVector Expression::copy(const ChildrenVector &rhs) {
  ChildrenVector result;

  for (const auto &value : rhs) {
    result.emplace_back(value->clone());
  }

  return result;
}

Expression::ChildrenVector Expression::getArgs(const TokenVector &tokens) {
  ChildrenVector args;

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

bool Expression::skipBrackets(const TokenVector &tokens, size_t &openBracketIndex) {
  if (openBracketIndex >= tokens.size() || tokens.at(openBracketIndex) != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = openBracketIndex; i < tokens.size(); i++) {
    if (tokens[i] == "(") {
      brackets++;
    } else if (tokens[i] == ")") {
      brackets--;
    }

    if (brackets == 0) {
      openBracketIndex = i + 1;
      return true;
    }
    if (brackets < 0) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
  }

  throw InvalidInputException(Tokenizer::tokensToString(tokens));
}

TokenVector Expression::cutBraces(const TokenVector &tokens) {
  if (tokens.empty()) {
    return tokens;
  }
  auto newTokens = tokens;
  if (newTokens.front() == "(" && newTokens.back() == ")") {
    newTokens.erase(newTokens.begin());
    newTokens.erase(newTokens.end() - 1);
  }
  return newTokens;
}

Expression &Expression::add(const Expression &rhs) {
  auto addExpr = SumExpression();
  addExpr.addElement({clone(), false});
  addExpr.addElement({rhs.clone(), false});
  *this = Expression(*addExpr.simplify());
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  auto addExpr = SumExpression();
  addExpr.addElement({clone(), false});
  addExpr.addElement({rhs.clone(), true});
  *this = Expression(*addExpr.simplify());
  return *this;
}

Expression &Expression::multiply(const Expression &rhs) {
  auto mulExpr = MulExpression();
  mulExpr.addElement({clone(), false});
  mulExpr.addElement({rhs.clone(), false});
  *this = Expression(*mulExpr.simplify());
  return *this;
}

Expression &Expression::divide(const Expression &rhs) {
  auto mulExpr = MulExpression();
  mulExpr.addElement({clone(), false});
  mulExpr.addElement({rhs.clone(), true});
  *this = Expression(*mulExpr.simplify());
  return *this;
}

// TODO: move this logic to NegExpression
Expression &Expression::negate() {
  if (is<Neg>(info)) {
    info = std::move(children.front());
    children.clear();
    return *this;
  }

  if (!children.empty()) {
    auto expr = std::make_unique<Expression>(*this);
    info = std::make_unique<Neg>();
    children.clear();
    children.emplace_back(std::move(expr));
    return *this;
  }

  if (cast<IArithmetic>(info.get())) {
    *this = Expression(neg(*info));
    return *this;
  }

  auto mul = MulExpression();
  mul.addElement({NEG_ONE.clone(), false});
  mul.addElement({clone(), false});
  info = std::make_unique<MulExpression>(mul)->simplify();
  children.clear();

  return *this;
}

void Expression::simplifyUnaryPlus() {
  if (!is<UnaryPlus>(info)) {
    return;
  }

  auto &child = children.front();
  if (auto *expr = cast<Expression>(child.get())) {
    *this = std::move(*expr);
  } else {
    info = std::move(child);
    children.clear();
  }
}

void Expression::simplifyNeg() {
  if (!is<Neg>(info)) {
    return;
  }

  auto &child = children.front();
  if (!is<Expression>(child)) {
    return;
  }

  const auto *childExpr = cast<Expression>(child.get());
  if (!is<Neg>(childExpr->info)) {
    return;
  }

  *this = Expression(childExpr->children.front());
}

void Expression::simplifyNot() {
  if (!is<Not>(info)) {
    return;
  }

  auto &child = children.front();
  if (!is<Expression>(child)) {
    return;
  }

  const auto *childExpr = cast<Expression>(child.get());
  if (!is<Not>(childExpr->info)) {
    return;
  }

  *this = Expression(childExpr->children.front());
}

void Expression::simplifyAnd() {
  if (!is<And>(info)) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  if (const auto *lhsBool = cast<Boolean>(&lhs)) {
    if (*lhsBool == true) {
      *this = rhs;
    } else {
      *this = Boolean(false);
    }
    return;
  }

  if (const auto *rhsBool = cast<Boolean>(&rhs)) {
    if (*rhsBool == true) {
      *this = lhs;
    } else {
      *this = Boolean(false);
    }
    return;
  }

  if (lhs == rhs) {
    *this = lhs;
    return;
  }

  if (lhs == notL(rhs)) {
    *this = Boolean(false);
    return;
  }
}

void Expression::simplifyOr() {
  if (!is<Or>(info)) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  if (const auto *lhsBool = cast<Boolean>(&lhs)) {
    if (*lhsBool == true) {
      *this = Boolean(true);
    } else {
      *this = rhs;
    }
    return;
  }

  if (const auto *rhsBool = cast<Boolean>(&rhs)) {
    if (*rhsBool == true) {
      *this = Boolean(true);
    } else {
      *this = lhs;
    }
    return;
  }

  if (lhs == rhs) {
    *this = lhs;
    return;
  }

  if (lhs == notL(rhs)) {
    *this = Boolean(true);
    return;
  }
}

void Expression::simplifyImpl() {
  if (!is<Impl>(info)) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(notL(lhs), rhs);
}

void Expression::simplifyEquiv() {
  if (!is<Equiv>(info)) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(andL(lhs, rhs), andL(notL(lhs), notL(rhs)));
}

void Expression::simplifyNequiv() {
  if (!is<Nequiv>(info)) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(andL(notL(lhs), rhs), andL(lhs, notL(rhs)));
}

void Expression::validate() const {
  const IFunction *func = getFunction();

  if (!func) {
    if (const auto *expr = cast<IExpression>(info.get())) {
      expr->validate();
    }

    return;
  }

  ArgumentsVector args;

  for (const auto &child : children) {
    if (const auto *childExpr = cast<IExpression>(child.get())) {
      childExpr->validate();
    }

    args.emplace_back(*child);
  }

  validateArgs(*func, args);
}

void Expression::setPrecision(uint8_t precision) {
  setPrecisionRec(precision);
}

MathObjectPtr Expression::simplify(bool isPrecise) const {
  Expression expr = *this;

  for (auto &child : expr.children) {
    if (const auto *childExpr = cast<IExpression>(child.get())) {
      child = childExpr->simplify(isPrecise);
      continue;
    }

    if (is<IConstant>(child)) {
      auto constant = cast<IConstant>(std::move(child));
      auto constVal = (*constant)();

      if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise() && isPrecise) {
        child = std::move(constant);
      } else {
        child = std::move(constVal);
      }

      continue;
    }

    child = child->simplify();
  }

  if (expr.children.empty()) {
    expr.simplifyConstant(isPrecise);

    if (const auto *childExpr = cast<IExpression>(expr.info.get())) {
      return childExpr->simplify(isPrecise);
    }

    return expr.info->simplify();
  }

  expr.simplifyFunction(isPrecise);

  expr.simplifyNot();
  expr.simplifyAnd();
  expr.simplifyOr();
  expr.simplifyImpl();
  expr.simplifyEquiv();
  expr.simplifyNequiv();

  expr.simplifyUnaryPlus();
  expr.simplifyNeg();
  expr.simplifyPow();

  if (expr.children.empty()) {
    return std::move(expr.info);
  }

  return std::make_unique<Expression>(std::move(expr));
}

MathObjectPtr Expression::simplify() const {
  return simplify(true);
}

std::string Expression::solve(uint8_t precision) const {
  if (const auto *expr = cast<EqvExpression>(info.get())) {
    return expr->solve(precision);
  }

  return toString(precision);
}

std::string Expression::solve() const {
  if (const auto *expr = cast<EqvExpression>(info.get())) {
    return expr->solve();
  }

  return toString();
}

void Expression::simplifyFunction(bool isPrecise) {
  if (children.empty()) {
    return;
  }

  const auto &func = cast<IFunction>(*info.get());
  const ArgumentsTypesVector argsTypes = func.getArgsTypes();

  ArgumentsVector args;
  bool canCallFunction = true;

  for (size_t i = 0; i < children.size(); i++) {
    const auto *child = children[i].get();

    if (!child) {
      continue;
    }

    const auto &type = argsTypes[i];

    if (is<Variable>(child) || is<IConstant>(child) || is<IExpression>(child)) {
      canCallFunction = false;
    }

    args.emplace_back(*child);
  }

  if (canCallFunction) {
    auto countResult = func(args);

    if (const auto *num = cast<INumber>(countResult.get()); num && !num->isPrecise() && isPrecise) {
      return;
    }

    info = std::move(countResult);
    children.clear();
  } else {
    auto funcExpr = buildRawFunctionExpression(func, args);

    if (is<Expression>(funcExpr)) {
      return;
    }

    info = std::move(funcExpr);
    children.clear();
  }
}

void Expression::simplifyConstant(bool isPrecise) {
  if (!is<IConstant>(info)) {
    return;
  }

  auto constant = cast<IConstant>(std::move(info));
  auto constVal = (*constant)();

  if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise() && isPrecise) {
    info = std::move(constant);
  } else {
    info = std::move(constVal);
  }
}

void Expression::simplifyPow() {
  if (!is<Pow>(info)) {
    return;
  }

  MathObjectPtr &lhsRef = children.front();
  MathObjectPtr &rhsRef = children.back();

  auto *lhsPtr = cast<IExpression>(lhsRef.get());
  auto *rhsPtr = cast<Integer>(rhsRef.get());

  if (lhsPtr && rhsPtr && !is<Expression>(lhsPtr)) {
    if (*rhsPtr == ZERO) {
      info = ONE.clone();
      children.clear();
      return;
    }
    if (*lhsPtr == ONE || *rhsPtr == ONE) {
      info = std::move(lhsRef);
      children.clear();
      return;
    }
    if (*rhsPtr == NEG_ONE) {
      info = std::make_unique<Div>();
      *rhsPtr = ONE;
      std::swap(lhsRef, rhsRef);
      return;
    }

    Integer rhs = *rhsPtr;
    MulElement lhs = std::move(lhsRef);

    if (rhs < ZERO) {
      lhs.inverted = true;
      rhs = -rhs;
    }

    MulExpression mul;
    for (size_t i = 0; i < rhs; i++) {
      mul.addElement(lhs);
    }

    info = mul.simplify();
    children.clear();
  }
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

  for (const auto &child : children) {
    if (is<Variable>(child)) {
      result.emplace_back(child->clone());
      continue;
    }

    if (const auto *expr = cast<IExpression>(info.get())) {
      auto addResult = expr->getVariables();
      for (const auto &add : addResult) {
        result.emplace_back(add->clone());
      }
    }
  }

  return result;
}

}
