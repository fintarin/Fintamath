#include "fintamath/expressions/Expression.hpp"

#include <algorithm>
#include <fintamath/functions/ConcreteFunction.hpp>
#include <fintamath/operators/Add.hpp>
#include <fintamath/operators/Div.hpp>
#include <fintamath/operators/Mul.hpp>
#include <fintamath/operators/Neg.hpp>
#include <fintamath/operators/Pow.hpp>
#include <fintamath/operators/Sub.hpp>
#include <regex>
#include <stdexcept>

#include "fintamath/constants/Constant.hpp"
#include "fintamath/functions/Function.hpp"
#include "fintamath/operators/Operator.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {
  constexpr int64_t INITIAL_PRECISION = 36;
  constexpr int64_t PRECISION_INCREASER = 9;
  constexpr int64_t NEW_PRECISION = INITIAL_PRECISION + PRECISION_INCREASER;
  constexpr int64_t NEW_ROUND_PRECISION = NEW_PRECISION - 1;

  std::vector<std::string> makeVectOfTokens(const std::string &strExpr);

  bool isDigit(char ch);
  bool isLetter(char ch);

  void toShortForm(std::string &strVal);
  void insertFloatingPoint(std::string &strVal, int64_t precision);
  size_t cutZeros(std::string &strVal);

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

  Expression::Expression(const MathObjectPtr &obj) {
    info = obj->clone();
  }

  std::string Expression::toString() const {
    if (!info) {
      return {};
    }
    std::string result;
    if(children.at(0)){
      result += ("(" + children.at(0)->toString() + ")");
    }
    result += info->toString();
    if(children.at(1)){
      result += ("(" + children.at(1)->toString() + ")");
    }
    return result;
  }

  bool Expression::equals(const Expression &rhs) const {
    return false;
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

  std::string cutBraces(const std::string &str){
    std::string strExpr = str;
    if(strExpr.front() == '(' && strExpr.back() == ')') {
      strExpr.erase(strExpr.begin());
      strExpr.erase(strExpr.end() - 1);
    }
    return strExpr;
  }

  bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
  }

  bool isLetter(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
  }

  void toShortForm(std::string &strVal) {
    bool isNegative = (*strVal.begin() == '-');
    if (isNegative) {
      strVal.erase(0, 1);
    }

    if (strVal == "0") {
      return;
    }

    if (*strVal.begin() == '0') {
      strVal.erase(strVal.begin() + 1);
      size_t order = cutZeros(strVal);
      insertFloatingPoint(strVal, INITIAL_PRECISION);
      strVal += "*10^(-";
      strVal += std::to_string(order) + ')';
    } else {
      size_t order = distance(begin(strVal), find(begin(strVal), end(strVal), '.'));
      if (order != strVal.size()) {
        strVal.erase(order, 1);
      }
      if (strVal.size() > INITIAL_PRECISION + 1) {
        strVal.erase(INITIAL_PRECISION + 2);
      }

      insertFloatingPoint(strVal, INITIAL_PRECISION);

      if (order > 1) {
        strVal += "*10^";
        strVal += std::to_string(order - 1);
      }
    }

    if (isNegative) {
      strVal.insert(strVal.begin(), '-');
    }
  }

  void insertFloatingPoint(std::string &strVal, int64_t precision) {
    strVal.insert(strVal.begin() + 1, '.');
    strVal += '0';
    strVal = Rational(strVal).toString(precision);
  }

  size_t cutZeros(std::string &strVal) {
    size_t order = 0;
    while (*strVal.begin() == '0') {
      strVal.erase(strVal.begin());
      order++;
    }
    return order;
  }

  static void ignoreBracketsRightLeft(const std::string_view &str, int &position) {
    int leftBracket = 0;
    int rightBracket = 0;

    while (position >= 0) {
      if (str[position] == ')') {
        rightBracket++;
      }
      if (str[position] == '(') {
        leftBracket++;
      }
      if (rightBracket == leftBracket) {
        return;
      }
      position--;
    }
    throw std::invalid_argument("Expression invalid input");
  }

  static void ignoreBracketsLeftRight(const std::string_view &str, int &position) {
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
        return;
      }
      position++;
    }
    throw std::invalid_argument("Expression invalid input");
  }
  /*
   * Expr: Expr+Expr | Expr-Expr | Expr*Expr | Expr/Expr | E
   * E: -E | E^Term | Term!! | Term! | Term
   * Term:
   */
  std::shared_ptr<Expression> Expression::parseExpression(const std::string& exprStr){
    auto expr = cutSpaces(exprStr);
    Expression elem;
    for(int i = int(expr.size() - 1); i > 0; i--) {
      if(expr[i] == '+' || expr[i] == '-'){
        if(i == expr.size() - 1) {
          return nullptr;
        }
        if(expr[i] == '+') {
          elem.info = std::make_shared<Add>();
        }
        else {
          elem.info = std::make_shared<Sub>();
        }
        elem.children.push_back(parseExpression(cutSpaces(expr.substr(0, i))));
        elem.children.push_back(parseDivMulTerm(cutSpaces(expr.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if(expr[i] == ')'){
        ignoreBracketsRightLeft(expr, i);
        continue;
      }
    }
    return parseDivMulTerm(expr);
  }

  std::shared_ptr<Expression> Expression::parseDivMulTerm(const std::string& term) {
    Expression elem;
    for(int i = int(term.size() - 1); i > 0; i--) {
      if(term[i] == '*' || term[i] == '/'){
        if(i == term.size() - 1) {
          return nullptr;
        }
        if(term[i] == '*') {
          elem.info = std::make_shared<Mul>();
        }
        else {
          elem.info = std::make_shared<Div>();
        }
        elem.children.push_back(parseDivMulTerm(cutSpaces(term.substr(0, i))));
        elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
      if(term[i] == ')'){
        ignoreBracketsRightLeft(term, i);
        continue;
      }
    }
    return parseNegPowFactorTerm(term);
  }

  std::shared_ptr<Expression> Expression::parseNegPowFactorTerm(const std::string& term){
    Expression elem;
    if(term[0] == '-'){
      elem.info = std::make_shared<Neg>();
      elem.children.push_back(nullptr);
      elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(1))));
      return std::make_shared<Expression>(elem);
    }

    for(int i = int(term.size() - 1); i > 0; i--) {
      if(term[i] == '^'){
        elem.info = std::make_shared<Pow>();
        elem.children.push_back(parseNegPowFactorTerm(cutSpaces(term.substr(0, i))));
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(i + 1))));
        return std::make_shared<Expression>(elem);
      }
    }

    if(term[term.size() - 1] == '!'){
      if(term[term.size() - 2] == '!'){
        elem.info = std::make_shared<ConcreteFunction>("!!");
        elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 2))));
        elem.children.push_back(nullptr);
        return std::make_shared<Expression>(elem);
      }
      elem.info = std::make_shared<ConcreteFunction>("!");
      elem.children.push_back(parseFiniteTerm(cutSpaces(term.substr(0, term.size() - 1))));
      elem.children.push_back(nullptr);
      return std::make_shared<Expression>(elem);
    }

    return parseFiniteTerm(term);
  }

  std::shared_ptr<Expression> Expression::parseFiniteTerm(const std::string& term) {
    if (auto parseResult = parseFunction(term); parseResult) {
      return parseResult;
    }
    Expression parseResult;
    if(term[0] == '(' && term[term.size() - 1] == ')'){
      return parseExpression(term.substr(1, term.size() - 2));
    }
    if(types::isConstant(term)){
      parseResult.info = std::make_shared<Constant>(term);
    }
    else if(types::isVariable(term)){
      parseResult.info = std::make_shared<Variable>(term);
    }
    else{
      try{
        parseResult.info = std::make_shared<Integer>(term);
      }
      catch(std::invalid_argument& ){
        try{
          parseResult.info = std::make_shared<Rational>(term);
        }
        catch(std::invalid_argument& ) {
          return nullptr;
        }
      }
    }
    return std::make_shared<Expression>(parseResult);
  }

  std::shared_ptr<Expression> Expression::parseFunction(const std::string& term){
    std::regex reg(R"(^((sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|acot|abs)\(.+\))$)");
    if(regex_search(term, reg)){
      Expression expr;
      int pos = 0;
      std::string funcName;
      while(term[pos] != '('){
        funcName += term[pos];
        pos++;
      }
      expr.info = std::make_shared<ConcreteFunction>(funcName);
      expr.children = getArgs(cutBraces(term.substr(pos)));
      return std::make_shared<Expression>(expr);
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<Expression>> Expression::getArgs(const std::string& argsStr){
    std::vector<std::shared_ptr<Expression>> args;
    for(int pos = 0; pos < argsStr.size(); pos++){
      if(argsStr[pos] == '('){
        ignoreBracketsLeftRight(argsStr, pos);
        continue;
      }
      if(argsStr[pos] == ','){
        if(pos == 0 || pos == argsStr.size()-1){
          throw std::invalid_argument("Expression invalid input");
        }
        args.push_back(parseExpression(cutSpaces(argsStr.substr(0, pos))));
        auto addArgs = getArgs(cutSpaces(argsStr.substr(pos + 1)));
        for(const auto& arg : addArgs){
          args.push_back(arg);
        }
        return args;
      }
    }
    args.push_back(parseExpression(argsStr));
    return args;
  }

  Expression Expression::simplify(){
    auto newExpr = std::make_shared<Expression>(*this);
    return *simplify(newExpr);
  }

  std::shared_ptr<Expression> Expression::simplify(const std::shared_ptr<Expression> &expr) {
    for(auto & child : expr->children){
      if(child != nullptr){
        child = simplify(child);
      }
    }
    return nullptr;
  }
}
