#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/literals/Variable.hpp"
#include <cstdint>
#include <vector>

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IMathObject &oper, MathObjectPtr &&lhs, MathObjectPtr &&rhs);

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  MathObjectPtr simplify(bool isPrecise) const override;

  void compress() override;

protected:
  IMathObject *simplify() override;

  // std::vector<MathObjectPtr> solvePowEquation(const Variable &x) const;

  // std::vector<MathObjectPtr> solveQuadraticEquation(const MathObjectPtr &v) const;

  // static bool sortFunc(const MathObjectPtr &lhs, const MathObjectPtr &rhs);

  // static std::vector<MathObjectPtr> sortResult(std::vector<MathObjectPtr> &result);

  // bool detectOneVariable(Variable &v) const;
};

}