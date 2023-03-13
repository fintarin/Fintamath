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

  Expression(Expression &&rhs) noexcept = default;

  Expression &operator=(const Expression &rhs);

  Expression &operator=(Expression &&rhs) noexcept = default;

  explicit Expression(const std::string &str);

  Expression(const IMathObject &obj);

  explicit Expression(const std::shared_ptr<IMathObject> &obj);

  Expression(int64_t val);

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  std::string toString() const override;

  std::string toString(uint8_t precision) const;

  // TODO: use friend function instead
  std::string solve() const;

  // TODO: remove this
  std::string solve(uint8_t precision) const;

  ArgumentsPtrVector getChildren() const override;

  std::shared_ptr<IFunction> getFunction() const override;

  void setPrecision(uint8_t precision) override;

  // TODO: remove this and implement precise()
  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  ArgumentsPtrVector getVariables() const override;

  // TODO: make private
  void validate() const override;

  // TODO: make this private
  void setPrecisionRec(uint8_t precision);

  static std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

  static std::shared_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

  static std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

  template <typename Function, typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void registerFunctionExpressionMaker(
      Parser::Function<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> &&builder) {
    Parser::Function<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> constructor =
        [builder = std::move(builder)](const ArgumentsPtrVector &args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || static_cast<uint16_t>(type) == args.size()) {
            return builder(args);
          }

          return std::shared_ptr<IExpression>();
        };
    Parser::add<Function>(expressionBuildersMap, constructor);
  }

protected:
  Expression &add(const Expression &rhs) override;

  Expression &substract(const Expression &rhs) override;

  Expression &multiply(const Expression &rhs) override;

  Expression &divide(const Expression &rhs) override;

  Expression &negate() override;

  std::shared_ptr<IMathObject> simplify() override;

private:
  explicit Expression(const TokenVector &tokens);

  bool parsePrefixOperator(const TokenVector &tokens);

  bool parsePostfixOperator(const TokenVector &tokens);

  bool parseBinaryOperator(const TokenVector &tokens);

  bool parseFiniteTerm(const TokenVector &tokens);

  bool parseFunction(const TokenVector &tokens);

  ArgumentsPtrVector getArgs(const TokenVector &tokens);

  // void callPowSimplify();

  static void compress(std::shared_ptr<IMathObject> &child);

private:
  std::shared_ptr<IMathObject> child;

  static Parser::Map<std::shared_ptr<IExpression>, const ArgumentsPtrVector &> expressionBuildersMap;
};

}
