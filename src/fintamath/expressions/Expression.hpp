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
    Expression() = default;

    Expression(const Expression &rhs) noexcept;

    Expression(Expression &&rhs) noexcept;

    explicit Expression(const TokenVector &tokens);

    Expression &operator=(const Expression &rhs) noexcept;

    Expression &operator=(Expression &&rhs) noexcept;

    ~Expression() override = default;

    explicit Expression(const std::string &str);

    explicit Expression(const IMathObject &obj);

    std::string toString() const override;

    MathObjectPtr simplify() const override;

    std::string getClassName() const override;

    const MathObjectPtr &getInfo() const;

    const Expression::Vector &getChildren() const;

    MathObjectPtr tryCompress() const;

    static ExpressionPtr buildFunctionExpression(const IFunction &func, const ArgumentsVector &args);

  protected:
    Expression &add(const Expression &rhs) override;

    Expression &substract(const Expression &rhs) override;

    Expression &multiply(const Expression &rhs) override;

    Expression &divide(const Expression &rhs) override;

    Expression &negate() override;

  private:
    static Vector copy(const Vector &rhs);

    void tryCompressTree();

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

    std::string powToString() const;

    std::string negToString() const;

    std::string factorialOrPercentToString() const;

    std::string functionToString() const;

    MathObjectPtr simplifyNeg(std::unique_ptr<Expression> &expr) const;

    /*ExprPtr baseSimplify() const;

    ExprPtr parseEqualExpression(const std::string &expr) const;

    ExprPtr mainSimplify(const ExprPtr &expr) const;

    ExprPtr simplifyOperators(const ExprPtr &expr) const;

    ExprPtr simplifyFunctions(const ExprPtr &expr) const;

    ExprPtr simplifyConstant(const ExprPtr &expr) const;

    ExprPtr invertSubDiv(const ExprPtr &expr) const;

    ExprPtr rebuildAdd(const ExprPtr &expr) const;

    ExprPtr rebuildMul(const ExprPtr &expr) const;

    ExprPtr simplifyAddNum(const ExprPtr &expr) const;

    ExprPtr simplifyMulNum(const ExprPtr &expr) const;

    ExprPtr simplifyPowNum(const ExprPtr &expr) const;

    ExprPtr simplifyAddVar(const ExprPtr &expr) const;

    ExprPtr simplifyMulVar(const ExprPtr &expr) const;

    ExprPtr createAddExpr(const ExprPtr &currExpr, const ExprPtr &addExpr) const;

    ExprPtr openBracketsMulAdd(const ExprPtr &expr) const;

    ExprPtr openBracketsPowMul(const ExprPtr &expr) const;

    ExprPtr openBracketsPowAdd(const ExprPtr &expr) const;

    ExprVect getOpenTwoBrackets(const ExprVect &lhsBracket, const ExprVect &rhsBracket, const IMathObject &o) const;

    ExprPtr sort(const ExprPtr &expr) const;

    std::string funcArgsToString(const ExprVect &args) const;

    size_t ignoreBracketsLeftRight(const std::string &str, size_t position) const;

    size_t ignoreBracketsRightLeft(const std::string &str, size_t position) const;

    ExprPtr revertPow(const ExprPtr &expr) const;*/

    MathObjectPtr info;
    Vector children;

    const std::vector<std::string> classNames = {getClassName(), AddExpression().getClassName(),
                                                 MulExpression().getClassName()};
  };
}
