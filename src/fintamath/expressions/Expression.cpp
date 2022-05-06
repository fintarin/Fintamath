#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <fintamath/functions/Abs.hpp>
#include <fintamath/functions/Acot.hpp>
#include <fintamath/functions/Asin.hpp>
#include <fintamath/functions/Atan.hpp>
#include <fintamath/functions/ConcreteFunction.hpp>
#include <fintamath/functions/Cos.hpp>
#include <fintamath/functions/Cot.hpp>
#include <fintamath/functions/DoubleFactorial.hpp>
#include <fintamath/functions/Exp.hpp>
#include <fintamath/functions/Factorial.hpp>
#include <fintamath/functions/Lb.hpp>
#include <fintamath/functions/Lg.hpp>
#include <fintamath/functions/Ln.hpp>
#include <fintamath/functions/Log.hpp>
#include <fintamath/functions/Percent.hpp>
#include <fintamath/functions/Sin.hpp>
#include <fintamath/functions/Sqrt.hpp>
#include <fintamath/functions/Tan.hpp>
#include <fintamath/operators/Add.hpp>
#include <fintamath/operators/Div.hpp>
#include <fintamath/operators/Mul.hpp>
#include <fintamath/operators/Neg.hpp>
#include <fintamath/operators/Pow.hpp>
#include <fintamath/operators/Sub.hpp>
#include <regex>
#include <stdexcept>

