#pragma once

#include <cstdint>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IndexExpression : public IExpressionCRTP<IndexExpression> {
public:
  IndexExpression() = default;

  IndexExpression(const IndexExpression &rhs);

  IndexExpression(IndexExpression &&rhs) = default;

  IndexExpression &operator=(const IndexExpression &rhs);

  IndexExpression &operator=(IndexExpression &&rhs) = default;

  explicit IndexExpression(const IMathObject &lhs, const IMathObject &rhs);

  explicit IndexExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  std::string toString() const override;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr toMinimalObject() const override;

  MathObjectPtr simplify(bool isPrecise) const override;

  // TODO: remove this
  void validate() const override;

private:
  MathObjectPtr lhsInfo;
  MathObjectPtr rhsInfo;
};

}