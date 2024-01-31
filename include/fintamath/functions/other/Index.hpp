#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Index final : public IOperatorCRTP<Variable, Index, Variable, Integer> {
public:
  Index() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "_";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Index;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Index, indexExpr);

}
