#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ranges>
#include <stack>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include "fintamath/core/Cache.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
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
#include "fintamath/functions/arithmetic/MulOper.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/other/Comma.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Expression)

using namespace detail;

Expression::Expression() : Expression(0) {
}

Expression::Expression(const std::string &str) : Expression(parseRawExpr(str)) {
}

Expression::Expression(const ArgumentPtr &obj) : child(compress(obj)) {
  simplifyChild(child);
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(const int64_t val) : Expression(Integer(val).clone()) {
}

std::string Expression::toString() const {
  return child->toString();
}

std::unique_ptr<IMathObject> Expression::toMinimalObject() const {
  return child->clone();
}

const std::shared_ptr<IFunction> &Expression::getFunction() const {
  static const std::shared_ptr<IFunction> func;
  return func;
}

const ArgumentPtrVector &Expression::getChildren() const {
  childrenCached = {child};
  return childrenCached;
}

Expression approximate(const Expression &rhs, unsigned precision) {
  Real::ScopedSetPrecision setPrecision(precision);
  ArgumentPtr newChild = rhs.child;
  Expression::approximateChild(newChild);
  return Expression(newChild);
}

std::unique_ptr<IMathObject> parseRawExpr(const std::string &str) try {
  auto tokens = Tokenizer::tokenize(str);
  auto terms = Expression::tokensToTerms(tokens);
  auto objects = Expression::termsToObjects(terms);
  auto expr = Expression::objectsToExpr(objects);
  return expr;
}
catch (const InvalidInputException &exc) {
  std::string message = exc.what();
  message[0] = static_cast<char>(std::tolower(message[0]));

  throw InvalidInputException(fmt::format(
      R"(Unable to parse an expression from "{}" ({}))",
      str,
      message));
}

TermVector Expression::tokensToTerms(TokenVector &tokens) {
  if (tokens.empty()) {
    throw InvalidInputException("empty input");
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
ObjectStack Expression::termsToObjects(TermVector &terms) {
  ObjectStack objects;
  FunctionTermStack functions;

  for (auto &term : terms) {
    if (!term.value) {
      if (term.name == "(") {
        functions.emplace(std::move(term), std::optional<IOperator::Priority>{});
      }
      else if (term.name == ")") {
        moveFunctionTermsToObjects(objects, functions, {});

        if (functions.empty()) {
          throw InvalidInputException("bracket mismatch");
        }

        functions.pop();
      }
      else {
        throw InvalidInputException(
            fmt::format(R"(invalid term "{}")",
                        term.name));
      }
    }
    else if (is<IFunction>(term.value)) {
      std::optional<IOperator::Priority> priority;

      if (const auto *oper = cast<IOperator>(term.value.get())) {
        moveFunctionTermsToObjects(objects, functions, oper);
        priority = oper->getPriority();
      }

      functions.emplace(std::move(term), priority);
    }
    else {
      objects.emplace(std::move(term.value));
    }
  }

  moveFunctionTermsToObjects(objects, functions, {});

  if (!functions.empty()) {
    throw InvalidInputException("bracket mismatch");
  }

  return objects;
}

std::unique_ptr<IMathObject> Expression::objectsToExpr(ObjectStack &objects) {
  if (objects.empty()) {
    throw InvalidInputException("incomplete expression inside brackets");
  }

  std::unique_ptr<IMathObject> arg = std::move(objects.top());
  objects.pop();

  if (is<IFunction>(arg)) {
    auto func = cast<IFunction>(std::move(arg));
    const ArgumentPtr rhsChild = objectsToExpr(objects);

    if (isBinaryOperator(func.get())) {
      const ArgumentPtr lhsChild = objectsToExpr(objects);
      return makeExprWithValidation(*func, {lhsChild, rhsChild});
    }

    ArgumentPtrVector children = unwrapComma(rhsChild);

    if (!func->isVariadic() && func->getArgumentClasses().size() != children.size()) {
      std::string funcStr = func->toString();
      func = findFunction(funcStr, children.size());

      if (!func) {
        throw InvalidInputException(fmt::format(
            R"(function "{}" with {} arguments not found)",
            funcStr,
            children.size()));
      }
    }

    return makeExprWithValidation(*func, std::move(children));
  }

  return arg;
}

std::unique_ptr<IFunction> Expression::findFunction(const std::string &str, const size_t argNum) {
  for (auto &func : IFunction::parse(str)) {
    if (func->getArgumentClasses().size() == argNum) {
      return std::move(func);
    }
  }

  return {};
}

auto Expression::findOperator(const std::string &str, const IOperator::Priority priority) -> std::unique_ptr<IOperator> {
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

void Expression::moveFunctionTermsToObjects(ObjectStack &objects, std::stack<FunctionTerm> &functions, const IOperator *nextOper) {
  if (isPrefixOperator(nextOper)) {
    return;
  }

  while (!functions.empty() &&
         functions.top().term.name != "(" &&
         (!nextOper ||
          !functions.top().priority ||
          *functions.top().priority <= nextOper->getPriority())) {

    objects.emplace(std::move(functions.top().term.value));
    functions.pop();
  }
}

void Expression::insertMultiplications(TermVector &terms) {
  static const ArgumentPtr mul = MulOper{}.clone();

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
  if (auto &term = terms.front();
      is<IOperator>(term.value) &&
      !isPrefixOperator(term.value.get())) {

    term.value = findOperator(term.name, IOperator::Priority::PrefixUnary);

    if (!term.value) {
      throw InvalidInputException(fmt::format(
          R"(incomplite expression with operator "{}")",
          term.name));
    }
  }

  if (auto &term = terms.back();
      is<IOperator>(term.value) &&
      !isPostfixOperator(term.value.get())) {

    term.value = findOperator(term.name, IOperator::Priority::PostfixUnary);

    if (!term.value) {
      throw InvalidInputException(fmt::format(
          R"(incomplite expression with operator "{}")",
          term.name));
    }
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

      term.value = findOperator(term.name, IOperator::Priority::PrefixUnary);

      if (!term.value) {
        throw InvalidInputException(fmt::format(
            R"(incomplite expression with operator "{}")",
            term.name));
      }
    }
  }

  for (size_t i = terms.size() - 2; i > 0; i--) {
    auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (is<IOperator>(term.value) &&
        !isPostfixOperator(term.value.get()) &&
        !canPrevTermBeBinaryOperator(termNext)) {

      term.value = findOperator(term.name, IOperator::Priority::PostfixUnary);

      if (!term.value) {
        throw InvalidInputException(fmt::format(
            R"(incomplite expression with operator "{}")",
            term.name));
      }
    }
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

  if (args.size() != expectedArgTypes.size()) {
    if (!func.isVariadic()) {
      throw InvalidInputException(fmt::format(
          R"(Unable to call {} "{}" with {} argument{} (expected {}))",
          func.getClass()->getName(),
          func.toString(),
          args.size(),
          args.size() != 1 ? "s" : "",
          func.getArgumentClasses().size()));
    }

    if (args.empty()) {
      throw InvalidInputException(fmt::format(
          R"(Unable to call {} "{}" with 0 arguments (expected > 0))",
          func.getClass()->getName(),
          func.toString()));
    }
  }

  const bool doesArgSizeMatch = !func.isVariadic() && args.size() == expectedArgTypes.size();
  MathObjectClass expectedClass = expectedArgTypes.front();

  for (size_t i = 0; i < args.size(); i++) {
    const ArgumentPtr &arg = args[i];

    if (doesArgSizeMatch) {
      expectedClass = expectedArgTypes[i];
    }

    if (auto [argClass, doesMatch] = doesArgMatch(expectedClass, arg); !doesMatch) {
      throw InvalidInputException(fmt::format(
          R"(Unable to call {} "{}" with argument #{} {} "{}" (expected {}))",
          func.getClass()->getName(),
          func.toString(),
          i,
          argClass->getName(),
          arg->toString(),
          expectedClass->getName()));
    }
  }
}

std::pair<MathObjectClass, bool> Expression::doesArgMatch(const MathObjectClass &expectedClass, const ArgumentPtr &arg) {
  if (const auto childExpr = cast<IExpression>(arg)) {
    const MathObjectClass argReturnClass = childExpr->getFunction()->getReturnClass();

    if (argReturnClass != Variable::getClassStatic() &&
        !is(expectedClass, argReturnClass) &&
        !is(argReturnClass, expectedClass)) {

      return {argReturnClass, false};
    }
  }
  else if (const auto argConst = cast<IConstant>(arg)) {
    if (const MathObjectClass argReturnClass = argConst->getReturnClass();
        !is(expectedClass, argReturnClass) &&
        !is(argReturnClass, expectedClass)) {

      return {argReturnClass, false};
    }
  }
  else {
    if (const MathObjectClass argClass = arg->getClass();
        argClass != Variable::getClassStatic() &&
        !is(expectedClass, argClass)) {

      return {argClass, false};
    }
  }

  return {arg->getClass(), true};
}

namespace detail {

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, ArgumentPtrVector args) {
  if (func.isVariadic() && args.size() == 1) {
    return std::move(args.front())->clone();
  }

  if (const auto strToConstr = Expression::getExpressionMaker().find(func.getClass());
      strToConstr != Expression::getExpressionMaker().end()) {

    if (auto expr = strToConstr->second(std::move(args))) {
      return expr;
    }
  }

  return FunctionExpression(func, std::move(args)).clone();
}

std::unique_ptr<IMathObject> makeExprWithValidation(const IFunction &func, ArgumentPtrVector args) {
  std::ranges::transform(args, args.begin(), &Expression::compress);
  Expression::validateFunctionArgs(func, args);
  return makeExpr(func, std::move(args));
}

}

}
