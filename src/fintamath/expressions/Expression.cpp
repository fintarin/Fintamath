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
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/DerivativeExpression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp" // TODO: remove this include after LogicException is implemented
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
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
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Boolean.hpp" // TODO: remove this include after LogicException is implemented
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression::Expression(const Expression &rhs) noexcept {
  if (rhs.info) {
    info = rhs.info->clone();
    children = copy(rhs.children);
  }
}

Expression::Expression() : info(ZERO.clone()) {
}

Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)), children(std::move(rhs.children)) {
  rhs.info = ZERO.clone();
}

Expression &Expression::operator=(const Expression &rhs) noexcept {
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
    rhs.info = ZERO.clone();
  }

  return *this;
}

Expression::Expression(const std::string &str) : Expression(Tokenizer::tokenize(str)) {
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
  if (obj->instanceOf<Expression>()) {
    *this = std::move(obj->to<Expression>());
  } else if (obj->instanceOf<IExpression>()) {
    info = std::move(obj);
    children.clear();
  } else {
    info = obj->simplify();
    children.clear();
  }
}

Expression::Expression(int64_t val) : info(std::make_unique<Integer>(val)) {
}

Expression &Expression::compressTree() {
  if (info->instanceOf<Expression>()) {
    auto exprInfo = info->to<Expression>();
    info = MathObjectPtr(exprInfo.info.release());
    children = copy(exprInfo.children);
  }

  return *this;
}

uint16_t Expression::getBaseOperatorPriority() const {
  if (info->instanceOf<IOperator>()) {
    return (uint16_t)info->to<IOperator>().getOperatorPriority();
  }
  return (uint16_t)IOperator::Priority::Any;
}

std::string putInBrackets(const std::string &str) {
  return "(" + str + ")";
}

