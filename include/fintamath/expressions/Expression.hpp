#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpressionCRTP<Expression>, public IArithmeticCRTP<Expression> {
public:
  Expression();

  Expression(const Expression &rhs);

  Expression(Expression &&rhs) noexcept;

  Expression &operator=(const Expression &rhs);

  Expression &operator=(Expression &&rhs) noexcept;

  explicit Expression(const std::string &str);

  Expression(const IMathObject &obj);

  explicit Expression(MathObjectPtr &&obj);

  Expression(int64_t val);

  std::string toString() const override;

  std::string toString(uint8_t precision) const;

  MathObjectPtr toMinimalObject() const override;

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  // TODO: implement iterator & remove this
  MathObjectPtr &getInfo();

  // TODO: implement iterator & remove this
  const MathObjectPtr &getInfo() const;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify(bool isPrecise) const override;

  std::vector<MathObjectPtr> getVariables() const override;

  void compress() override;

  // TODO: make private
  void validate() const override;

  // TODO: make this private
  void setPrecisionRec(uint8_t precision);

  static MathObjectPtr makeFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args);

  static ExpressionPtr makeRawFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args);

  template <typename Function, typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void registerFunctionExpressionMaker(Parser::Function<ExpressionPtr, ArgumentsPtrVector &&> &&builder) {
    Parser::Function<ExpressionPtr, ArgumentsPtrVector &&> constructor =
        [builder = std::move(builder)](ArgumentsPtrVector &&args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || static_cast<uint16_t>(type) == args.size()) {
            return builder(std::move(args));
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

  IMathObject *simplify() override;

private:
  explicit Expression(const TokenVector &tokens);

  bool parsePrefixOperator(const TokenVector &tokens);

  bool parsePostfixOperator(const TokenVector &tokens);

  bool parseBinaryOperator(const TokenVector &tokens);

  bool parseFiniteTerm(const TokenVector &tokens);

  bool parseFunction(const TokenVector &tokens);

  ArgumentsPtrVector getArgs(const TokenVector &tokens);

private:
  MathObjectPtr info;

  static Parser::Map<ExpressionPtr, ArgumentsPtrVector &&> expressionBuildersMap;
};

}
