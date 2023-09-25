#include "fintamath/expressions/Expression.hpp"

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
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Expression::Expression() : child(Integer(0).clone()) {
}

Expression::Expression(const std::string &str) : child(fintamath::parseExpr(str)) {
}

Expression::Expression(const ArgumentPtr &obj) : child(compress(obj)) {
}

Expression::Expression(const IMathObject &obj) : Expression(obj.clone()) {
}

Expression::Expression(int64_t val) : child(Integer(val).clone()) {
}

std::string Expression::toString() const {
  simplifyMutable();
  return stringCached;
}

Expression Expression::precise(uint8_t precision) const {
  // TODO: rework so that small ints don't convert to reals
  // TODO: move this transfer to the approximation function
  simplifyMutable();
  Expression preciseExpr(preciseSimplify());
  preciseExpr.simplifyMutable();
  preciseRec(preciseExpr.child, precision);
  preciseExpr.updateStringMutable();
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

  if (res.parseOperator(terms, start, end) ||
      res.parseFunction(terms, start, end) ||
      res.parseBrackets(terms, start, end) ||
      res.parseTerm(terms, start, end)) {

    return res.child;
  }

  throw InvalidInputException(Expression::termsToString(terms));
}

bool Expression::parseOperator(const TermVector &terms, size_t start, size_t end) {
  // TODO! use more efficient algorithm

  size_t foundOperPos = std::numeric_limits<size_t>::max();
  IOperator::Priority foundOperPriority = IOperator::Priority::Any;
  bool isPreviousTermBinaryOper = false;

  for (size_t i = start; i < end; i++) {
    if (skipBrackets(terms, i)) {
      isPreviousTermBinaryOper = false;
      i--;
      continue;
    }

    if (auto oper = cast<IOperator>(terms[i]->value)) {
      if (!isPreviousTermBinaryOper) {
        IOperator::Priority priority = oper->getOperatorPriority();

        bool newOperFound = foundOperPriority == IOperator::Priority::Any ||
                            foundOperPriority < priority;

        newOperFound = newOperFound || (isBinaryOperator(oper) &&
                                        foundOperPriority == priority &&
                                        foundOperPos < i);

        if (newOperFound) {
          foundOperPriority = priority;
          foundOperPos = i;
        }

        isPreviousTermBinaryOper = isBinaryOperator(oper);
      }
    }
    else {
      isPreviousTermBinaryOper = false;
    }
  }

  if (foundOperPos == std::numeric_limits<size_t>::max()) {
    return false;
  }

  auto foundOper = cast<IOperator>(terms[foundOperPos]->value);

  if (isPrefixOperator(foundOper)) {
    ArgumentPtr arg = parseExpr(terms, start + 1, end);
    child = makeExpr(*foundOper, arg);
  }
  else if (isPostfixOperator(foundOper)) {
    ArgumentPtr arg = parseExpr(terms, start, end - 1);
    child = makeExpr(*foundOper, arg);
  }
  else {
    ArgumentPtr lhsArg = parseExpr(terms, start, foundOperPos);
    ArgumentPtr rhsArg = parseExpr(terms, foundOperPos + 1, end);
    child = makeExpr(*foundOper, lhsArg, rhsArg);
  }

  child = compress(child);

  return true;
}

bool Expression::parseFunction(const TermVector &terms, size_t start, size_t end) {
  const auto &term = terms[start];

  if (start + 1 >= end) {
    return false;
  }

  if (auto termFirstValue = term->value;
      !is<IFunction>(termFirstValue) || is<IOperator>(termFirstValue)) {

    return false;
  }

  start++;
  cutBrackets(terms, start, end);

  ArgumentPtrVector args = parseFunctionArgs(terms, start, end);
  std::shared_ptr<const IFunction> func = cast<IFunction>(term->value);

  if (func->getFunctionType() != IFunction::Type(args.size()) &&
      func->getFunctionType() != IFunction::Type::Any) {

    if (auto newFunc = IFunction::parse(term->name, IFunction::Type(args.size()))) {
      func = std::move(newFunc);
    }
    else {
      return false;
    }
  }

  child = makeExpr(*func, args);

  return true;
}

