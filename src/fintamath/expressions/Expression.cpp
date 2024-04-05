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
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
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

Expression::Expression(const std::string &str) : child(parseExpr(str)) {
}

Expression::Expression(const ArgumentPtr &obj) : child(compress(obj)) {
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(const int64_t val) : child(Integer(val).clone()) {
}

std::string Expression::toString() const noexcept {
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
  Expression::approximateChild(approxExpr.child);
  Expression::setPrecisionChild(approxExpr.child, precision, cache[precision]);
  approxExpr.updateStringMutable();

  return approxExpr;
}

const std::shared_ptr<IFunction> &Expression::getFunction() const noexcept {
  static const std::shared_ptr<IFunction> func;
  return func;
}

const ArgumentPtrVector &Expression::getChildren() const noexcept {
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

std::unique_ptr<IMathObject> parseExpr(const std::string &str) {
  try {
    auto tokens = Tokenizer::tokenize(str);
    auto terms = Expression::tokensToTerms(tokens);
    auto stack = Expression::termsToOperands(terms);
    auto obj = Expression::operandsToObject(stack);
    return obj;
  }
  catch (const InvalidInputException &) {
    throw InvalidInputException(str);
  }
}

TermVector Expression::tokensToTerms(TokenVector &tokens) {
  if (tokens.empty()) {
    throw InvalidInputException("");
  }

  TermVector terms(tokens.size());

  for (size_t i = 0U; i < terms.size(); i++) {
    terms[i] = parseTerm(tokens[i]);
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
        moveFunctionTermsToOperands(operands, functions, {});

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
        moveFunctionTermsToOperands(operands, functions, oper);
        priority = oper->getPriority();
      }

      functions.emplace(std::move(term), priority);
    }
    else {
      operands.emplace(std::move(term.value));
    }
  }

  moveFunctionTermsToOperands(operands, functions, {});

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

    if (!func->isVariadic() && func->getArgumentClasses().size() != children.size()) {
      func = parseFunction(func->toString(), children.size());

      if (!func) {
        throw InvalidInputException("");
      }
    }

    return makeExpr(*func, std::move(children));
  }

  return arg;
}

std::unique_ptr<IFunction> Expression::parseFunction(const std::string &str, const size_t argNum) {
  for (auto &func : IFunction::parse(str)) {
    if (func->getArgumentClasses().size() == argNum) {
      return std::move(func);
    }
  }

  return {};
}

auto Expression::parseOperator(const std::string &str, const IOperator::Priority priority) -> std::unique_ptr<IOperator> {
  for (auto &oper : IOperator::parse(str)) {
    if (oper->getPriority() == priority) {
      return std::move(oper);
    }
  }

  return {};
}

Term Expression::parseTerm(const std::string &str) {
  static auto termValueParser = [] {
    Parser<std::unique_ptr<IMathObject>> parser;
    parser.registerType<IFunction>();
    parser.registerType<ILiteral>();
    parser.registerType<INumber>();
    return parser;
  }();

  Term term = {str, {}};

  if (auto termValue = termValueParser.parseFirst(str)) {
    term.value = std::move(*termValue);
  }

  return term;
}

void Expression::moveFunctionTermsToOperands(OperandStack &operands, std::stack<FunctionTerm> &functions, const IOperator *nextOper) {
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

    term.value = parseOperator(term.name, IOperator::Priority::PrefixUnary);
    isFixed = static_cast<bool>(term.value);
  }

  if (auto &term = terms.back();
      is<IOperator>(term.value) &&
      !isPostfixOperator(term.value.get())) {

    term.value = parseOperator(term.name, IOperator::Priority::PostfixUnary);
    isFixed = isFixed && static_cast<bool>(term.value);
  }

  if (!isFixed) {
    throw InvalidInputException("");
  }

  if (terms.size() < 3) {
    return;
  }

  for (size_t i = 1; i + 1 < terms.size(); i++) {
    auto &term = terms[i];
    const auto &termPrev = terms[i - 1];

    if (is<IOperator>(term.value) &&
        !isPrefixOperator(term.value.get()) &&
        !canNextTermBeBinaryOperator(termPrev)) {

      term.value = parseOperator(term.name, IOperator::Priority::PrefixUnary);
      isFixed = isFixed && term.value;
    }
  }

  for (size_t i = terms.size() - 2; i > 0; i--) {
    auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (is<IOperator>(term.value) &&
        !isPostfixOperator(term.value.get()) &&
        !canPrevTermBeBinaryOperator(termNext)) {

      term.value = parseOperator(term.name, IOperator::Priority::PostfixUnary);
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
  return oper && oper->getArgumentClasses().size() == 2;
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

Expression::ExpressionMaker &Expression::getExpressionMaker() {
  static ExpressionMaker map;
  return map;
}

void Expression::validateFunctionArgs(const IFunction &func, const ArgumentPtrVector &args) {
  const ArgumentTypeVector &expectedArgTypes = func.getArgumentClasses();

  if (args.empty() || (!func.isVariadic() && args.size() < expectedArgTypes.size())) {
    throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
  }

  const bool doesArgSizeMatch = !func.isVariadic() && args.size() == expectedArgTypes.size();
  MathObjectClass expectedType = expectedArgTypes.front();

  for (size_t i = 0; i < args.size(); i++) {
    if (doesArgSizeMatch) {
      expectedType = expectedArgTypes[i];
    }

    if (const ArgumentPtr &arg = args[i]; !doesArgMatch(expectedType, arg)) {
      throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
    }
  }
}

bool Expression::doesArgMatch(const MathObjectClass &expectedType, const ArgumentPtr &arg) {
  if (const auto childExpr = cast<IExpression>(arg)) {
    const std::shared_ptr<IFunction> &childFunc = childExpr->getFunction();
    const MathObjectClass childType = childFunc->getReturnClass();

    if (childType != Variable::getClassStatic() &&
        !is(expectedType, childType) &&
        !is(childType, expectedType)) {

      return false;
    }
  }
  else if (const auto childConst = cast<IConstant>(arg)) {
    if (const MathObjectClass childType = childConst->getReturnClass();
        !is(expectedType, childType) &&
        !is(childType, expectedType)) {

      return false;
    }
  }
  else {
    if (const MathObjectClass childType = arg->getClass();
        childType != Variable::getClassStatic() &&
        !is(expectedType, childType)) {

      return false;
    }
  }

  return true;
}

namespace detail {

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, ArgumentPtrVector args) {
  std::ranges::transform(args, args.begin(), &Expression::compress);
  Expression::validateFunctionArgs(func, args);

  if (const auto strToConstr = Expression::getExpressionMaker().find(func.getClass());
      strToConstr != Expression::getExpressionMaker().end()) {

    if (auto expr = strToConstr->second(std::move(args))) {
      return expr;
    }
  }

  return FunctionExpression(func, std::move(args)).clone();
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentRefVector &args) {
  return makeExpr(func, argumentRefVectorToArgumentPtrVector(args));
}

}

}
