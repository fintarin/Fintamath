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
#include "fintamath/expressions/EqvExpression.hpp"
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
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression::Vector Expression::copy(const Vector &rhs) {
  Vector result;
  for (const auto &value : rhs) {
    result.emplace_back(value->clone());
  }
  return result;
}

Expression::Expression(const Expression &rhs) noexcept {
  if (rhs.info) {
    info = rhs.info->clone();
    children = copy(rhs.children);
  }
}

Expression::Expression() : info(Integer(0).clone()) {
}

Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)), children(std::move(rhs.children)) {
  rhs.info = Integer(0).clone();
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
    rhs.info = Integer(0).clone();
  }
  return *this;
}

Expression::Expression(const std::string &str) {
  info = IExpression::parse(str);
  if (!info) {
    throw InvalidInputException(str);
  }
  *this = Expression(*info->simplify());
}

Expression::Expression(const MathObjectPtr &obj) {
  if (obj->is<Expression>()) {
    *this = obj->to<Expression>();
  } else {
    info = obj->clone();
  }
}

Expression::Expression(const IMathObject &obj) : Expression(obj.simplify()) {
}

Expression::Expression(int64_t val) : info(std::make_unique<Integer>(val)) {
}

Expression &Expression::compressTree() {
  if (info->is<Expression>()) {
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

Expression::Expression(const TokenVector &tokens) {
  parse(tokens);
  if (!info) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }
  //*this = Expression(*simplify());
}

std::string putInBrackets(const std::string &str) {
  return "(" + str + ")";
}

std::string Expression::binaryOperatorToString() const {
  std::string result;

  for (const auto &child : children) {
    if (child->instanceOf<IExpression>()) {
      auto parentPriority = info->to<IOperator>().getOperatorPriority();
      auto childPriority = IOperator::Priority(child->to<IExpression>().getBaseOperatorPriority());

      if (childPriority != IOperator::Priority::Any && parentPriority <= childPriority) {
        result += putInBrackets(child->toString());
      } else {
        result += child->toString();
      }
    } else {
      result += child->toString();
    }

    result += info->toString();
  }

  for (int i = 0; i < info->toString().size(); i++) {
    result.pop_back();
  }
  return result;
}

std::string Expression::prefixUnaryOperatorToString() const {
  std::string result = info->toString();

  if (children.at(0)->instanceOf<IExpression>()) {
    if (auto priority = IOperator::Priority(children.at(0)->to<IExpression>().getBaseOperatorPriority());
        priority != IOperator::Priority::Any && priority != IOperator::Priority::PrefixUnary) {
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
  if (children.at(0)->instanceOf<IComparable>() && children.at(0)->to<IComparable>() < Integer(0)) {
    return putInBrackets(result) + info->toString();
  }
  return result + info->toString();
}

std::string Expression::functionToString() const {
  std::string result = info->toString() + "(";

  for (const auto &child : children) {
    result += child->toString() + ",";
  }

  result.pop_back();

  return result + ")";
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

  for (auto &child : children) {
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

  if (info->instanceOf<IFunction>()) {
    const auto &func = info->to<IFunction>();
    ArgumentsVector args;

    for (const auto &child : children) {
      args.emplace_back(*child);
    }

    if (func.doAgsMatch(args)) {
      auto countResult = func(args);
      if (countResult->instanceOf<INumber>() && !countResult->to<INumber>().isPrecise() && isPrecise) {
        return;
      }
      info = countResult->clone();
      children.clear();
    } else {
      validateFunctionArgs(func, args);
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

void Expression::parse(const TokenVector &tokens) {
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

  auto newTokens = splitLiteral(tokens.at(0), tokens.size() > 1);
  for (size_t i = 1; i < tokens.size(); i++) {
    newTokens.emplace_back(tokens.at(i));
  }

  info = MulExpression(newTokens).clone();

  for (const auto &child : children) {
    if (info == nullptr || child == nullptr) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
  }
}

bool Expression::parsePrefixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.front(), IOperator::Priority::PrefixUnary)) {
    info = std::move(oper);

    auto value = IExpression::parse(TokenVector(tokens.begin() + 1, tokens.end()));
    if (!value) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }

    children.emplace_back(std::move(value));
    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TokenVector &tokens) {
  if (auto oper = IOperator::parse(tokens.back(), IOperator::Priority::PostfixUnary)) {
    info = std::move(oper);

    auto value = IExpression::parse(TokenVector(tokens.begin(), tokens.end() - 1));
    if (!value) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }

    children.emplace_back(std::move(value));
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
  for (auto it = operMap.begin(); it != operMap.end(); ++it) {
    size_t foundIndex = foundOperIt->first;
    size_t index = it->first;
    IOperator::Priority foundPriority = foundOperIt->second->to<IOperator>().getOperatorPriority();
    IOperator::Priority priority = it->second->to<IOperator>().getOperatorPriority();

    if (foundPriority < priority ||
        (foundPriority != IOperator::Priority::Exponentiation && foundPriority == priority && index > foundIndex)) {
      foundOperIt = it;
    }
  }

  info = std::move(foundOperIt->second);

  auto leftValue = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + int64_t(foundOperIt->first)));
  auto rightValue = IExpression::parse(TokenVector(tokens.begin() + int64_t(foundOperIt->first) + 1, tokens.end()));

  if (!leftValue || !rightValue) {
    return false;
  }

  children.emplace_back(leftValue->clone());
  children.emplace_back(rightValue->clone());

  return true;
}

bool Expression::parseFiniteTerm(const TokenVector &tokens) {
  if (tokens.at(0) == "(" && tokens.at(tokens.size() - 1) == ")") {
    info = IExpression::parse(cutBraces(tokens));
    if (!info) {
      throw InvalidInputException(Tokenizer::tokensToString(tokens));
    }
    if (info->is<Expression>()) {
      auto exprInfo = info->to<Expression>();
      info = MathObjectPtr(exprInfo.info.release());
      children = copy(exprInfo.children);
    }
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
      i--;
      continue;
    }

    if (auto oper = IOperator::parse(tokens.at(i));
        oper && oper->to<IOperator>().getFunctionType() == IFunction::Type::Binary) {
      if (i + 1 >= tokens.size()) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

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
  while (copyExpr.info->is<Expression>() && copyExpr.children.empty()) {
    copyExpr = copyExpr.to<Expression>();
  }
  if (children.empty()) {
    return copyExpr.info->clone();
  }
  return copyExpr.clone();
}

MathObjectPtr Expression::buildFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  return buildRawFunctionExpression(func, args).simplify();
}

ExpressionPtr Expression::buildAddExpression(const IFunction &func, const ArgumentsVector &args) {
  auto addExpr = std::make_unique<AddExpression>();
  addExpr->addElement(AddExpression::Element(args.at(0).get().clone()));
  addExpr->addElement(AddExpression::Element(args.at(1).get().clone(), func.is<Sub>()));
  return addExpr;
}

ExpressionPtr Expression::buildMulExpression(const IFunction &func, const ArgumentsVector &args) {
  auto mulExpr = std::make_unique<MulExpression>();
  mulExpr->addElement(MulExpression::Element(args.at(0).get().clone()));
  mulExpr->addElement(MulExpression::Element(args.at(1).get().clone(), func.is<Div>()));
  return mulExpr;
}

ExpressionPtr Expression::buildEqvExpression(const IFunction &func, const ArgumentsVector &args) {
  return std::make_unique<EqvExpression>(func, args.at(0).get(), args.at(1).get());
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

      auto arg = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)pos));
      if (!arg) {
        throw InvalidInputException(Tokenizer::tokensToString(tokens));
      }

      args.emplace_back(arg->clone());
      auto addArgs = getArgs(TokenVector(tokens.begin() + (long)pos + 1, tokens.end()));

      for (auto &token : addArgs) {
        args.push_back(MathObjectPtr(token.release()));
      }
      return args;
    }
  }

  auto arg = IExpression::parse(tokens);
  if (!arg) {
    throw InvalidInputException(Tokenizer::tokensToString(tokens));
  }

  args.emplace_back(arg->clone());
  return args;
}

