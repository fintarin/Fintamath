#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Expression : public MathObjectImpl<Expression> {
  public:
    Expression() = default;

    Expression(const Expression &rhs) noexcept;

    Expression(Expression &&rhs) noexcept;

    Expression &operator=(const Expression &rhs) noexcept;

    Expression &operator=(Expression &&rhs) noexcept;

    ~Expression() override = default;

    explicit Expression(const std::string &str);

    explicit Expression(const MathObject &obj);

    std::string toString() const override;

    MathObjectPtr simplify() const override;

  protected:
    bool equals(const Expression &rhs) const override;

  private:
    using ExprPtr = std::shared_ptr<Expression>;
    using ExprVect = std::vector<ExprPtr>;

    ExprPtr baseSimplify() const;

    static ExprPtr parseEqualExpression(const std::string &expr);

    static ExprPtr parseExpression(const std::string &exprStr);

    static ExprPtr parseDivMulTerm(const std::string &term);

    static ExprPtr parseNegPowFactorPercentTerm(const std::string &term);

    static ExprPtr parseFiniteTerm(const std::string &term);

    static ExprPtr parseConstant(const std::string &term);

    static ExprPtr parseFunction(const std::string &term);

    static ExprVect getArgs(const std::string &args);

    static ExprPtr mainSimplify(const ExprPtr &expr);

    static ExprPtr simplifyOperators(const ExprPtr &expr);

    static ExprPtr simplifyFunctions(const ExprPtr &expr);

    static ExprPtr simplifyConstant(const ExprPtr &expr);

    static ExprPtr invertSubDiv(const ExprPtr &expr);

    static ExprPtr simplifyNeg(const ExprPtr &expr);

    static ExprPtr rebuildAdd(const ExprPtr &expr);

    static ExprPtr rebuildMul(const ExprPtr &expr);

    static ExprPtr simplifyAddNum(const ExprPtr &expr);

    static ExprPtr simplifyMulNum(const ExprPtr &expr);

    static ExprPtr simplifyPowNum(const ExprPtr &expr);

    static ExprPtr simplifyAddVar(const ExprPtr &expr);

    static ExprPtr simplifyMulVar(const ExprPtr &expr);

    static ExprPtr createAddExpr(const ExprPtr &currNode, const ExprPtr &addNode);

    static ExprPtr openBracketsMulAdd(const ExprPtr &expr);

    static ExprPtr openBracketsPowMul(const ExprPtr &expr);

    static ExprPtr openBracketsPowAdd(const ExprPtr &expr);

    static ExprVect getOpenTwoBrackets(const ExprVect &lhsBracket, const ExprVect &rhsBracket, const MathObject &o);

    static ExprPtr sort(const ExprPtr &expr);

    static std::string funcArgsToString(const ExprVect &args);

    static ExprPtr revertPow(const ExprPtr &expr);

    std::shared_ptr<MathObject> info;
    ExprVect children;
  };
}
