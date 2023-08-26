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
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression::Expression() : child(std::make_shared<Integer>(0)) {
}

Expression::Expression(const std::string &str) : child(fintamath::parseExpr(str)) {
  validateChild(child);
  simplifyChild(child);
}

Expression::Expression(const ArgumentPtr &obj) {
  if (auto expr = cast<Expression>(obj)) {
    child = expr->child;
  }
  else {
    child = obj;
    validateChild(child);
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
  Expression preciseExpr(preciseSimplify());
  preciseRec(preciseExpr.child, precision);
  return preciseExpr;
}

ArgumentPtr parseExpr(const std::string &str) {
  return parseExpr(Expression::tokensToTerms(Tokenizer::tokenize(str)));
}

ArgumentPtr parseExpr(const TermVector &terms) {
  return parseExpr(terms, 0, terms.size());
}

ArgumentPtr parseExpr(const TermVector &terms, size_t start, size_t end) {
  if (start >= end) {
    throw InvalidInputException(Expression::termsToString(terms));
  }

  Expression res;

  if (res.parseBinaryOperator(terms, start, end) ||
      res.parsePrefixOperator(terms, start, end) ||
      res.parsePostfixOperator(terms, start, end) ||
      res.parseFunction(terms, start, end) ||
      res.parseBrackets(terms, start, end) ||
      res.parseFiniteTerm(terms, start, end)) {
    return res.child;
  }

  throw InvalidInputException(Expression::termsToString(terms));
}

bool Expression::parseBinaryOperator(const TermVector &terms, size_t start, size_t end) {
  // TODO! use more efficient algorithm

  size_t foundOperPos = 0;
  IOperator::Priority foundPriority = IOperator::Priority::Any;
  bool isPreviousBinaryOper = false;

  for (size_t i = start; i < end; i++) {
    if (skipBrackets(terms, i)) {
      isPreviousBinaryOper = false;
      i--;
      continue;
    }

    if (auto oper = cast<IOperator>(getTermValueIf(*terms[i], isBinaryOperator))) {
      if (!isPreviousBinaryOper) {
        IOperator::Priority priority = oper->getOperatorPriority();

        if (foundPriority == IOperator::Priority::Any ||
            foundPriority < priority ||
            (foundPriority == priority && foundOperPos < i)) {

          foundPriority = priority;
          foundOperPos = i;
        }
      }

      isPreviousBinaryOper = true;
    }
    else {
      isPreviousBinaryOper = false;
    }
  }

  if (foundOperPos <= start || foundOperPos + 1 >= end) {
    return false;
  }

  auto foundOper = cast<IOperator>(getTermValueIf(*terms[foundOperPos], isBinaryOperator));
  ArgumentPtr lhsArg = parseExpr(terms, start, foundOperPos);
  ArgumentPtr rhsArg = parseExpr(terms, foundOperPos + 1, end);
  std::shared_ptr<IExpression> funcExpr = cast<IExpression>(makeExpr(*foundOper, lhsArg, rhsArg));

  if (auto expr = cast<Expression>(funcExpr)) {
    *this = std::move(*expr);
  }
  else {
    child = funcExpr;
  }

  return true;
}

bool Expression::parsePrefixOperator(const TermVector &terms, size_t start, size_t end) {
  if (start + 1 >= end) {
    return false;
  }

  if (auto oper = cast<IOperator>(getTermValueIf(*terms[start], isPrefixOperator))) {
    ArgumentPtr arg = parseExpr(terms, start + 1, end);
    child = makeExpr(*oper, arg);
    compressChild(child);
    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TermVector &terms, size_t start, size_t end) {
  if (start + 1 >= end) {
    return false;
  }

  if (std::shared_ptr<const IOperator> constOper =
          cast<IOperator>(getTermValueIf(*terms[end - 1], isPostfixOperator))) {
    if (std::shared_ptr<IOperator> oper = cast<IOperator>(constOper->clone())) {
      size_t order = 1;

      if (auto factor = cast<Factorial>(oper)) {
        for (; order < end; order++) {
          if (terms[end - order - 1]->name != oper->toString()) {
            break;
          }
        }

        factor->setOrder(order);
      }

      ArgumentPtr arg = parseExpr(terms, start, end - order);
      child = makeExpr(*oper, arg);
      compressChild(child);
      return true;
    }
  }

  return false;
}

bool Expression::parseFunction(const TermVector &terms, size_t start, size_t end) {
  size_t funcPos = start;

  if (start + 1 >= end || terms[funcPos]->values.empty()) {
    return false;
  }

  if (auto termFirstValue = terms[funcPos]->values.front();
      !is<IFunction>(termFirstValue) || is<IOperator>(termFirstValue)) {
    return false;
  }

  start++;
  cutBrackets(terms, start, end);

  ArgumentsPtrVector args = parseFunctionArgs(terms, start, end);
  std::shared_ptr<const IFunction> func;

  for (const auto &value : terms[funcPos]->values) {
    auto valueFunc = cast<IFunction>(value);

    if (valueFunc->getFunctionType() == IFunction::Type(args.size()) ||
        valueFunc->getFunctionType() == IFunction::Type::Any) {
      func = valueFunc;
    }
  }

  if (!func) {
    return false;
  }

  child = makeExpr(*func, args);

  return true;
}

ArgumentsPtrVector Expression::parseFunctionArgs(const TermVector &terms, size_t start, size_t end) {
  if (start >= end) {
    return {};
  }

  ArgumentsPtrVector funcArgs;

  for (size_t i = start; i < end; i++) {
    if (terms[i]->name == "(") {
      skipBrackets(terms, i);
    }

    if (terms[i]->name == ",") {
      if (i == 0 || i + 1 == end) {
        throw InvalidInputException(termsToString(terms));
      }

      ArgumentPtr lhsArg = parseExpr(terms, start, i);
      ArgumentsPtrVector rhsArgs = parseFunctionArgs(terms, i + 1, end);

      funcArgs.emplace_back(lhsArg);
      for (const auto &arg : rhsArgs) {
        funcArgs.emplace_back(ArgumentPtr(arg));
      }

      return funcArgs;
    }
  }

  funcArgs.emplace_back(parseExpr(terms, start, end));
  return funcArgs;
}

bool Expression::parseBrackets(const TermVector &terms, size_t start, size_t end) {
  if (start + 2 >= end) {
    return false;
  }

  if (terms[start]->name == "(" && terms[end - 1]->name == ")") {
    cutBrackets(terms, start, end);
    child = parseExpr(terms, start, end);
    return true;
  }

  return false;
}

bool Expression::parseFiniteTerm(const TermVector &terms, size_t start, size_t end) {
  if (start + 1 != end || terms[start]->values.size() != 1) {
    return false;
  }

  *this = Expression(terms[start]->values.front());
  return true;
}

std::shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

Expression &Expression::add(const Expression &rhs) {
  child = makeExprChecked(Add(), *child, *rhs.child);
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  child = makeExprChecked(Sub(), *child, *rhs.child);
  return *this;
}

Expression &Expression::multiply(const Expression &rhs) {
  child = makeExprChecked(Mul(), *child, *rhs.child);
  return *this;
}

Expression &Expression::divide(const Expression &rhs) {
  child = makeExprChecked(Div(), *child, *rhs.child);
  return *this;
}

Expression &Expression::negate() {
  child = makeExprChecked(Neg(), *child);
  return *this;
}

ArgumentsPtrVector Expression::getChildren() const {
  return {child};
}

ArgumentPtr Expression::simplify() const {
  return child;
}

ArgumentPtr Expression::preciseSimplify() const {
  ArgumentPtr preciseChild = child;
  preciseSimplifyChild(preciseChild);
  return preciseChild;
}

TermVector Expression::tokensToTerms(const TokenVector &tokens) {
  TermVector terms(tokens.size());

  for (size_t i = 0; i < tokens.size(); i++) {
    if (auto term = Parser::parse(getTermMakers(), (tokens[i]))) {
      terms[i] = std::move(term);
    }
    else {
      terms[i] = std::make_unique<Term>(tokens[i], ArgumentsPtrVector{});
    }
  }

  insertDelimiters(terms);

  return terms;
}

void Expression::insertDelimiters(TermVector &terms) {
  ArgumentPtr delimiter = std::make_unique<Mul>();

  for (size_t i = 1; i < terms.size(); i++) {
    if (!getTermValueIf(*terms[i - 1], isBinaryOperator) &&
        !getTermValueIf(*terms[i - 1], isPrefixOperator) &&
        !getTermValueIf(*terms[i - 1], isNonOperatorFunction) &&
        terms[i - 1]->name != "(" &&
        terms[i - 1]->name != "," &&
        !getTermValueIf(*terms[i], isBinaryOperator) &&
        !getTermValueIf(*terms[i], isPostfixOperator) &&
        terms[i]->name != ")" &&
        terms[i]->name != ",") {

      auto term = std::make_shared<Term>(delimiter->toString(), ArgumentsPtrVector{delimiter});
      terms.insert(terms.begin() + TermVector::difference_type(i), term);
      i++;
    }
  }
}

bool Expression::skipBrackets(const TermVector &terms, size_t &openBracketIndex) {
  if (openBracketIndex >= terms.size() || terms[openBracketIndex]->name != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (size_t i = openBracketIndex; i < terms.size(); i++) {
    if (terms[i]->name == "(") {
      brackets++;
    }
    else if (terms[i]->name == ")") {
      brackets--;
    }

    if (brackets == 0) {
      openBracketIndex = i + 1;
      return true;
    }
  }

  throw InvalidInputException(termsToString(terms));
}

void Expression::cutBrackets(const TermVector &terms, size_t &start, size_t &end) {
  if (start + 1 >= end) {
    return;
  }

  if (terms[start]->name == "(" && terms[end - 1]->name == ")") {
    start++;
    end--;
  }
}

std::string Expression::termsToString(const TermVector &terms) {
  std::string res;

  for (const auto &term : terms) {
    res += term->name;
  }

  return res;
}

bool Expression::isBinaryOperator(const ArgumentPtr &val) {
  auto oper = cast<IOperator>(val);
  return oper && oper->getFunctionType() == IFunction::Type::Binary;
}

bool Expression::isPrefixOperator(const ArgumentPtr &val) {
  auto oper = cast<IOperator>(val);
  return oper && oper->getOperatorPriority() == IOperator::Priority::PrefixUnary;
}

bool Expression::isPostfixOperator(const ArgumentPtr &val) {
  auto oper = cast<IOperator>(val);
  return oper && oper->getOperatorPriority() == IOperator::Priority::PostfixUnary;
}

bool Expression::isNonOperatorFunction(const ArgumentPtr &val) {
  return is<IFunction>(val) && !is<IOperator>(val);
}

void Expression::validateChild(const ArgumentPtr &inChild) {
  const auto childExpr = cast<IExpression>(inChild);

  if (!childExpr) {
    return;
  }

  const std::shared_ptr<IFunction> func = childExpr->getFunction();
  const ArgumentsPtrVector children = childExpr->getChildren();

  if (func->getFunctionType() == IFunction::Type::Any || children.size() <= size_t(func->getFunctionType())) {
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

void Expression::validateFunctionArgs(const std::shared_ptr<IFunction> &func, const ArgumentsPtrVector &args) {
  if (func->getFunctionType() == IFunction::Type::Any && args.empty()) {
    throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(args));
  }

  ArgumentsTypeIdsVector childrenTypeIds = func->getArgsTypeIds();

  if (func->getFunctionType() == IFunction::Type::Any) {
    childrenTypeIds = ArgumentsTypeIdsVector(args.size(), childrenTypeIds.front());
  }

  for (size_t i = 0; i < args.size(); i++) {
    const ArgumentPtr &arg = args[i];
    const MathObjectTypeId typeId = childrenTypeIds[i];

    if (const auto childExpr = cast<IExpression>(arg)) {
      const std::shared_ptr<IFunction> childFunc = childExpr->getFunction();
      const MathObjectTypeId childTypeId = childFunc->getReturnTypeId();

      if (childTypeId != Variable::getTypeIdStatic() &&
          !isBaseOf(typeId, childTypeId) &&
          !isBaseOf(childTypeId, typeId)) {

        throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(args));
      }
    }
    else if (const auto childConst = cast<IConstant>(arg)) {
      const MathObjectTypeId childTypeId = childConst->getReturnTypeId();

      if (!isBaseOf(typeId, childTypeId) && !isBaseOf(childTypeId, typeId)) {
        throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(args));
      }
    }
    else {
      MathObjectTypeId childTypeId = arg->getTypeId();

      if (childTypeId != Variable::getTypeIdStatic() && !isBaseOf(typeId, childTypeId)) {
        throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(args));
      }
    }
  }
}

void Expression::preciseRec(ArgumentPtr &arg, uint8_t precision) {
  if (const auto realArg = cast<Real>(arg)) {
    arg = std::make_shared<Real>(realArg->precise(precision));
  }
  else if (const auto exprArg = cast<IExpression>(arg)) {
    ArgumentsPtrVector newChildren = exprArg->getChildren();

    for (auto &child : newChildren) {
      preciseRec(child, precision);
    }

    auto newExprArg = cast<IExpression>(exprArg->clone());
    newExprArg->setChildren(newChildren);
    arg = ArgumentPtr(std::move(newExprArg));
  }
}

std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsPtrVector &args) {
  Expression res(makeExpr(func, args));
  return res.getChildren().front()->clone();
}

