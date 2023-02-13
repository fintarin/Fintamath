#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpressionCRTP<Expression>, public IArithmeticCRTP<Expression> {
public:
  using ChildrenVector = std::vector<MathObjectPtr>;

public:
  Expression();

  Expression(const Expression &rhs);

  Expression(Expression &&rhs) noexcept;

  Expression &operator=(const Expression &rhs);

  Expression &operator=(Expression &&rhs) noexcept;

  explicit Expression(const std::string &str);

  Expression(const IMathObject &obj);

  explicit Expression(const MathObjectPtr &obj);

  explicit Expression(MathObjectPtr &&obj);

  Expression(int64_t val);

  std::string toString() const override;

  std::string toString(uint8_t precision) const;

  MathObjectPtr simplify() const override;

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  // TODO: implement iterator & remove this
  MathObjectPtr &getInfo();

  // TODO: implement iterator & remove this
  const MathObjectPtr &getInfo() const;

  // TODO: implement iterator & remove this
  Expression::ChildrenVector &getChildren();

  // TODO: implement iterator & remove this
  const Expression::ChildrenVector &getChildren() const;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify(bool isPrecise) const override;

  std::vector<MathObjectPtr> getVariables() const override;

  void compress() override;

  // TODO: make private
  void validate() const override;

  // TODO: make this private
  void setPrecisionRec(uint8_t precision);

  static MathObjectPtr buildFunctionExpression(const IFunction &func, const ArgumentsVector &args);

  static ExpressionPtr buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args);

  template <typename Function, typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void registerExpressionBuilder(Parser::Function<ExpressionPtr, ArgumentsVector> &&builder) {
    Parser::Function<ExpressionPtr, ArgumentsVector> constructor =
        [builder = std::move(builder)](const ArgumentsVector &args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || static_cast<uint16_t>(type) == args.size()) {
            return builder(args);
          }

          return ExpressionPtr();
        };
    Parser::add<Function>(expressionBuildersMap, constructor);
  }

protected:
  Expression &add(const Expression &rhs) override;

  Expression &substract(const Expression &rhs) override;

  Expression &multiply(const Expression &rhs) override;

  Expression &divide(const Expression &rhs) override;

  Expression &negate() override;

private:
  explicit Expression(const TokenVector &tokens);

  static ChildrenVector copy(const ChildrenVector &rhs);

  bool parsePrefixOperator(const TokenVector &tokens);

  bool parsePostfixOperator(const TokenVector &tokens);

  bool parseBinaryOperator(const TokenVector &tokens);

  bool parseFiniteTerm(const TokenVector &tokens);

  bool parseFunction(const TokenVector &tokens);

  static std::map<size_t, MathObjectPtr> findBinaryOperators(const TokenVector &tokens);

  ChildrenVector getArgs(const TokenVector &tokens);

  static bool skipBrackets(const TokenVector &tokens, size_t &openBracketIndex);

  static TokenVector cutBraces(const TokenVector &tokens);

  std::string binaryOperatorToString() const;

  std::string prefixUnaryOperatorToString() const;

  std::string postfixUnaryOperatorToString() const;

  std::string functionToString() const;

  void simplifyFunction(bool isPrecise);

  void simplifyConstant(bool isPrecise);

  void simplifyPow(); // TODO: move to PowExpression

  void simplifyNeg(); // TODO move to NegExpression

  void simplifyNot(); // TODO move to LogicExpression

  void simplifyAnd(); // TODO move to LogicExpression

  void simplifyOr(); // TODO move to LogicExpression

  void simplifyImpl(); // TODO move to LogicExpression

  void simplifyEquiv(); // TODO move to LogicExpression

  void simplifyNequiv(); // TODO move to LogicExpression

private:
  MathObjectPtr info;

  ChildrenVector children;

  static Parser::Map<ExpressionPtr, ArgumentsVector> expressionBuildersMap;
};

}
