#include "fintamath/expressions/Expression.hpp"

#include <fintamath/functions/ConcreteFunction.hpp>
#include <fintamath/operators/Add.hpp>
#include <fintamath/operators/Div.hpp>
#include <fintamath/operators/Mul.hpp>
#include <fintamath/operators/Neg.hpp>
#include <fintamath/operators/Pow.hpp>
#include <fintamath/operators/Sub.hpp>
#include <regex>
#include <stdexcept>
#include <algorithm>

#include "fintamath/constants/Constant.hpp"
#include "fintamath/functions/Function.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {
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
            ((rootOp.is<Neg>()||rootOp.is<Pow>()) && rootOp.getPriority() == nodeOp.getPriority())) {
          result += putInBrackets(children.at(0)->toString());
        }
        else {
          result += children.at(0)->toString();
        }
      }

      if (rootOp.is<Neg>()) {
        result = rootOp.toString() + result;
        return result;
      }
      for(size_t i = 1;i < children.size();i++) {
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

    return info->toString();

    // TODO: add instanceOf for functions
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
  std::shared_ptr<Expression> Expression::parseExpression(const std::string &exprStr) {
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

  std::shared_ptr<Expression> Expression::parseDivMulTerm(const std::string &term) {
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
        elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(i + 1))));
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
    return parseNegPowFactorTerm(term);
  }

  std::shared_ptr<Expression> Expression::parseNegPowFactorTerm(const std::string &term) {
    Expression elem;
    if (term[0] == '-') {
      elem.info = std::make_shared<Neg>();
      elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(1))));
      return std::make_shared<Expression>(elem);
    }

    for (size_t i = 0; i < term.size(); i++) {
      if (term[i] == '^') {
        elem.info = std::make_shared<Pow>();
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, i))));
        elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if (term[i] == '(') {
        i = ignoreBracketsLeftRight(term, i);
      }
    }

    if (term[term.size() - 1] == '!') {
      if (term[term.size() - 2] == '!') {
        elem.info = std::make_shared<ConcreteFunction>("!!");
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 2))));
        return std::make_shared<Expression>(elem);
      }
      elem.info = std::make_shared<ConcreteFunction>("!");
      elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 1))));
      return std::make_shared<Expression>(elem);
    }

    return parseFiniteTerm(term);
  }

  std::shared_ptr<Expression> Expression::parseFiniteTerm(const std::string &term) {
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

  std::shared_ptr<Expression> Expression::parseFunction(const std::string &term) {
    if (std::regex reg(R"(^((sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|acot|abs)\(.+\))$)");
        regex_search(term, reg)) {
      Expression expr;
      size_t pos = 0;
      std::string funcName;
      while (term.at(pos) != '(') {
        funcName += term.at(pos);
        pos++;
      }
      expr.info = std::make_shared<ConcreteFunction>(funcName);
      expr.children = getArgs(cutBraces(term.substr(pos)));
      return std::make_shared<Expression>(expr);
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<Expression>> Expression::getArgs(const std::string &argsStr) {
    std::vector<std::shared_ptr<Expression>> args;
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

  Expression Expression::simplify() {
    auto newExpr = std::make_shared<Expression>(*this);
    newExpr = simplifyNumbers(newExpr);
    newExpr = invertSubDiv(newExpr);
    newExpr = simplifyNeg(newExpr);
    newExpr = rebuildAdd(newExpr);
    newExpr = rebuildMul(newExpr);

    newExpr = mainSimplify(newExpr);
    return *newExpr;
  }

  std::shared_ptr<Expression> Expression::simplifyNumbers(const std::shared_ptr<Expression> &expr) {
    for (auto &child : expr->children) {
      if (child != nullptr) {
        child = simplifyNumbers(child);
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
        // skip operation if child is Variable
      }
    }
    // TODO: add functions
    return expr;
  }

  std::shared_ptr<Expression> Expression::mainSimplify(const std::shared_ptr<Expression> &expr) {
    auto newExpr = simplifyMulNum(expr);
    newExpr = simplifyAddNum(newExpr);
    newExpr = openBracketsPowMul(newExpr);
    newExpr = openBracketsMulAdd(newExpr);
    newExpr = sort(newExpr);
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::invertSubDiv(const std::shared_ptr<Expression> &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    if (newExpr->info->is<Sub>()) {
      newExpr->info = std::make_shared<Add>();
      auto rightNode = std::make_shared<Expression>();
      rightNode->info = std::make_shared<Neg>();
      rightNode->children.push_back(newExpr->children.at(1));
      rightNode = simplifyNumbers(rightNode);
      newExpr->children.at(1) = rightNode;
    }
    if (newExpr->info->is<Div>()) {
      newExpr->info = std::make_shared<Mul>();
      auto rightNode = std::make_shared<Expression>();
      if (newExpr->children.at(1)->is<Arithmetic>()) {
        rightNode->info = std::make_shared<Div>();
        rightNode->children.push_back(std::make_shared<Expression>(Integer(1)));
        rightNode->children.push_back(newExpr->children.at(1));
        rightNode = simplifyNumbers(rightNode);
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

  std::shared_ptr<Expression> Expression::simplifyNeg(const std::shared_ptr<Expression> &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    while (newExpr->info->is<Neg>() && newExpr->children.at(0)->info->is<Neg>()) {
      newExpr = newExpr->children.at(0)->children.at(0);
    }
    if(newExpr->info->is<Neg>() && !newExpr->children.at(0)->info->is<Arithmetic>()){
      newExpr->info = std::make_shared<Mul>();
      newExpr->children.insert(newExpr->children.begin(), std::make_shared<Expression>(Integer(-1)));
    }
    for(auto& child : newExpr->children){
      child = simplifyNeg(child);
    }
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::rebuildAdd(const std::shared_ptr<Expression> &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    for (auto &child : newExpr->children) {
      child = rebuildAdd(child);
    }
    if (!newExpr->info->is<Add>()) {
      return newExpr;
    }
    std::vector<std::shared_ptr<Expression>> newChildren;
    for (auto &child : newExpr->children) {
      if (child->info->is<Add>()) {
        for (auto &childChild : child->children) {
          newChildren.push_back(childChild);
        }
      } else {
        newChildren.push_back(child);
      }
    }
    newExpr->children = newChildren;
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::rebuildMul(const std::shared_ptr<Expression> &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    for (auto &child : newExpr->children) {
      child = rebuildMul(child);
    }
    if (!newExpr->info->is<Mul>()) {
      return newExpr;
    }
    std::vector<std::shared_ptr<Expression>> newChildren;
    for (auto &child : newExpr->children) {
      if (child->info->is<Mul>()) {
        for (auto &childChild : child->children) {
          newChildren.push_back(childChild);
        }
      } else {
        newChildren.push_back(child);
      }
    }
    newExpr->children = newChildren;
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::simplifyAddNum(const std::shared_ptr<Expression> &expr) {
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
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::simplifyMulNum(const std::shared_ptr<Expression> &expr) {
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
    return newExpr;
  }

  std::vector<std::shared_ptr<Expression>>
  Expression::getOpenTwoBrackets(const std::vector<std::shared_ptr<Expression>> &lhsBracket,
                              const std::vector<std::shared_ptr<Expression>> &rhsBracket, const MathObject&  o) {
    auto openBrackets = std::vector<std::shared_ptr<Expression>>();
    for(const auto& lhs: lhsBracket){
      for(const auto& rhs: rhsBracket){
        auto newExpr = std::make_shared<Expression>();
        newExpr->info = o.clone();
        newExpr->children = {lhs, rhs};
        openBrackets.push_back(newExpr);
      }
    }
    return openBrackets;
  }

  std::shared_ptr<Expression> Expression::openBracketsMulAdd(const std::shared_ptr<Expression> &expr) {
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
      auto lhs = std::vector<std::shared_ptr<Expression>>();
      auto rhs = std::vector<std::shared_ptr<Expression>>();
      if(newExpr->children.at(pos - 1)->info->is<Add>()){
        lhs = newExpr->children.at(pos - 1)->children;
      }
      else{
        lhs = {newExpr->children.at(pos - 1)};
      }

      if(newExpr->children.at(pos)->info->is<Add>()){
        rhs = newExpr->children.at(pos)->children;
      }
      else{
        rhs = {newExpr->children.at(pos)};
      }
      if(rhs.size() == 1 && lhs.size() == 1){
        return newExpr;
      }
      newExpr->children.pop_back();
      newExpr->children.pop_back();

      auto lastExpr = std::make_shared<Expression>();
      lastExpr->info = std::make_shared<Add>();
      lastExpr->children = getOpenTwoBrackets(lhs, rhs, Mul());
      newExpr->children.push_back(lastExpr);
    }

    return mainSimplify(newExpr->children.at(0));
  }

  std::shared_ptr<Expression> Expression::openBracketsPowMul(const std::shared_ptr<Expression> &expr) {
    auto newExpr = std::make_shared<Expression>(*expr);
    for (auto &child : newExpr->children) {
      child = openBracketsPowMul(child);
    }
    if (!newExpr->info->is<Pow>()) {
      return newExpr;
    }

    if(!newExpr->children.at(0)->info->is<Mul>()){
      return newExpr;
    }

    auto newChildren = std::vector<std::shared_ptr<Expression>>();
    for(auto& child: newExpr->children.at(0)->children){
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

  void Expression::sortVarVect(std::vector<std::shared_ptr<Expression>>& varVect){
    if(varVect.size() < 2){
      return;
    }
    for(size_t i = 0;i < varVect.size() - 1;i++){
      for(size_t j = i + 1; j < varVect.size(); j++){
        if(!varVect[i]->info->is<Variable>() || !varVect[j]->info->is<Variable>()){
          throw std::invalid_argument("Expression invalid input");
        }
        if(varVect[i]->info->toString() > varVect[j]->info->toString()){
          std::swap(varVect[i], varVect[j]);
        }
      }
    }
  }

  bool compareExprVar(const std::shared_ptr<Expression>& lhs, const std::shared_ptr<Expression>& rhs){
    return lhs->toString() > rhs->toString();
  }

  bool compareExprMulPow(const std::shared_ptr<Expression>& lhs, const std::shared_ptr<Expression>& rhs){
    return lhs->toString() < rhs->toString();
  }

  std::shared_ptr<Expression> Expression::sort(const std::shared_ptr<Expression> &expr){
    auto newExpr = std::make_shared<Expression>(*expr);
    for(auto& child:newExpr->children){
      child = sort(child);
    }
    if(!newExpr->info->instanceOf<Operator>()||newExpr->info->is<Pow>()){
      return newExpr;
    }
    auto numVect = std::vector<std::shared_ptr<Expression>>();
    auto powVect = std::vector<std::shared_ptr<Expression>>();
    auto varVect = std::vector<std::shared_ptr<Expression>>();
    auto mulVect = std::vector<std::shared_ptr<Expression>>();

    for(auto& child:newExpr->children){
      if(child->info->instanceOf<Arithmetic>()){
        numVect.push_back(child);
      }
      if(child->info->is<Pow>()){
        powVect.push_back(child);
      }
      if(child->info->is<Variable>()){
        varVect.push_back(child);
      }
      if(child->info->is<Mul>()){
        mulVect.push_back(child);
      }
    }
    newExpr->children.clear();
    std::sort(varVect.begin(), varVect.end(), compareExprVar);
    std::sort(powVect.begin(), powVect.end(), compareExprMulPow);
    std::sort(mulVect.begin(), mulVect.end(), compareExprMulPow);

    if(newExpr->info->is<Add>()){
      for(const auto& pow:powVect){
        newExpr->children.push_back(pow);
      }
      for(const auto& mul:mulVect){
        newExpr->children.push_back(mul);
      }
      for(const auto& var:varVect){
        newExpr->children.push_back(var);
      }
      for(const auto& num:numVect){
        newExpr->children.push_back(num);
      }
    }

    if(newExpr->info->is<Mul>()){
      for(const auto& num:numVect){
        newExpr->children.push_back(num);
      }
      for(const auto& pow:powVect){
        newExpr->children.push_back(pow);
      }
      for(const auto& mul:mulVect){
        newExpr->children.push_back(mul);
      }
      for(const auto& var:varVect){
        newExpr->children.push_back(var);
      }
    }
    return newExpr;
  }

  std::shared_ptr<Expression> Expression::simplifyAddVar(const std::shared_ptr<Expression> &expr){
    auto newExpr = std::make_shared<Expression>(*expr);
    for(auto& child:newExpr->children){
      child = simplifyAddVar(child);
    }
    if(!newExpr->info->is<Add>()){
      return newExpr;
    }
    for(auto& child:newExpr->children){
      if(child->info->is<Mul>()){
        if(!child->children.at(0)->info->instanceOf<Arithmetic>()){
          child->children.insert(child->children.begin(), std::make_shared<Expression>(Integer(1)));
        }
      }
      else{
        auto newChild = std::make_shared<Expression>();
        newChild->info = std::make_shared<Mul>();
        newChild->children.push_back(std::make_shared<Expression>(Integer(1)));
        newChild->children.push_back(child);
        child = newChild;
      }
    }
    return newExpr;
  }
}