std::string Expression::binaryOperatorToString() const {
  std::string result;

  std::string operStr = info->toString();
  if (auto priority = info->to<IOperator>().getOperatorPriority();
      priority != IOperator::Priority::Multiplication && priority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  for (size_t i = 0; i < children.size(); i++) {
    const auto &child = children[i];

    if (child->instanceOf<IExpression>()) {
      auto parentPriority = info->to<IOperator>().getOperatorPriority();
      auto childPriority = IOperator::Priority(child->to<IExpression>().getBaseOperatorPriority());

      if (childPriority != IOperator::Priority::Any &&
          (parentPriority < childPriority ||
           (parentPriority == childPriority && !info->to<IOperator>().isAssociative() && i > 0))) {
        result += putInBrackets(child->toString());
      } else {
        result += child->toString();
      }
    } else {
      result += child->toString();
    }

    result += operStr;
  }

  result = result.substr(0, result.length() - operStr.length());

  return result;
}

std::string Expression::prefixUnaryOperatorToString() const {
  std::string result = info->toString();

  if (children.at(0)->instanceOf<IExpression>()) {
    const auto &child = children.at(0)->to<IExpression>();

    if (auto priority = IOperator::Priority(child.getBaseOperatorPriority());
        priority != IOperator::Priority::Any && priority != IOperator::Priority::PrefixUnary) {

      if (child.instanceOf<MulExpression>()) {
        return result + children.at(0)->toString();
      }

      if (child.instanceOf<Expression>()) {
        const auto &childExpr = child.to<Expression>();

        if (childExpr.info->instanceOf<Pow>()) {
          return result + children.at(0)->toString();
        }
      }

      return result + putInBrackets(children.at(0)->toString());
    }
  }

  return result + children.at(0)->toString();
}

std::string Expression::postfixUnaryOperatorToString() const {
  std::string result = children.at(0)->toString();

  if (children.at(0)->instanceOf<IExpression>()) {
    if (auto priority = IOperator::Priority(children.at(0)->to<IExpression>().getBaseOperatorPriority());
        priority != IOperator::Priority::Any && priority != IOperator::Priority::PostfixUnary) {
      return putInBrackets(result) + info->toString();
    }
  }
  if (children.at(0)->instanceOf<IComparable>() && children.at(0)->to<IComparable>() < ZERO) {
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

void Expression::simplifyConstant(bool isPrecise) {
  if (info->instanceOf<IConstant>()) {
    auto constant = (*castPtr<IConstant>(info->clone()))();
    if (!isPrecise || !constant->instanceOf<INumber>() || constant->to<INumber>().isPrecise()) {
      info = constant->clone();
      return;
    }
  }
  if (info->instanceOf<IExpression>()) {
    info = info->to<IExpression>().simplify(isPrecise);
    return;
  }
  info = info->simplify();
}

void Expression::setPrecisionRec(uint8_t precision) {
  if (children.empty()) {
    if (info->instanceOf<INumber>()) {
      info = Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
      return;
    }
    if (info->instanceOf<IExpression>()) {
      auto copyExpr = castPtr<IExpression>(info->clone());
      copyExpr->setPrecision(precision);
      info = std::move(copyExpr);
    }
  }

  for (auto &child : children) {
    if (child->instanceOf<IExpression>()) {
      auto copyChild = castPtr<IExpression>(child->clone());
      copyChild->setPrecision(precision);
      child = copyChild->simplify(false);
    }
    if (child->instanceOf<INumber>()) {
      child = Converter::convert(*child, Real())->to<Real>().precise(precision).clone();
      continue;
    }
    if (child->instanceOf<IExpression>()) {
      auto copyExpr = castPtr<IExpression>(child->clone());
      copyExpr->setPrecision(precision);
      child = copyExpr->simplify(false);
    }
  }

  if (info->instanceOf<IFunction>()) {
    const auto &func = info->to<IFunction>();
    ArgumentsVector args;

    for (const auto &child : children) {
      args.emplace_back(*child);
    }

    if (func.doAgsMatch(args)) {
      auto countResult = func(args);
      if (countResult->instanceOf<INumber>()) {
        info = Converter::convert(*countResult, Real())->to<Real>().precise(precision).clone();
        children.clear();
      }
    }
  }
}

void Expression::simplifyFunctionsRec(bool isPrecise) {
  if (children.empty()) {
    simplifyConstant(isPrecise);
    return;
  }

  if (info->instanceOf<IFunction>()) {
    const auto &func = info->to<IFunction>();
    ArgumentsVector args;

    bool hasExpressionArg = false;
    for (const auto &child : children) {
      if (child->instanceOf<IExpression>()) {
        hasExpressionArg = true;
      }

      args.emplace_back(*child);
    }

    if (!hasExpressionArg && func.doAgsMatch(args)) {
      auto countResult = func(args);

      if (countResult->instanceOf<INumber>() && !countResult->to<INumber>().isPrecise() && isPrecise) {
        return;
      }

      info = countResult->clone();
      children.clear();
    } else {
      validateFunctionArgs(func, args);

      auto funcExpr = buildRawFunctionExpression(func, args);
      if (funcExpr->instanceOf<Expression>()) {
        return;
      }

      info = std::move(funcExpr);
      children.clear();

      if (!info->instanceOf<IFunction>()) {
        info = info->simplify();
      }
    }
  }
}

MathObjectPtr &Expression::getInfo() {
  return info;
}

const MathObjectPtr &Expression::getInfo() const {
  return info;
}

Expression::Vector &Expression::getChildren() {
  return children;
}

const Expression::Vector &Expression::getChildren() const {
  return children;
}

std::string Expression::toString() const {
  if (children.empty()) {
    return info ? info->toString() : "";
  }

  std::string result;

  if (info->instanceOf<IOperator>()) {
    switch (info->to<IOperator>().getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixUnaryOperatorToString();
    case IOperator::Priority::PrefixUnary:
      return prefixUnaryOperatorToString();
    default:
      return binaryOperatorToString();
    }
  }

  if (info && info->instanceOf<IFunction>()) {
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
    info = std::move(oper);
    children.emplace_back(std::unique_ptr<Expression>(new Expression(TokenVector(tokens.begin() + 1, tokens.end()))));
    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.back(), IOperator::Priority::PostfixUnary)) {
    int64_t order = 1;

    if (oper->instanceOf<Factorial>()) {
      while (tokens[tokens.size() - order - 1] == oper->toString()) {
        order++;
      }

      oper->to<Factorial>().setOrder(order);
    }

    info = std::move(oper);
    children.emplace_back(
        std::unique_ptr<Expression>(new Expression(TokenVector(TokenVector(tokens.begin(), tokens.end() - order)))));
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
  auto foundPriority = foundOperIt->second->to<IOperator>().getOperatorPriority();

  auto it = operMap.begin();
  ++it;

  for (; it != operMap.end(); ++it) {
    auto index = it->first;
    auto priority = it->second->to<IOperator>().getOperatorPriority();

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
  auto funcExpr = buildRawFunctionExpression(foundOperIt->second->to<IFunction>(), {lhsExpr, rhsExpr});

  if (funcExpr->instanceOf<Expression>()) {
    *this = std::move(funcExpr->to<Expression>());
  } else {
    info = std::move(funcExpr);
    children.clear();
  }

  return true;
}

bool Expression::parseFiniteTerm(const TokenVector &tokens) {
  if (tokens.at(0) == "(" && tokens.at(tokens.size() - 1) == ")") {
    *this = Expression(cutBraces(tokens));
    return true;
  }

  if (tokens.size() > 1) {
    return false;
  }

  if (auto ptr = ILiteral::parse(tokens.at(0))) {
    info = std::unique_ptr<ILiteral>(ptr.release());
    return true;
  }

  if (auto ptr = INumber::parse(tokens.at(0))) {
    info = std::unique_ptr<INumber>(ptr.release());
    return true;
  }

  return false;
}

bool Expression::parseFunction(const TokenVector &tokens) {
  if (tokens.size() <= 1) {
    return false;
  }
  if (auto ptr = IFunction::parse(tokens.at(0)); ptr && !ptr->instanceOf<IOperator>()) {
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

    if (auto oper = IOperator::parse(tokens.at(i));
        oper && oper->to<IOperator>().getFunctionType() == IFunction::Type::Binary) {
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

MathObjectPtr Expression::compress() const {
  auto copyExpr = *this;
  while (copyExpr.info->instanceOf<Expression>() && copyExpr.children.empty()) {
    copyExpr = copyExpr.to<Expression>();
  }
  if (children.empty()) {
    return copyExpr.info->clone();
  }
  return copyExpr.clone();
}

MathObjectPtr Expression::buildFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  return buildRawFunctionExpression(func, args)->simplify();
}

ExpressionPtr Expression::buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  if (func.instanceOf<Add>() || func.instanceOf<Sub>()) {
    return buildAddExpression(func, args);
  }

  if (func.instanceOf<Mul>() || func.instanceOf<Div>()) {
    return buildMulExpression(func, args);
  }

  if (func.instanceOf<IOperator>() && func.to<IOperator>().getOperatorPriority() == IOperator::Priority::Comparison) {
    return buildEqvExpression(func, args);
  }

  if (func.instanceOf<Derivative>()) {
    return buildDerivateExpression(args);
  }

  auto funcExpr = std::make_unique<Expression>();
  funcExpr->info = func.clone();

  for (const auto &arg : args) {
    funcExpr->children.push_back(arg.get().clone());
  }

  return funcExpr;
}

ExpressionPtr Expression::buildAddExpression(const IFunction &func, const ArgumentsVector &args) {
  auto addExpr = std::make_unique<AddExpression>();
  addExpr->addElement(AddExpression::Element(args.at(0).get().clone()));
  addExpr->addElement(AddExpression::Element(args.at(1).get().clone(), func.instanceOf<Sub>()));
  return addExpr;
}

ExpressionPtr Expression::buildMulExpression(const IFunction &func, const ArgumentsVector &args) {
  auto mulExpr = std::make_unique<MulExpression>();
  mulExpr->addElement(MulExpression::Element(args.at(0).get().clone()));
  mulExpr->addElement(MulExpression::Element(args.at(1).get().clone(), func.instanceOf<Div>()));
  return mulExpr;
}

ExpressionPtr Expression::buildEqvExpression(const IFunction &func, const ArgumentsVector &args) {
  return std::make_unique<EqvExpression>(func, args.at(0).get(), args.at(1).get());
}

ExpressionPtr Expression::buildDerivateExpression(const ArgumentsVector &args) {
  return std::make_unique<DerivativeExpression>(args.at(0).get());
}

Expression::Vector Expression::copy(const Vector &rhs) {
  Vector result;

  for (const auto &value : rhs) {
    result.emplace_back(value->clone());
  }

  return result;
}

Expression::Vector Expression::getArgs(const TokenVector &tokens) {
  Vector args;

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
  auto addExpr = AddExpression();
  addExpr.addElement({clone(), false});
  addExpr.addElement({rhs.clone(), false});
  *this = Expression(*addExpr.simplify());
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  auto addExpr = AddExpression();
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

Expression &Expression::negate() {
  auto neg = Neg();
  if (info->instanceOf<Neg>()) {
    info = children.at(0)->clone();
    children.clear();
    return *this;
  }
  if (!children.empty()) {
    auto expr = *this;
    info = std::make_unique<Neg>();
    children.clear();
    children.emplace_back(expr.clone());
    return *this;
  }
  if (info->instanceOf<IArithmetic>()) {
    *this = Expression(neg(*info));
    return *this;
  }

  auto mul = MulExpression();
  mul.addElement(MulExpression::Element(NEG_ONE.clone(), false));
  mul.addElement(MulExpression::Element(clone(), false));
  info = std::make_unique<MulExpression>(mul)->simplify();
  children.clear();
  return *this;
}

void Expression::simplifyUnaryPlus() {
  if (!info->instanceOf<UnaryPlus>()) {
    return;
  }

  auto &child = children.at(0);
  if (child->instanceOf<Expression>()) {
    *this = std::move(child->to<Expression>());
  } else {
    info = std::move(child);
    children.clear();
  }
}

void Expression::simplifyNeg() {
  if (!info->instanceOf<Neg>()) {
    return;
  }

  auto &child = children.at(0);
  if (!child->instanceOf<Expression>()) {
    return;
  }

  auto &childExpr = child->to<Expression>();
  if (!childExpr.info->instanceOf<Neg>()) {
    return;
  }

  *this = Expression(childExpr.children.front());
}

void Expression::simplifyNot() {
  if (!info->instanceOf<Not>()) {
    return;
  }

  auto &child = children.at(0);
  if (!child->instanceOf<Expression>()) {
    return;
  }

  auto &childExpr = child->to<Expression>();
  if (!childExpr.info->instanceOf<Not>()) {
    return;
  }

  *this = Expression(childExpr.children.front());
}

void Expression::simplifyAnd() {
  if (!info->instanceOf<And>()) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  if (lhs.instanceOf<Boolean>()) {
    if (lhs.to<Boolean>() == true) {
      *this = rhs;
    } else {
      *this = Boolean(false);
    }
  } else if (rhs.instanceOf<Boolean>()) {
    if (rhs.to<Boolean>() == true) {
      *this = lhs;
    } else {
      *this = Boolean(false);
    }
  } else if (lhs == rhs) {
    *this = lhs;
  } else if (lhs == notL(rhs)) {
    *this = Boolean(false);
  }
}

void Expression::simplifyOr() {
  if (!info->instanceOf<Or>()) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  if (lhs.instanceOf<Boolean>()) {
    if (lhs.to<Boolean>() == true) {
      *this = Boolean(true);
    } else {
      *this = rhs;
    }
  } else if (rhs.instanceOf<Boolean>()) {
    if (rhs.to<Boolean>() == true) {
      *this = Boolean(true);
    } else {
      *this = lhs;
    }
  } else if (lhs == rhs) {
    *this = lhs;
    return;
  } else if (lhs == notL(rhs)) {
    *this = Boolean(true);
  }
}

void Expression::simplifyImpl() {
  if (!info->instanceOf<Impl>()) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(notL(lhs), rhs);
}

void Expression::simplifyEquiv() {
  if (!info->instanceOf<Equiv>()) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(andL(lhs, rhs), andL(notL(lhs), notL(rhs)));
}

void Expression::simplifyNequiv() {
  if (!info->instanceOf<Nequiv>()) {
    return;
  }

  const auto &lhs = *children.front();
  const auto &rhs = *children.back();

  *this = orL(andL(notL(lhs), rhs), andL(lhs, notL(rhs)));
}

void Expression::setPrecision(uint8_t precision) {
  setPrecisionRec(precision);
}

MathObjectPtr Expression::simplify(bool isPrecise) const {
  Expression expr = *this;
  expr.compressTree();

  for (auto &child : expr.children) {
    if (child->instanceOf<IConstant>()) {
      auto constant = (*castPtr<IConstant>(child->clone()))();
      if (!isPrecise || !constant->instanceOf<INumber>() || constant->to<INumber>().isPrecise()) {
        child = constant->clone();
        continue;
      }
    }

    if (child->instanceOf<IExpression>()) {
      child = child->to<IExpression>().simplify(isPrecise);
      continue;
    }

    child = child->simplify();
  }

  expr.simplifyFunctionsRec(isPrecise);

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
    return expr.info->clone();
  }

  return expr.clone();
}

MathObjectPtr Expression::simplify() const {
  return simplify(true);
}

std::string Expression::solve(uint8_t precision) const {
  if (info->instanceOf<EqvExpression>()) {
    return info->to<EqvExpression>().solve(precision);
  }
  return toString(precision);
}

std::string Expression::solve() const {
  if (info->instanceOf<EqvExpression>()) {
    return info->to<EqvExpression>().solve();
  }
  return toString();
}

void Expression::simplifyPow() {
  if (!info->instanceOf<Pow>()) {
    return;
  }

  MathObjectPtr &lhsRef = children.at(0);
  MathObjectPtr &rhsRef = children.at(1);

  if (rhsRef->instanceOf<Integer>() && lhsRef->instanceOf<IExpression>() && !lhsRef->instanceOf<Expression>()) {
    Integer rhs = rhsRef->to<Integer>();

    if (rhs == 0) {
      info = ONE.clone();
      children.clear();
      return;
    }
    if (lhsRef->toString() == "1" || rhs == 1) {
      info = lhsRef->clone();
      children.clear();
      return;
    }
    if (rhs == -1) {
      info = std::make_unique<Div>();
      rhsRef = ONE.clone();
      std::swap(lhsRef, rhsRef);
      return;
    }

    MulExpression::Element lhs = lhsRef;

    if (rhs < 0) {
      lhs.inverted = true;
      rhs = -rhs;
    }

    MulExpression mul;
    for (Integer i = 0; i < rhs; i++) {
      mul.addElement(lhs);
    }

    info = mul.simplify();
    children.clear();
  }
}

std::vector<MathObjectPtr> Expression::getVariables() const {
  std::vector<MathObjectPtr> result;
  if (info->instanceOf<Variable>()) {
    result.emplace_back(info->clone());
    return result;
  }
  if (info->instanceOf<IExpression>()) {
    auto addResult = info->to<IExpression>().getVariables();
    for (const auto &add : addResult) {
      result.emplace_back(add->clone());
    }
    return result;
  }
  for (const auto &child : children) {
    if (child->instanceOf<Variable>()) {
      result.emplace_back(child->clone());
      continue;
    }
    if (child->instanceOf<IExpression>()) {
      auto addResult = child->to<IExpression>().getVariables();
      for (const auto &add : addResult) {
        result.emplace_back(add->clone());
      }
    }
  }
  return result;
}
}
