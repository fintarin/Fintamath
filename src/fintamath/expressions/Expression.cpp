#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ranges>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/Cache.hpp"
#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/ExpressionParser.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/other/Comma.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

using namespace detail;

Expression::Expression() : child(Integer(0).clone()) {
}

Expression::Expression(const std::string &str) : child(parseFintamath(str)) {
}

Expression::Expression(const ArgumentPtr &obj) : child(compress(obj)) {
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(const int64_t val) : child(Integer(val).clone()) {
}

std::string Expression::toString() const {
  simplifyMutable();
  return stringCached;
}

Expression approximate(const Expression &rhs, const unsigned precision) {
  const Real::ScopedSetPrecision setPrecision(precision);

  static Cache<unsigned, Integer> cache([](const unsigned inPrecision) {
    static const Integer powBase = 10;
    return pow(powBase, inPrecision);
  });

  Expression approxExpr = rhs;
  Expression::approximateSimplifyChild(approxExpr.child);
  Expression::setPrecisionChild(approxExpr.child, precision, cache[precision]);
  approxExpr.updateStringMutable();

  return approxExpr;
}

const std::shared_ptr<IFunction> &Expression::getFunction() const {
  static const std::shared_ptr<IFunction> func;
  return func;
}

Expression &Expression::add(const Expression &rhs) {
  child = makeExpr(Add{}, *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  child = makeExpr(Sub{}, *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::multiply(const Expression &rhs) {
  child = makeExpr(Mul{}, *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::divide(const Expression &rhs) {
  child = makeExpr(Div{}, *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::negate() {
  child = makeExpr(Neg{}, *child);
  isSimplified = false;
  return *this;
}

const ArgumentPtrVector &Expression::getChildren() const {
  simplifyMutable();
  childrenCached.front() = child;
  return childrenCached;
}

void Expression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.size() != 1) {
    throw InvalidInputFunctionException("", argumentVectorToStringVector(childVect));
  }

  *this = Expression(childVect.front());
}

void Expression::setVariables(const std::vector<std::pair<Variable, ArgumentPtr>> &varsToVals) {
  simplifyMutable();
  IExpression::setVariables(varsToVals);
}

void Expression::setVariable(const Variable &var, const Expression &val) {
  setVariables({{var, val.child}});
}

ArgumentPtr Expression::simplify() const {
  simplifyMutable();
  return child;
}

void Expression::simplifyMutable() const {
  if (isSimplified) {
    return;
  }

  ArgumentPtr prevChild = child;
  simplifyChild(child);

  while (*child != *prevChild) {
    prevChild = child;
    simplifyChild(child);
  }

  isSimplified = true;
  updateStringMutable();
}

void Expression::updateStringMutable() const {
  stringCached = child->toString();
}

std::unique_ptr<IMathObject> parseFintamath(const std::string &str) {
  try {
    const auto tokens = Tokenizer::tokenize(str);
    auto terms = Expression::tokensToTerms(tokens);
    auto stack = Expression::termsToOperands(terms);
    auto obj = Expression::operandsToObject(stack);
    return obj;
  }
  catch (const InvalidInputException &) {
    throw InvalidInputException(str);
  }
}

TermVector Expression::tokensToTerms(const TokenVector &tokens) {
  if (tokens.empty()) {
    throw InvalidInputException("");
  }

  TermVector terms(tokens.size());

  for (const auto i : stdv::iota(0U, terms.size())) {
    if (auto term = getTermParser().parse(tokens[i])) {
      terms[i] = std::move(*term);
    }
    else {
      terms[i] = Term(tokens[i], std::unique_ptr<IMathObject>{});
    }
  }

  fixOperatorTypes(terms);
  insertMultiplications(terms);
  collapseFactorials(terms);

  return terms;
}

// Use the shunting yard algorithm
// https://en.m.wikipedia.org/wiki/Shunting_yard_algorithm
OperandStack Expression::termsToOperands(TermVector &terms) {
  OperandStack operands;
  FunctionTermStack functions;

  for (auto &term : terms) {
    if (!term.value) {
      if (term.name == "(") {
        functions.emplace(std::move(term), std::optional<IOperator::Priority>{});
      }
      else if (term.name == ")") {
        moveFunctionsToOperands(operands, functions, {});

        if (functions.empty()) {
          throw InvalidInputException("");
        }

        functions.pop();
      }
      else {
        throw InvalidInputException("");
      }
    }
    else if (is<IFunction>(term.value)) {
      std::optional<IOperator::Priority> priority;

      if (const auto *oper = cast<IOperator>(term.value.get())) {
        moveFunctionsToOperands(operands, functions, oper);
        priority = oper->getPriority();
      }

      functions.emplace(std::move(term), priority);
    }
    else {
      operands.emplace(std::move(term.value));
    }
  }

  moveFunctionsToOperands(operands, functions, {});

  if (!functions.empty()) {
    throw InvalidInputException("");
  }

  return operands;
}

std::unique_ptr<IMathObject> Expression::operandsToObject(OperandStack &operands) {
  if (operands.empty()) {
    throw InvalidInputException("");
  }

  std::unique_ptr<IMathObject> arg = std::move(operands.top());
  operands.pop();

  if (is<IFunction>(arg)) {
    auto func = cast<IFunction>(std::move(arg));
    const ArgumentPtr rhsChild = operandsToObject(operands);

    if (isBinaryOperator(func.get())) {
      const ArgumentPtr lhsChild = operandsToObject(operands);
      return makeExpr(*func, {lhsChild, rhsChild});
    }

    ArgumentPtrVector children = unwrapComma(rhsChild);

    if (!func->isVariadic() && func->getArgumentTypes().size() != children.size()) {
      func = IFunction::parse(func->toString(), children.size());

      if (!func) {
        throw InvalidInputException("");
      }
    }

    return makeExpr(*func, std::move(children));
  }

  return arg;
}

void Expression::moveFunctionsToOperands(OperandStack &operands, std::stack<FunctionTerm> &functions, const IOperator *nextOper) {
  if (isPrefixOperator(nextOper)) {
    return;
  }

  while (!functions.empty() &&
         functions.top().term.name != "(" &&
         (!nextOper ||
          !functions.top().priority ||
          *functions.top().priority <= nextOper->getPriority())) {

    operands.emplace(std::move(functions.top().term.value));
    functions.pop();
  }
}

void Expression::insertMultiplications(TermVector &terms) {
  static const ArgumentPtr mul = Mul{}.clone();

  for (size_t i = 1; i < terms.size(); i++) {
    if (canNextTermBeBinaryOperator(terms[i - 1]) &&
        canPrevTermBeBinaryOperator(terms[i])) {

      Term term(mul->toString(), mul->clone());
      terms.insert(terms.begin() + static_cast<ptrdiff_t>(i), std::move(term));
      i++;
    }
  }
}

void Expression::fixOperatorTypes(TermVector &terms) {
  bool isFixed = true;

  if (auto &term = terms.front();
      is<IOperator>(term.value) &&
      !isPrefixOperator(term.value.get())) {

    term.value = IOperator::parse(term.name, IOperator::Priority::PrefixUnary);
    isFixed = static_cast<bool>(term.value);
  }

  if (auto &term = terms.back();
      is<IOperator>(term.value) &&
      !isPostfixOperator(term.value.get())) {

    term.value = IOperator::parse(term.name, IOperator::Priority::PostfixUnary);
    isFixed = isFixed && static_cast<bool>(term.value);
  }

  if (!isFixed) {
    throw InvalidInputException("");
  }

  if (terms.size() < 3) {
    return;
  }

  for (const auto i : stdv::iota(1U, terms.size() - 1)) {
    auto &term = terms[i];
    const auto &termPrev = terms[i - 1];

    if (is<IOperator>(term.value) &&
        !isPrefixOperator(term.value.get()) &&
        !canNextTermBeBinaryOperator(termPrev)) {

      term.value = IOperator::parse(term.name, IOperator::Priority::PrefixUnary);
      isFixed = isFixed && term.value;
    }
  }

  for (const auto i : stdv::iota(1U, terms.size() - 1) | stdv::reverse) {
    auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (is<IOperator>(term.value) &&
        !isPostfixOperator(term.value.get()) &&
        !canPrevTermBeBinaryOperator(termNext)) {

      term.value = IOperator::parse(term.name, IOperator::Priority::PostfixUnary);
      isFixed = isFixed && term.value;
    }
  }

  if (!isFixed) {
    throw InvalidInputException("");
  }
}

void Expression::collapseFactorials(TermVector &terms) {
  for (size_t i = 1; i + 1 < terms.size(); i++) {
    auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (is<Factorial>(term.value) && is<Factorial>(termNext.value)) {
      const auto &oldFactorial = cast<Factorial>(*term.value);
      term.value = Factorial(oldFactorial.getOrder() + 1).clone();

      terms.erase(terms.begin() + static_cast<ptrdiff_t>(i) + 1);
      i--;
    }
  }
}

bool Expression::canNextTermBeBinaryOperator(const Term &term) {
  return !(isPrefixOperator(term.value.get()) ||
           isBinaryOperator(term.value.get()) ||
           isNonOperatorFunction(term.value.get()) ||
           term.name == "(" ||
           term.name == ",");
}

bool Expression::canPrevTermBeBinaryOperator(const Term &term) {
  return !(isPostfixOperator(term.value.get()) ||
           isBinaryOperator(term.value.get()) ||
           term.name == ")" ||
           term.name == ",");
}

bool Expression::isBinaryOperator(const IMathObject *val) {
  const auto *oper = cast<IOperator>(val);
  return oper && oper->getArgumentTypes().size() == 2;
}

bool Expression::isPrefixOperator(const IMathObject *val) {
  const auto *oper = cast<IOperator>(val);
  return oper && oper->getPriority() == IOperator::Priority::PrefixUnary;
}

bool Expression::isPostfixOperator(const IMathObject *val) {
  const auto *oper = cast<IOperator>(val);
  return oper && oper->getPriority() == IOperator::Priority::PostfixUnary;
}

bool Expression::isNonOperatorFunction(const IMathObject *val) {
  return is<IFunction>(val) && !is<IOperator>(val);
}

ArgumentPtrVector Expression::unwrapComma(const ArgumentPtr &child) {
  if (const auto childExpr = cast<IExpression>(child);
      childExpr &&
      is<Comma>(childExpr->getFunction())) {

    const ArgumentPtr &lhs = childExpr->getChildren().front();
    const ArgumentPtr &rhs = childExpr->getChildren().back();

    ArgumentPtrVector children = unwrapComma(lhs);
    children.push_back(rhs);
    return children;
  }

  return {child};
}

ArgumentPtr Expression::compress(const ArgumentPtr &child) {
  if (const auto expr = cast<Expression>(child)) {
    return expr->child;
  }

  return child;
}

Expression::TermParser &Expression::getTermParser() {
  static TermParser parser;
  return parser;
}

Expression::ExpressionParser &Expression::getExpressionParser() {
  static ExpressionParser parser;
  return parser;
}

void Expression::validateFunctionArgs(const IFunction &func, const ArgumentPtrVector &args) {
  const ArgumentTypeVector &expectedArgTypes = func.getArgumentTypes();

  if (args.empty() || (!func.isVariadic() && args.size() < expectedArgTypes.size())) {
    throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
  }

  const bool doesArgSizeMatch = !func.isVariadic() && args.size() == expectedArgTypes.size();
  MathObjectType expectedType = expectedArgTypes.front();

  for (const auto i : stdv::iota(0U, args.size())) {
    if (doesArgSizeMatch) {
      expectedType = expectedArgTypes[i];
    }

    if (const ArgumentPtr &arg = args[i]; !doesArgMatch(expectedType, arg)) {
      throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
    }
  }
}

bool Expression::doesArgMatch(const MathObjectType &expectedType, const ArgumentPtr &arg) {
  if (const auto childExpr = cast<IExpression>(arg)) {
    const std::shared_ptr<IFunction> &childFunc = childExpr->getFunction();
    const MathObjectType childType = childFunc->getReturnType();

    if (childType != Variable::getTypeStatic() &&
        !isBaseOf(expectedType, childType) &&
        !isBaseOf(childType, expectedType)) {

      return false;
    }
  }
  else if (const auto childConst = cast<IConstant>(arg)) {
    if (const MathObjectType childType = childConst->getReturnType();
        !isBaseOf(expectedType, childType) &&
        !isBaseOf(childType, expectedType)) {

      return false;
    }
  }
  else {
    if (const MathObjectType childType = arg->getType();
        childType != Variable::getTypeStatic() &&
        !isBaseOf(expectedType, childType)) {

      return false;
    }
  }

  return true;
}

Expression operator+(const Variable &lhs, const Variable &rhs) {
  return Expression(addExpr(lhs, rhs));
}

Expression operator+(const Expression &lhs, const Variable &rhs) {
  return Expression(addExpr(lhs, rhs));
}

Expression operator+(const Variable &lhs, const Expression &rhs) {
  return Expression(addExpr(lhs, rhs));
}

Expression operator-(const Variable &lhs, const Variable &rhs) {
  return Expression(subExpr(lhs, rhs));
}

Expression operator-(const Expression &lhs, const Variable &rhs) {
  return Expression(subExpr(lhs, rhs));
}

Expression operator-(const Variable &lhs, const Expression &rhs) {
  return Expression(subExpr(lhs, rhs));
}

Expression operator*(const Variable &lhs, const Variable &rhs) {
  return Expression(mulExpr(lhs, rhs));
}

Expression operator*(const Expression &lhs, const Variable &rhs) {
  return Expression(mulExpr(lhs, rhs));
}

Expression operator*(const Variable &lhs, const Expression &rhs) {
  return Expression(mulExpr(lhs, rhs));
}

Expression operator/(const Variable &lhs, const Variable &rhs) {
  return Expression(divExpr(lhs, rhs));
}

Expression operator/(const Expression &lhs, const Variable &rhs) {
  return Expression(divExpr(lhs, rhs));
}

Expression operator/(const Variable &lhs, const Expression &rhs) {
  return Expression(divExpr(lhs, rhs));
}

namespace detail {

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, ArgumentPtrVector args) {
  stdr::transform(args, args.begin(), &Expression::compress);
  Expression::validateFunctionArgs(func, args);

  if (auto expr = Expression::getExpressionParser().parse(func.toString(), std::move(args))) {
    return expr;
  }

  return FunctionExpression(func, std::move(args)).clone();
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentRefVector &args) {
  return makeExpr(func, argumentRefVectorToArgumentPtrVector(args));
}

}

}
