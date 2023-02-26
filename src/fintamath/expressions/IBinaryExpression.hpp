#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IBinaryExpression : virtual public IExpression {
public:
  IBinaryExpression() = default;

  IBinaryExpression(const IBinaryExpression &rhs);

  IBinaryExpression(IBinaryExpression &&rhs) noexcept = default;

  IBinaryExpression &operator=(const IBinaryExpression &rhs);

  IBinaryExpression &operator=(IBinaryExpression &&rhs) noexcept = default;

  explicit IBinaryExpression(const IMathObject &lhs, const IMathObject &rhs);

  explicit IBinaryExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  void setPrecision(uint8_t precision) final;

  std::string toString() const final;

  // TODO: remove this
  void validate() const final;

protected:
  MathObjectPtr lhsInfo;
  MathObjectPtr rhsInfo;
};

template <typename Derived>
class IBinaryExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IBinaryExpression {};
}