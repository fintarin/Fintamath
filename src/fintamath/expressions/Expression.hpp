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

    Expression simplify();

  protected:
    bool equals(const Expression &rhs) const override;

  private:
    using ExprPtr = std::shared_ptr<Expression>;
    using ExprVect = std::vector<ExprPtr>;

    static ExprPtr parseExpression(const std::string &expr);
    static ExprPtr parseDivMulTerm(const std::string &term);
    static ExprPtr parseNegPowFactorTerm(const std::string &term);
    static ExprPtr parseFiniteTerm(const std::string &term);
    static ExprPtr parseFunction(const std::string &term);
    static ExprVect getArgs(const std::string &args);

    static ExprPtr mainSimplify(const ExprPtr &expr);
    static ExprPtr simplifyNumbers(const ExprPtr &expr);
    static ExprPtr invertSubDiv(const ExprPtr &expr);
    static ExprPtr simplifyNeg(const ExprPtr &expr);
    static ExprPtr rebuildAdd(const ExprPtr &expr);
    static ExprPtr rebuildMul(const ExprPtr &expr);
    static ExprPtr simplifyAddNum(const ExprPtr &expr);
    static ExprPtr simplifyMulNum(const ExprPtr &expr);
    static ExprPtr simplifyAddVar(const ExprPtr &expr);
    static ExprPtr openBracketsMulAdd(const ExprPtr &expr);
    static ExprPtr openBracketsPowMul(const ExprPtr &expr);

    static ExprVect getOpenTwoBrackets(const ExprVect &lhsBracket, const ExprVect &rhsBracket,
                                               const MathObject &o);
    static ExprPtr sort(const ExprPtr &expr);

    std::shared_ptr<MathObject> info;
    ExprVect children;
  };
}