TokenVector Expression::splitLiteral(const std::string &token, bool addMultiplyToEnd) {
  if (token.empty()) {
    throw InvalidInputException(token); // TODO: throw InvalidInputException(Tokenizer::tokensToString(tokens))
  }
  TokenVector tokens;
  for (const auto &var : token) {
    if (!Tokenizer::isLetter(var)) {
      throw InvalidInputException(token); // TODO: throw InvalidInputException(Tokenizer::tokensToString(tokens))
    }
    tokens.emplace_back(std::string(1, var));
    tokens.emplace_back("*");
  }
  if (!addMultiplyToEnd) {
    tokens.pop_back();
  }
  return tokens;
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
  if (info->is<Neg>()) {
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
  mul.addElement(MulExpression::Element(Integer(-1).clone(), false));
  mul.addElement(MulExpression::Element(clone(), false));
  info = std::make_unique<MulExpression>(mul)->simplify();
  children.clear();
  return *this;
}

Expression Expression::buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
  Expression funcExpr;

  if (func.is<Add>() || func.is<Sub>()) {
    funcExpr.info = buildAddExpression(func, args);
    return funcExpr;
  }

  if (func.is<Mul>() || func.is<Div>()) {
    funcExpr.info = buildMulExpression(func, args);
    return funcExpr;
  }

  if (func.instanceOf<IOperator>() && func.to<IOperator>().getOperatorPriority() == IOperator::Priority::Comparison) {
    funcExpr.info = buildEqvExpression(func, args);
    return funcExpr;
  }

  funcExpr.info = func.clone();

  for (const auto &arg : args) {
    funcExpr.children.push_back(arg.get().clone());
  }

  return funcExpr;
}

