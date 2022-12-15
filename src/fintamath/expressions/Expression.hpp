#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/Defines.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/expressions/AddExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/helpers/Converter.hpp"

namespace fintamath {
  class IFunction;

  class Expression : public IExpressionCRTP<Expression>, public IArithmeticCRTP<Expression> {
  public:
    using Vector = std::vector<MathObjectPtr>;

  public:
    Expression();

    Expression(const Expression &rhs) noexcept;

    Expression(Expression &&rhs) noexcept;

    Expression &operator=(const Expression &rhs) noexcept;

    Expression &operator=(Expression &&rhs) noexcept;

    ~Expression() override = default;

    explicit Expression(const TokenVector &tokens);

    explicit Expression(const std::string &str);

    Expression(const IMathObject &obj);

    Expression(int64_t val);

    std::string toString() const override;

    std::string toString(uint8_t precision) const;

    MathObjectPtr simplify() const override;

    std::string getClassName() const override;

    Expression solve() const;

    const MathObjectPtr &getInfo() const;

    const Expression::Vector &getChildren() const;

    MathObjectPtr compress() const;

    static Expression buildFunctionExpression(const IFunction &func, const ArgumentsVector &args);

    uint16_t getInfoPriority() override;

  protected:
    Expression &add(const Expression &rhs) override;

    Expression &substract(const Expression &rhs) override;

    Expression &multiply(const Expression &rhs) override;

    Expression &divide(const Expression &rhs) override;

    Expression &negate() override;

  private:
    static Expression buildRawFunctionExpression(const IFunction &func, const ArgumentsVector &args);

    static ExpressionPtr buildAddExpression(const IFunction &func, const ArgumentsVector &args);

    static ExpressionPtr buildMulExpression(const IFunction &func, const ArgumentsVector &args);

    static Vector copy(const Vector &rhs);

    Expression &compressTree();

    void parse(const TokenVector &tokens);

    bool parseNeg(const TokenVector &tokens);

    bool parsePow(const TokenVector &tokens);

    bool parsePercent(const TokenVector &tokens);

    bool parseFactorial(const TokenVector &tokens);

    bool parseFiniteTerm(const TokenVector &tokens);

    bool parseFunction(const TokenVector &tokens);

    bool parseLiteral(const TokenVector &tokens);

    bool parseNumber(const TokenVector &tokens);

    Vector getArgs(const TokenVector &tokens);

    TokenVector splitLiteral(const std::string &token, bool addMultiplyToEnd = false);

    std::string binaryOperatorToString() const;

    std::string prefixUnaryOperatorToString() const;

    std::string postfixUnaryOperatorToString() const;

    std::string functionToString() const;

    void simplifyFunctionsRec();

    void simplifyConstant();

    static Expression simplifyPrefixUnaryOperator(Expression expr);

    static Expression simplifyNeg(Expression expr);

    static Expression simplifyPow(Expression expr);

    void setPrecision(uint8_t precision);

    MathObjectPtr info;
    Vector children;

    const std::vector<std::string> classNames = {getClassName(), AddExpression().getClassName(),
                                                 MulExpression().getClassName()};
  };
}
