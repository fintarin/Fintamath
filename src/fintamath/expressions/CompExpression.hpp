#pragma once

#include <cstdint>
#include <vector>

#include "fintamath/expressions/polynomial/MulExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class CompExpression : public IExpressionCRTP<CompExpression> {
public:
  CompExpression() = default;

  CompExpression(const IMathObject &oper, MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  CompExpression(const CompExpression &rhs);

  CompExpression(CompExpression &&rhs) noexcept;

  CompExpression &operator=(const CompExpression &rhs);

  CompExpression &operator=(CompExpression &&rhs) noexcept;

  std::string toString() const override;

  ~CompExpression() override = default;

  MathObjectPtr toMinimalObject() const override;

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  const IFunction *getFunction() const override;

  void setPrecision(uint8_t precision) override;

  MathObjectPtr simplify(bool isPrecise) const override;

  void compress() override;

  // TODO: remove this
  void validate() const override;

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