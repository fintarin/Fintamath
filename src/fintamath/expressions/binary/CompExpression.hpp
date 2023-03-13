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
  CompExpression(const IOperator &oper, const std::shared_ptr<IMathObject> &lhsChild,
                 const std::shared_ptr<IMathObject> &rhsChild);

  std::string solve() const;

  std::string solve(uint8_t precision) const;

  std::unique_ptr<IMathObject> simplify(bool isPrecise) const override;

protected:
  std::shared_ptr<IMathObject> postSimplify() const override;

  // std::vector<std::unique_ptr<IMathObject>> solvePowEquation(const Variable &x) const;

  // std::vector<std::unique_ptr<IMathObject>> solveQuadraticEquation(const std::unique_ptr<IMathObject> &v) const;

  // static bool sortFunc(const std::unique_ptr<IMathObject> &lhs, const std::unique_ptr<IMathObject> &rhs);

  // static std::vector<std::unique_ptr<IMathObject>> sortResult(std::vector<std::unique_ptr<IMathObject>> &result);

  // bool detectOneVariable(Variable &v) const;
};

}