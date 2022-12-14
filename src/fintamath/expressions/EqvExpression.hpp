#pragma once
#include "fintamath/core/Defines.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/helpers/Converter.hpp"
#include <cstdint>

namespace fintamath {
  class EqvExpression : public IExpressionCRTP<EqvExpression> {
  public:
    EqvExpression() = default;

    explicit EqvExpression(const TokenVector& tokens);

    EqvExpression(const EqvExpression &rhs) noexcept;

    EqvExpression(EqvExpression &&rhs) noexcept;

    EqvExpression &operator=(const EqvExpression &rhs) noexcept;

    EqvExpression &operator=(EqvExpression &&rhs) noexcept;

    std::string toString() const override;

    std::string getClassName() const override;

    ~EqvExpression() override = default;

    MathObjectPtr simplify() const override;

    uint16_t getInfoPriority() override;

  private:

    MathObjectPtr leftExpr;
    MathObjectPtr rightExpr;
    MathObjectPtr oper;

    void parse(const TokenVector& tokens);
  };
}