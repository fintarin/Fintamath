#include "fintamath/expressions/Expression.hpp"
#include "fintamath/core/Constants.hpp"
#include "fintamath/core/Defines.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <regex>
#include <stdexcept>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/helpers/Caster.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  std::string cutBraces(const std::string &str) {
    std::string strExpr = str;
    if (strExpr.front() == '(' && strExpr.back() == ')') {
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

  Expression::Vector Expression::copy(const Vector &rhs) {
    Vector result;
    for (const auto &value : rhs) {
      result.emplace_back(value->clone());
    }
    return result;
  }

  Expression::Expression(const Expression &rhs) noexcept {
    if (rhs.info) {
      info = rhs.info->clone();
      children = copy(rhs.children);
    }
  }

  Expression::Expression() : info(Integer(0).clone()) {
  }

  Expression::Expression(Expression &&rhs) noexcept : info(std::move(rhs.info)), children(std::move(rhs.children)) {
    rhs.info = Integer(0).clone();
  }

  Expression &Expression::operator=(const Expression &rhs) noexcept {
    if (&rhs != this) {
      if (rhs.info) {
        info = rhs.info->clone();
        children = copy(rhs.children);
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
      rhs.info = Integer(0).clone();
    }
    return *this;
  }

  Expression::Expression(const std::string &str) {
    info = IExpression::parse(str);
    if (!info) {
      throw InvalidInputException(*this, str);
    }
    *this = Expression(*info->simplify());
  }

  Expression &Expression::compressTree() {
    if (info->is<Expression>()) {
      auto exprInfo = info->to<Expression>();
      info = MathObjectPtr(exprInfo.info.release());
      children = copy(exprInfo.children);
    }

    return *this;
  }

  uint16_t Expression::getInfoPriority() {
    if (info->instanceOf<IOperator>()) {
      auto oper = helpers::cast<IOperator>(info);
      return (uint16_t)oper->getOperatorPriority();
    }
    return (uint16_t)IOperator::Priority::Any;
  }

  Expression::Expression(const IMathObject &obj) {
    if (obj.is<Expression>()) {
      auto expr = obj.to<Expression>();
      info = expr.info->clone();
      children = copy(expr.children);
      return;
    }
    info = obj.clone();
  }

  Expression::Expression(int64_t val) : info(std::make_unique<Integer>(val)) {
  }

  std::string tokenVectorToString(const TokenVector &tokens) {
    std::string result;
    for (const auto &token : tokens) {
      result += token;
    }
    return result;
  }

  Expression::Expression(const TokenVector &tokens) {
    parse(tokens);
    if (!info) {
      throw InvalidInputException(*this, tokenVectorToString(tokens));
    }
    *this = Expression(*simplify());
  }

  std::string putInBrackets(const std::string &str) {
    return "(" + str + ")";
  }

  std::string Expression::binaryOperatorToString() const {
    std::string result;

    for (const auto &child : children) {
      if (!child->instanceOf<IExpression>()) {
        if (child->instanceOf<IComparable>() && child->to<IComparable>() < Integer(0)) {
          result += putInBrackets(child->toString());
        } else {
          result += child->toString();
        }
      } else {
        auto parentPriority = helpers::cast<IOperator>(info->clone())->getOperatorPriority();

        if (auto childPriority = (IOperator::Priority)helpers::cast<IExpression>(child->clone())->getInfoPriority();
            childPriority == IOperator::Priority::PostfixUnary || childPriority == IOperator::Priority::PrefixUnary ||
            (parentPriority >= childPriority)) {
          result += putInBrackets(child->toString());
        } else {
          result += child->toString();
        }
      }
      result += info->toString();
    }

    for (int i = 0; i < info->toString().size(); i++) {
      result.pop_back();
    }
    return result;
  }

  std::string Expression::prefixUnaryOperatorToString() const {
    std::string result = info->toString();

    if (children.at(0)->instanceOf<IExpression>()) {
      return result + putInBrackets(children.at(0)->toString());
    }
    if (children.at(0)->instanceOf<IComparable>() && children.at(0)->to<IComparable>() < Integer(0)) {
      return result + putInBrackets(children.at(0)->toString());
    }
    return result + children.at(0)->toString();
  }

  std::string Expression::postfixUnaryOperatorToString() const {
    std::string result = children.at(0)->toString();

    if (children.at(0)->instanceOf<IExpression>()) {
      return putInBrackets(result) + info->toString();
    }
    if (children.at(0)->instanceOf<IComparable>() && children.at(0)->to<IComparable>() < Integer(0)) {
      return putInBrackets(result) + info->toString();
    }
    return result + info->toString();
  }

  std::string Expression::functionToString() const {
    std::string result = info->toString() + "(";

    for (const auto &child : children) {
      result += child->toString() + ",";
    }

    result.pop_back();

    return result + ")";
  }

  void Expression::simplifyConstant() {
    if (info->instanceOf<IConstant>()) {
      info = (*helpers::cast<IConstant>(info->clone()))().simplify();
      return;
    }
    info = info->simplify();
  }

  void Expression::simplifyFunctionsRec() {
    if (children.empty()) {
      simplifyConstant();
      return;
    }

    for (auto &child : children) {
      if (child->instanceOf<IExpression>()) {
        child = child->simplify();
      }
    }

    if (info->instanceOf<IFunction>()) {
      const auto &func = info->to<IFunction>();
      ArgumentsVector args;

      for (const auto &child : children) {
        args.emplace_back(*child);
      }

      if (func.doAgsMatch(args)) {
        info = func(args).info;
        children.clear();
      }
    }
  }

  const MathObjectPtr &Expression::getInfo() const {
    return info;
  }

  const Expression::Vector &Expression::getChildren() const {
    return children;
  }

  std::string Expression::toString() const {
    if (children.empty()) {
      return info ? info->toString() : "";
    }

    std::string result;

    if (info->instanceOf<IOperator>()) {
      switch (info->to<IOperator>().getOperatorPriority()) {
      case IOperator::Priority::PostfixUnary:
        return postfixUnaryOperatorToString();
      case IOperator::Priority::PrefixUnary:
        return prefixUnaryOperatorToString();
      default:
        return binaryOperatorToString();
      }
    }

    if (info && info->instanceOf<IFunction>()) {
      return functionToString();
    }

    return result;
  }

  std::string Expression::toString(uint8_t precision) const {
    Expression expr = *this;
    expr.setPrecision(precision);
    return expr.toString();
  }

  void Expression::parse(const TokenVector &tokens) {
    if (tokens.empty()) {
      throw InvalidInputException(*this, " token is empty");
    }
    if (tokens.at(0) == "*" || tokens.at(0) == "/") {
      throw InvalidInputException(*this, " unexpected sign");
    }

    if (parseNeg(tokens)) {
      return;
    }

    if (parsePow(tokens)) {
      return;
    }

    if (parsePercent(tokens)) {
      return;
    }

    if (parseFactorial(tokens)) {
      return;
    }

    if (parseFunction(tokens)) {
      return;
    }

    if (parseFiniteTerm(tokens)) {
      return;
    }

    auto newTokens = splitLiteral(tokens.at(0), tokens.size() > 1);
    for (size_t i = 1; i < tokens.size(); i++) {
      newTokens.emplace_back(tokens.at(i));
    }

    info = IExpression::parse(newTokens);

    for (const auto &child : children) {
      if (info == nullptr || child == nullptr) {
        throw InvalidInputException(*this, tokensToString(tokens));
      }
    }
  }

  bool Expression::parseNeg(const TokenVector &tokens) {
    if (tokens.at(0) != "-" && tokens.at(0) != "+") {
      return false;
    }
    if (tokens.at(0) == "+") {
      *this = Expression(TokenVector(tokens.begin() + 1, tokens.end()));
      return true;
    }
    info = std::make_unique<Neg>();

    auto value = IExpression::parse(TokenVector(tokens.begin() + 1, tokens.end()));
    if (!value) {
      throw InvalidInputException(*this, tokensToString(tokens));
    }

    children.emplace_back(value->clone());
    return true;
  }

  bool Expression::parsePow(const TokenVector &tokens) {
    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens.at(i) == "(" && !skipBrackets(tokens, i)) {
        throw InvalidInputException(*this, " braces must be closed");
      }
      if (i == tokens.size()) {
        break;
      }
      if (tokens.at(i) == "^") {
        if (i == tokens.size() - 1) {
          throw InvalidInputException(*this, "too low operands for pow");
        }
        info = std::make_unique<Pow>();

        auto leftValue = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)i));
        auto rightValue = IExpression::parse(TokenVector(tokens.begin() + (long)i + 1, tokens.end()));

        if (!leftValue || !rightValue) {
          throw InvalidInputException(*this, tokenVectorToString(tokens));
        }

        children.emplace_back(leftValue->clone());
        children.emplace_back(rightValue->clone());
        return true;
      }
    }
    return false;
  }

  bool Expression::parsePercent(const TokenVector &tokens) {
    if (tokens.at(tokens.size() - 1) != "%") {
      return false;
    }
    info = std::make_unique<Percent>();

    auto value = IExpression::parse(TokenVector(tokens.begin(), tokens.end() - 1));
    if (!value) {
      throw InvalidInputException(*this, tokenVectorToString(tokens));
    }
    children.emplace_back(value->clone());
    return true;
  }

  bool Expression::parseFactorial(const TokenVector &tokens) {
    if (tokens.size() < 2) {
      return false;
    }
    if (tokens.at(tokens.size() - 1) == "!") {
      if (tokens.at(tokens.size() - 2) == "!") {
        info = std::make_unique<DoubleFactorial>();
        auto result = IExpression::parse(TokenVector(tokens.begin(), tokens.end() - 2));
        if (!result) {
          throw InvalidInputException(*this, tokensToString(tokens));
        }
        children.push_back(result->clone());
        return true;
      }
      info = std::make_unique<Factorial>();
      auto result = IExpression::parse(TokenVector(tokens.begin(), tokens.end() - 1));
      if (!result) {
        throw InvalidInputException(*this, tokensToString(tokens));
      }
      children.push_back(result->clone());
      return true;
    }
    return false;
  }

  bool Expression::parseFiniteTerm(const TokenVector &tokens) {
    if (tokens.at(0) == "(" && tokens.at(tokens.size() - 1) == ")") {
      info = IExpression::parse(cutBraces(tokens));
      if (!info) {
        throw InvalidInputException(*this, tokenVectorToString(tokens));
      }
      if (info->is<Expression>()) {
        auto exprInfo = info->to<Expression>();
        info = MathObjectPtr(exprInfo.info.release());
        children = copy(exprInfo.children);
      }
      return true;
    }

    if (tokens.size() > 1) {
      return false;
    }

    if (auto ptr = ILiteral::parse(tokens.at(0))) {
      info = std::unique_ptr<ILiteral>(ptr.release());
      return true;
    }

    if (auto ptr = INumber::parse(tokens.at(0))) {
      info = std::unique_ptr<INumber>(ptr.release());
      return true;
    }
    return false;
  }

  bool Expression::parseFunction(const TokenVector &tokens) {
    if (tokens.size() <= 1) {
      return false;
    }
    if (auto ptr = IFunction::parse(tokens.at(0)); ptr && !ptr->instanceOf<IOperator>()) {
      info = std::unique_ptr<IFunction>(ptr.release());
      children = getArgs(TokenVector(tokens.begin() + 1, tokens.end()));
      return true;
    }
    return false;
  }

  MathObjectPtr Expression::compress() const {
    auto copyExpr = *this;
    while (copyExpr.info->is<Expression>() && copyExpr.children.empty()) {
      copyExpr = copyExpr.to<Expression>();
    }
    if (children.empty()) {
      return copyExpr.info->clone();
    }
    return copyExpr.clone();
  }

  Expression Expression::buildFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
    return {*buildRawFunctionExpression(func, args).simplify()};
  }

  ExpressionPtr Expression::buildAddExpression(const IFunction &func, const ArgumentsVector &args) {
    auto addExpr = std::make_unique<AddExpression>();
    addExpr->addElement(AddExpression::Element(args.at(0).get().clone()));
    addExpr->addElement(AddExpression::Element(args.at(1).get().clone(), func.is<Sub>()));
    return addExpr;
  }

  ExpressionPtr Expression::buildMulExpression(const IFunction &func, const ArgumentsVector &args) {
    auto mulExpr = std::make_unique<MulExpression>();
    mulExpr->addElement(MulExpression::Element(args.at(0).get().clone()));
    mulExpr->addElement(MulExpression::Element(args.at(1).get().clone(), func.is<Div>()));
    return mulExpr;
  }

  Expression::Vector Expression::getArgs(const TokenVector &tokens) {
    Vector args;
    for (size_t pos = 0; pos < tokens.size(); pos++) {
      bool isBracketsSkip = false;
      if (tokens.at(pos) == "(") {
        if (pos == 0) {
          isBracketsSkip = true;
        }
        if (!skipBrackets(tokens, pos)) {
          throw InvalidInputException(*this, " braces must be closed");
        }
      }

      if (pos == tokens.size()) {
        if (isBracketsSkip) {
          return getArgs(cutBraces(tokens));
        }
        break;
      }

      if (tokens.at(pos) == ",") {
        if (pos == 0 || pos == tokens.size() - 1) {
          throw InvalidInputException(*this, " incorrect use of a comma");
        }

        auto arg = IExpression::parse(TokenVector(tokens.begin(), tokens.begin() + (long)pos));
        if (!arg) {
          throw InvalidInputException(*this, tokenVectorToString(tokens));
        }

        args.emplace_back(arg->clone());
        auto addArgs = getArgs(TokenVector(tokens.begin() + (long)pos + 1, tokens.end()));

        for (auto &token : addArgs) {
          args.push_back(MathObjectPtr(token.release()));
        }
        return args;
      }
    }

    auto arg = IExpression::parse(tokens);
    if (!arg) {
      throw InvalidInputException(*this, tokenVectorToString(tokens));
    }

    args.emplace_back(arg->clone());
    return args;
  }

  TokenVector Expression::splitLiteral(const std::string &token, bool addMultiplyToEnd) {
    if (token.empty()) {
      throw InvalidInputException(*this, "");
    }
    TokenVector tokens;
    for (const auto &var : token) {
      if (!isLetter(var)) {
        throw InvalidInputException(*this, " incorrect variable");
      }
      tokens.emplace_back(std::string(1, var));
      tokens.emplace_back("*");
    }
    if (!addMultiplyToEnd) {
      tokens.pop_back();
    }
    return tokens;
  }

  Expression &Expression::add(const Expression &rhs) {
    auto addExpr = std::make_unique<AddExpression>();
    addExpr->addElement({clone(), false});
    addExpr->addElement({rhs.clone(), false});
    this->info = helpers::cast<AddExpression>(addExpr->simplify());
    this->children.clear();
    return *this;
  }

  Expression &Expression::substract(const Expression &rhs) {
    auto addExpr = std::make_unique<AddExpression>();
    addExpr->addElement({clone(), false});
    addExpr->addElement({rhs.clone(), true});
    this->info = helpers::cast<AddExpression>(addExpr->simplify());
    this->children.clear();
    return *this;
  }

  Expression &Expression::multiply(const Expression &rhs) {
    auto mulExpr = std::make_unique<MulExpression>();
    mulExpr->addElement({clone(), false});
    mulExpr->addElement({rhs.clone(), false});
    this->info = helpers::cast<MulExpression>(mulExpr->simplify());
    this->children.clear();
    return *this;
  }

  Expression &Expression::divide(const Expression &rhs) {
    auto divExpr = std::make_unique<MulExpression>();
    divExpr->addElement({clone(), false});
    divExpr->addElement({rhs.clone(), true});
    this->info = helpers::cast<MulExpression>(divExpr->simplify());
    this->children.clear();
    return *this;
  }

  Expression &Expression::negate() {
    auto neg = Neg();
    if (info->is<Neg>()) {
      info = children.at(0)->clone();
      children.clear();
      return *this;
    }
    if (!children.empty()) {
      auto expr = *this;
      info = std::make_unique<Neg>();
      children.clear();
      children.emplace_back(expr.clone());
      return *this;
    }
    if (info->instanceOf<IArithmetic>()) {
      *this = neg(*info);
      return *this;
    }

    auto mul = MulExpression();
    mul.addElement(MulExpression::Element(Integer(-1).clone(), false));
    mul.addElement(MulExpression::Element(clone(), false));
    info = std::make_unique<MulExpression>(mul)->simplify();
    children.clear();
    return *this;
  }

  Expression Expression::buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args) {
    Expression funcExpr;

    if (func.is<Add>() || func.is<Sub>()) {
      funcExpr.info = buildAddExpression(func, args);
      return funcExpr;
    }

    if (func.is<Mul>() || func.is<Div>()) {
      funcExpr.info = buildMulExpression(func, args);
      return funcExpr;
    }

    funcExpr.info = func.clone();

    for (const auto &arg : args) {
      funcExpr.children.push_back(arg.get().clone());
    }

    return funcExpr;
  }

  /*
    Expr: AddExpr | MulExpr | PowExpr | FuncExpr | (Expr) | Term
    AddExpr: +Expr | -Expr | Expr + Expr | Expr - Expr
    MulExpr: Expr * Expr | Expr / Expr
    PowExpr: Expr^Expr
    FuncExpr: PreFuncName Expr | Expr PostFuncName
    Term: Const | Var | Num
   */
  /* ExprPtr Expression::parseEqualExpression(const std::string &exprStr) const {
     for (size_t i = exprStr.size() - 1; i > 0; i--) {
       if (exprStr[i] == '=') {
         if (i == exprStr.size() - 1) {
           throw InvalidInputException(*this); // TODO add comment here
         }
         auto lhs = Expression(exprStr.substr(0, i));
         auto rhs = Expression(exprStr.substr(i + 1));
         if (*Eqv()(lhs, rhs) == Integer(1)) {
           return std::make_shared<Expression>(Integer(1));
         }
         auto eqExpr = Expression();
         eqExpr.info = std::make_shared<Sub>();
         eqExpr.children.push_back(std::make_shared<Expression>(lhs));
         eqExpr.children.push_back(std::make_shared<Expression>(rhs));

         auto newExpr = Expression();
         newExpr.info = std::make_shared<Eqv>();
         newExpr.children.push_back(eqExpr.baseSimplify());
         newExpr.children.push_back(std::make_shared<Expression>(Integer(0)));
         return std::make_shared<Expression>(newExpr);
       }
     }
     throw InvalidInputException(*this);
   }
   */
  Expression Expression::simplifyPrefixUnaryOperator(Expression expr) {
    if (expr.info->is<UnaryPlus>()) {
      return *expr.children.at(0);
    }

    if (expr.info->is<Neg>()) {
      return simplifyNeg(expr);
    }

    return expr;
  }

  Expression Expression::simplifyNeg(Expression expr) {
    auto childExpr = helpers::cast<Expression>(expr.children.at(0)->clone());
    if (!childExpr) {
      return expr;
    }

    if (!childExpr->info->is<Neg>()) {
      return buildRawFunctionExpression(Neg(), {*childExpr->compress()});
    }

    expr.info = childExpr->children.at(0)->clone();

    return expr.compressTree();
  }

  void Expression::setPrecision(uint8_t precision) {
    for (auto &child : children) {
      if (child->instanceOf<IExpression>()) {
        auto copyChild = helpers::cast<IExpression>(child->clone());
        copyChild->setPrecision(precision);
        child = copyChild->clone();
      }
    }

    if (info->instanceOf<INumber>()) {
      info = helpers::Converter::convert(*info, Real())->to<Real>().precise(precision).clone();
    }
  }

  MathObjectPtr Expression::simplify() const {
    Expression expr = *this;
    expr = expr.compressTree();
    expr.simplifyFunctionsRec();

    expr = simplifyPrefixUnaryOperator(expr);
    // expr = simplifyPow(expr);
    if (expr.children.empty()) {
      return expr.info->clone();
    }
    return expr.clone();
  }

  std::string Expression::getClassName() const {
    return "Expression";
  }

  Expression Expression::solve() const {
    return {};
  }
}
