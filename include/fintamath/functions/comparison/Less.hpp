#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Less final : public IOperatorCRTP<Boolean, Less, IComparable, IComparable> {
public:
  Less() : IOperatorCRTP(IOperator::Priority::Comparison, true) {
  }

  std::string toString() const override {
    return "<";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Less;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Less, lessExpr);

}