#include "fintamath/functions/Function.hpp"
#include "fintamath/literals/Constant.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {
  using ExprPtr = std::shared_ptr<Expression>;
  using ExprVect = std::vector<ExprPtr>;

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
    *this = *parseExpression(str);
    *this = *baseSimplify();
  }

  Expression::Expression(const MathObject &obj) : info(obj.clone()) {
  }

  std::string putInBrackets(const std::string &str) {
    return "(" + str + ")";
  }

  std::string Expression::toString() const {
    if (!info) {
      return {};
    }
    std::string result;
    if (info->instanceOf<Operator>()) {
      const auto &rootOp = info->to<Operator>();

      if (!children.at(0)->info->instanceOf<Operator>()) {
        result += children.at(0)->toString();
      } else {
        if (const auto &nodeOp = children.at(0)->info->to<Operator>();
            (rootOp.getPriority() > nodeOp.getPriority()) ||
            ((rootOp.is<Neg>() || rootOp.is<Pow>()) && rootOp.getPriority() == nodeOp.getPriority())) {
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

        if (!children.at(i)->info->instanceOf<Operator>()) {
          result += children.at(i)->toString();
          continue;
        }
        const auto &nodeOp = children.at(i)->info->to<Operator>();
        if (rootOp.getPriority() > nodeOp.getPriority()) {
          result += putInBrackets(children.at(i)->toString());
          continue;
        }
        if ((rootOp.is<Sub>() || rootOp.is<Div>()) && rootOp.getPriority() == nodeOp.getPriority()) {
          result += putInBrackets(children.at(i)->toString());
          continue;
        }
        result += children.at(i)->toString();
      }
      return result;
    }

    if (info->instanceOf<Function>()) {
      const auto &rootFunc = info->to<Function>();
      if (rootFunc.is<Factorial>() || rootFunc.is<DoubleFactorial>() || rootFunc.is<Percent>()) {
        if ((children.at(0)->is<Factorial>() && rootFunc.is<Factorial>()) ||
            children.at(0)->info->instanceOf<Operator>()) {
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

  std::string Expression::funcArgsToString(const ExprVect &args) {
    std::string result;
    for (size_t i = 0; i < args.size() - 1; i++) {
      result += args.at(i)->toString();
      result += ',';
    }
    result += args.at(args.size() - 1)->toString();
    return result;
  }

  bool Expression::equals(const Expression &rhs) const {
    bool flag = *info == *rhs.info;
    if (children.size() == rhs.children.size()) {
      for (size_t pos = 0; pos < children.size(); pos++) {
        flag = flag && *children.at(pos) == *rhs.children.at(pos);
      }
    } else {
      return false;
    }
    return flag;
  }

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

  static size_t ignoreBracketsRightLeft(const std::string_view &str, size_t position) {
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
    return position;
  }

  static size_t ignoreBracketsLeftRight(const std::string_view &str, size_t position) {
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
    throw std::invalid_argument("Expression invalid input");
  }

  /*
   * Expr: Expr+Expr | Expr-Expr | Expr*Expr | Expr/Expr | E
   * E: -E | E^Term | Term!! | Term! | Term
   * Term: Function | (Expr) | Const | Var | Num
   * Function: Name(Args)
   * Args: Expr, Args | Expr
   */
  ExprPtr Expression::parseExpression(const std::string &exprStr) {
    auto expr = cutSpaces(exprStr);
    Expression elem;
    for (size_t i = expr.size() - 1; i > 0; i--) {
      if (expr[i] == '+' || expr[i] == '-') {
        if (i == expr.size() - 1) {
          return nullptr;
        }
        if (expr[i] == '+') {
          elem.info = std::make_shared<Add>();
        } else {
          elem.info = std::make_shared<Sub>();
        }
        elem.children.push_back(parseExpression(cutSpaces(expr.substr(0, i))));
        elem.children.push_back(parseDivMulTerm(cutSpaces(expr.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if (expr[i] == ')') {
        i = ignoreBracketsRightLeft(expr, i);
        if (i == 0) {
          break;
        }
        continue;
      }
    }
    return parseDivMulTerm(expr);
  }

  ExprPtr Expression::parseDivMulTerm(const std::string &term) {
    Expression elem;
    for (size_t i = term.size() - 1; i > 0; i--) {
      if (term[i] == '*' || term[i] == '/') {
        if (i == term.size() - 1) {
          return nullptr;
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

  ExprPtr Expression::parseNegPowFactorPercentTerm(const std::string &term) {
    Expression elem;
    if (term[0] == '-') {
      elem.info = std::make_shared<Neg>();
      elem.children.push_back(parseNegPowFactorPercentTerm(cutSpaces(term.substr(1))));
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

  ExprPtr Expression::parseFiniteTerm(const std::string &term) {
    if (auto parseResult = parseFunction(term); parseResult) {
      return parseResult;
    }
    Expression parseResult;
    if (term[0] == '(' && term[term.size() - 1] == ')') {
      return parseExpression(term.substr(1, term.size() - 2));
    }
    if (types::isConstant(term)) {
      parseResult.info = std::make_shared<Constant>(term);
    } else if (types::isVariable(term)) {
      parseResult.info = std::make_shared<Variable>(term);
    } else {
      try {
        parseResult.info = std::make_shared<Integer>(term);
      } catch (const std::invalid_argument &) {
        try {
          parseResult.info = std::make_shared<Rational>(term);
        } catch (const std::invalid_argument &) {
          return nullptr;
        }
      }
    }
    return std::make_shared<Expression>(parseResult);
  }

  ExprPtr Expression::parseFunction(const std::string &term) {
    if (std::regex reg(R"(^((sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|atan|acot|abs)\(.+\))$)");
        regex_search(term, reg)) {
      Expression expr;
      size_t pos = 0;
      std::string funcName;
      while (term.at(pos) != '(') {
        funcName += term.at(pos);
        pos++;
      }
      if (funcName == "sqrt") {
        expr.info = std::make_shared<Sqrt>();
      } else if (funcName == "exp") {
        expr.info = std::make_shared<Exp>();
      } else if (funcName == "log") {
        expr.info = std::make_shared<Log>();
      } else if (funcName == "ln") {
        expr.info = std::make_shared<Ln>();
      } else if (funcName == "lb") {
        expr.info = std::make_shared<Lb>();
      } else if (funcName == "lg") {
        expr.info = std::make_shared<Lg>();
      } else if (funcName == "sin") {
        expr.info = std::make_shared<Sin>();
      } else if (funcName == "cos") {
        expr.info = std::make_shared<Cos>();
      } else if (funcName == "tan") {
        expr.info = std::make_shared<Tan>();
      } else if (funcName == "cot") {
        expr.info = std::make_shared<Cot>();
      } else if (funcName == "asin") {
        expr.info = std::make_shared<Asin>();
      } else if (funcName == "acot") {
        expr.info = std::make_shared<Acot>();
      } else if (funcName == "atan") {
        expr.info = std::make_shared<Atan>();
      } else if (funcName == "abs") {
        expr.info = std::make_shared<Abs>();
      }
      expr.children = getArgs(cutBraces(term.substr(pos)));
      return std::make_shared<Expression>(expr);
    }
    return nullptr;
  }

  ExprVect Expression::getArgs(const std::string &argsStr) {
    ExprVect args;
    for (size_t pos = 0; pos < argsStr.size(); pos++) {
      if (argsStr[pos] == '(') {
        pos = ignoreBracketsLeftRight(argsStr, pos);
        continue;
      }
      if (argsStr[pos] == ',') {
        if (pos == 0 || pos == argsStr.size() - 1) {
          throw std::invalid_argument("Expression invalid input");
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

  ExprPtr Expression::simplifyOperators(const ExprPtr &expr) {
    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyOperators(child);
      }
    }
    if (expr->info->instanceOf<Operator>()) {
      const auto &o = expr->info->to<Operator>();
      try {
        if (o.instanceOf<Neg>()) {
          auto newExpr = std::make_shared<Expression>(*o(*expr->children.at(0)->info));
          return newExpr;
        }
        return std::make_shared<Expression>(*o(*expr->children.at(0)->info, *expr->children.at(1)->info));
      } catch (const std::invalid_argument &) {
        // skip operation if child is Variable or Function
      }
    }
    return expr;
  }

  ExprPtr Expression::simplifyFunctions(const ExprPtr &expr) {
    const int defaultPrecision = 36;
    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyFunctions(child);
        child = simplifyOperators(child);
      }
    }
    if (expr->info->instanceOf<Function>()) {
      const auto &o = expr->info->to<Function>();
      try {
        if (o.instanceOf<Log>()) {
          return std::make_shared<Expression>(*o(*expr->children.at(0)->info, *expr->children.at(1)->info));
        }
        return std::make_shared<Expression>(*o(*expr->children.at(0)->info));
      } catch (const std::invalid_argument &) {
        // skip operation if child is Variable or Function
      }
    }
    if (expr->info->is<Constant>()) {
      auto constant = expr->info->to<Constant>();
      expr->info = std::make_shared<Rational>(constant.toRational(defaultPrecision));
    }
    return expr;
  }

  ExprPtr Expression::mainSimplify(const ExprPtr &expr) {
    auto newExpr = rebuildMul(expr);
    newExpr = rebuildAdd(newExpr);

    newExpr = openBracketsPowMul(newExpr);
    newExpr = openBracketsMulAdd(newExpr);

    newExpr = rebuildMul(newExpr);
    newExpr = rebuildAdd(newExpr);

    newExpr = simplifyAddVar(newExpr);
    newExpr = simplifyMulNum(newExpr);
    newExpr = simplifyAddNum(newExpr);
    newExpr = sort(newExpr);

    return newExpr;
  }

  ExprPtr Expression::invertSubDiv(const ExprPtr &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
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
      if (newExpr->children.at(1)->is<Arithmetic>()) {
        rightNode->info = std::make_shared<Div>();
        rightNode->children.push_back(std::make_shared<Expression>(Integer(1)));
        rightNode->children.push_back(newExpr->children.at(1));
        rightNode = simplifyOperators(rightNode);
      } else {
        rightNode->info = std::make_shared<Pow>();
        rightNode->children.push_back(newExpr->children.at(1));
        rightNode->children.push_back(std::make_shared<Expression>(Integer(-1)));
      }
      newExpr->children.at(1) = rightNode;
    }
    for (auto &child : newExpr->children) {
      if (child != nullptr) {
        child = invertSubDiv(child);
      }
    }
    return newExpr;
  }

  ExprPtr Expression::simplifyNeg(const ExprPtr &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    while (newExpr->info->is<Neg>() && newExpr->children.at(0)->info->is<Neg>()) {
      newExpr = newExpr->children.at(0)->children.at(0);
    }
    if (newExpr->info->is<Neg>() && !newExpr->children.at(0)->info->is<Arithmetic>()) {
      newExpr->info = std::make_shared<Mul>();
      newExpr->children.insert(newExpr->children.begin(), std::make_shared<Expression>(Integer(-1)));
    }
    for (auto &child : newExpr->children) {
      child = simplifyNeg(child);
    }
    return newExpr;
  }

  ExprPtr Expression::rebuildAdd(const ExprPtr &expr) {
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

  ExprPtr Expression::rebuildMul(const ExprPtr &expr) {
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

  ExprPtr Expression::simplifyAddNum(const ExprPtr &expr) {
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
      if (newExpr->children.at(position)->info->instanceOf<Arithmetic>()) {
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

  ExprPtr Expression::simplifyMulNum(const ExprPtr &expr) {
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
      if (newExpr->children.at(position)->info->instanceOf<Arithmetic>()) {
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

  ExprVect Expression::getOpenTwoBrackets(const ExprVect &lhsBracket, const ExprVect &rhsBracket, const MathObject &o) {
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

  ExprPtr Expression::openBracketsMulAdd(const ExprPtr &expr) {
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

  ExprPtr Expression::openBracketsPowMul(const ExprPtr &expr) {
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

  ExprPtr Expression::sort(const ExprPtr &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    for (auto &child : newExpr->children) {
      child = sort(child);
    }
    if (!newExpr->info->instanceOf<Operator>() || newExpr->info->is<Pow>()) {
      return newExpr;
    }
    auto numVect = ExprVect();
    auto powVect = ExprVect();
    auto varVect = ExprVect();
    auto mulVect = ExprVect();
    auto funcVect = ExprVect();
    auto constVect = ExprVect();

    for (const auto &child : newExpr->children) {
      if (child->info->instanceOf<Arithmetic>()) {
        numVect.push_back(child);
      }
      if (child->info->is<Pow>()) {
        powVect.push_back(child);
        continue;
      }
      if (child->info->is<Variable>()) {
        varVect.push_back(child);
        continue;
      }
      if (child->info->is<Constant>()) {
        constVect.push_back(child);
        continue;
      }
      if (child->info->is<Mul>()) {
        mulVect.push_back(child);
        continue;
      }
      if (child->info->instanceOf<Function>()) {
        funcVect.push_back(child);
        continue;
      }
    }
    newExpr->children.clear();
    std::sort(varVect.begin(), varVect.end(), compareExprVar);
    std::sort(powVect.begin(), powVect.end(), compareExprMulPowFunc);
    std::sort(mulVect.begin(), mulVect.end(), compareExprMulPowFunc);
    std::sort(funcVect.begin(), funcVect.end(), compareExprMulPowFunc);
    std::sort(constVect.begin(), constVect.end(), compareExprVar);

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

  ExprPtr Expression::simplifyAddVar(const ExprPtr &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    for (auto &child : newExpr->children) {
      child = simplifyAddVar(child);
    }
    if (!newExpr->info->is<Add>()) {
      return newExpr;
    }
    for (auto &child : newExpr->children) {
      if (child->info->is<Mul>()) {
        if (!child->children.at(0)->info->instanceOf<Arithmetic>()) {
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
  MathObjectPtr Expression::simplify() const {
    auto newExpr = std::make_shared<Expression>(*this);
    newExpr = simplifyFunctions(newExpr);
    newExpr = simplifyOperators(newExpr);
    newExpr = invertSubDiv(newExpr);
    newExpr = simplifyNeg(newExpr);

    auto oldExpr = newExpr;
    newExpr = mainSimplify(newExpr);
    while (*oldExpr != *newExpr) {
      oldExpr = newExpr;
      newExpr = mainSimplify(newExpr);
    }
    if (newExpr->children.empty()) {
      return newExpr->info->clone();
    }
    return std::make_unique<Expression>(*newExpr);
  }
}
