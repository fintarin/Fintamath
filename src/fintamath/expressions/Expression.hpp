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

  protected:
    bool equals(const Expression &rhs) const override;

  private:
    std::shared_ptr<MathObject> info;
    std::vector<std::shared_ptr<Expression>> children;

    static std::shared_ptr<Expression> parseExpression(const std::string& expr);
    static std::shared_ptr<Expression> parseDivMulTerm(const std::string& term);
    static std::shared_ptr<Expression> parseNegPowFactorTerm(const std::string& term);
    static std::shared_ptr<Expression> parseFiniteTerm(const std::string& term);
    static std::shared_ptr<Expression> parseFunction(const std::string& term);
  };
}