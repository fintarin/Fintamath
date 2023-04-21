#pragma once

#include "fintamath/core/CoreConstants.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Expression : public IExpressionCRTP<Expression>, public IArithmeticCRTP<Expression> {
public:
  Expression();

  explicit Expression(const string &str);

  explicit Expression(const ArgumentPtr &obj);

  Expression(const IMathObject &obj);

  Expression(int64_t val);

  string toString() const override;

  Expression precise(uint8_t precision = FINTAMATH_ROUND_PRECISION) const;

  shared_ptr<IFunction> getFunction() const override;

  ArgumentsPtrVector getChildren() const override;

  void setChildren(const ArgumentsPtrVector &childVect) override;

  template <typename Function, bool isPolynomial = false,
            typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void
  registerFunctionExpressionMaker(Parser::Function<shared_ptr<IExpression>, const ArgumentsPtrVector &> &&builder) {
    Parser::Function<shared_ptr<IExpression>, const ArgumentsPtrVector &> constructor =
        [builder = move(builder)](const ArgumentsPtrVector &args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || uint16_t(type) == args.size()) {
            return builder(args);
          }
          if (isPolynomial && uint16_t(type) < args.size()) {
            return builder(args);
          }

          return shared_ptr<IExpression>();
        };
    Parser::add<Function>(expressionBuildersMap, constructor);
  }

protected:
  Expression &add(const Expression &rhs) override;

  Expression &substract(const Expression &rhs) override;

  Expression &multiply(const Expression &rhs) override;

  Expression &divide(const Expression &rhs) override;

  Expression &negate() override;

  ArgumentPtr simplify() const override;

private:
  explicit Expression(const TokenVector &tokens);

  bool parsePrefixOperator(const TokenVector &tokens);

  bool parsePostfixOperator(const TokenVector &tokens);

  bool parseBinaryOperator(const TokenVector &tokens);

  bool parseFiniteTerm(const TokenVector &tokens);

  bool parseFunction(const TokenVector &tokens);

  static ArgumentsPtrVector parseFunctionArgs(const TokenVector &tokens);

  void validateChild(const ArgumentPtr &child) const;

  void validateFunctionArgs(const std::shared_ptr<IFunction> &func, const ArgumentsPtrVector &args) const;

  static ArgumentPtr preciseRec(const ArgumentPtr &arg, uint8_t precision, bool shouldSimplify);

  static ArgumentPtr preciseExpressionRec(const std::shared_ptr<const IExpression> &expr, uint8_t precision,
                                          bool shouldSimplify);

  friend unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

  friend ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

  friend shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

private:
  ArgumentPtr child;

  static Parser::Map<shared_ptr<IExpression>, const ArgumentsPtrVector &> expressionBuildersMap;
};

Expression operator+(const Variable &lhs, const Variable &rhs);

Expression operator-(const Variable &lhs, const Variable &rhs);

Expression operator*(const Variable &lhs, const Variable &rhs);

Expression operator/(const Variable &lhs, const Variable &rhs);

}