/*
  Expr: AddExpr | MulExpr | PowExpr | FuncExpr | (Expr) | Term
  AddExpr: +Expr | -Expr | Expr + Expr | Expr - Expr
  MulExpr: Expr * Expr | Expr / Expr
  PowExpr: Expr^Expr
  FuncExpr: PreFuncName Expr | Expr PostFuncName
  Term: Const | Var | Num
 */

Expression Expression::simplifyPrefixUnaryOperator(Expression expr) {
  if (expr.info->is<UnaryPlus>()) {
    return *expr.children.at(0);
  }

  if (expr.info->is<Neg>()) {
    return simplifyNeg(expr);
  }

  return expr;
}

Expression Expression::simplifyNeg(Expression expr) {
  auto childExpr = Expression(*expr.children.at(0)->clone());

  if (!childExpr.info->is<Neg>()) {
    return buildRawFunctionExpression(Neg(), {*childExpr.compress()});
  }

  expr.info = childExpr.children.at(0)->clone();

  return expr.compressTree();
}

void Expression::setPrecision(uint8_t precision) {
  setPrecisionRec(precision);
}

MathObjectPtr Expression::simplify(bool isPrecise) const {
  Expression expr = *this;
  expr = expr.compressTree();
  expr.simplifyFunctionsRec(isPrecise);

  expr = simplifyPrefixUnaryOperator(expr);
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
  if (info->is<EqvExpression>()) {
    return info->to<EqvExpression>().solve(precision);
  }
  return toString(precision);
}

std::string Expression::solve() const {
  if (info->is<EqvExpression>()) {
    return info->to<EqvExpression>().solve();
  }
  return toString();
}

void Expression::simplifyPow() {
  if (!info->is<Pow>()) {
    return;
  }

  MathObjectPtr &lhsRef = children.at(0);
  MathObjectPtr &rhsRef = children.at(1);

  if (rhsRef->is<Integer>() && lhsRef->instanceOf<IExpression>() && !lhsRef->is<Expression>()) {
    Integer rhs = rhsRef->to<Integer>();

    if (rhs == 0) {
      info = std::make_unique<Integer>(1);
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
      rhsRef = std::make_unique<Integer>(1);
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
  if (info->is<Variable>()) {
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
    if (child->is<Variable>()) {
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
