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

  explicit Expression(std::unique_ptr<IMathObject> &&obj);

  Expression(int64_t val);

  std::string toString() const override;

  std::string toString(uint8_t precision) const;

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  // TODO: implement iterator & remove this
  std::unique_ptr<IMathObject> &getChild();

  // TODO: implement iterator & remove this
  const std::unique_ptr<IMathObject> &getInfo() const;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

  std::vector<std::unique_ptr<IMathObject>> getVariables() const override;

  void compress() override;

  // TODO: make private
  void validate() const override;

  // TODO: make this private
  void setPrecisionRec(uint8_t precision);

  static std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args);

  static std::unique_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, ArgumentsPtrVector &&args);

  template <typename Function, typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void
  registerFunctionExpressionMaker(Parser::Function<std::unique_ptr<IExpression>, ArgumentsPtrVector &&> &&builder) {
    Parser::Function<std::unique_ptr<IExpression>, ArgumentsPtrVector &&> constructor =
        [builder = std::move(builder)](ArgumentsPtrVector &&args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || static_cast<uint16_t>(type) == args.size()) {
            return builder(std::move(args));
          }

          return std::unique_ptr<IExpression>();
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

  void callPowSimplify();

private:
  std::unique_ptr<IMathObject> info;

  static Parser::Map<std::unique_ptr<IExpression>, ArgumentsPtrVector &&> expressionBuildersMap;
};

}
