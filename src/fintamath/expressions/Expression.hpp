#pragma once

#include <memory>
#include <vector>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {
  class Expression : public IExpressionCRTP<Expression> {
  public:
    Expression() = default;

    Expression(const Expression &rhs) noexcept;

    Expression(Expression &&rhs) noexcept;

    Expression &operator=(const Expression &rhs) noexcept;

    Expression &operator=(Expression &&rhs) noexcept;

    ~Expression() override = default;

    explicit Expression(const std::string &str);

    explicit Expression(const IMathObject &obj);

    std::string toString() const override;

    MathObjectPtr simplify() const override;

    std::string getClassName() const override;

  private:
    using ExprPtr = std::shared_ptr<Expression>; // TODO replace with ExpressionPtr
    using ExprVect = std::vector<ExprPtr>;

    ExprPtr baseSimplify() const;

    ExprPtr parseEqualExpression(const std::string &expr) const;

    ExprPtr parseExpression(const std::string &exprStr) const;

    ExprPtr parseDivMulTerm(const std::string &term) const;

    ExprPtr parseNegPowFactorPercentTerm(const std::string &term) const;

    ExprPtr parseFiniteTerm(const std::string &term) const;

    ExprPtr parseFunction(const std::string &term) const;

    ExprVect getArgs(const std::string &args) const;

    ExprPtr mainSimplify(const ExprPtr &expr) const;

    ExprPtr simplifyOperators(const ExprPtr &expr) const;

    ExprPtr simplifyFunctions(const ExprPtr &expr) const;

    ExprPtr simplifyConstant(const ExprPtr &expr) const;

    ExprPtr invertSubDiv(const ExprPtr &expr) const;

    ExprPtr simplifyNeg(const ExprPtr &expr) const;

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

    ExprPtr revertPow(const ExprPtr &expr) const;

    std::shared_ptr<IMathObject> info;
    ExprVect children;
  };
}