ArgumentPtrVector Expression::parseFunctionArgs(const TermVector &terms, size_t start, size_t end) {
  if (start >= end) {
    return {};
  }

  ArgumentPtrVector funcArgs;

  for (size_t i = start; i < end; i++) {
    if (terms[i]->name == "(") {
      skipBrackets(terms, i);
    }

    if (terms[i]->name == ",") {
      if (i == 0 || i + 1 == end) {
        throw InvalidInputException(termsToString(terms));
      }

      ArgumentPtr lhsArg = parseExpr(terms, start, i);
      ArgumentPtrVector rhsArgs = parseFunctionArgs(terms, i + 1, end);

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

bool Expression::parseTerm(const TermVector &terms, size_t start, size_t end) {
  if (start + 1 != end || !terms[start]->value) {
    return false;
  }

  child = terms[start]->value;
  return true;
}

std::shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

Expression &Expression::add(const Expression &rhs) {
  child = makeExpr(Add(), *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::substract(const Expression &rhs) {
  child = makeExpr(Sub(), *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::multiply(const Expression &rhs) {
  child = makeExpr(Mul(), *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::divide(const Expression &rhs) {
  child = makeExpr(Div(), *child, *rhs.child);
  isSimplified = false;
  return *this;
}

Expression &Expression::negate() {
  child = makeExpr(Neg(), *child);
  isSimplified = false;
  return *this;
}

ArgumentPtrVector Expression::getChildren() const {
  simplifyMutable();
  return {child};
}

void Expression::setChildren(const ArgumentPtrVector &childVect) {
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

ArgumentPtr Expression::simplify() const {
  return child;
}

ArgumentPtr Expression::preciseSimplify() const {
  ArgumentPtr preciseChild = child;
  preciseSimplifyChild(preciseChild);
  return preciseChild;
}

void Expression::simplifyMutable() const {
  if (!isSimplified) {
    simplifyChild(child);
    isSimplified = true;
    updateStringMutable();
  }
}

void Expression::updateStringMutable() const {
  stringCached = child->toString();
}

TermVector Expression::tokensToTerms(const TokenVector &tokens) {
  if (tokens.empty()) {
    return {};
  }

  TermVector terms(tokens.size());

  for (auto i : std::views::iota(0U, terms.size())) {
    if (auto term = Parser::parse(getTermMakers(), (tokens[i]))) {
      terms[i] = std::move(term);
    }
    else {
      terms[i] = std::make_unique<Term>(tokens[i], ArgumentPtr());
    }
  }

  fixOperatorTypes(terms);
  insertMultiplications(terms);
  collapseFactorials(terms);

  return terms;
}

void Expression::insertMultiplications(TermVector &terms) {
  static const ArgumentPtr mul = Mul().clone();

  for (size_t i = 1; i < terms.size(); i++) {
    if (canNextTermBeBinaryOperator(*terms[i - 1]) &&
        canPrevTermBeBinaryOperator(*terms[i])) {

      auto term = std::make_shared<Term>(mul->toString(), mul);
      terms.insert(terms.begin() + ptrdiff_t(i), term);
      i++;
    }
  }
}

void Expression::fixOperatorTypes(TermVector &terms) {
  bool isFixed = true;

  if (const auto &term = terms.front();
      is<IOperator>(term->value) &&
      !isPrefixOperator(term->value)) {

    term->value = IOperator::parse(term->name, IOperator::Priority::PrefixUnary);
    isFixed = isFixed && term->value;
  }

  if (const auto &term = terms.back();
      is<IOperator>(term->value) &&
      !isPostfixOperator(term->value)) {

    term->value = IOperator::parse(term->name, IOperator::Priority::PostfixUnary);
    isFixed = isFixed && term->value;
  }

  if (terms.size() < 3) {
    return;
  }

  for (auto i : std::views::iota(1U, terms.size() - 1)) {
    const auto &term = terms[i];
    const auto &termPrev = terms[i - 1];

    if (is<IOperator>(term->value) &&
        !isPrefixOperator(term->value) &&
        !canNextTermBeBinaryOperator(*termPrev)) {

      term->value = IOperator::parse(term->name, IOperator::Priority::PrefixUnary);
      isFixed = isFixed && term->value;
    }
  }

  // TODO: use reverse(iota(1, terms.size() - 1)) when it is work
  for (size_t i = terms.size() - 2; i > 0; i--) {
    const auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (is<IOperator>(term->value) &&
        !isPostfixOperator(term->value) &&
        !canPrevTermBeBinaryOperator(*termNext)) {

      term->value = IOperator::parse(term->name, IOperator::Priority::PostfixUnary);
      isFixed = isFixed && term->value;
    }
  }

  if (!isFixed) {
    throw InvalidInputException(termsToString(terms));
  }
}

void Expression::collapseFactorials(TermVector &terms) {
  for (size_t i = 1; i + 1 < terms.size(); i++) {
    const auto &term = terms[i];
    const auto &termNext = terms[i + 1];

    if (auto factorial = cast<Factorial>(term->value);
        factorial &&
        is<Factorial>(termNext->value)) {

      Factorial newFactorial;
      newFactorial.setOrder(factorial->getOrder() + 1);
      term->value = newFactorial.clone();

      terms.erase(terms.begin() + ptrdiff_t(i) + 1);
      i--;
    }
  }
}

bool Expression::canNextTermBeBinaryOperator(const Term &term) {
  return !(isPrefixOperator(term.value) ||
           isBinaryOperator(term.value) ||
           isNonOperatorFunction(term.value) ||
           term.name == "(" ||
           term.name == ",");
}

bool Expression::canPrevTermBeBinaryOperator(const Term &term) {
  return !(isPostfixOperator(term.value) ||
           isBinaryOperator(term.value) ||
           term.name == ")" ||
           term.name == ",");
}

bool Expression::skipBrackets(const TermVector &terms, size_t &openBracketIndex) {
  if (openBracketIndex >= terms.size() || terms[openBracketIndex]->name != "(") {
    return false;
  }

  int64_t brackets = 0;

  for (auto i : std::views::iota(openBracketIndex, terms.size())) {
    const auto &term = terms[i];

    if (term->name == "(") {
      brackets++;
    }
    else if (term->name == ")") {
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

void Expression::preciseRec(ArgumentPtr &arg, uint8_t precision) {
  if (const auto realArg = cast<Real>(arg)) {
    arg = realArg->precise(precision).clone();
  }
  else if (const auto complexArg = cast<Complex>(arg)) {
    arg = Complex(convert<Real>(complexArg->real())->precise(precision),
                  convert<Real>(complexArg->imag())->precise(precision))
              .clone();
  }
  else if (const auto exprArg = cast<IExpression>(arg)) {
    ArgumentPtrVector newChildren = exprArg->getChildren();

    for (auto &child : newChildren) {
      preciseRec(child, precision);
    }

    auto newExprArg = cast<IExpression>(exprArg->clone());
    newExprArg->setChildren(newChildren);
    arg = ArgumentPtr(std::move(newExprArg));
  }
}

ArgumentPtr Expression::compress(const ArgumentPtr &child) {
  if (const auto expr = cast<Expression>(child)) {
    return expr->child;
  }

  return child;
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentPtrVector &args) {
  auto argsView = args | std::views::transform(&Expression::compress);
  ArgumentPtrVector compressedArgs(argsView.begin(), argsView.end());

  Expression::validateFunctionArgs(func, compressedArgs);

  if (auto expr = Parser::parse(Expression::getExpressionMakers(), func.toString(), compressedArgs)) {
    return expr;
  }

  return FunctionExpression(func, compressedArgs).clone();
}

std::unique_ptr<IMathObject> makeExpr(const IFunction &func, const ArgumentRefVector &args) {
  return makeExpr(func, argumentRefVectorToArgumentPtrVector(args));
}

void Expression::validateFunctionArgs(const IFunction &func, const ArgumentPtrVector &args) {
  IFunction::Type funcType = func.getFunctionType();

  if ((funcType != IFunction::Type::None && args.empty()) ||
      (funcType != IFunction::Type::Any && args.size() < size_t(funcType))) {

    throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
  }

  bool doesArgSizeMatch = funcType != IFunction::Type::Any && args.size() == size_t(funcType);

  ArgumentTypeVector expectedArgTypes = func.getArgTypes();
  MathObjectType expectedType = expectedArgTypes.front();

  for (auto i : std::views::iota(0U, args.size())) {
    if (doesArgSizeMatch) {
      expectedType = expectedArgTypes[i];
    }

    const ArgumentPtr &arg = args[i];

    if (!doesArgMatch(expectedType, arg)) {
      throw InvalidInputFunctionException(func.toString(), argumentVectorToStringVector(args));
    }
  }
}

bool Expression::doesArgMatch(const MathObjectType &expectedType, const ArgumentPtr &arg) {
  if (const auto childExpr = cast<IExpression>(arg)) {
    const std::shared_ptr<IFunction> childFunc = childExpr->getFunction();
    const MathObjectType childType = childFunc->getReturnType();

    if (childType != Variable::getTypeStatic() &&
        !isBaseOf(expectedType, childType) &&
        !isBaseOf(childType, expectedType)) {

      return false;
    }
  }
  else if (const auto childConst = cast<IConstant>(arg)) {
    const MathObjectType childType = childConst->getReturnType();

    if (!isBaseOf(expectedType, childType) && !isBaseOf(childType, expectedType)) {
      return false;
    }
  }
  else {
    MathObjectType childType = arg->getType();

    if (childType != Variable::getTypeStatic() && !isBaseOf(expectedType, childType)) {
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
}
