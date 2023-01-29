#pragma once

#include <cstdint>
#include <vector>

#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class EqvExpression : public IExpressionCRTP<EqvExpression> {
public:
  EqvExpression() = default;

  EqvExpression(const IMathObject &oper, const IMathObject &lhs, const IMathObject &rhs);

  EqvExpression(const EqvExpression &rhs);

  EqvExpression(EqvExpression &&rhs) noexcept;

  EqvExpression &operator=(const EqvExpression &rhs);

  EqvExpression &operator=(EqvExpression &&rhs) noexcept;

  std::string toString() const override;

  ~EqvExpression() override = default;

  MathObjectPtr simplify() const override;

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify(bool isPrecise) const override;

private:
  MathObjectPtr leftExpr;

  MathObjectPtr rightExpr;

  OperatorPtr oper;

  std::vector<MathObjectPtr> solvePowEquation(const Variable &x) const;

  std::vector<MathObjectPtr> solveQuadraticEquation(const MathObjectPtr &v) const;

  static bool sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);

  static std::vector<MathObjectPtr> sortResult(std::vector<MathObjectPtr> &result);

  bool detectOneVariable(Variable &v) const;
};

}