std::unique_ptr<IMathObject> makeExprChecked(const IFunction &func, const ArgumentsRefVector &args) {
  return makeExprChecked(func, argumentRefVectorToArgumentPtrVector(args));
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsPtrVector &args) {
  if (auto expr = Parser::parse(Expression::getExpressionMakers(), func.toString(), args)) {
    return expr;
  }

  return std::make_unique<FunctionExpression>(func, args);
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentsRefVector &args) {
  return makeExpr(func, argumentRefVectorToArgumentPtrVector(args));
}

void Expression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 1) {
    throw InvalidInputFunctionException("", argumentVectorToStringVector(childVect));
  }

  *this = Expression(childVect.front());
}

void Expression::setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) {
  IExpression::setVariables(varsToVals);
}

void Expression::setVariable(const Variable &var, const Expression &val) {
  setVariables({{var, val.child}});
}

Expression operator+(const Variable &lhs, const Variable &rhs) {
  return Expression(addExpr(lhs, rhs));
}

Expression operator+(const Expression &lhs, const Variable &rhs) {
  return Expression(addExpr(lhs.getChildren().front(), rhs.clone()));
}

Expression operator+(const Variable &lhs, const Expression &rhs) {
  return Expression(addExpr(lhs.clone(), rhs.getChildren().front()));
}

