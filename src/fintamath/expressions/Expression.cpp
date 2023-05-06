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

Expression::Expression(const std::string &str) : Expression(tokensToTerms(Tokenizer::tokenize(str))) {
  validateChild(child);
  simplifyChild(child);
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

Expression::Expression(const TermVector &terms) {
  if (terms.empty()) {
    throw InvalidInputException(termsToString(terms));
  }

  if (parseBinaryOperator(terms) ||  //
      parsePrefixOperator(terms) ||  //
      parsePostfixOperator(terms) || //
      parseFunction(terms) ||        //
      parseBrackets(terms) ||        //
      parseFiniteTerm(terms)         //
  ) {
    return;
  }

  throw InvalidInputException(termsToString(terms));
}

TermVector Expression::tokensToTerms(const TokenVector &tokens) {
  TermVector terms(tokens.size());

  for (size_t i = 0; i < tokens.size(); i++) {
    if (auto term = Parser::parse(getTermMakers(), (tokens[i]))) {
      terms[i] = term;
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
    if (!getTermValueIf(*terms[i - 1], isBinaryOperator) &&      //
        !getTermValueIf(*terms[i - 1], isPrefixOperator) &&      //
        !getTermValueIf(*terms[i - 1], isNonOperatorFunction) && //
        terms[i - 1]->name != "(" &&                             //
        terms[i - 1]->name != "," &&                             //
        !getTermValueIf(*terms[i], isBinaryOperator) &&          //
        !getTermValueIf(*terms[i], isPostfixOperator) &&         //
        terms[i]->name != ")" &&                                 //
        terms[i]->name != ","                                    //
    ) {
      terms.insert(terms.begin() + int64_t(i),
                   std::make_shared<Term>(delimiter->toString(), ArgumentsPtrVector{delimiter}));
      i++;
    }
  }
}

bool Expression::parseBinaryOperator(const TermVector &terms) {
  size_t foundOperPos = 0;
  IOperator::Priority foundPriority = IOperator::Priority::Any;
  bool isPreviousBinaryOper = false;

  for (size_t i = 0; i < terms.size(); i++) {
    if (skipBrackets(terms, i)) {
      isPreviousBinaryOper = false;
      i--;
      continue;
    }

    if (auto oper = cast<IOperator>(getTermValueIf(*terms[i], isBinaryOperator))) {
      if (!isPreviousBinaryOper) {
        IOperator::Priority priority = oper->getOperatorPriority();

        if (foundPriority == IOperator::Priority::Any || foundPriority < priority ||
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

  if (foundOperPos < 1 || foundOperPos + 1 >= terms.size()) {
    return false;
  }

  auto foundOper = cast<IOperator>(getTermValueIf(*terms[foundOperPos], isBinaryOperator));

  auto lhsExpr = std::shared_ptr<Expression>(new Expression(
      TermVector(terms.begin(), terms.begin() + ArgumentsPtrVector::iterator::difference_type(foundOperPos))));
  auto rhsExpr = std::shared_ptr<Expression>(new Expression(
      TermVector(terms.begin() + ArgumentsPtrVector::iterator::difference_type(foundOperPos) + 1, terms.end())));
  std::shared_ptr<IExpression> funcExpr =
      makeRawFunctionExpression(*foundOper, {lhsExpr->getChildren().front(), rhsExpr->getChildren().front()});

  if (auto expr = cast<Expression>(funcExpr)) {
    *this = std::move(*expr);
  }
  else {
    child = funcExpr;
  }

  return true;
}

bool Expression::parsePrefixOperator(const TermVector &terms) {
  if (terms.size() <= 1) {
    return false;
  }

  if (auto oper = cast<IOperator>(getTermValueIf(*terms.front(), isPrefixOperator))) {
    Expression arg(TermVector(terms.begin() + 1, terms.end()));
    child = makeRawFunctionExpression(*oper, {arg.child});
    compressChild(child);
    return true;
  }

  return false;
}

bool Expression::parsePostfixOperator(const TermVector &terms) {
  if (terms.size() <= 1) {
    return false;
  }

  if (std::shared_ptr<const IOperator> constOper = cast<IOperator>(getTermValueIf(*terms.back(), isPostfixOperator))) {
    if (std::shared_ptr<IOperator> oper = cast<IOperator>(constOper->clone())) {
      size_t order = 1;

      if (auto factor = cast<Factorial>(oper)) {
        for (; order < terms.size(); order++) {
          if (terms[terms.size() - order - 1]->name != oper->toString()) {
            break;
          }
        }

        factor->setOrder(order);
      }

      Expression arg(TermVector(terms.begin(), terms.end() - TokenVector::iterator::difference_type(order)));
      child = makeRawFunctionExpression(*oper, {arg.child});
      compressChild(child);
      return true;
    }
  }

  return false;
}

bool Expression::parseFunction(const TermVector &terms) {
  if (terms.size() <= 1 || terms.front()->values.empty()) {
    return false;
  }

  if (auto func = cast<IFunction>(terms.front()->values.front())) {
    ArgumentsPtrVector args = parseFunctionArgs(TermVector(terms.begin() + 1, terms.end()));
    child = makeRawFunctionExpression(*func, args);
    return true;
  }

  return false;
}

bool Expression::parseBrackets(const TermVector &terms) {
  if (terms.size() <= 2) {
    return false;
  }

  if (terms.front()->name == "(" && terms.back()->name == ")") {
    *this = Expression(cutBrackets(terms));
    return true;
  }

  return false;
}

bool Expression::parseFiniteTerm(const TermVector &terms) {
  if (terms.size() != 1 || terms.front()->values.size() != 1) {
    return false;
  }

  *this = Expression(terms.front()->values.front());
  return true;
}

std::shared_ptr<IFunction> Expression::getFunction() const {
  return {};
}

ArgumentsPtrVector Expression::parseFunctionArgs(const TermVector &terms) {
  ArgumentsPtrVector args;

  for (size_t pos = 0; pos < terms.size(); pos++) {
    bool isBracketsSkip = false;
    if (terms[pos]->name == "(") {
      if (pos == 0) {
        isBracketsSkip = true;
      }

      skipBrackets(terms, pos);
    }

    if (pos == terms.size()) {
      if (isBracketsSkip) {
        return parseFunctionArgs(cutBrackets(terms));
      }
      break;
    }

    if (terms[pos]->name == ",") {
      if (pos == 0 || pos + 1 == terms.size()) {
        throw InvalidInputException(termsToString(terms));
      }

      args.emplace_back(std::shared_ptr<Expression>(new Expression(
          TermVector(terms.begin(), terms.begin() + ArgumentsPtrVector::iterator::difference_type(pos)))));

      ArgumentsPtrVector addArgs = parseFunctionArgs(
          TermVector(terms.begin() + ArgumentsPtrVector::iterator::difference_type(pos) + 1, terms.end()));

      for (const auto &token : addArgs) {
        args.emplace_back(ArgumentPtr(token));
      }

      return args;
    }
  }

  args.emplace_back(std::shared_ptr<Expression>(new Expression(terms)));

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

bool Expression::skipBrackets(const TermVector &terms, size_t &openBracketIndex) {
  if (openBracketIndex >= terms.size() || terms.at(openBracketIndex)->name != "(") {
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

TermVector Expression::cutBrackets(const TermVector &terms) {
  if (terms.empty()) {
    return terms;
  }

  auto newTokens = terms;

  if (newTokens.front()->name == "(" && newTokens.back()->name == ")") {
    newTokens.erase(newTokens.begin());
    newTokens.erase(newTokens.end() - 1);
  }

  return newTokens;
}

std::string Expression::termsToString(const TermVector &terms) {
  std::string res;

  for (const auto &term : terms) {
    res += term->name;
  }

  return res;
}

ArgumentPtr Expression::getTermValueIf(const Term &term, std::function<bool(const ArgumentPtr &)> &&predicate) {
  for (const auto &val : term.values) {
    if (predicate(val)) {
      return val;
    }
  }

  return {};
}

void Expression::removeTermValuesIf(Term &term, std::function<bool(const ArgumentPtr &)> &&predicate) {
  term.values.erase(std::remove_if(term.values.begin(), term.values.end(),
                                   [predicate = std::move(predicate)](const ArgumentPtr &val) {
                                     return predicate(val);
                                   }),
                    term.values.end());
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
