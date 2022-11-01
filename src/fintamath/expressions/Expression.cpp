#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <memory>
#include <regex>
#include <stdexcept>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/Eq.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  using ExprPtr = std::shared_ptr<Expression>; // TODO remove
  using ExprVect = std::vector<ExprPtr>;       // TODO remove

  std::string cutSpaces(const std::string &str) {
    std::string strExpr = str;
    while (!strExpr.empty()) {
      if (strExpr.front() != ' ') {
        break;
      }
      strExpr.erase(strExpr.begin());
    }

    int64_t i = 0;
    while (i < int64_t(strExpr.size())) {
      if (strExpr[size_t(i)] == ' ') {
        strExpr.erase(size_t(i), 1);
        i--;
      }
      i++;
    }
    return strExpr;
  }

  std::string cutBraces(const std::string &str) {
    std::string strExpr = str;
    if (strExpr.front() == '(' && strExpr.back() == ')') {
      strExpr.erase(strExpr.begin());
      strExpr.erase(strExpr.end() - 1);
    }
    return strExpr;
  }

  int countEqual(const std::string &str) {
    int counter = 0;
    for (const auto &ch : str) {
      if (ch == '=') {
        counter++;
      }
    }
    return counter;
  }

  Expression::Expression(const Expression &rhs) noexcept {
    if (rhs.info) {
      info = rhs.info->clone();
      children = rhs.children;
    }
  }

  Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)), children(std::move(rhs.children)) {
  }

  Expression &Expression::operator=(const Expression &rhs) noexcept {
    if (&rhs != this) {
      if (rhs.info) {
        info = rhs.info->clone();
        children = rhs.children;
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

  Expression::Expression(const std::string &str) {
    auto exprStr = cutSpaces(str);
    if (exprStr.empty()) {
      throw InvalidInputException(*this, str);
    }

    if (countEqual(exprStr) == 0) {
      *this = *parseExpression(exprStr);
      *this = *baseSimplify();
      return;
    }

    if (countEqual(exprStr) == 1) {
      *this = *parseEqualExpression(exprStr);
      return;
    }

    throw InvalidInputException(*this, str);
  }

  Expression::Expression(const IMathObject &obj) : info(obj.clone()) {
  }

  std::string putInBrackets(const std::string &str) {
    return "(" + str + ")";
  }

  std::string Expression::toString() const {
    if (!info) {
      return {};
    }

    std::string result;
    if (info->instanceOf<IOperator>()) {
      const auto &rootOp = info->to<IOperator>();

      if (!children.at(0)->info->instanceOf<IOperator>()) {
        if (children.at(0)->info->instanceOf<IComparable>() && children.at(0)->info->to<IComparable>() < Integer(0)) {
          result += putInBrackets(children.at(0)->toString());
        } else {
          result += children.at(0)->toString();
        }
      } else {
        if (const auto &nodeOp = children.at(0)->info->to<IOperator>();
            (rootOp.getOperatorPriority() > nodeOp.getOperatorPriority()) ||
            ((rootOp.is<Neg>() || rootOp.is<Pow>()) && rootOp.getOperatorPriority() == nodeOp.getOperatorPriority())) {
          result += putInBrackets(children.at(0)->toString());
        } else {
          result += children.at(0)->toString();
        }
      }

      if (rootOp.is<Neg>()) {
        result = rootOp.toString() + result;
        return result;
      }
      for (size_t i = 1; i < children.size(); i++) {
        result += info->toString();

        if (!children.at(i)->info->instanceOf<IOperator>()) {
          if (children.at(i)->info->instanceOf<IComparable>() && children.at(i)->info->to<IComparable>() < Integer(0)) {
            result += putInBrackets(children.at(i)->toString());
            continue;
          }
          result += children.at(i)->toString();
          continue;
        }
        const auto &nodeOp = children.at(i)->info->to<IOperator>();
        if (rootOp.getOperatorPriority() > nodeOp.getOperatorPriority()) {
          result += putInBrackets(children.at(i)->toString());
          continue;
        }
        if ((rootOp.is<Sub>() || rootOp.is<Div>()) && rootOp.getOperatorPriority() == nodeOp.getOperatorPriority()) {
          result += putInBrackets(children.at(i)->toString());
          continue;
        }
        result += children.at(i)->toString();
      }
      return result;
    }

    if (info->instanceOf<IFunction>()) {
      const auto &rootFunc = info->to<IFunction>();
      if (rootFunc.is<Factorial>() || rootFunc.is<DoubleFactorial>() || rootFunc.is<Percent>()) {
        if ((children.at(0)->is<Factorial>() && rootFunc.is<Factorial>()) ||
            children.at(0)->info->instanceOf<IOperator>()) {
          result += putInBrackets(children.at(0)->toString());
        } else {
          result += children.at(0)->toString();
        }
        result += rootFunc.toString();
        return result;
      }

      result += rootFunc.toString();
      result += putInBrackets(funcArgsToString(children));
      return result;
    }

    return info->toString();
  }

  std::string Expression::funcArgsToString(const ExprVect &args) const {
    std::string result;

    for (size_t i = 0; i < args.size() - 1; i++) {
      result += args.at(i)->toString();
      result += ',';
    }

    result += args.at(args.size() - 1)->toString();
    return result;
  }

  size_t Expression::ignoreBracketsRightLeft(const std::string &str, size_t position) const {
    if (position == 0) {
      throw InvalidInputException(*this); // TODO add comment here
    }
    int leftBracket = 0;
    int rightBracket = 1;
    do {
      position--;
      if (str[position] == ')') {
        rightBracket++;
      }
      if (str[position] == '(') {
        leftBracket++;
      }
      if (rightBracket == leftBracket) {
        return position;
      }
    } while (position > 0);

    throw InvalidInputException(*this); // TODO add comment here
  }

  size_t Expression::ignoreBracketsLeftRight(const std::string &str, size_t position) const {
    int leftBracket = 0;
    int rightBracket = 0;

    while (position < str.size()) {
      if (str[position] == ')') {
        rightBracket++;
      }
      if (str[position] == '(') {
        leftBracket++;
      }
      if (rightBracket == leftBracket) {
        return position;
      }
      position++;
    }

    throw InvalidInputException(*this); // TODO add comment here
  }

  /*
    Expr: AddExpr | MulExpr | PowExpr | FuncExpr | (Expr) | Term
    AddExpr: +Expr | -Expr | Expr + Expr | Expr - Expr
    MulExpr: Expr * Expr | Expr / Expr
    PowExpr: Expr^Expr
    FuncExpr: PreFuncName Expr | Expr PostFuncName
    Term: Const | Var | Num
   */
  ExprPtr Expression::parseEqualExpression(const std::string &exprStr) const {
    for (size_t i = exprStr.size() - 1; i > 0; i--) {
      if (exprStr[i] == '=') {
        if (i == exprStr.size() - 1) {
          throw InvalidInputException(*this); // TODO add comment here
        }
        auto lhs = Expression(exprStr.substr(0, i));
        auto rhs = Expression(exprStr.substr(i + 1));
        if (*Eq()(lhs, rhs) == Integer(1)) {
          return std::make_shared<Expression>(Integer(1));
        }
        auto eqExpr = Expression();
        eqExpr.info = std::make_shared<Sub>();
        eqExpr.children.push_back(std::make_shared<Expression>(lhs));
        eqExpr.children.push_back(std::make_shared<Expression>(rhs));

        auto newExpr = Expression();
        newExpr.info = std::make_shared<Eq>();
        newExpr.children.push_back(eqExpr.baseSimplify());
        newExpr.children.push_back(std::make_shared<Expression>(Integer(0)));
        return std::make_shared<Expression>(newExpr);
      }
    }
    throw InvalidInputException(*this); // TODO add comment here
  }
  ExprPtr Expression::parseExpression(const std::string &exprStr) const {
    if (exprStr.empty()) {
      throw InvalidInputException(*this); // TODO add comment here
    }

    Expression elem;

    for (size_t i = exprStr.size() - 1; i > 0; i--) {
      if (exprStr[i] == '+' || exprStr[i] == '-') {
        if (i == exprStr.size() - 1) {
          throw InvalidInputException(*this); // TODO add comment here
        }
        if (exprStr[i - 1] == '+' || exprStr[i - 1] == '-' || exprStr[i - 1] == '*' || exprStr[i - 1] == '/' ||
            exprStr[i - 1] == '^') {
          continue;
        }
        if (exprStr[i] == '+') {
          elem.info = std::make_shared<Add>();
        } else {
          elem.info = std::make_shared<Sub>();
        }
        elem.children.push_back(parseExpression(cutSpaces(exprStr.substr(0, i))));
        elem.children.push_back(parseDivMulTerm(cutSpaces(exprStr.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if (exprStr[i] == ')') {
        i = ignoreBracketsRightLeft(exprStr, i);
        if (i == 0) {
          break;
        }
        continue;
      }
    }

    return parseDivMulTerm(exprStr);
  }

  ExprPtr Expression::parseDivMulTerm(const std::string &term) const {
    Expression elem;

    for (size_t i = term.size() - 1; i > 0; i--) {
      if (term[i] == '*' || term[i] == '/') {
        if (i == term.size() - 1) {
          throw InvalidInputException(*this); // TODO add comment here
        }
        if (term[i] == '*') {
          elem.info = std::make_shared<Mul>();
        } else {
          elem.info = std::make_shared<Div>();
        }
        elem.children.push_back(parseDivMulTerm(cutSpaces(term.substr(0, i))));
        elem.children.push_back(parseNegPowFactorPercentTerm(cutSpaces(term.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if (term[i] == ')') {
        i = ignoreBracketsRightLeft(term, i);
        if (i == 0) {
          break;
        }
        continue;
      }
    }

    return parseNegPowFactorPercentTerm(term);
  }

  ExprPtr Expression::parseNegPowFactorPercentTerm(const std::string &term) const {
    if (term.empty() || term[0] == '*' || term[0] == '/') {
      throw InvalidInputException(*this); // TODO add comment here
    }
    Expression elem;

    if (term[0] == '-') {
      elem.info = std::make_shared<Neg>();
      elem.children.push_back(parseNegPowFactorPercentTerm(cutSpaces(term.substr(1))));
      return std::make_shared<Expression>(elem);
    }

    if (term[0] == '+') {
      elem = *parseNegPowFactorPercentTerm(cutSpaces(term.substr(1)));
      return std::make_shared<Expression>(elem);
    }

    for (size_t i = 0; i < term.size(); i++) {
      if (term[i] == '^') {
        elem.info = std::make_shared<Pow>();
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, i))));
        elem.children.push_back(parseNegPowFactorPercentTerm(cutSpaces(term.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if (term[i] == '(') {
        i = ignoreBracketsLeftRight(term, i);
      }
    }

    if (term[term.size() - 1] == '%') {
      elem.info = std::make_shared<Percent>();
      elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 1))));
      return std::make_shared<Expression>(elem);
    }
    if (term[term.size() - 1] == '!') {
      if (term[term.size() - 2] == '!') {
        elem.info = std::make_shared<DoubleFactorial>();
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 2))));
        return std::make_shared<Expression>(elem);
      }
      elem.info = std::make_shared<Factorial>();
      elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 1))));
      return std::make_shared<Expression>(elem);
    }

    return parseFiniteTerm(term);
  }

  ExprPtr Expression::parseFiniteTerm(const std::string &term) const {
    if (term[0] == '(' && term[term.size() - 1] == ')') {
      return parseExpression(term.substr(1, term.size() - 2));
    }

    if (auto parseResult = parseFunction(term); parseResult) {
      return parseResult;
    }

    if (LiteralPtr ptr = ILiteral::parse(term)) {
      return std::make_shared<Expression>(*ptr);
    }

    if (NumberPtr ptr = INumber::parse(term)) {
      return std::make_shared<Expression>(*ptr);
    }

    throw InvalidInputException(*this); // TODO add comment here
  }

  ExprPtr Expression::parseFunction(const std::string &term) const {
    const std::regex reg("^(sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|atan|acot|abs)");
    std::smatch funcNameMatch;
    std::regex_search(term, funcNameMatch, reg);

    if (!funcNameMatch.empty()) {
      const std::string funcName = funcNameMatch.str();
      Expression expr;
      FunctionPtr functPtr = IFunction::parse(funcName);
      expr.info = std::shared_ptr<IMathObject>(functPtr.release());
      expr.children = getArgs(cutBraces(term.substr(funcName.size())));
      return std::make_shared<Expression>(expr);
    }

    return {};
  }

  ExprVect Expression::getArgs(const std::string &argsStr) const {
    ExprVect args;

    for (size_t pos = 0; pos < argsStr.size(); pos++) {
      if (argsStr[pos] == '(') {
        pos = ignoreBracketsLeftRight(argsStr, pos);
        continue;
      }
      if (argsStr[pos] == ',') {
        if (pos == 0 || pos == argsStr.size() - 1) {
          throw InvalidInputException(*this); // TODO add comment here
        }
        args.push_back(parseExpression(cutSpaces(argsStr.substr(0, pos))));
        auto addArgs = getArgs(cutSpaces(argsStr.substr(pos + 1)));
        for (const auto &arg : addArgs) {
          args.push_back(arg);
        }
        return args;
      }
    }

    args.push_back(parseExpression(argsStr));
    return args;
  }

  ExprPtr Expression::baseSimplify() const {
    auto newExpr = std::make_shared<Expression>(*this);
    newExpr = simplifyOperators(newExpr);
    newExpr = invertSubDiv(newExpr);
    newExpr = simplifyNeg(newExpr);

    auto oldExpr = newExpr;
    newExpr = mainSimplify(newExpr);
    while (*oldExpr != *newExpr) {
      oldExpr = newExpr;
      newExpr = mainSimplify(newExpr);
    }

    return newExpr;
  }

  ExprPtr Expression::simplifyOperators(const ExprPtr &expr) const {
    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyOperators(child);
      }
    }

    if (expr->info->instanceOf<IOperator>()) {
      const auto &o = expr->info->to<IOperator>();
      try {
        if (o.instanceOf<Neg>()) {
          auto newExpr = std::make_shared<Expression>(*o(*expr->children.at(0)->info));
          return newExpr;
        }
        return std::make_shared<Expression>(*o(*expr->children.at(0)->info, *expr->children.at(1)->info));
      } catch (const FunctionCallException &) { // TODO revisit this
        // skip operation if child is Variable,  IFunction or IConstant
      }
    }

    return expr;
  }

  ExprPtr Expression::simplifyFunctions(const ExprPtr &expr) const {
    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyFunctions(child);
        child = simplifyOperators(child);
      }
    }

    if (expr->info->instanceOf<IFunction>() && !expr->info->instanceOf<IOperator>()) {
      const auto &o = expr->info->to<IFunction>();
      if (o.is<Log>()) {
        return std::make_shared<Expression>(*o(*expr->children.at(0)->info, *expr->children.at(1)->info));
      }
      return std::make_shared<Expression>(*o(*expr->children.at(0)->info));
    }

    return expr;
  }

  ExprPtr Expression::simplifyConstant(const ExprPtr &expr) const {
    const int defaultPrecision = 36;

    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyConstant(child);
      }
    }

    if (expr->info->instanceOf<IConstant>()) {
      const auto &constant = expr->info->to<IConstant>();
      expr->info = std::make_shared<Rational>(constant.getValue(defaultPrecision));
    }
    return expr;
  }

  ExprPtr Expression::mainSimplify(const ExprPtr &expr) const {
    auto newExpr = rebuildMul(expr);
    newExpr = rebuildAdd(newExpr);

    newExpr = sort(newExpr);

    newExpr = simplifyMulVar(newExpr);
    newExpr = simplifyPowNum(newExpr);

    newExpr = simplifyAddVar(newExpr);
    newExpr = simplifyMulNum(newExpr);

    newExpr = simplifyAddNum(newExpr);

    newExpr = openBracketsPowMul(newExpr);
    newExpr = openBracketsPowAdd(newExpr);
    newExpr = openBracketsMulAdd(newExpr);

    newExpr = sort(newExpr);

    return newExpr;
  }

  ExprPtr Expression::invertSubDiv(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      if (child != nullptr) {
        child = invertSubDiv(child);
      }
    }

    if (newExpr->info->is<Sub>()) {
      newExpr->info = std::make_shared<Add>();
      auto rightNode = std::make_shared<Expression>();
      rightNode->info = std::make_shared<Neg>();
      rightNode->children.push_back(newExpr->children.at(1));
      rightNode = simplifyOperators(rightNode);
      newExpr->children.at(1) = rightNode;
    }
    if (newExpr->info->is<Div>()) {
      newExpr->info = std::make_shared<Mul>();
      auto rightNode = std::make_shared<Expression>();
      if (newExpr->children.at(1)->info->instanceOf<INumber>()) {
        rightNode->info = std::make_shared<Div>();
        rightNode->children.push_back(std::make_shared<Expression>(Integer(1)));
        rightNode->children.push_back(newExpr->children.at(1));
        rightNode = simplifyOperators(rightNode);
      } else {
        rightNode = revertPow(newExpr->children.at(1));
      }
      newExpr->children.at(1) = rightNode;
    }
    return newExpr;
  }

  ExprPtr Expression::revertPow(const ExprPtr &expr) const {
    if (!expr->info->is<Pow>()) {
      auto newExpr = std::make_shared<Expression>();
      newExpr->info = std::make_shared<Pow>();
      newExpr->children.push_back(expr);
      newExpr->children.push_back(std::make_shared<Expression>(Integer(-1)));
      return newExpr;
    }
    auto rightNode = std::make_shared<Expression>();
    rightNode->info = std::make_shared<Neg>();
    rightNode->children.push_back(expr->children.at(1));
    expr->children.at(1) = rightNode;
    return expr;
  }

  ExprPtr Expression::simplifyNeg(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    while (newExpr->info->is<Neg>() && newExpr->children.at(0)->info->is<Neg>()) {
      newExpr = newExpr->children.at(0)->children.at(0);
    }

    if (newExpr->info->is<Neg>() && !newExpr->children.at(0)->info->is<IArithmetic>()) {
      newExpr->info = std::make_shared<Mul>();
      newExpr->children.insert(newExpr->children.begin(), std::make_shared<Expression>(Integer(-1)));
    }

    for (auto &child : newExpr->children) {
      child = simplifyNeg(child);
    }

    return newExpr;
  }

  ExprPtr Expression::rebuildAdd(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = rebuildAdd(child);
    }

    if (!newExpr->info->is<Add>()) {
      return newExpr;
    }

    ExprVect newChildren;

    for (const auto &child : newExpr->children) {
      if (child->info->is<Add>()) {
        for (const auto &childChild : child->children) {
          newChildren.push_back(childChild);
        }
      } else {
        newChildren.push_back(child);
      }
    }

    newExpr->children = newChildren;
    return newExpr;
  }

  ExprPtr Expression::rebuildMul(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = rebuildMul(child);
    }

    if (!newExpr->info->is<Mul>()) {
      return newExpr;
    }

    ExprVect newChildren;

    for (const auto &child : newExpr->children) {
      if (child->info->is<Mul>()) {
        for (const auto &childChild : child->children) {
          newChildren.push_back(childChild);
        }
      } else {
        newChildren.push_back(child);
      }
    }

    newExpr->children = newChildren;
    return newExpr;
  }

  ExprPtr Expression::simplifyAddNum(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = simplifyAddNum(child);
    }

    if (!newExpr->info->is<Add>()) {
      return newExpr;
    }

    auto op = Add();
    MathObjectPtr result = std::make_unique<Integer>(0);
    size_t position = newExpr->children.size();

    do {
      position--;
      if (newExpr->children.at(position)->info->instanceOf<IArithmetic>()) {
        result = op(*result, *newExpr->children.at(position)->info);
        newExpr->children.erase(newExpr->children.begin() + static_cast<long long int>(position));
      }
    } while (position > 0);

    if (result->toString() != "0") {
      newExpr->children.push_back(std::make_shared<Expression>(*result));
    }
    if (newExpr->children.size() == 1) {
      return newExpr->children.at(0);
    }
    if (newExpr->children.empty()) {
      return std::make_shared<Expression>(Integer(0));
    }

    return newExpr;
  }

  ExprPtr Expression::simplifyMulNum(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = simplifyMulNum(child);
    }

    if (!newExpr->info->is<Mul>()) {
      return newExpr;
    }

    auto op = Mul();
    MathObjectPtr result = std::make_unique<Integer>(1);
    size_t position = newExpr->children.size();

    do {
      position--;
      if (newExpr->children.at(position)->info->toString() == "0") {
        return newExpr->children.at(position);
      }
      if (newExpr->children.at(position)->info->instanceOf<IArithmetic>()) {
        result = op(*result, *newExpr->children.at(position)->info);
        newExpr->children.erase(newExpr->children.begin() + static_cast<long long int>(position));
      }
    } while (position > 0);

    if (result->toString() != "1") {
      newExpr->children.push_back(std::make_shared<Expression>(*result));
    }
    if (newExpr->children.size() == 1) {
      return newExpr->children.at(0);
    }
    if (newExpr->children.empty()) {
      return std::make_shared<Expression>(Integer(1));
    }

    return newExpr;
  }

  ExprPtr Expression::simplifyPowNum(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = simplifyPowNum(child);
    }

    if (!newExpr->info->is<Pow>()) {
      return newExpr;
    }

    if (*newExpr->children.at(1)->info == Integer(1)) {
      return newExpr->children.at(0);
    }

    if (*newExpr->children.at(1)->info == Integer(0)) {
      return std::make_shared<Expression>(Integer(1));
    }

    return newExpr;
  }

  ExprVect Expression::getOpenTwoBrackets(const ExprVect &lhsBracket, const ExprVect &rhsBracket,
                                          const IMathObject &o) const {
    auto openBrackets = ExprVect();

    for (const auto &lhs : lhsBracket) {
      for (const auto &rhs : rhsBracket) {
        auto newExpr = std::make_shared<Expression>();
        newExpr->info = o.clone();
        newExpr->children = {lhs, rhs};
        openBrackets.push_back(newExpr);
      }
    }

    return openBrackets;
  }

  ExprPtr Expression::openBracketsPowAdd(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = openBracketsPowAdd(child);
    }

    if (!newExpr->info->is<Pow>() || !newExpr->children.at(0)->info->is<Add>() ||
        !newExpr->children.at(1)->info->is<Integer>()) {
      return newExpr;
    }

    auto mulExpr = Expression();
    mulExpr.info = std::make_shared<Mul>();

    auto range = newExpr->children.at(1)->info->to<Integer>();
    for (int i = 0; i < range; i++) {
      const std::shared_ptr<IMathObject> copyExpr = newExpr->children.at(0)->clone();
      mulExpr.children.push_back(std::make_shared<Expression>(copyExpr->to<Expression>()));
    }
    return openBracketsMulAdd(std::make_shared<Expression>(mulExpr));
  }

  ExprPtr Expression::openBracketsMulAdd(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = openBracketsMulAdd(child);
    }

    if (!newExpr->info->is<Mul>()) {
      return newExpr;
    }

    size_t pos = newExpr->children.size();
    while (newExpr->children.size() > 1) {
      pos--;
      auto lhs = ExprVect();
      auto rhs = ExprVect();
      if (newExpr->children.at(pos - 1)->info->is<Add>()) {
        lhs = newExpr->children.at(pos - 1)->children;
      } else {
        lhs = {newExpr->children.at(pos - 1)};
      }

      if (newExpr->children.at(pos)->info->is<Add>()) {
        rhs = newExpr->children.at(pos)->children;
      } else {
        rhs = {newExpr->children.at(pos)};
      }
      if (rhs.size() == 1 && lhs.size() == 1) {
        return newExpr;
      }
      newExpr->children.pop_back();
      newExpr->children.pop_back();

      auto lastExpr = std::make_shared<Expression>();
      lastExpr->info = std::make_shared<Add>();
      lastExpr->children = getOpenTwoBrackets(lhs, rhs, Mul());
      newExpr->children.push_back(lastExpr);
    }

    return newExpr->children.at(0);
  }

  ExprPtr Expression::openBracketsPowMul(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = openBracketsPowMul(child);
    }

    if (!newExpr->info->is<Pow>()) {
      return newExpr;
    }
    if (!newExpr->children.at(0)->info->is<Mul>()) {
      return newExpr;
    }

    auto newChildren = ExprVect();

    for (const auto &child : newExpr->children.at(0)->children) {
      auto newChild = std::make_shared<Expression>();
      newChild->info = std::make_shared<Pow>();
      newChild->children.push_back(child);
      newChild->children.push_back(std::make_shared<Expression>(*newExpr->children.at(1)));
      newChildren.push_back(newChild);
    }

    newExpr->children = newChildren;
    newExpr->info = std::make_shared<Mul>();
    return newExpr;
  }

  bool compareExprVar(const ExprPtr &lhs, const ExprPtr &rhs) {
    return lhs->toString() < rhs->toString();
  }

  bool compareExprMulPowFunc(const ExprPtr &lhs, const ExprPtr &rhs) {
    return lhs->toString() > rhs->toString();
  }

  ExprPtr Expression::sort(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = sort(child);
    }

    if (!newExpr->info->instanceOf<IOperator>() || newExpr->info->is<Pow>()) {
      return newExpr;
    }

    auto numVect = ExprVect();
    auto powVect = ExprVect();
    auto varVect = ExprVect();
    auto mulVect = ExprVect();
    auto funcVect = ExprVect();
    auto constVect = ExprVect();

    for (const auto &child : newExpr->children) {
      if (child->info->instanceOf<IArithmetic>()) {
        numVect.push_back(child);
      } else if (child->info->is<Pow>()) {
        powVect.push_back(child);
      } else if (child->info->is<Variable>()) {
        varVect.push_back(child);
      } else if (child->info->instanceOf<IConstant>()) {
        constVect.push_back(child);
      } else if (child->info->is<Mul>()) {
        mulVect.push_back(child);
      } else if (child->info->instanceOf<IFunction>()) {
        funcVect.push_back(child);
      } else {
        throw InvalidInputException(*this); // TODO add input and comment here
      }
    }

    std::sort(varVect.begin(), varVect.end(), compareExprVar);
    std::sort(powVect.begin(), powVect.end(), compareExprMulPowFunc);
    std::sort(mulVect.begin(), mulVect.end(), compareExprMulPowFunc);
    std::sort(funcVect.begin(), funcVect.end(), compareExprMulPowFunc);
    std::sort(constVect.begin(), constVect.end(), compareExprVar);

    newExpr->children.clear();

    if (newExpr->info->is<Add>()) {
      for (const auto &func : funcVect) {
        newExpr->children.push_back(func);
      }
      for (const auto &pow : powVect) {
        newExpr->children.push_back(pow);
      }
      for (const auto &mul : mulVect) {
        newExpr->children.push_back(mul);
      }
      for (const auto &constant : constVect) {
        newExpr->children.push_back(constant);
      }
      for (const auto &var : varVect) {
        newExpr->children.push_back(var);
      }
      for (const auto &num : numVect) {
        newExpr->children.push_back(num);
      }
    }

    if (newExpr->info->is<Mul>()) {
      for (const auto &num : numVect) {
        newExpr->children.push_back(num);
      }
      for (const auto &func : funcVect) {
        newExpr->children.push_back(func);
      }
      for (const auto &pow : powVect) {
        newExpr->children.push_back(pow);
      }
      for (const auto &mul : mulVect) {
        newExpr->children.push_back(mul);
      }
      for (const auto &constant : constVect) {
        newExpr->children.push_back(constant);
      }
      for (const auto &var : varVect) {
        newExpr->children.push_back(var);
      }
    }

    return newExpr;
  }

  bool compareVect(const ExprVect &lhs, const ExprVect &rhs) {
    if (lhs.size() != rhs.size()) {
      return false;
    }

    for (size_t i = 1; i < lhs.size(); i++) {
      if (*lhs.at(i) != *rhs.at(i)) {
        return false;
      }
    }

    return true;
  }

  ExprPtr Expression::simplifyAddVar(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = simplifyAddVar(child);
    }

    if (!newExpr->info->is<Add>()) {
      return newExpr;
    }

    for (auto &child : newExpr->children) {
      if (child->info->is<Mul>()) {
        if (!child->children.at(0)->info->instanceOf<IArithmetic>()) {
          child->children.insert(child->children.begin(), std::make_shared<Expression>(Integer(1)));
        }
      } else {
        auto newChild = std::make_shared<Expression>();
        newChild->info = std::make_shared<Mul>();
        newChild->children.push_back(std::make_shared<Expression>(Integer(1)));
        newChild->children.push_back(child);
        child = newChild;
      }
    }

    auto newChildren = ExprVect();

    for (const auto &child : newExpr->children) {
      bool isAdd = false;
      for (const auto &newChild : newChildren) {
        if (compareVect(child->children, newChild->children)) {
          newChild->children.at(0)->info = Add()(*newChild->children.at(0)->info, *child->children.at(0)->info);
          isAdd = true;
          break;
        }
      }
      if (!isAdd) {
        newChildren.push_back(child);
      }
    }

    newExpr->children = newChildren;

    if (newExpr->children.size() == 1) {
      return newExpr->children.at(0);
    }

    return newExpr;
  }

  ExprPtr Expression::createAddExpr(const ExprPtr &currExpr, const ExprPtr &addExpr) const {
    if (currExpr->info->is<Add>()) {
      currExpr->children.push_back(addExpr);
      return currExpr;
    }
    auto newExpr = std::make_shared<Expression>();
    newExpr->info = std::make_shared<Add>();
    newExpr->children.push_back(currExpr);
    newExpr->children.push_back(addExpr);
    return newExpr;
  }

  ExprPtr Expression::simplifyMulVar(const ExprPtr &expr) const {
    auto newExpr = std::make_shared<Expression>(*expr);

    for (auto &child : newExpr->children) {
      child = simplifyMulVar(child);
    }

    if (!newExpr->info->is<Mul>()) {
      return newExpr;
    }

    for (auto &child : newExpr->children) {
      if (!child->info->is<Pow>()) {
        auto newChild = std::make_shared<Expression>();
        newChild->info = std::make_shared<Pow>();
        newChild->children.push_back(child);
        newChild->children.push_back(std::make_shared<Expression>(Integer(1)));
        child = newChild;
      }
    }

    auto newChildren = ExprVect();

    for (const auto &child : newExpr->children) {
      bool isMul = false;
      for (const auto &newChild : newChildren) {
        if (*child->children.at(0) == *newChild->children.at(0)) {
          newChild->children.at(1) = createAddExpr(newChild->children.at(1), child->children.at(1));
          isMul = true;
          break;
        }
      }
      if (!isMul) {
        newChildren.push_back(child);
      }
    }

    newExpr->children = newChildren;

    if (newExpr->children.size() == 1) {
      return newExpr->children.at(0);
    }

    return newExpr;
  }

  MathObjectPtr Expression::simplify() const {
    auto newExpr = std::make_shared<Expression>(*this);

    newExpr = simplifyConstant(newExpr);
    newExpr = simplifyFunctions(newExpr);

    newExpr = invertSubDiv(newExpr);
    newExpr = simplifyNeg(newExpr);

    auto oldExpr = newExpr;
    newExpr = mainSimplify(newExpr);

    while (*oldExpr != *newExpr) {
      oldExpr = newExpr;
      newExpr = mainSimplify(newExpr);
    }

    newExpr = simplifyOperators(newExpr);

    if (newExpr->children.empty()) {
      return newExpr->info->clone();
    }

    return std::make_unique<Expression>(*this);
  }

  std::string Expression::getClassName() const {
    return "Expression";
  }
}
