#pragma once
#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/helpers/Converter.hpp"
#include "fintamath/literals/Variable.hpp"
#include <cstdint>

namespace fintamath {
  class EqvExpression : public IExpressionCRTP<EqvExpression> {
  public:
    EqvExpression() = default;

    explicit EqvExpression(const TokenVector &tokens);

    EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs);

    EqvExpression(const EqvExpression &rhs) noexcept;

    EqvExpression(EqvExpression &&rhs) noexcept;

    EqvExpression &operator=(const EqvExpression &rhs) noexcept;

    EqvExpression &operator=(EqvExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~EqvExpression() override = default;

    MathObjectPtr simplify() const override;

    std::string solve() const;

    std::string solve(uint8_t precision) const;

    uint16_t getInfoPriority() override;

    void setPrecision(uint8_t precision) override;

    MathObjectPtr simplify(bool isPrecise) const override;


  private:
    MathObjectPtr leftExpr;
    MathObjectPtr rightExpr;
    MathObjectPtr oper;

    void parse(const TokenVector &tokens);

    std::vector<MathObjectPtr> solvePowEquation(const Variable& x) const;
    std::vector<MathObjectPtr> solveQuadraticEquation(const MathObjectPtr& v) const;

    bool detectOneVariable(Variable &v) const;
  };
}