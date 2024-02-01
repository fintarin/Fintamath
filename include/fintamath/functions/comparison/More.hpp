#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class More final : public IOperatorCRTP<Boolean, More, IComparable, IComparable> {
public:
  More() : IOperatorCRTP(Priority::Comparison, true) {
  }

  std::string toString() const override {
    return ">";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::More;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(More, moreExpr);

}
