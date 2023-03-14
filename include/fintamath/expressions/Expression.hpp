#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/CoreConstants.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class Expression : public IExpressionCRTP<Expression>, public IArithmeticCRTP<Expression> {
public:
  Expression();

  explicit Expression(const string &str);

  explicit Expression(const shared_ptr<IMathObject> &obj);

  Expression(const IMathObject &obj);

  Expression(int64_t val);

  unique_ptr<IMathObject> toMinimalObject() const override;

  string toString() const override;

  Expression precise(size_t precision = FINTAMATH_ROUND_PRECISION) const;

  ArgumentsPtrVector getChildren() const override;

  shared_ptr<IFunction> getFunction() const override;

  // void setPrecision(uint8_t precision) override;

  ArgumentsPtrVector getVariables() const override;

  // TODO: make this private
  // void setPrecisionRec(uint8_t precision);

  static unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

  static shared_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

  static shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

  template <typename Function, typename = std::enable_if_t<std::is_base_of_v<IFunction, Function>>>
  static void
  registerFunctionExpressionMaker(Parser::Function<shared_ptr<IExpression>, const ArgumentsPtrVector &> &&builder) {
    Parser::Function<shared_ptr<IExpression>, const ArgumentsPtrVector &> constructor =
        [builder = move(builder)](const ArgumentsPtrVector &args) {
          static const IFunction::Type type = Function().getFunctionType();

          if (type == IFunction::Type::Any || static_cast<uint16_t>(type) == args.size()) {
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

  shared_ptr<IMathObject> simplify() override;

private:
  explicit Expression(const TokenVector &tokens);

  bool parsePrefixOperator(const TokenVector &tokens);

  bool parsePostfixOperator(const TokenVector &tokens);

  bool parseBinaryOperator(const TokenVector &tokens);

  bool parseFiniteTerm(const TokenVector &tokens);

  bool parseFunction(const TokenVector &tokens);

  static ArgumentsPtrVector parseFunctionArgs(const TokenVector &tokens);

  void validateChild(const shared_ptr<IMathObject> &child) const;

  void validateFunctionArgs(const std::shared_ptr<IFunction> &func, const ArgumentsPtrVector &args) const;

  // void callPowSimplify();

private:
  shared_ptr<IMathObject> child;

  static Parser::Map<shared_ptr<IExpression>, const ArgumentsPtrVector &> expressionBuildersMap;
};

}