Expression operator-(const Variable &lhs, const Variable &rhs) {
  return Expression(subExpr(lhs, rhs));
}

Expression operator-(const Expression &lhs, const Variable &rhs) {
  return Expression(subExpr(lhs.getChildren().front(), rhs.clone()));
}

Expression operator-(const Variable &lhs, const Expression &rhs) {
  return Expression(subExpr(lhs.clone(), rhs.getChildren().front()));
}

Expression operator*(const Variable &lhs, const Variable &rhs) {
  return Expression(mulExpr(lhs, rhs));
}

Expression operator*(const Expression &lhs, const Variable &rhs) {
  return Expression(mulExpr(lhs.getChildren().front(), rhs.clone()));
}

Expression operator*(const Variable &lhs, const Expression &rhs) {
  return Expression(mulExpr(lhs.clone(), rhs.getChildren().front()));
}

Expression operator/(const Variable &lhs, const Variable &rhs) {
  return Expression(divExpr(lhs, rhs));
}

Expression operator/(const Expression &lhs, const Variable &rhs) {
  return Expression(divExpr(lhs.getChildren().front(), rhs.clone()));
}

Expression operator/(const Variable &lhs, const Expression &rhs) {
  return Expression(divExpr(lhs.clone(), rhs.getChildren().front()));
}

}
